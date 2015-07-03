/**
  ******************************************************************************
  * @file    Project/ee_drivers/i2c_ee.h
  * @author  FrSky Application Team
  * @version V 0.2
  * @date    12-JLY-2012
  * @brief   Header for i2c.c module
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

#ifndef __I2C_H
#define __I2C_H

#define	EE_CMD_WRITE  (0)
#define	EE_CMD_READ   (1)

#define SCL_H         do{I2C_EE_GPIO->BSRRL = I2C_EE_SCL;}while(0)
#define SCL_L         do{I2C_EE_GPIO->BSRRH  = I2C_EE_SCL;}while(0)
#define SDA_H         do{I2C_EE_GPIO->BSRRL = I2C_EE_SDA;}while(0)
#define SDA_L         do{I2C_EE_GPIO->BSRRH  = I2C_EE_SDA;}while(0)
#define SCL_read      (I2C_EE_GPIO->IDR  & I2C_EE_SCL)
#define SDA_read      (I2C_EE_GPIO->IDR  & I2C_EE_SDA)
#define WP_H          do{I2C_EE_WP_GPIO->BSRRL = I2C_EE_WP;}while(0)
#define WP_L          do{I2C_EE_WP_GPIO->BSRRH = I2C_EE_WP;}while(0)

/* Exported functions ------------------------------------------------------- */
void I2C_EE_Init(void);
void I2C_EE_ByteWrite(uint8_t* pBuffer, uint16_t WriteAddr);
void I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite);
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
void I2C_EE_WaitEepromStandbyState(void);

void I2C_set_volume(register uint8_t volume);
uint8_t I2C_read_volume();

#endif /* __I2C_EE_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

