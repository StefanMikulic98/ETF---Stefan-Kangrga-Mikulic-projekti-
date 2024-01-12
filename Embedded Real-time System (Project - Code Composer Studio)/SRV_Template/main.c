/**
 * @file    main.c
 * @author  Haris Turkmanovic(haris@etf.rs)
 * @date    2021
 * @brief   SRV Template
 *
 * Template to be used for lab work and projects
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
//#include <18F452.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"

/* Hardware includes. */
#include "msp430.h"

/* User's includes */
#include "ETF5529_HAL/hal_ETF_5529.h"

/**
 * @brief Button enumeration
 */
typedef enum{
    BUTTON_S1,
    BUTTON_S4,
    BUTTON_UNDEF
}button_command_t;

#define ULONG_MAX                       0xFFFFFFFF

/** "xTask2" priority */
#define mainxTask2_PRIO               ( 3 )
/** "ADC task" priority */
#define mainADC_TASK_PRIO             ( 3 )
/** "xTimerTask" priority */
#define mainxTaskTimer_PRIO           ( 3 )
/** "xTask1" priority */
#define mainxTask1_PRIO               ( 2 )
/** "xTask3" priority */
#define mainxTask3_PRIO               ( 1 )

/** xTask1 bit masks */
#define mainNEW_MESSAGE                       0x04
#define mainBUTTON_S1                         0x01
#define mainBUTTON_S4                         0x02

#define mainADC_PERIOD_MS    1000

/* Display queue parameters value*/
/* Queue with length 1 is mailbox*/
#define mainDISPLAY_QUEUE_LENGTH            1

static void prvSetupHardware( void );

/* This queue will be used to send data to ADC task*/
xQueueHandle        xADC0Mailbox;
/* This queue will be used to send data to xTask1 task*/
xQueueHandle        xTask1Mailbox;
/* This queue will be used to send data to xTask3 task*/
xQueueHandle        xTask3Mailbox;
/* This handle will be used as ADC task instance*/
TaskHandle_t        xADCTaskHandle;
/* This handle will be used as xTask1 task instance*/
TaskHandle_t        xTask1Handle;
/* This handle will be used as xTask2 task instance*/
TaskHandle_t        xTask2Handle;

/* Remember which diode is pressed*/
button_command_t    buttonCommand;


/**
 * @brief "xTask3 Task" Function
 *
 * This task read data from xTask3Mailbox but reading is not blocking.
 * xTask3Mailbox is used to send data which as string will sent
 * over UART to PC
 */
static void prvxTask3Function( void *pvParameters )
{   int     previous_result=0;
    int     new_result;
    /* New received 16bit data */
    uint16_t newMessage;
    char        string_mask[]  = "111";
    char        string_s1[]  = "Kanal 0: ";
    char        string_s4[]  = "Kanal 1: ";
    char        string_newLine[]  = "\r\n";
    char        *tmp;
    char number;


    for ( ;; )
    {
        /* Check if new number is received*/
        if(xQueueReceive(xTask3Mailbox, &newMessage, 0) == pdTRUE){
            /* Check if new number higher than previous number to calculate the difference*/
            if((int)newMessage>previous_result){
                new_result=(int)newMessage-previous_result;
            }
            else{
                new_result=previous_result-(int)newMessage;
            }
            previous_result=newMessage;

            /* Sending first string for each channel depends on the active canals*/
            switch(buttonCommand){
                case BUTTON_S1:
                    tmp = string_s1;
                    break;
                case BUTTON_S4:
                    tmp = string_s4;
                    break;
                case BUTTON_UNDEF:
                    break;
            }

            while(*tmp != 0){
              while (!(UCA1IFG&UCTXIFG));
                  UCA1TXBUF = *tmp;
                  tmp += 1;
            }

            UCA1TXBUF= ' ';

            /* Sending difference between new and previous number as string over UART to PC*/
            tmp   =   string_mask;
            while(*tmp != 0){
                while(!(UCA1IFG&UCTXIFG));
                /* Separating the largest number to the smallest*/
                number= new_result/100 + '0';
                UCA1TXBUF = number;

                new_result %= 100;
                new_result *= 10;
                tmp += 1;
            }

            /* Sending new line string over UART to PC*/
            tmp = string_newLine;
            while(*tmp != 0){
                while (!(UCA1IFG&UCTXIFG));
                UCA1TXBUF   =   *tmp;
                tmp        +=   1;
            }
        }
    }

}

