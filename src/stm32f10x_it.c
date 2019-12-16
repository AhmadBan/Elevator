/**
  ******************************************************************************
  * @file    EXTI/EXTI_Config/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stm32f10x_it.h"
#include "ElevatorEvent.h"
#include "cmsis_os.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup EXTI_Config
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern osMailQId qid_EventQueue;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
__attribute ((noreturn)) void NMI_Handler(void)
{
	assert_failed((uint8_t*)"NMI_Handler", __LINE__);
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
__attribute ((noreturn)) void HardFault_Handler(void)
{
	 assert_failed((uint8_t*)"HardFault_Handler", __LINE__);
  
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
__attribute ((noreturn)) void MemManage_Handler(void)
{
 
  assert_failed((uint8_t*)"MemManage_Handler", __LINE__);
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
__attribute ((noreturn)) void BusFault_Handler(void)
{
  assert_failed((uint8_t*)"BusFault_Handler", __LINE__);
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
__attribute ((noreturn)) void UsageFault_Handler(void)
{
  assert_failed((uint8_t*)"UsageFault_Handler", __LINE__);
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI0_IRQHandler(void)
{

  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    FloorBtnEvt_t *pMail = 0; /* button 0 (Parking) Interrupt */
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = FLOORBUTTON_SIG;
      pMail->targetFloor = 0;
      osMailPut(qid_EventQueue, pMail);
    }
    /* Clear the  EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/**
  * @brief  This function handles External line 1 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI1_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    FloorBtnEvt_t *pMail = 0; /* Button 1 Interrupt  */

    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = FLOORBUTTON_SIG;
      pMail->targetFloor = 1;

      osMailPut(qid_EventQueue, pMail);
    }
  }
  /* Clear the  EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line1);
}

/**
  * @brief  This function handles External line 2 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI2_IRQHandler(void)
{
  FloorBtnEvt_t *pMail = 0; /* Button 2 Interrupt */

  pMail = osMailAlloc(qid_EventQueue, 0);
  if (pMail)
  {
    pMail->ancestor.sig = FLOORBUTTON_SIG;
    pMail->targetFloor = 2;

    osMailPut(qid_EventQueue, pMail);
  }

  /* Clear the  EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line2);
}
/**
  * @brief  This function handles External line 3 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI3_IRQHandler(void)
{
  FloorBtnEvt_t *pMail = 0; /* Button 3 Interrupt */

  pMail = osMailAlloc(qid_EventQueue, 0);
  if (pMail)
  {
    pMail->ancestor.sig = FLOORBUTTON_SIG;
    pMail->targetFloor = 3;

    osMailPut(qid_EventQueue, pMail);
  }
  /* Clear the  EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line3);
}
/**
  * @brief  This function handles External lines 4 interrupt request.
  * @param  None
  * @retval None
  */

void EXTI4_IRQHandler(void)
{
  LimitSWEvt_t *pMail = 0; /* Up limit switch Interrupt*/
  pMail = osMailAlloc(qid_EventQueue, 0);
  if (pMail)
  {
    pMail->ancestor.sig = LIMITSWITCH_SIG;
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET)
    {
      pMail->status |= 1;
    }
    else
    {
      pMail->status &= ~1;
    }

    osMailPut(qid_EventQueue, pMail);
  }
  /* Clear the  EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line4);
}
/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{

  if (EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    LimitSWEvt_t *pMail = 0; /* Down limit switch down Interrupt */
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = LIMITSWITCH_SIG;
      if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == Bit_SET)
      {
        pMail->status |= 2;
      }
      else
      {
        pMail->status &= ~2;
      }
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line5);
  }

  if (EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
    OverWeightEvt_t *pMail = 0; /* Overweight Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = OVERWEIGHT_SIG;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line6);
  }

  if (EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
    OverTemperatureEvt_t *pMail = 0; /* Overtemperature Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = OVERTEMPERATURE_SIG;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line7);
  }

  if (EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    HalSensorEvt_t *pMail = 0; /* Hall Sensor Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = HALSENSOR_SIG;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line8);
  }

  if (EXTI_GetITStatus(EXTI_Line9) != RESET)
  {
    DoorOpenEvt_t *pMail = 0; /* Parking door Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 0;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line9);
  }
}
void EXTI10_15_IRQHandler(void)
{

  if (EXTI_GetITStatus(EXTI_Line10) != RESET)
  {
    DoorOpenEvt_t *pMail = 0; /* First door Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 1;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line10);
  }

  if (EXTI_GetITStatus(EXTI_Line11) != RESET)
  {
    DoorOpenEvt_t *pMail = 0; /* Second door Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 2;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line11);
  }

  if (EXTI_GetITStatus(EXTI_Line12) != RESET)
  {
    DoorOpenEvt_t *pMail = 0; /* Third door Interrupt*/
    pMail = osMailAlloc(qid_EventQueue, 0);
    if (pMail)
    {
      pMail->ancestor.sig = DOOR_SIG;
      pMail->floor = 3;
      pMail->status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
      osMailPut(qid_EventQueue, pMail);
    }
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
