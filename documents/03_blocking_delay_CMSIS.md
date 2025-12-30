# Bare Metal Blocking Delay Using CMSIS
The purpose of this project is to become familiar with purely using CMSIS in place of HAL/STM32CubeIDE/MX. A project template was created and can be seen (here). 
## Pinout
Pins 5 and 6 will be used, they will be initialized within gpio.c and then called into the main function when needed. 
## Program
SysTick_Handler() will be called to increment g_ms which will count up by 1ms. 
```code
void SysTick_Handler(void) 
{
    g_ms++; 
}
```
The delay will be made by creating the delay() function.
The variable ms will be created as an argument. The variable start will be made to equal g_ms. The while loop will then subtract the current g_ms value to start. While it is less than ms (which will be entered later) it will delay the processor.
```code
void delay(volatile uint32_t ms)
{
    uint32_t start = g_ms;

    while ((g_ms - start) < ms)
    {
        
    }
}
```
Finally, or main() will enable the SysTick, the GPIOA AHB1 clock, and the desired output pin. During the super loop, the pin is toggled which is then followed by a delay of 500ms.
```code
int main(void)
{
    clock_init();

    gpio_enable_port_a(); //GPIOA clock on AHB1 from gpio.c
    gpio_set_output_a(5); //sets pin 5 as an output from gpio.c

    while (1)
    {
        gpio_toggle_a(5);
        delay(500);
    }
}
```
The gpio_enable_port_a() and     gpio_set_output_a() functions live in gpio.c which are then called in main() to simplify and produce neat code. 
## Results
As seen below with 500 entered in the delay function, the LED toggles every 500ms. 

https://github.com/user-attachments/assets/41dbd318-36b7-4d57-a222-cfa4c9671267

## Expanded with Two LEDs
A second LED will then be added on GPIO pin 6.
## Results
An identical effect can be seen compared to the HAL example where the toggle becomes longer when an additional delay is introduced showing the processor delay.

https://github.com/user-attachments/assets/3796bb2c-e423-43b2-8d4d-02fd5a052518