/**
 * @brief "xTask1" Function
 *
 * This task send result of conversion or change ADC channel wich depends on
 * notification value
 */
static void prvxTask1Function( void *pvParameters )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* New received 32bit data */
    uint32_t    notifyValue;
    uint16_t     message;

    for ( ;; )
    {
        /* Waits for notification value */
        xTaskNotifyWait(ULONG_MAX, ULONG_MAX, &notifyValue, portMAX_DELAY);

        /* Check if notification bit value, defined with mainNEW_MESSAGE mask, is set*/
        if((notifyValue & mainNEW_MESSAGE) != 0){
            if(xQueueReceive(xTask1Mailbox, &message, 0) == pdTRUE){
                /* Delete the bits that indicate the conversion channel  */
                message = message << 4;
                message = message >> 4;

                xQueueSendToBack(xTask3Mailbox,&message,&xHigherPriorityTaskWoken);
            }
        }

        /* Check if notification bit value, defined with mainBUTTON_S1 mask, is set*/
        if((notifyValue & mainBUTTON_S1) != 0){
            buttonCommand      =   BUTTON_S1;
            /* Change ADC12 periphery channel from channel 1 to channel 0 */
            ADC12CTL0      &=~ ADC12ENC;

            ADC12MCTL0     &=~ ADC12INCH_1;
            ADC12MCTL0     |= ADC12INCH_0;

            ADC12CTL0      |= ADC12ENC;
        }

        /* Check if notification bit value, defined with mainBUTTON_S4 mask, is set*/
        if((notifyValue & mainBUTTON_S4) != 0){
            buttonCommand      =   BUTTON_S4;
            /* Change ADC12 periphery channel from channel 0 to channel 1*/
            ADC12CTL0      &=~ ADC12ENC;

            ADC12MCTL0     &=~ ADC12INCH_0;
            ADC12MCTL0     |= ADC12INCH_1;

            ADC12CTL0      |= ADC12ENC;

        }

    }
}

static void prvxTask2Function( void *pvParameters )
{
    uint16_t i;
    uint8_t         currentButtonState  = 1;

    for ( ;; )
    {
        /* Waits for notification value */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        /*wait for a little to check that button is still pressed*/
        for(i = 0; i < 1000; i++);

        /* check if button SW4 is pressed*/
        currentButtonState = ((P1IN & 0x20) >> 5);
        if(currentButtonState == 0){
            /* If S4 is pressed set xTask1 task notification value bit defined
             * with mainBUTTON_S4 mask */
            xTaskNotify(xTask1Handle, mainBUTTON_S4, eSetBits);
            continue;
        }

        /* check if button SW1 is pressed*/
        currentButtonState = ((P2IN & 0x02) >> 1);
        if(currentButtonState == 0){
            /* If S3 is pressed set xTask1 task notification value bit defined
             * with mainBUTTON_S1 mask */
            xTaskNotify(xTask1Handle, mainBUTTON_S1, eSetBits);
            continue;
        }
    }
}



static void prvxTaskTimerFunction( void *pvParameters )
{
    TickType_t xLastWakeTime;

    for ( ;; )
    {
       /* Initialise the xLastWakeTime variable with the current time*/
       xLastWakeTime = xTaskGetTickCount();

       /*Trigger ADC Conversion*/
       ADC12CTL0 |= ADC12SC;
       vTaskDelayUntil( &xLastWakeTime, mainADC_PERIOD_MS );
    }
}

