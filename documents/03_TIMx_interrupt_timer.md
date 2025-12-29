## TIM3 Interrupt Timer
xxxx

## Pinout
PA5 will be designated as GPIO_Output.

## Calculations
The formula to calculate timer update event frequency:
```math
f_u = f_t/[(PSC+1)(ARR+1)]
```
f_u is the timer update event frequency
f_t is the timer input clock (APB).
PSC is prescaler register.
ARR is auto-reload register.

In our case:
```math
f_t = 100MHz
```
We are looking to have an LED interrupt every 500ms similar to the prior examples. PWM frequency will be set to 1kHz and the schedular tick, how often it updates, will be 1ms.

So, LED toggle = 2Hz and 1ms tick = 1000Hz

The counter resolution will be maintained at 10kHz as this will provide a stable frequency for LED blinking and prevent any flicker. 
Counter clock (f_c)= 10kHz

To calculate the PSC:
```math
PSC = (f_t/f_c)-1 = (100MHz/10kHz)-1 = 10kHz - 1 = 9999
```

To calculate ARR:
```math
ARR = (f_c*t_p)-1 = (10000*0.5)-1 = 4999
```

## Program
Within STM32CubeMX TIM3 must be enabled and the previously calculated PSC and ARR will be set.

htim3 will be initialized in peripherals.
```c
  HAL_TIM_Base_Start_IT(&htim3);
```

Separate of main() the following code will be added:
```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  }
}
```

```c
void HAL_TIM_PeriodElapsedCallback()
```
This calls the timer when the timer update event occurs.
```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
```
TIM_HandleTypeDef stores the configuration, state, and register base address for the timer. *htim is the pointer that says which timer specifically activated the event.

## Results


