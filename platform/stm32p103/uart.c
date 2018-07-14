void uart_init(void)
{
        struct stm32_uart_port ports[STM32_USART_MAX] = {
                /* [0] USART1 */
                /* [1] USART2 */
                [1] = {
                        .gpio_tx = GPIOA,
                        .gpio_rx = GPIOA,
                
                
                },
        };
}
