## Blocking Delay
A blocking delay puts the CPU in a hold state. This interrupts all operations making it difficult for multitasking but remains simple to use for individual projects.

## Pinout
PA5 will be designated as GPIO Output within STM32CubeMX.

## Program
HAL_GPIO_TogglePin() and HAL_Delay() functions will be used inside of a while loop in order to blink the LED. Both functions are already defined when the STM32CubeMX generates the code. 

HAL_GPIO_TogglePin() enables the desired pin that we want to use, which will look like: HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5) with pin 5 being PA5

HAL_Delay() creates a blocking time delay in milliseconds. If called in its default state of HAL_Delay() it will produce a delay of 1ms. In our case it will look like HAL_Delay(500).
