## Blocking Delay HAL
### Blocking Delay Timing Table
| Time (ms) | CPU             | LED1 | LED2 |
|-----------|-----------------------|------|------|
| 0         | Toggle LED1           | ON   | OFF  |
| 0–500     | HAL_Delay(500)        | ON   | OFF  |
| 500       | Toggle LED2           | ON   | ON   |
| 500–1000  | HAL_Delay(500)        | ON   | ON   |
| 1000      | Toggle LED1           | OFF  | ON   |
| 1000-1500 | HAL_DELAY(500)        | OFF  | ON   |
| 1500      | Toggle LED2           | OFF  | OFF  |
| 1500-2000 | HAL_DELAY(500)        | OFF  | OFF  |

### Blocking Delay Timing Diagram HAL
Below is a visual representation of the LEDs active and in active states relative to each other. With annotations of the code states in increments.

<img width="1100" height="380" alt="timing_diagram_HAL" src="https://github.com/user-attachments/assets/c2c5c575-5e62-4c39-b68a-7641fd62efbc" />

