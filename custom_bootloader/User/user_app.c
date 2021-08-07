/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "xmodem.h"
#include "flash.h"
#include "drv_uart.h"

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int BLD_UserApp_Init(void)
{
  /* Send welcome message on startup. */
  uart_transmit_str((uint8_t*)"\n\r================================\n\r");
  uart_transmit_str((uint8_t*)"UART Bootloader\n\r");
  uart_transmit_str((uint8_t*)"================================\n\r\n\r");

  /* If the button is pressed, then jump to the user application,
   * otherwise stay in the bootloader. */
  if(HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin))
  {
    uart_transmit_str((uint8_t*)"Jumping to user application...\n\r");
    flash_jump_to_app();
  }

  return 1;
}

  int BLD_UserApp_Run(void)
  {
	flash_init();
    /* Turn on the green LED to indicate, that we are in bootloader mode.*/
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
    /* Ask for new data and start the Xmodem protocol. */
    uart_transmit_str((uint8_t*)"Please send a new binary file with Xmodem protocol to update the firmware.\n\r");
    xmodem_receive();
    /* We only exit the xmodem protocol, if there are any errors.
     * In that case, notify the user and start over. */
    uart_transmit_str((uint8_t*)"\n\rFailed... Please try again.\n\r");

    return 1;
 }

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
