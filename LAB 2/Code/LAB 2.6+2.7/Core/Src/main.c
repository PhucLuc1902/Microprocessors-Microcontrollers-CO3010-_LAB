#include "main.h"
#include <stdint.h>

TIM_HandleTypeDef htim2;

int led_buffer[4];
int hour = 15, minute = 8, second = 50;

volatile int timerLED = 0;
volatile int timer7SEG = 0;

volatile uint8_t LED_flag = 0;
volatile uint8_t SEVENSEG_flag = 0;

const int TIMER_CYCLE = 10;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer(void);

void set_timerLED(int duration_ms);
void set_timer7SEG(int duration_ms);
void timer_run(void);

void set_timerLED(int duration_ms){
    timerLED = duration_ms / TIMER_CYCLE;
    LED_flag = 0;
}
void set_timer7SEG(int duration_ms){
    timer7SEG = duration_ms / TIMER_CYCLE;
    SEVENSEG_flag = 0;
}
void timer_run(void){
    if(timerLED > 0){
        timerLED--;
        if(timerLED == 0) LED_flag = 1;
    }
    if(timer7SEG > 0){
        timer7SEG--;
        if(timer7SEG == 0) SEVENSEG_flag = 1;
    }
}

void updateClockBuffer(void){
    led_buffer[0] = hour / 10;
    led_buffer[1] = hour % 10;
    led_buffer[2] = minute / 10;
    led_buffer[3] = minute % 10;
}



int main(void)
{
void display7SEG(int num)
{
    if(num < 0 || num > 9) return;

    if(num == 0){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);
        return;
    }

    if(num == 1){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);
        return;
    }
    else if (num == 2){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
    else if (num == 3){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
    else if (num == 4){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
    else if (num == 5){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
    else if (num == 6){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
    else if (num == 7){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);
        return;
    }
    else if (num == 8){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
    else if (num == 9){
        HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
        return;
    }
}
void update7SEG(int index){
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);

    switch(index){
        case 0:
            display7SEG(led_buffer[0]);
            HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            display7SEG(led_buffer[1]);
            HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            display7SEG(led_buffer[2]);
            HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            display7SEG(led_buffer[3]);
            HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM2_Init();

    HAL_TIM_Base_Start_IT(&htim2);

    updateClockBuffer();
    set_timerLED(1000);
    set_timer7SEG(100);

    int index_led = 0;
    const int MAX_LED = 4;

    while(1){
        if(LED_flag){
            LED_flag = 0;
            second++;
            if(second >= 60){ second = 0; minute++; }
            if(minute >= 60){ minute = 0; hour++; }
            if(hour >= 24){ hour = 0; }

            HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            updateClockBuffer();
            set_timerLED(1000);
        }

        if(SEVENSEG_flag){
            SEVENSEG_flag = 0;
            update7SEG(index_led);
            index_led++;
            if(index_led >= MAX_LED) index_led = 0;
            set_timer7SEG(100);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM2){
        timer_run();
    }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) Error_Handler();
}

static void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK) Error_Handler();
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) Error_Handler();
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) Error_Handler();
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, DOT_Pin|LED_RED_Pin|EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = DOT_Pin|LED_RED_Pin|EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Error_Handler(void){
    __disable_irq();
    while(1){}
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif
