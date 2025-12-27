## Blocking Delay
### Blocking Delay Timing Table
| Time (ms) | CPU             | LED1 | LED2 |
|-----------|-----------------------|------|------|
| 0         | Toggle LED1           | ON   | OFF  |
| 0–500     | HAL_Delay(500)        | ON   | OFF  |
| 500       | Toggle LED2           | ON   | ON   |
| 500–1000  | HAL_Delay(500)        | ON   | ON   |
| 1000      | Toggle LED1           | OFF  | ON   |
### Blocking Delay Timing Diagram
(fill)
