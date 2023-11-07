/**************************************************************************//**
 * @file
 * @brief LCD controller demo for EFM32GG_STK3700 development kit
 * @author Energy Micro AS
 * @version 3.20.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "bsp.h"
#include "segmentlcd.h"
#include "bsp_trace.h"
#include <stdio.h>
#include "em_emu.h"
#include "em_gpio.h"
#include "em_prs.h"
#include "em_system.h"
#include "em_timer.h"
#include "em_chip.h"
#include "em_adc.h"
#include "OlED_I2C.h"

#define PWM_FREQ 100
#define OUTPUT_PORT gpioPortE
#define OUTPUT_PIN 2
#define LOCATION TIMER_ROUTE_LOCATION_LOC1
#define LIGHTSENSE_EXCITE_PORT gpioPortD
#define LIGHTSENSE_EXCITE_PIN 6U
#define LIGHTSENSE_SENSOR_PORT gpioPortC
#define LIGHTSENSE_SENSOR_PIN 6U
#define MAX_TEMP 37
#define E 2.718

#define LED_PORT gpioPortE
#define BUTTON_PORT gpioPortB
#define LED0 2
#define LED1 3
#define PB0 9
#define PB1 10

#define ADC_PORT 3 // gpioPortD (ADC Channel 6 location #0: PD6)
#define ADC_pin 6 // ADC Channel 6

#define ADC_CLOCK 11000000
#define ADC_12BIT_MAX 4096

extern uint8_t SmallFont[];

volatile kalibrisan=0;
volatile uint32_t msTicks; /* counts 1ms timeTicks */

/* Locatl prototypes */
void Delay(uint32_t dlyTicks);
void RETARGET_SerialInit(void);
void RETARGET_SerialCrLf(int on);
int RETARGET_ReadChar(void);
int RETARGET_WriteString(char *s);

/**************************************************************************//**
 * @brief ADS_configuration and sampling
 *****************************************************************************/

uint16_t adcSingle(void)
{
  uint16_t sampleValue;
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

  /*inicijalizacija AD konvertora*/
  init.timebase=ADC_TimebaseCalc(0);
  init.prescale=ADC_PrescaleCalc(ADC_CLOCK, 0);
  ADC_Init(ADC0, &init);

  //inicijalizacija procesa konverzije
  singleInit.input=adcSingleInpCh0; //kanal na kome se meri - jednostruka konverzija(ima 8 konvertorskih kanala)
  singleInit.reference=adcRefVDD;
  singleInit.acqTime=adcAcqTime32; // 32 takta za konverziju, vece vreme=> bolji rezultat

  ADC_InitSingle(ADC0,&singleInit); //mod jednostruka konverzija pa stane

  ADC_Start(ADC0, adcStartSingle); // zapoceta konverzija

  while(ADC0->STATUS & ADC_STATUS_SINGLEACT);//ceka se kraj konverzije

  //prikupljanje rezultata
  sampleValue=ADC_DataSingleGet(ADC0); //funkcija koja obradjuje i dohvati vrednost

  //obrada konverzije
  sampleValue=(sampleValue*3300)/ADC_12BIT_MAX; //rezultat u mV

  return(sampleValue);

}

uint16_t adcSingle1(void)
{
  uint16_t sampleValue;
  ADC_Init_TypeDef init1 = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef singleInit1 = ADC_INITSINGLE_DEFAULT;

  /*inicijalizacija AD konvertora*/
  init1.timebase=ADC_TimebaseCalc(0);
  init1.prescale=ADC_PrescaleCalc(ADC_CLOCK, 0);
  ADC_Init(ADC0, &init1);

  //inicijalizacija procesa konverzije
  singleInit1.input=adcSingleInpCh1; //kanal na kome se meri - jednostruka konverzija(ima 8 konvertorskih kanala)
  singleInit1.reference=adcRefVDD;
  singleInit1.acqTime=adcAcqTime32; // 32 takta za konverziju, vece vreme=> bolji rezultat

  ADC_InitSingle(ADC0,&singleInit1); //mod jednostruka konverzija pa stane

  ADC_Start(ADC0, adcStartSingle); // zapoceta konverzija

  while(ADC0->STATUS & ADC_STATUS_SINGLEACT);//ceka se kraj konverzije

  //prikupljanje rezultata
  sampleValue=ADC_DataSingleGet(ADC0); //funkcija koja obradjuje i dohvati vrednost

  //obrada konverzije
  sampleValue=(sampleValue*5000)/ADC_12BIT_MAX; //rezultat u mV

  return(sampleValue);

}

