/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
	ע�⣺1.��ʱ��4�������ò����ʣ���Ҫ�޸Ĳ���tim.h�и���
				2.ע�͵�TIM3_Init,ԭ��δ֪
				3.������Ϊ115200.
				4.ע��ad7606.h�е�#define AD_MISO_IN	PGin(12)����
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"



/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ad7606.h"
#include "ad9910.h"
#include "stdio.h"
#include "arm_math.h"
#include "arm_const_structs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern UART_HandleTypeDef huart1;


uint16_t sampleVol[8];
int32_t int_sampleVol[8];
int32_t sampleval;

float32_t i;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern uchar cfr2[4]; //cfr2������
extern uchar cfr1[4]; //cfr1������

char str[30];	//��ʾ����
extern u8 _return;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	ad7606_init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
	//��ʱ��4�������ò����ʣ�������ע�͵�tim4_init�������亯�����޸���ad7606_StartRecord�е���

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_TIM3_Init();
  //MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	//HAL_TIM_Base_Start_IT(&htim3);
	
	/*��ʼ��AD9910*/
	/*
	HAL_Delay(72);	//��ʼ����ʱ����
	Init_ad9910();
	Freq_convert(1000);   //����Ƶ��Ϊ1k
	Write_Amplitude(10); //���÷�ֵΪ100mV ��1-640mV��
	*/
	
	
	
	/*��ʼ������AD7606����*/
	//����10V��Ӧת��  (10*(float)((short)g_tAD.usBuf[j])/32768)     AD_RANGE_10V()
	//����5V��Ӧת��  (10*(float)((short)g_tAD.usBuf[j])/32768/2)    AD_RANGE_5V()
	
	
	AD_RANGE_5V();                                        //���������ѹ���ֵ
  ad7606_StartRecord(64000);                            //���ò���Ƶ��Ϊ64khz��������Ӧ���Ǳ������źŵ�2������
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		
//		int32_t average_val;
//		average_val = ad7606_get_signal_average_val(1,8);//AIN1����8�ε�ֵ
//		printf("average_val = %d mv\n",average_val);
		
//		for(int j=0;j<8;j++)
//		{
//		i = (10*(float)((short)g_tAD.usBuf[j])/32768/2);  //g_tAD.usBuf[2]��ʾ��ȡAIN3�ĵ�ѹֵ
//		printf("AIN%d = %f V\r\n",j,i);
//		}
//		printf("\n");	
		
		printf("AIN1 = %f mV\r\n",(10000*(float)((short)g_tAD.usBuf[1])/32768/2));
		//AD7606��FFT���ݴ�����tim3�жϺ�����
		fft_get_maxvalue();
		printf("\n");
		
		HAL_Delay(1000);
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef  *htim)
{
  
	  static unsigned char ledstate = 0;
	  
    if (htim == (&htim4))                    //TIM4�жϺ��ȡadc��ֵ
    {
        ad7606_IRQSrc();
    }
		/*
		if(htim == (&htim3))
		{
			if (ledstate == 0)
            LED_HIGH();
        else
            LED_LOW();
      ledstate = !ledstate;
		}
		*/
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
