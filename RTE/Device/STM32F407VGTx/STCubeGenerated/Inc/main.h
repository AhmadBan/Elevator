/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define OverWeight_Pin GPIO_PIN_3
#define OverWeight_GPIO_Port GPIOA
#define OverWeight_EXTI_IRQn EXTI3_IRQn
#define HalSensor_Pin GPIO_PIN_4
#define HalSensor_GPIO_Port GPIOC
#define DoorParking_Pin GPIO_PIN_5
#define DoorParking_GPIO_Port GPIOC
#define DoorParking_EXTI_IRQn EXTI9_5_IRQn
#define DownLimitSwitch_Pin GPIO_PIN_0
#define DownLimitSwitch_GPIO_Port GPIOB
#define DownLimitSwitch_EXTI_IRQn EXTI0_IRQn
#define UpLimitSwitch_Pin GPIO_PIN_1
#define UpLimitSwitch_GPIO_Port GPIOB
#define UpLimitSwitch_EXTI_IRQn EXTI1_IRQn
#define Overtemperature_Pin GPIO_PIN_2
#define Overtemperature_GPIO_Port GPIOB
#define Overtemperature_EXTI_IRQn EXTI2_IRQn
#define ParkingBTN_Pin GPIO_PIN_10
#define ParkingBTN_GPIO_Port GPIOE
#define ParkingBTN_EXTI_IRQn EXTI15_10_IRQn
#define FirstFloorBtn_Pin GPIO_PIN_11
#define FirstFloorBtn_GPIO_Port GPIOE
#define FirstFloorBtn_EXTI_IRQn EXTI15_10_IRQn
#define SecondFloorBtn_Pin GPIO_PIN_12
#define SecondFloorBtn_GPIO_Port GPIOE
#define SecondFloorBtn_EXTI_IRQn EXTI15_10_IRQn
#define ThirdFloorBtn_Pin GPIO_PIN_13
#define ThirdFloorBtn_GPIO_Port GPIOE
#define ThirdFloorBtn_EXTI_IRQn EXTI15_10_IRQn
#define DoorFirstFloor_Pin GPIO_PIN_6
#define DoorFirstFloor_GPIO_Port GPIOC
#define DoorFirstFloor_EXTI_IRQn EXTI9_5_IRQn
#define DoorSecondFloor_Pin GPIO_PIN_7
#define DoorSecondFloor_GPIO_Port GPIOC
#define DoorSecondFloor_EXTI_IRQn EXTI9_5_IRQn
#define DoorThirdFloor_Pin GPIO_PIN_8
#define DoorThirdFloor_GPIO_Port GPIOC
#define DoorThirdFloor_EXTI_IRQn EXTI9_5_IRQn

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
