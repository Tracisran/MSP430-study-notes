/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2016,CTGU-GB
 *     All rights reserved.
 *
 *
 * @file       main.c
* @brief      MSP430F5529 平台主程序

 * @author     CTGU-GB
 * @version    v2.7
 * @date       2016-11-26
 */
#include "include.h"

//DMA完成中断
__interrupt void DMA_IRQ_Handler()
{
  if(DMA_GetITStatus(DMA_CH1) == TRUE)  //是所有数据传输完后才进入中断，而不是每传输一次就进入一次
  {
     OLED_PrintfAt(FONT_ASCII_6X8,5,0,"DMA Transfer Succeed!");//显示更新 
     DMA_ClearITPendingBit(DMA_CH1);
  }
}
uint16_t Sdata=10,DData=0;
void main()
{
  DisableInterrupts();            //禁止总中断
  
  LED_Init(LED_ALL);              //LED灯初始化
  OLED_Init();                       //OLED初始化
  
  TIMER_Interval_Ms(TIMER_A1,200);    //设置TA1为定时中断，中断时间为500Ms
  TIMER_ITConfig(TIMER_A1,TIMER_CCR0_IRQn,DISABLE);                    //禁止TIMER的某一个中断,使用DMA时必须关掉中断
  
  DMA_Init(DMA_CH1, &Sdata, &DData,DMATSEL_TA1CCR0,10,  DMA_SRCAddr_KeepOn|DMA_DSTAddr_KeepOn|DMA_WORD|DMA_Single|DMA_Edge);
           //通道1，源地址，目的地址，触发源，传输10个字，源地址不变，目的地址不变，字传输，单次触发，边沿触发
  Set_Vector_Handler(VECTOR_DMA,DMA_IRQ_Handler);
  DMA_ITConfig (DMA_CH1,ENABLE);                      //DMA中断开启 */
  
  EnableInterrupts();              //使能中断
 
  while(1)
  {  
    OLED_PrintfAt(FONT_ASCII_6X8,3,0,"Sdata=%d,DData=%d",Sdata,DData);//显示更新 
    DELAY_MS(200);
    Sdata++;
  }
}
























