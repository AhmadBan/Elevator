#include "RCC.h"
#include "main.h"

void RCC_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* DMA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USARTz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USARTz Clock */
  RCC_APB1PeriphClockCmd(USARTz_CLK, ENABLE);
}
