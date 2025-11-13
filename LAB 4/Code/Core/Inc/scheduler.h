#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

#ifndef SCH_MAX_TASKS
#define SCH_MAX_TASKS   16
#endif

#define TICK_MS         10u
#define MS_TO_TICKS(ms) ((uint32_t)((ms) / TICK_MS))
#define SEC_TO_TICKS(s) ((uint32_t)(((s) * 1000u) / TICK_MS))

typedef void (*TaskFunc)(void);

/* Required by the lab */
void     SCH_Init(void);
uint32_t SCH_Add_Task(TaskFunc pFunction, uint32_t DELAY_ticks, uint32_t PERIOD_ticks);
uint8_t  SCH_Delete_Task(uint32_t task_id);
void     SCH_Update(void);          // call from TIM ISR every 10 ms
void     SCH_Dispatch_Tasks(void);  // call from while(1)
uint32_t SCH_GetTimeMs(void);       // get_time()

#endif