static void prvADCTaskFunction( void *pvParameters )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint16_t     value_canal;
    for ( ;; )
    {

        /* Wait for new number from ADC conversion*/
        xQueueReceive(xADC0Mailbox, &value_canal,portMAX_DELAY);

        /* Check which channel is active and set bit 13 or bit 14 on "1" depends on active channel*/
        switch(buttonCommand){
            case BUTTON_S1:
                value_canal |= 0x1000;
                break;
            case BUTTON_S4:
                value_canal |= 0x2000;
                break;
            case BUTTON_UNDEF:
                break;
        }

        xQueueSendToBack(xTask1Mailbox,&value_canal,&xHigherPriorityTaskWoken);
        /* If new number arrived set xTask1 task notification value bit defined
         * with mainNEW_MESSAGE mask */
        xTaskNotify(xTask1Handle, mainNEW_MESSAGE, eSetBits);

    }
}
/**
 * @brief main function
 */
void main( void )
{
    /* Configure peripherals */
    prvSetupHardware();

    /* Create tasks */
    xTaskCreate( prvxTask1Function,
                 "xTask1",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainxTask1_PRIO,
                 &xTask1Handle
               );
    xTaskCreate( prvxTask2Function,
                  "xTask2",
                  configMINIMAL_STACK_SIZE,
                  NULL,
                  mainxTask2_PRIO,
                  &xTask2Handle
                  );
    xTaskCreate( prvxTask3Function,
                  "xTask3",
                  configMINIMAL_STACK_SIZE,
                  NULL,
                  mainxTask3_PRIO,
                  NULL
                  );
    xTaskCreate( prvxTaskTimerFunction,
                 "xTaskTimer",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainxTaskTimer_PRIO,
                 NULL
               );
    xTaskCreate( prvADCTaskFunction,
                 "ADC Task",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 mainADC_TASK_PRIO,
                 &xADCTaskHandle
               );

    /* Create FreeRTOS objects  */
    xADC0Mailbox       =   xQueueCreate(mainDISPLAY_QUEUE_LENGTH,sizeof(uint16_t));
    xTask1Mailbox      =   xQueueCreate(mainDISPLAY_QUEUE_LENGTH,sizeof(uint16_t));
    xTask3Mailbox      =   xQueueCreate(mainDISPLAY_QUEUE_LENGTH,sizeof(uint16_t));
    buttonCommand      =   BUTTON_S1;
    /* Start the scheduler. */
    vTaskStartScheduler();


    /* If all is well then this line will never be reached.  If it is reached
    then it is likely that there was insufficient (FreeRTOS) heap memory space
    to create the idle task.  This may have been trapped by the malloc() failed
    hook function, if one is configured. */
    for( ;; );
}

/**
 * @brief Configure hardware upon boot
 */
static void prvSetupHardware( void )
{
    taskDISABLE_INTERRUPTS();

    /* Disable the watchdog. */
    WDTCTL = WDTPW + WDTHOLD;

    hal430SetSystemClock( configCPU_CLOCK_HZ, configLFXT_CLOCK_HZ );

    /* - Init buttons - */
    /*Set direction to input*/
    P1DIR &= ~0x20;
    /*Enable pull-up resistor*/
    P1REN |= 0x30;
    P1OUT |= 0x30;
    /*Enable interrupt for pin connected to SW4*/
    P1IE  |= 0x20;
    P1IFG &=~0x20;
    /*Interrupt is generated during high to low transition*/
    P1IES |= 0x20;

    /*Set direction to input*/
    P2DIR &= ~0x02;
    /*Enable pull-up resistor*/
    P2REN |= 0x02;
    P2OUT |= 0x02;
    /*Enable interrupt for pin connected to SW1*/
    P2IE  |= 0x02;
    P2IFG &=~0x02;
    /*Interrupt is generated during high to low transition*/
    P2IES |= 0x02;


    /*Initialize ADC */
    ADC12CTL0      = ADC12SHT02 + ADC12ON;       // Sampling time, ADC12 on
    ADC12CTL1      = ADC12SHP;                   // Use sampling timer
    ADC12IE        = 0x01;                       // Enable interrupt
    ADC12MCTL0     |= ADC12INCH_0;
    ADC12CTL0      |= ADC12ENC;
    P6SEL          |= 0x03;                      // P6.0 and P6.1 ADC option select


    /* Initialize UART */

     P4SEL       |= BIT4+BIT5;                    // P4.4,5 = USCI_AA TXD/RXD
     UCA1CTL1    |= UCSWRST;                      // **Put state machine in reset**
     UCA1CTL1    |= UCSSEL_2;                     // SMCLK
     UCA1BRW      = 1041;                         // 1MHz 115200
     UCA1MCTL    |= UCBRS_6 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
     UCA1CTL1    &= ~UCSWRST;                     // **Initialize USCI state machine**
     UCA1IE      |= UCRXIE;                       // Enable USCI_A1 RX interrupt

    /*enable global interrupts*/
    taskENABLE_INTERRUPTS();

}

