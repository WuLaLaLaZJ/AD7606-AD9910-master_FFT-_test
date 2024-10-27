/*
****************************************************************************
// Created by TerrorBlade on 2020/7/28.

	*�ļ���ad7606.h
	*���ߣ�xzw
	*�������޸��� �����Ƽ�AD7606 stm32f103����
						1����f103�ĳ�f407����
						2������׼���ΪHal������
				
				��������
				
				PC11 -> RD			OUT_PP		VERY_HIGH
				PG12 -> D7			IPD
				PC12 -> CS			OUT_PP		VERY_HIGH
				PC10 -> RST			OUT_PP		VERY_HIGH
				PG13 -> CB			OUT_PP		VERY_HIGH
				PG11 -> RANGE		OUT_PP		VERY_HIGH
				PC4 -> OS0			OUT_PP		VERY_HIGH
				PC5 -> OS1			OUT_PP		VERY_HIGH
				PC6 -> OS2			OUT_PP		VERY_HIGH
				GND -> GND			OUT_PP    VERY_HIGH
			
	*���ѣ����ڵ�Ƭ����IO�ӿڵ��ٶ����ƣ��޷��ﵽ8ͨ��ͬʱ200KHz�ɼ��������������
				32��Ӳ�������жϣ����Լ��˴���
	
	*����޸�ʱ�䣺2020/8/7

****************************************************************************
*/
#ifndef ad7606_ad7606_H
#define ad7606_ad7606_H
#include "stdint.h"
#include "sys.h"
#include "string.h"
#include "arm_math.h"
#include "main.h"
/*����ȫ���жϵĺ�*/
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

/*ÿ���������ֽڣ�ͨ����*/
#define CH_NUM			8   //����8��ͨ��
#define FIFO_SIZE		1*1024*2

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int


#define AD_CS_LOW()     				CS_GPIO_Port->BSRR = CS_Pin << 16U
#define AD_CS_HIGH()     				CS_GPIO_Port->BSRR = CS_Pin

#define AD_RESET_LOW()					RST_GPIO_Port->BSRR = RST_Pin << 16U
#define AD_RESET_HIGH()					RST_GPIO_Port->BSRR = RST_Pin

#define AD_CONVST_LOW()					CB_GPIO_Port->BSRR = CB_Pin << 16U
#define AD_CONVST_HIGH()				CB_GPIO_Port->BSRR = CB_Pin  //CB--CONVST

#define AD_RANGE_5V()					  RANGE_GPIO_Port->BSRR = RANGE_Pin << 16U
#define AD_RANGE_10V()					RANGE_GPIO_Port->BSRR = RANGE_Pin

#define AD_OS0_0()						  OS0_GPIO_Port->BSRR = OS0_Pin << 16U
#define AD_OS0_1()						  OS0_GPIO_Port->BSRR = OS0_Pin

#define AD_OS1_0()						  OS1_GPIO_Port->BSRR = OS1_Pin << 16U
#define AD_OS1_1()						  OS1_GPIO_Port->BSRR = OS1_Pin

#define AD_OS2_0()						  OS2_GPIO_Port->BSRR = OS2_Pin << 16U
#define AD_OS2_1()						  OS2_GPIO_Port->BSRR = OS2_Pin

#define AD_MISO_LOW()					  D7_GPIO_Port->BSRR  = D7_Pin << 16U
#define AD_MISO_HIGH()				  D7_GPIO_Port->BSRR  = D7_Pin   //D7--MISO

#define AD_SCK_LOW()					  RD_GPIO_Port->BSRR  = RD_Pin << 16U
#define AD_CSK_HIGH()				    RD_GPIO_Port->BSRR  = RD_Pin		//RD--SCLk

#define AD_MISO_IN					PGin(12)

/*AD���ݲɼ�������*/
typedef struct
{
    uint16_t usRead;
    uint16_t usWrite;
    uint16_t usCount;
    uint16_t usBuf[FIFO_SIZE];
}FIFO_T;

void ad7606_Reset(void);
void ad7606_init(void);
void ad7606_SetOS(uint8_t _ucMode);
void ad7606_StartRecord(uint32_t _ulFreq);
void ad7606_StopRecord(void);
void ad7606_IRQSrc(void);
void ad7606_StartConv(void);
void ad7606_get_fft_data();
void fft_get_maxvalue();
float32_t filter_fft();
int32_t ad7606_get_signal_average_val(int8_t channal,int8_t average_num);
uint8_t GetAdcFormFifo(uint16_t *_usReadAdc);

extern FIFO_T  g_tAD;

#endif //ad7606_ad7606_H

