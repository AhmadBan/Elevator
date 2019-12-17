#include "RCC.h"
#include "main.h"

void Clock_Configuration(void)
{
	//Configure System Clock to 64 MHz Using HSI and PLL
	RCC->CFGR &= ~(3);		   /* Select HSI as sysclk */
	RCC->CR &= ~(1 << 24);	 /* disable PLL */
	RCC->CFGR &= ~(1 << 16);   /* Select HSI/2 as source to PLL */
	RCC->CFGR &= ~(0xf << 18); /* Reset PLLM */
	RCC->CFGR |= (0xf << 18);  /* PLLM=16 */
	FLASH->ACR &= ~(3);		   /*  Reset Flash Latency  */
	FLASH->ACR |= 2;		   /* Changing Flash Latency to 2 clock cycles Page 60 RM */
	RCC->CR |= (1 << 24);	  /* Enable PLL */
	while (!(RCC->CR & (1 << 25)))
	{
		/* wait until PLL is ready */
	}
	RCC->CFGR |= (2); /* Select PLL as SystemClock */
}

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