void __attribute__ ( ( interrupt( ADC12_VECTOR  ) ) ) vADC12ISR( void )
{
    //BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;
    uint16_t    temp;
    switch(__even_in_range(ADC12IV,34))
    {
        case  0: break;                           // Vector  0:  No interrupt
        case  2: break;                           // Vector  2:  ADC overflow
        case  4: break;                           // Vector  4:  ADC timing overflow
        case  6:                                  // Vector  6:  ADC12IFG0
            /* Scaling ADC value from 12 bits to 9 bits*/
            temp    = ADC12MEM0>>3;
            xQueueSendToBackFromISR(xADC0Mailbox,&temp,&xHigherPriorityTaskWoken);
            break;
        case  8:                                  // Vector  8:  ADC12IFG1
            break;
        case 10: break;                           // Vector 10:  ADC12IFG2
        case 12: break;                           // Vector 12:  ADC12IFG3
        case 14: break;                           // Vector 14:  ADC12IFG4
        case 16: break;                           // Vector 16:  ADC12IFG5
        case 18: break;                           // Vector 18:  ADC12IFG6
        case 20: break;                           // Vector 20:  ADC12IFG7
        case 22: break;                           // Vector 22:  ADC12IFG8
        case 24: break;                           // Vector 24:  ADC12IFG9
        case 26: break;                           // Vector 26:  ADC12IFG10
        case 28: break;                           // Vector 28:  ADC12IFG11
        case 30: break;                           // Vector 30:  ADC12IFG12
        case 32: break;                           // Vector 32:  ADC12IFG13
        case 34: break;                           // Vector 34:  ADC12IFG14
        default: break;
    }
    /* trigger scheduler if higher priority task is woken */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void __attribute__ ( ( interrupt( PORT1_VECTOR  ) ) ) vPORT1ISR( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* If button SW4 is pressed*/
    if((P1IFG & 0x20) == 0x20){
        vTaskNotifyGiveFromISR(xTask2Handle, &xHigherPriorityTaskWoken);
    }
    /*Clear IFG register on exit. Read more about it in offical MSP430F5529 documentation*/
    P1IFG &=~0x20;
    /* trigger scheduler if higher priority task is woken */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void __attribute__ ( ( interrupt( PORT2_VECTOR  ) ) ) vPORT2ISR( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* If button SW1 is pressed*/
    if((P2IFG & 0x02) == 0x02){   //|| ((P1IFG & 0x10) == 0x10) || ((P1IFG & 0x02) == 0x02) za dugme s2 i s3 ako treba
        vTaskNotifyGiveFromISR(xTask2Handle, &xHigherPriorityTaskWoken);
    }
    /*Clear IFG register on exit. Read more about it in offical MSP430F5529 documentation*/
    P2IFG &=~0x02;
    /* trigger scheduler if higher priority task is woken */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
