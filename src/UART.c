#include "UART.h"
#include "main.h"
#include "DMA.h"
USART_InitTypeDef USART_InitStructure;

/**
  * @brief  Configures the DMA TX.
  * @param  None
  * @retval None
  */

void UART_Configuration(void)
{
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_Even;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* Configure USARTz */
  USART_Init(USARTz, &USART_InitStructure);
  /* Enable USARTz DMA Rx and TX request */
  USART_DMACmd(USARTz, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);
  /* Enable the USARTz */

  /* Enable USARTz TX DMA1 Channel */
  DMA_Cmd(USARTz_Tx_DMA_Channel, ENABLE);
  /* Enable USARTz RX DMA1 Channel */
  DMA_Cmd(USARTz_Rx_DMA_Channel, ENABLE);

  USART_Cmd(USARTz, ENABLE);
}

void print(uint8_t *data, size_t size)
{
  USART_Cmd(USARTz, DISABLE);
  DMA_Cmd(USARTz_Tx_DMA_Channel, DISABLE);
  DMA_Tx_Configuration(data, size);
  /* Enable USARTz TX DMA1 Channel */
  DMA_Cmd(USARTz_Tx_DMA_Channel, ENABLE);
  USART_Cmd(USARTz, ENABLE);
  while (DMA_GetFlagStatus(USARTz_Tx_DMA_FLAG) == RESET)
  {
  }
}
