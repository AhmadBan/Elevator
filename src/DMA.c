#include "DMA.h"
#include "main.h"

void DMA_Tx_Configuration(uint8_t *TxBuffer, size_t TxBufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;

  /* USARTz TX DMA1 Channel (triggered by USARTz Tx event) Config */
  DMA_DeInit(USARTz_Tx_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTz_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize;
  DMA_Init(USARTz_Tx_DMA_Channel, &DMA_InitStructure);
}

/**
  * @brief  Configures the DMA RX.
  * @param  None
  * @retval None
  */
void DMA_Rx_Configuration(uint8_t *RxBuffer, size_t RxBufferSize)
{
  DMA_InitTypeDef DMA_InitStructure;
  /* USARTz RX DMA1 Channel (triggered by USARTz Rx event) Config */
  DMA_DeInit(USARTz_Rx_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTz_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = RxBufferSize;
  DMA_Init(USARTz_Rx_DMA_Channel, &DMA_InitStructure);
}