/**************************************************************************//**
 * @brief TIMER3_IRQHandler
 * Interrupt Service Routine TIMER3 Interrupt Line
 *****************************************************************************/
void TIMER3_IRQHandler(void)
{
  uint32_t compareValue;

  /* Clear flag for TIMER3 overflow interrupt */
  TIMER_IntClear(TIMER3, TIMER_IF_OF);

  compareValue = TIMER_CaptureGet(TIMER3, 2);
  /* increment duty-cycle or reset if reached TOP value */
  if( compareValue >= TIMER_TopGet(TIMER3))
    TIMER_CompareBufSet(TIMER3, 2, 0);
  else
    {
      compareValue+=10;
      TIMER_CompareBufSet(TIMER3, 2, compareValue);
    }
}

/**************************************************************************//**
 * @brief SysTick_Handler
 *   Interrupt Service Routine for system tick counter
 * @note
 *   No wrap around protection
 *****************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
  //ms++;
}


/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  int i, c=0;
  char x[128];

  /* Chip errata */
  CHIP_Init();

  /* If first word of user data page is non-zero, enable eA Profiler trace */
  BSP_TraceProfilerSetup();

  /* Enable two leds to show we're alive */
  BSP_LedsInit();
  BSP_LedSet(0);
  //BSP_LedSet(1);

  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

  /* Enable clock for GPIO module */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Enable clock for TIMER3 module */
  CMU_ClockEnable(cmuClock_TIMER3, true);

  /* Set CC0 pin as output */
  GPIO_PinModeSet(OUTPUT_PORT, OUTPUT_PIN, gpioModePushPull, 0);

  /* Select CC channel parameters */
  TIMER_InitCC_TypeDef timerCCInit =
  {
    .eventCtrl  = timerEventEveryEdge,
    .edge       = timerEdgeBoth,
    .prsSel     = timerPRSSELCh2,
    .cufoa      = timerOutputActionNone,
    .cofoa      = timerOutputActionNone,
    .cmoa       = timerOutputActionToggle,
    .mode       = timerCCModePWM,
    .filter     = false,
    .prsInput   = false,
    .coist      = false,
    .outInvert  = false,
  };

  /* Configure CC channel 2 */
  TIMER_InitCC(TIMER3, 2, &timerCCInit);

  /* Route CC2 to location 1 (PE2) and enable pin */
  TIMER3->ROUTE |= (TIMER_ROUTE_CC2PEN | LOCATION);

  /* Set compare value starting at 0 - it will be incremented in the interrupt handler */
  TIMER_CompareBufSet(TIMER3, 2, 0);

  /* Select timer parameters */
  TIMER_Init_TypeDef timerInit =
  {
    .enable     = true,
    .debugRun   = true,
    .prescale   = timerPrescale128,
    .clkSel     = timerClkSelHFPerClk,
    .fallAction = timerInputActionNone,
    .riseAction = timerInputActionNone,
    .mode       = timerModeUp,
    .dmaClrAct  = false,
    .quadModeX4 = false,
    .oneShot    = false,
    .sync       = false,
  };

  /* Set Top Value */
  TIMER_TopSet(TIMER3, (CMU_ClockFreqGet(cmuClock_TIMER3)/(1L<<timerInit.prescale))/PWM_FREQ);

  /* Enable overflow interrupt */
  TIMER_IntEnable(TIMER3, TIMER_IF_OF);

  /* Enable TIMER3 interrupt vector in NVIC */
  NVIC_EnableIRQ(TIMER3_IRQn);

  /* Configure timer */
  TIMER_Init(TIMER3, &timerInit);
  /* Enable LCD without voltage boost */
  SegmentLCD_Init(false);
  RETARGET_SerialInit();
  RETARGET_SerialCrLf(0);

  GPIO_PinModeSet(LED_PORT, LED0, gpioModePushPull, 0);      // Configure LED0 pin as digital output (push-pull)
  GPIO_PinModeSet(LED_PORT, LED1, gpioModePushPullDrive, 1); // Configure LED1 pin as digital output (push-pull) with drive-strength to lowest setting
  //GPIO_DriveModeSet(LED_PORT, gpioDriveModeLowest);          // Set DRIVEMODE to lowest setting (0.5 mA) for all LEDs configured with alternate drive strength
  GPIO_PinModeSet(BUTTON_PORT, PB0, gpioModeInputPull, 1);   // Configure PB0 as input with pull-up enabled
  GPIO_PinModeSet(BUTTON_PORT, PB1, gpioModeInputPull, 1);
  GPIO_DriveModeSet(LIGHTSENSE_EXCITE_PORT, gpioDriveModeStandard);//upali se excite port i dovodi se logicna 1 da bi radio senzor
  GPIO_DriveModeSet(LIGHTSENSE_SENSOR_PORT, gpioDriveModeStandard);

  GPIO_PinModeSet(LIGHTSENSE_EXCITE_PORT, LIGHTSENSE_EXCITE_PIN, gpioModePushPull,1);// konfigurise se EXCITE_PIN kao izlazni pin, odnosno EXCITE_PORT kao izlazni port
  GPIO_PinModeSet(LIGHTSENSE_SENSOR_PORT, LIGHTSENSE_SENSOR_PIN, gpioModeDisabled,0);
  GPIO_PinModeSet(gpioPortD,0, gpioModeInput,1); //postaje ulazni pin i iskljucuje se digitalna finkcija- koristi se za analogni signla

  CMU_ClockEnable(cmuClock_ADC0, true);


  OLEDI2C_begin();
  OLEDI2C_setFont(SmallFont);
  OLEDI2C_clrScr();
  OLEDI2C_update();

  char messageVoltage[] = "Napon[mV]:";
  char messageTemp[] = "Temperatura[C]:";
  char messageTempPredicted[] = "Predvidjena temp:";
  char messageKalibrisan[] = "Kalibrisan:";
  char messageMS[] = "MS:";

  while(1){
      int adc_count1=0,adc_count2=0;
      long adc_result1,adc_result2;
      long previous_result;
      long temp;

      int voltage_predict;
      int temp_predict;
      volatile ms1,ms2;
      double k;
      double j;


      //if(ms2>1000000){
      //    ms2=0;
      //}
      while(adc_count2++<1000)
        adc_result2+=adcSingle1();
      adc_result2/=1000; //usrednjavanje radi boljeg odnosa signala/sum

      if(adc_result2<100 && kalibrisan==0){
          kalibrisan=1;
          msTicks=0;
          OLEDI2C_clrScr();
      }

      while(adc_count1++<1000)
        adc_result1+=adcSingle();
      adc_result1/=1000; //usrednjavanje radi boljeg odnosa signala/sum
      temp=adc_result1*0.1;

     if(kalibrisan==1){//adc_result1 > previous_result &&
         ms1=msTicks;
         k=((adc_result1-previous_result)*10000)/(ms1-ms2);//((adc_result1-previous_result)*1000)/(ms1-ms2);//(adc_result1-previous_result);//(ms1-ms2);
         if(k!=0){
             j=k;
             voltage_predict=k*(ms1+10000)/10000;
         }else{
             voltage_predict=adc_result1;
             j=0;
         }

         temp_predict=voltage_predict*0.1;
         OLEDI2C_clrScr();
      }


      if(! (GPIO_PinInGet(BUTTON_PORT, PB0)) ) {               // If PB0 is pressed
          GPIO_PinOutSet(LED_PORT, LED1);                        // Turn on LED1
          //Umin=adc_result1;
          OLEDI2C_clrScr();
      }else{
          GPIO_PinOutClear(LED_PORT, LED1);                      // Turn off LED1
      }
      if(! (GPIO_PinInGet(BUTTON_PORT, PB1)) ) {               // If PB1 is pressed
          GPIO_PinOutSet(LED_PORT, LED1);                      // Turn off LED0
          //Umax=adc_result1;
          OLEDI2C_clrScr();

      }else{
          GPIO_PinOutClear(LED_PORT, LED1);                        // Turn on LED0
      }

      Delay(250);
      ms2=ms1;
      previous_result = adc_result1;

      SegmentLCD_Number(adc_result2);
      OLEDI2C_print(messageVoltage, 2, 2);
      OLEDI2C_print(messageTemp, 2, 12);
      OLEDI2C_print(messageTempPredicted, 2, 22);
      OLEDI2C_print(messageKalibrisan, 2, 32);
      OLEDI2C_print(messageMS, 2, 42);

      OLEDI2C_printNumI(adc_result1, 105 ,2 ,2,' ');
      OLEDI2C_printNumI(temp, 105 ,12 ,2,' ');
      OLEDI2C_printNumI(temp_predict, 105 ,22 ,2,' ');
      OLEDI2C_printNumI(kalibrisan, 105 ,32 ,2,' ');
      OLEDI2C_printNumI(msTicks, 20 ,42 ,2,' ');
      OLEDI2C_printNumI(j, 20 ,52 ,2,' ');

      OLEDI2C_update();
    }

}
