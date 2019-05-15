/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 * @defgroup uart_example_main main.c
 * @{
 * @ingroup uart_example
 * @brief UART Example Application main file.
 *
 * This file contains the source code for a sample application using UART.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <string.h>

#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


//#define ENABLE_LOOPBACK_TEST  /**< if defined, then this example will be a loopback test, which means that TX should be connected to RX to get data loopback. */

//#define MAX_TEST_DATA_BYTES     (15U)                /**< max number of test bytes to be used for tx and rx. */
#define UART_TX_BUF_SIZE 256u                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 512u                         /**< UART RX buffer size. */

void handle_gps(uint8_t * p_data, uint8_t length)
{
  
  // Do something with the string
  char * received_command = (char*)p_data;

}

void uart_error_handle(app_uart_evt_t * p_event)
{
    
    uint32_t err_code;
    static uint16_t index = 0u;
    static uint8_t data[UART_RX_BUF_SIZE];


    switch(p_event->evt_type)
    {
      case APP_UART_DATA_READY:
        // recover the string
        UNUSED_VARIABLE(app_uart_get(&data[index]));
        index++;

        if((data[index-1] == '\n') || (index >= UART_RX_BUF_SIZE))
        {
          // Handle the GPS string
          handle_gps(data, index);

          index = 0;
          app_uart_flush(); // Attempt to prevent buffer overflow?
        }

        break;

      case APP_UART_COMMUNICATION_ERROR:
        APP_ERROR_HANDLER(p_event->data.error_communication);
        break;

      case APP_UART_FIFO_ERROR:
        APP_ERROR_HANDLER(p_event->data.error_code);
        break;

      default:
        break;
    }
    
}


void send_gps_msg(uint8_t * msg_string, uint16_t length)
{
  
  
  for(uint32_t i = 0; i < length; i++)
  {
     while (app_uart_put(msg_string[i]) != NRF_SUCCESS);
  }

}

/**@brief  Function for initializing the UART module.
 */
/**@snippet [UART Initialization] */
static void uart_init(void)
{
    uint32_t err_code;

    const app_uart_comm_params_t comm_params =
    {
          ARDUINO_1_PIN,
          ARDUINO_0_PIN,
          NULL,
          NULL,
          APP_UART_FLOW_CONTROL_DISABLED,
          false,
          NRF_UART_BAUDRATE_9600

    };

    APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);

}

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    uint32_t err_code;

    bsp_board_init(BSP_INIT_LEDS);

    // ARDUINO_1_PIN RX_PIN_NUMBER
    // ARDUINO_0_PIN TX_PIN_NUMBER

    uart_init();
    
    char command[] = "$PMTK104*37\r\n";
    uint8_t length = strlen(command); //sizeof(command)/sizeof(char);
    uint8_t * msg = (uint8_t *)(command);
    send_gps_msg(msg, length);

    nrf_delay_ms(200u);

    strcpy(command, "$PMTK301,1*2D\r\n");
    length = strlen(command);
    msg = (uint8_t *)(command);
    send_gps_msg(msg, length);

    nrf_delay_ms(200u);

    strcpy(command, "$PMTK250,1,1,9600*16\r\n");
    length = strlen(command);
    msg = (uint8_t *)(command);
    send_gps_msg(msg, length);

    nrf_delay_ms(200u);

    strcpy(command, "$PMTK458*3B\r\n");
    length = strlen(command);
    msg = (uint8_t *)(command);
    send_gps_msg(msg, length);

    //printf("\r\nUART example started.\r\n");

    while(true)
    {

      // wait to receive data

    }

    

    /*
    while (true)
    {
        uint8_t cr;
        while (app_uart_get(&cr) != NRF_SUCCESS);
        while (app_uart_put(cr) != NRF_SUCCESS);

        if (cr == 'q' || cr == 'Q')
        {
            printf(" \r\nExit!\r\n");

            while (true)
            {
                // Do nothing.
            }
        }
    }
    */

}


/** @} */
