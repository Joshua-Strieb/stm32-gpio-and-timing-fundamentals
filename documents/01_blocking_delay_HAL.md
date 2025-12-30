## Blocking Delay
A blocking delay puts the CPU in a hold state. This interrupts all operations making it difficult for multitasking but remains simple to use for individual projects.

## Pinout
PA5 will be connected to an LED with it being designated as a GPIO Output within STM32CubeMX. Later on, PA6 will be disgnated the same with an additional LED.

## Program
HAL_GPIO_TogglePin() and HAL_Delay() functions will be used inside of the infinite while loop in order to blink the LED. Both functions are already defined when the STM32CubeMX generates the code. 

HAL_GPIO_TogglePin() enables the desired pin that we want to use, which will look like: HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5) with pin 5 being PA5

HAL_Delay() relies on SysTick timebase which creates a blocking time delay in milliseconds. If called in its default state of HAL_Delay() it will produce a delay of 1ms. In our case it will look like HAL_Delay(500) to produce a delay of 500ms. 

```c
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(500);
  }
```

## Results

https://github.com/user-attachments/assets/194f9ef2-5770-415d-864b-b5842985b3ec

## HAL_Delay Expanded with Two LEDs
A second LED will be added to provide a visual example of HAL_DELAY. It will be connected to PA6 with jumper wires on an external breadboard. The while loop will now appear as: 
```c
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(500);

    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    HAL_Delay(500);
  }
```
## Results
A timing diagram of the two LEDs can be seen [here](timing_diagrams.md) in addition to the video below. This shows that even though it seems that both LEDs should operated at the same time, the HAL_Delay prevents this. Additionally, they operate incorrectly, as the desired time enabled is 500ms. But due to the delay each LED stays active for 1000ms.

https://github.com/user-attachments/assets/659181d2-4269-4a2d-ab7c-a2501c445348
