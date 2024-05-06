
#pragma once

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE


//F401
/*


#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE

#define STM32_PLLM_VALUE    (STM32_HSECLK/1000000)
#define STM32_PLLN_VALUE    192
#define STM32_PLLP_VALUE    4
#define STM32_PLLQ_VALUE    4

*/