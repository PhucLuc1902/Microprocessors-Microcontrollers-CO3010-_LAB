#include "scheduler.h"
#include "main.h"
#include <string.h>

/* Delta-queue scheduler: O(1) ISR, ready FIFO (producer: ISR, consumer: main) */

typedef struct TaskNode {
    TaskFunc  pTask;
    uint32_t  period;    // in ticks (0 => one-shot)
    uint32_t  delay;     // relative delay to previous node
    uint32_t  id;
    int16_t   next, prev;
    uint8_t   in_use;
    uint8_t   cancelled;
} TaskNode;

static TaskNode g_tasks[SCH_MAX_TASKS];
static int16_t  g_wait_head = -1;
static uint32_t g_next_id   = 1;
static volatile uint32_t g_tick_count = 0;

/* ready FIFO */
#define READY_Q_SIZE (SCH_MAX_TASKS + 2)
static volatile int16_t rq_buf[READY_Q_SIZE];
static volatile uint8_t rq_head = 0, rq_tail = 0;

static inline uint8_t rq_next(uint8_t i){ return (uint8_t)((i + 1u) % READY_Q_SIZE); }
static inline uint8_t rq_empty(void){ return rq_head == rq_tail; }
static void rq_push_from_isr(int16_t idx){
    uint8_t n = rq_next(rq_head);
    if (n == rq_tail) return; // overflow: drop instance
    rq_buf[rq_head] = idx; rq_head = n;
}
static int16_t rq_pop_from_main(void){
    if (rq_empty()) return -1;
    int16_t idx = rq_buf[rq_tail]; rq_tail = rq_next(rq_tail); return idx;
}

/* pool */
static int16_t alloc_slot(void){
    for (int16_t i=0;i<SCH_MAX_TASKS;i++){
        if (!g_tasks[i].in_use){
            memset(&g_tasks[i],0,sizeof(TaskNode));
            g_tasks[i].in_use=1; g_tasks[i].next=g_tasks[i].prev=-1;
            g_tasks[i].id=g_next_id++; if(!g_next_id) g_next_id=1;
            return i;
        }
    }
    return -1;
}
static int16_t find_index_by_id(uint32_t id){
    for (int16_t i=0;i<SCH_MAX_TASKS;i++)
        if (g_tasks[i].in_use && g_tasks[i].id==id) return i;
    return -1;
}

/* delta-list ops (IRQs disabled when called) */
static void insert_with_delay(int16_t idx, uint32_t delay){
    TaskNode *n=&g_tasks[idx]; n->delay=delay;
    if (g_wait_head<0){ g_wait_head=idx; n->prev=n->next=-1; return; }
    int16_t cur=g_wait_head, prev=-1; uint32_t remain=delay;
    while(cur>=0 && remain>g_tasks[cur].delay){
        remain-=g_tasks[cur].delay; prev=cur; cur=g_tasks[cur].next;
    }
    n->delay=remain; n->prev=prev; n->next=cur;
    if(cur>=0){
        g_tasks[cur].prev=idx;
        g_tasks[cur].delay = (g_tasks[cur].delay>=remain)? (g_tasks[cur].delay-remain):0;
    }
    if(prev>=0) g_tasks[prev].next=idx; else g_wait_head=idx;
}
static void remove_from_wait_list(int16_t idx){
    TaskNode *n=&g_tasks[idx]; int16_t p=n->prev, q=n->next;
    if(q>=0){ g_tasks[q].delay+=n->delay; g_tasks[q].prev=p; }
    if(p>=0) g_tasks[p].next=q; else g_wait_head=q;
    n->prev=n->next=-1;
}

/* API */
void SCH_Init(void){
    __disable_irq();
    memset((void*)g_tasks,0,sizeof(g_tasks));
    g_wait_head=-1; g_next_id=1; rq_head=rq_tail=0; g_tick_count=0;
    __enable_irq();
}
uint32_t SCH_Add_Task(TaskFunc fn, uint32_t delay, uint32_t period){
    if(!fn) return 0;
    int16_t idx=alloc_slot(); if(idx<0) return 0;
    g_tasks[idx].pTask=fn; g_tasks[idx].period=period; g_tasks[idx].cancelled=0;
    __disable_irq(); insert_with_delay(idx, delay); __enable_irq();
    return g_tasks[idx].id;
}
uint8_t SCH_Delete_Task(uint32_t id){
    if(!id) return 0; uint8_t ok=0; __disable_irq();
    int16_t idx=find_index_by_id(id);
    if(idx>=0 && g_tasks[idx].in_use){
        if(idx==g_wait_head || g_tasks[idx].prev!=-1 || g_tasks[idx].next!=-1){
            remove_from_wait_list(idx); g_tasks[idx].in_use=0; ok=1;
        } else { g_tasks[idx].cancelled=1; ok=1; }
    }
    __enable_irq(); return ok;
}
void SCH_Update(void){
    g_tick_count++;
    if(g_wait_head<0) return;
    if(g_tasks[g_wait_head].delay>0) g_tasks[g_wait_head].delay--;
    while(g_wait_head>=0 && g_tasks[g_wait_head].delay==0){
        int16_t due=g_wait_head; g_wait_head=g_tasks[due].next;
        if(g_wait_head>=0) g_tasks[g_wait_head].prev=-1;
        g_tasks[due].next=g_tasks[due].prev=-1;
        rq_push_from_isr(due);
    }
}
void SCH_Dispatch_Tasks(void){
    for(;;){
        int16_t idx=rq_pop_from_main(); if(idx<0) break;
        TaskNode *n=&g_tasks[idx];
        if(!n->in_use || n->cancelled || !n->pTask){ n->in_use=0; continue; }
        n->pTask();
        if(n->period>0 && n->in_use && !n->cancelled){
            __disable_irq(); insert_with_delay(idx, n->period); __enable_irq();
        } else { n->in_use=0; }
    }
    // optional: __WFI();
}
uint32_t SCH_GetTimeMs(void){
    uint32_t t; __disable_irq(); t=g_tick_count; __enable_irq();
    return t*TICK_MS;
}
