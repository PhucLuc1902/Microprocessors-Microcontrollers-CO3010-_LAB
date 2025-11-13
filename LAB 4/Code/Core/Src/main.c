#include "main.h"
#include <stdio.h>
#include "scheduler.h"

/* GPIO pin labels (if Cube didn't generate them) */
#ifndef LED1_Pin
#define LED1_Pin        GPIO_PIN_5
#define LED1_GPIO_Port  GPIOA
#endif
#ifndef BTN1_Pin
#define BTN1_Pin        GPIO_PIN_0
#define BTN1_GPIO_Port  GPIOA
#endif

UART_HandleTypeDef huart1;
TIM_HandleTypeDef  htim2;

/* ---- Forward declarations ---- */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);

/* Task prototypes */
static void Task_Print_10ms(void);
static void Task_ButtonScan_10ms(void);
static void Task_500ms(void);
static void Task_1000ms(void);
static void Task_1500ms(void);
static void Task_2000ms(void);
static void Task_2500ms(void);
static void OneShot_A(void);
static void OneShot_B(void);

/* -------------------------------------------------------------------------- */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();

  SCH_Init();
  HAL_TIM_Base_Start_IT(&htim2);

  /* Lab demo tasks --------------------------------------------------------- */
  SCH_Add_Task(Task_Print_10ms,      0, MS_TO_TICKS(10));
  SCH_Add_Task(Task_ButtonScan_10ms, 0, MS_TO_TICKS(10));
  SCH_Add_Task(Task_500ms,  0, MS_TO_TICKS(500));
  SCH_Add_Task(Task_1000ms, 0, MS_TO_TICKS(1000));
  SCH_Add_Task(Task_1500ms, 0, MS_TO_TICKS(1500));
  SCH_Add_Task(Task_2000ms, 0, MS_TO_TICKS(2000));
  SCH_Add_Task(Task_2500ms, 0, MS_TO_TICKS(2500));
  SCH_Add_Task(OneShot_A, MS_TO_TICKS(300), 0);
  SCH_Add_Task(OneShot_B, MS_TO_TICKS(1200), 0);

  printf("\r\n=== Scheduler demo (F103C6) ===\r\n");

  while (1) {
    SCH_Dispatch_Tasks();
  }
}

/* -------------------------------------------------------------------------- */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
    SCH_Update();   // called every 10 ms
  }
}

/* --------------------------- Task implementations ------------------------- */
static void Task_Print_10ms(void) {
  printf("[10ms]  t=%lu ms\r\n", (unsigned long)SCH_GetTimeMs());
}

static void Task_ButtonScan_10ms(void)
{
  static GPIO_PinState last_raw = GPIO_PIN_SET;
  static GPIO_PinState stable   = GPIO_PIN_SET;
  static uint8_t cnt = 0;
  GPIO_PinState raw = HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);

  if (raw != last_raw) { last_raw = raw; cnt = 0; }
  else if (cnt < 3) { cnt++; }
  else if (raw != stable) {
    stable = raw;
    if (stable == GPIO_PIN_RESET) {
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      printf("[BTN] pressed; LED toggled; t=%lu\r\n", (unsigned long)SCH_GetTimeMs());
    } else {
      printf("[BTN] released; t=%lu\r\n", (unsigned long)SCH_GetTimeMs());
    }
  }
}

static void Task_500ms(void)  { HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin); printf("[500ms]  t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }
static void Task_1000ms(void) { printf("[1000ms] t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }
static void Task_1500ms(void) { printf("[1500ms] t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }
static void Task_2000ms(void) { printf("[2000ms] t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }
static void Task_2500ms(void) { printf("[2500ms] t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }

static void OneShot_A(void) { printf("[OneShot A] t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }
static void OneShot_B(void) { printf("[OneShot B] t=%lu\r\n", (unsigned long)SCH_GetTimeMs()); }

/* ----------------------- Peripheral initialization ------------------------ */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;   // 8/2*16 = 64 MHz
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|
                                RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) Error_Handler();
}


static void MX_TIM2_Init(void)
{
  /* 72 MHz / (7199+1) = 10 kHz → ARR=99 ⇒ 10 ms */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler         = 7199;
  htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim2.Init.Period            = 99;
  htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&htim2);

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

static void MX_USART1_UART_Init(void)
{
  huart1.Instance          = USART1;
  huart1.Init.BaudRate     = 115200;
  huart1.Init.WordLength   = UART_WORDLENGTH_8B;
  huart1.Init.StopBits     = UART_STOPBITS_1;
  huart1.Init.Parity       = UART_PARITY_NONE;
  huart1.Init.Mode         = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* LED */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin   = LED1_Pin;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

  /* Button */
  GPIO_InitStruct.Pin  = BTN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN1_GPIO_Port, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    HAL_Delay(200);
  }
}
