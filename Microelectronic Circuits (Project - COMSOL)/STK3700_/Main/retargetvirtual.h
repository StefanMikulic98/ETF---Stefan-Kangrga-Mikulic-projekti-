/**************************************************************************//**
 * @file
 * @brief RETARGET prototypes and definitions
 * @version 1.00.00
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#ifndef __RETARGETCDC_H
#define __RETARGETCDC_H

#define RETARGET_PORT_USB 1
#define RETARGET_PORT_BLUETOOTH 2

//#if RETARGET_PORT == RETARGET_PORT_USB
//  #define RETARGET_IRQ_NAME    UART0_RX_IRQHandler              /* USART IRQ Handler */
//  #define RETARGET_CLK         cmuClock_UART0                   /* HFPER Clock */
//  #define RETARGET_IRQn        UART0_RX_IRQn                    /* IRQ number */
//  #define RETARGET_UART        UART0                            /* USART instance */
//  #define RETARGET_TX          USART_Tx                         /* Set TX to USART_Tx */
//  #define RETARGET_RX          USART_Rx                         /* Set RX to USART_Rx */
//  #define RETARGET_LOCATION    UART_ROUTE_LOCATION_LOC1         /* Location of of the USART I/O pins */
//  #define RETARGET_TXPORT      gpioPortE                        /* USART transmission port */
//  #define RETARGET_TXPIN       0                                /* USART transmission pin */
//  #define RETARGET_RXPORT      gpioPortE                        /* USART reception port */
//  #define RETARGET_RXPIN       1                                /* USART reception pin */
//  #define RETARGET_USART       1                                /* Includes em_usart.h */
//  #define RETARGET_ENPORT      gpioPortF                        /* USART transmission port */
//  #define RETARGET_ENPIN       7                                /* USART transmission pin */
//#elif RETARGET_PORT == 'X'
//  #define RETARGET_IRQ_NAME    USART1_RX_IRQHandler             /* USART IRQ Handler */
//  #define RETARGET_CLK         cmuClock_USART1                  /* HFPER Clock */
//  #define RETARGET_IRQn        USART1_RX_IRQn                   /* IRQ number */
//  #define RETARGET_UART        USART1                           /* USART instance */
//  #define RETARGET_TX          USART_Tx                         /* Set TX to USART_Tx */
//  #define RETARGET_RX          USART_Rx                         /* Set RX to USART_Rx */
//  #define RETARGET_LOCATION    USART_ROUTE_LOCATION_LOC1        /* Location of of the USART I/O pins */
//  #define RETARGET_TXPORT      gpioPortD                        /* USART transmission port */
//  #define RETARGET_TXPIN       0                                /* USART transmission pin */
//  #define RETARGET_RXPORT      gpioPortD                        /* USART reception port */
//  #define RETARGET_RXPIN       1                                /* USART reception pin */
//  #define RETARGET_USART       1                                /* Includes em_usart.h */
//  #define RETARGET_ENPORT      gpioPortF                        /* USART transmission port */
//  #define RETARGET_ENPIN       7                                /* USART transmission pin */
//#elif RETARGET_PORT == RETARGET_PORT_BLUETOOTH
  #define RETARGET_IRQ_NAME    LEUART0_IRQHandler               /* LEUART IRQ Handler */
  #define RETARGET_CLK         cmuClock_LEUART0                 /* LFB Clock */
  #define RETARGET_IRQn        LEUART0_IRQn                     /* IRQ number */
  #define RETARGET_UART        LEUART0                          /* LEUART instance */
  #define RETARGET_TX          LEUART_Tx                        /* Set TX to LEUART_Tx */
  #define RETARGET_RX          LEUART_Rx                        /* Set RX to LEUART_Rx */
  #define RETARGET_TXPORT      gpioPortD                        /* LEUART transmission port */
  #define RETARGET_TXPIN       4                                /* LEUART transmission pin */
  #define RETARGET_RXPORT      gpioPortD                        /* LEUART reception port */
  #define RETARGET_RXPIN       5                                /* LEUART reception pin */
  #define RETARGET_LOCATION    LEUART_ROUTE_LOCATION_LOC0       /* Location of of the LEUART I/O pins */
  #define RETARGET_LEUART      1                                /* Includes em_leuart.h */
  #define RETARGET_ENPORT      gpioPortF                        /* USART transmission port */
  #define RETARGET_ENPIN       7                                /* USART transmission pin */
//#endif

/***************************************************************************//**
 * @addtogroup Drivers
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup RetargetIo
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__CROSSWORKS_ARM)
int __putchar(int ch);
int __getchar(void);
#endif

int  RETARGET_ReadChar(void);
int  RETARGET_WriteChar(char c);

void RETARGET_SerialCrLf(int on);
void RETARGET_SerialInit(void);

#ifdef __cplusplus
}
#endif

/** @} (end group RetargetIo) */
/** @} (end group Drivers) */

#endif
