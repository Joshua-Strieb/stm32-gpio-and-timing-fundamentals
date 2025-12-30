## Non-Blocking Delay with Systick
The non-blocking delay will be achieved by using system tick (systick). Systick operates as 24-bit countdown timer that is internal to the ARM Cortex M-Core. If using systick to operate two seperate LEDs on different GPIO pins we shouldn't see the effect that HAL_DELAY caused previously and both LEDs should operate simultaneously. 

## Pinout
PA5 will be connected to an LED with it being designated as a GPIO Output within STM32CubeMX. Later on, PA6 will be disgnated the same with an additional LED.

## Program
The following variables will be made:

```c
uint32_t last1 = 0, last2 = 0; //last2 will be used later on
const uint32_t period = 500; //This will be in milliseconds
```
In infinite while loop, the following code will be added:

```c
uint32_t curent = HAL_GetTick();

if (current - last1 >= 500) //compares the difference of current tick and last time the loop was performed. If its greater than 500ms it continues. This ensures that the loop is being performed every 500ms and thus the LED is enabled every 500ms
	  {
	    last1 = current;
	    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	  }
```
HAL_GetTick() retrieves the current systme time from boot.

## Results

(video)

## Systick Expanded with Two LEDs
An additinnal LED and and additional "if" statement is used in addition to what was previously discussed. The updated while loop will look like:

```c
	  uint32_t curent = HAL_GetTick();

	  if (current - last1 >= 500) 
	  {
	    last1 = current;
	    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	  }

	  /*
	  if (current - last2 >= 500)
	  {
	    last2 = current;
	    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
	  }
```
## Results
The video below shows the result of the dual LEDs. They operate simultaneously, which is a stark difference compared to the blocking delay.
xx
(video)
