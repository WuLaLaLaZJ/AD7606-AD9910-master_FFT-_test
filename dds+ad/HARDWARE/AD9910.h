/*
****************************************************************************
// Created by TerrorBlade on 2020/8/7.

	*�ļ���ad9910.c
	*���ߣ�xzw
	*�������޸��� �����Ƽ�AD9910 stm32f103����
						1����f103�ĳ�f407����
						2������׼���ΪHal������
						
	*��������
				PB5 -> PWR
				PB6 -> SDIO
				PB7 -> DPH
				PB8 -> DRO
				PB9 -> IOUP
				PB12 -> PF1
				
				PA2 -> REST
				PA3 -> SCLK
				PA4 -> DRC
				PA5 -> OSK
				PA6 -> PF0
				PA7 -> PF2
				PA8 -> CS
	
	*����޸�ʱ�䣺2020/8/7

****************************************************************************
*/
#ifndef __AD9910_H__
#define __AD9910_H__

#include "stm32f4xx.h"
#include "sys.h"

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int						


#define AD9910_PWR 	PBout(5)	 
#define AD9910_SDIO PBout(6)    
#define DRHOLD 			PBout(7)   
#define DROVER 			PBout(8)   
#define UP_DAT 			PBout(9)    
#define PROFILE1 		PBout(12) 

#define MAS_REST 		PAout(2)  
#define SCLK 				PAout(3)     
#define DRCTL  			PAout(4)   
#define OSK 				PAout(5)       
#define PROFILE0 		PAout(6)  
#define PROFILE2 		PAout(7)  
#define CS  				PAout(8)      

           


void Init_ad9910(void);
void Freq_convert(ulong Freq);										//дƵ��

//void Write_Amplitude(bit Channel,unsigned int Amplitude);	//д����

void txd_8bit(uchar txdat);
void Txcfr(void);

void Write_Amplitude(uint Amp); //д���ȣ����뷶Χ��1-650 mV

//ɨƵ������Ƶ�ʣ�����Ƶ�ʣ�Ƶ�ʲ�������λ��Hz��������ʱ��������λ��ns����Χ��4*(1~65536)ns��
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime);

void Square_wave(uint Sample_interval);//����������ʱ�������뷶Χ��4*(1~65536)ns

#endif

