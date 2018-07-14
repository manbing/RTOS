#ifndef _DRIVER_SERIAL_STM32_USART_H
#define _DRIVER_SERIAL_STM32_USART_H

#include "platform.h"

struct stm32_uart_port {
        GPIO_TypeDef *gpio_tx;
        GPIO_TypeDef *gpio_rx;
};

#endif /*!_DRIVER_SERIAL_STM32_USART_H */
