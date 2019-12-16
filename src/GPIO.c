#include "GPIO.h"

void GPIO_Configuration(void)
{
    //------------External Interruts-----*/
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure PA pins as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ----------UART----------------- */

    /* Enable the USART2 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
    /* Configure USARTz Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = USARTz_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);

    /* Configure USARTy Tx as alternate function push-pull */

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = USARTz_TxPin;
    GPIO_Init(USARTz_GPIO, &GPIO_InitStructure);
}
