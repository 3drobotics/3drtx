#ifndef _HAL_
#define _HAL_

/*
 * GPIOS
 */

#define RCC_AHB1Periph_GPIOBUTTON       (RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE)

// Keys
#define GPIO_BUTTON_ENTER               GPIOE->IDR
#define GPIO_BUTTON_PLUS                GPIOE->IDR
#define GPIO_BUTTON_MINUS               GPIOE->IDR
#define GPIO_BUTTON_MENU                GPIOD->IDR
#define GPIO_BUTTON_EXIT                GPIOD->IDR
#define GPIO_BUTTON_PAGE                GPIOD->IDR
#define	PIN_BUTTON_PLUS                 GPIO_Pin_10	//SW3 PE.10
#define PIN_BUTTON_MINUS                GPIO_Pin_11     //SW1 PE.12
#define	PIN_BUTTON_ENTER                GPIO_Pin_12	//SW2 PE.11
#define PIN_BUTTON_MENU                 GPIO_Pin_7	//SW4 PD.07
#define PIN_BUTTON_PAGE                 GPIO_Pin_3      //SW6 PD.02
#define PIN_BUTTON_EXIT                 GPIO_Pin_2      //SW5 PD.03

// Trims
#define GPIO_TRIM_LH_L                  GPIOE->IDR
#define GPIO_TRIM_LV_DN                 GPIOE->IDR
#define GPIO_TRIM_RV_UP                 GPIOC->IDR
#define GPIO_TRIM_RH_L                  GPIOC->IDR
#define GPIO_TRIM_LH_R                  GPIOE->IDR
#define GPIO_TRIM_LV_UP                 GPIOE->IDR
#define GPIO_TRIM_RV_DN                 GPIOC->IDR
#define GPIO_TRIM_RH_R                  GPIOC->IDR
#define	PIN_TRIM_RV_DN                  GPIO_Pin_3	//PC.03
#define	PIN_TRIM_RV_UP                  GPIO_Pin_2	//PC.02
#define	PIN_TRIM_RH_L                   GPIO_Pin_1	//PC.01
#define PIN_TRIM_RH_R                   GPIO_Pin_13	//PC.13
#if defined(REV3)
  #define PIN_TRIM_LH_R                 GPIO_Pin_4	//PE.04
  #define PIN_TRIM_LH_L                 GPIO_Pin_3      //PE.03
#else
  #define PIN_TRIM_LH_L                 GPIO_Pin_4      //PE.04
  #define PIN_TRIM_LH_R                 GPIO_Pin_3      //PE.03
#endif
#define PIN_TRIM_LV_DN                  GPIO_Pin_6      //PE.06
#define PIN_TRIM_LV_UP                  GPIO_Pin_5      //PE.05

// Switchs
#if defined(REV3)
  #define GPIO_PIN_SW_F                 (~GPIOE->IDR)
  #define PIN_SW_F		        GPIO_Pin_14	//PE.14
#else
  #define GPIO_PIN_SW_F                 GPIOE->IDR
  #define PIN_SW_F                      GPIO_Pin_14     //PE.14
#endif

#define GPIO_PIN_SW_E_L                 GPIOB->IDR
#define GPIO_PIN_SW_E_H                 GPIOB->IDR
#define	PIN_SW_E_L		        GPIO_Pin_3	//PB.03
#define	PIN_SW_E_H		        GPIO_Pin_4	//PB.04

#if defined(REV3)
  #define GPIO_PIN_SW_B_L               GPIOB->IDR
  #define GPIO_PIN_SW_B_H               GPIOB->IDR
  #define PIN_SW_B_L                    GPIO_Pin_5      //PB.05
  #define PIN_SW_B_H                    GPIO_Pin_6      //PB.06
#else
  #define GPIO_PIN_SW_B_H               GPIOE->IDR
  #define GPIO_PIN_SW_B_L               GPIOE->IDR
  #define PIN_SW_B_H                    GPIO_Pin_1      //PE.01
  #define PIN_SW_B_L                    GPIO_Pin_2      //PE.02
#endif

#if defined(REV3)
  #define GPIO_PIN_SW_A_H               (~GPIOB->IDR)
  #define GPIO_PIN_SW_A_L               (~GPIOE->IDR)
  #define PIN_SW_A_H		        GPIO_Pin_7	//PB.07
  #define PIN_SW_A_L		        GPIO_Pin_2	//PE.02
#else
  #define GPIO_PIN_SW_A_H               GPIOB->IDR
  #define GPIO_PIN_SW_A_L               GPIOE->IDR
  #define PIN_SW_A_H                    GPIO_Pin_5      //PB.05
  #define PIN_SW_A_L                    GPIO_Pin_0      //PE.00
#endif

#if defined(REV3)
  #define GPIO_PIN_SW_G_H               (~GPIOA->IDR)
  #define GPIO_PIN_SW_G_L               (~GPIOB->IDR)
  #define PIN_SW_G_H                    GPIO_Pin_5      //PA.05
  #define PIN_SW_G_L		        GPIO_Pin_0	//PB.00
#else
  #define GPIO_PIN_SW_G_H               GPIOE->IDR
  #define GPIO_PIN_SW_G_L               GPIOE->IDR
  #define PIN_SW_G_H                    GPIO_Pin_9      //PE.09
  #define PIN_SW_G_L                    GPIO_Pin_8      //PE.08
#endif

#if defined(REV3)
  #define GPIO_PIN_SW_C_H               (~GPIOB->IDR)
  #define GPIO_PIN_SW_C_L               (~GPIOE->IDR)
  #define PIN_SW_C_H                    GPIO_Pin_1      //PB.01
  #define PIN_SW_C_L		        GPIO_Pin_7	//PE.07
#else
  #define GPIO_PIN_SW_C_H               GPIOE->IDR
  #define GPIO_PIN_SW_C_L               GPIOA->IDR
  #define PIN_SW_C_H                    GPIO_Pin_15     //PE.15
  #define PIN_SW_C_L                    GPIO_Pin_5      //PA.05
#endif

#if defined(REV3)
  #define GPIO_PIN_SW_D_H               (~GPIOE->IDR)
  #define GPIO_PIN_SW_D_L               (~GPIOE->IDR)
  #define PIN_SW_D_H		        GPIO_Pin_9	//PE.09
  #define PIN_SW_D_L		        GPIO_Pin_8	//PE.08
#else
  #define GPIO_PIN_SW_D_H               GPIOE->IDR
  #define GPIO_PIN_SW_D_L               GPIOB->IDR
  #define PIN_SW_D_H                    GPIO_Pin_7      //PE.07
  #define PIN_SW_D_L                    GPIO_Pin_1      //PB.01
#endif

#if defined(REV3)
  #define GPIO_PIN_SW_H                 (~GPIOE->IDR)
  #define PIN_SW_H                      GPIO_Pin_13     //PE.13
#else
  #define GPIO_PIN_SW_H                 GPIOE->IDR
  #define PIN_SW_H                      GPIO_Pin_13     //PE.13
#endif

// ADC
#define PIN_STK_J1                      GPIO_Pin_0  //PA.00
#define PIN_STK_J2                      GPIO_Pin_1  //PA.01
#define PIN_STK_J3                      GPIO_Pin_2  //PA.02
#define PIN_STK_J4                      GPIO_Pin_3  //PA.03
#define PIN_SLD_J1                      GPIO_Pin_4  //PC.04
#define PIN_SLD_J2                      GPIO_Pin_5  //PC.05
#define PIN_FLP_J1                      GPIO_Pin_6  //PA.06
#if defined(REV3)
  #define PIN_FLP_J2                    GPIO_Pin_7  //PA.07
#else
  #define PIN_FLP_J2                    GPIO_Pin_0  //PB.00
#endif
#define PIN_MVOLT                       GPIO_Pin_0  //PC.00
#if defined(REV3)
  #define RCC_AHB1Periph_GPIOADC        RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC
#else
  #define RCC_AHB1Periph_GPIOADC        RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
#endif

// DAC
#define PIN_AUDIO_DAC                   GPIO_Pin_4  //PA.04

// Power_OFF Delay and LED
#define PIN_PWR_LED                     GPIO_Pin_6  //PC.06
#define PIN_PWR_STATUS                  GPIO_Pin_1  //PD.01
#define PIN_MCU_PWR                     GPIO_Pin_0  //PD.00
#define RCC_AHB1Periph_GPIOPWR          RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD
#define GPIOPWRLED                      GPIOC
#define GPIOPWR                         GPIOD
#define PIN_INT_RF_PWR                  GPIO_Pin_15
#define PIN_EXT_RF_PWR                  GPIO_Pin_8

// Trainer Port
#define GPIO_TR_INOUT                   GPIOC
#define PIN_TR_PPM_IN                   GPIO_Pin_8  //PC.08
#define PIN_TR_PPM_OUT                  GPIO_Pin_9  //PC.09
#define GPIOTRNDET                      GPIOA
#define PIN_TRNDET                      GPIO_Pin_8

// TODO merge these constants
#define PIN_PER_1                       0x0010
#define PIN_PER_2                       0x0020
#define PIN_PORTA                       0x0000
#define PIN_PER_3                       0x0030
#define PIN_PER_5                       0x0050
// #define PIN_OS2                         0x0000
#define PIN_OS25                        0x2000
// #define PIN_OS50                        0x4000
// #define PIN_OS100                       0x6000

// Cppm
#define RCC_AHB1Periph_GPIO_INTPPM      RCC_AHB1Periph_GPIOA
#define PIN_INTPPM_OUT                  GPIO_Pin_10  //PA.10
#define GPIO_INTPPM                     GPIOA
#define GPIO_PinSource_INTPPM           GPIO_PinSource10
#define RCC_AHB1Periph_GPIO_EXTPPM      RCC_AHB1Periph_GPIOA
#define PIN_EXTPPM_OUT                  GPIO_Pin_7  //PA.07
#define GPIO_EXTPPM                     GPIOA
#define GPIO_PinSource_EXTPPM           GPIO_PinSource7

// Heart Beat
#define PIN_HEART_BEAT                  GPIO_Pin_7  //PC.07

// UART3
#define RCC_AHB1Periph_GPIO_UART3       RCC_AHB1Periph_GPIOB
#define RCC_APB1Periph_UART3            RCC_APB1Periph_USART3
#define GPIO_UART3                      GPIOB
#define GPIO_PIN_UART3_TX               GPIO_Pin_10 //PB.10
#define GPIO_PIN_UART3_RX               GPIO_Pin_11 //PB.11
#define GPIO_PinSource_UART3_TX         GPIO_PinSource10
#define GPIO_PinSource_UART3_RX         GPIO_PinSource11
#define GPIO_AF_UART3                   GPIO_AF_USART3
#define UART3                           USART3

// Smart-Port
#define RCC_AHB1Periph_GPIO_SPORT       RCC_AHB1Periph_GPIOD
#define RCC_APB1Periph_SPORT            RCC_APB1Periph_USART2
#define GPIO_PIN_SPORT_ON               GPIOD
#define PIN_SPORT_ON                    GPIO_Pin_4  //PD.04
#define GPIO_PIN_SPORT_TXRX             GPIOD
#define PIN_SPORT_TX                    GPIO_Pin_5  //PD.05
#define PIN_SPORT_RX                    GPIO_Pin_6  //PD.06
#define GPIO_PinSource_SPORT_TX         GPIO_PinSource5
#define GPIO_PinSource_SPORT_RX         GPIO_PinSource6
#define GPIO_AF_SPORT                   GPIO_AF_USART2
#define SPORT                           USART2 

// USB_OTG
#define PIN_FS_VBUS                     GPIO_Pin_9  //PA.09
#define PIN_FS_DM                       GPIO_Pin_11 //PA.11
#define PIN_FS_DP                       GPIO_Pin_12 //PA.12

// BackLight PB8
#define RCC_AHB1Periph_GPIOBL           RCC_AHB1Periph_GPIOB
#define GPIO_Pin_BL                     GPIO_Pin_8  //PB.08
#define GPIOBL                          GPIOB
#define GPIO_PinSource_BL               GPIO_PinSource8

// LCD GPIOD 10-14
#define RCC_AHB1Periph_LCD              RCC_AHB1Periph_GPIOD
#define GPIO_LCD                        GPIOD
#define PIN_LCD_MOSI                    GPIO_Pin_10 //PD.10
#define PIN_LCD_CLK                     GPIO_Pin_11 //PD.11
#define PIN_LCD_NCS                     GPIO_Pin_14 //PD.14
#define PIN_LCD_A0                      GPIO_Pin_13 //PD.13
#define PIN_LCD_RST                     GPIO_Pin_12  //pd12 test //RESET occurs when powered up,but should delay before initialize

// Audio - I2S3
#define CODEC_I2S                       SPI3
#define CODEC_I2S_CLK                   RCC_APB1Periph_SPI3
#define CODEC_I2S_GPIO_AF               GPIO_AF_SPI3
#define CODEC_I2S_IRQ                   SPI3_IRQn
#define CODEC_I2S_GPIO_CLOCK            (RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC )//| RCC_AHB1Periph_GPIOE)
#define CODEC_I2S_WS_PIN                GPIO_Pin_15 //PA.15
#define CODEC_I2S_SCK_PIN               GPIO_Pin_10 //PC.10
#define CODEC_I2S_SD_PIN                GPIO_Pin_12 //PC.12
#define CODEC_I2S_MCK_PIN               GPIO_Pin_6  //DISABLED
#define CODEC_I2S_WS_PINSRC             GPIO_PinSource15
#define CODEC_I2S_SCK_PINSRC            GPIO_PinSource10
#define CODEC_I2S_SD_PINSRC             GPIO_PinSource12
#define CODEC_I2S_MCK_PINSRC            GPIO_PinSource6
#define CODEC_I2S_GPIO                  GPIOC
#define CODEC_I2S_MCK_GPIO              GPIOC
#define CODEC_I2S_WS_GPIO               GPIOA
#define CODEC_I2S_MUTE                  GPIO_Pin_11 //PC.11
//#define CODEC_I2S_FLT                  GPIO_Pin_  //IIR/FIR
//#define CODEC_I2S_MODE                 GPIO_Pin_  //Connect to GND=I2S_STANDARD

// Eeprom 5137
#if defined(REV3)
#define I2C_EE_GPIO                     GPIOE
#define I2C_EE_WP_GPIO                  GPIOB
#define I2C_EE_GPIO_CLK                 RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE
#define I2C_EE_SCL                      GPIO_Pin_1  //PE1
#define I2C_EE_SDA                      GPIO_Pin_0  //PE0
#define I2C_EE_WP                       GPIO_Pin_9  //PB9
#else
#define RCC_APBPeriph_I2C_EE            RCC_APB1Periph_I2C1
#define I2C_EE                          I2C1
#define GPIO_AF_I2C_EE                  GPIO_AF_I2C1
#define GPIO_PinSource_I2C_EE_SCL       GPIO_PinSource6
#define GPIO_PinSource_I2C_EE_SDA       GPIO_PinSource7
#define I2C_EE_GPIO                     GPIOB
#define I2C_EE_WP_GPIO                  GPIOB
#define I2C_EE_GPIO_CLK                 RCC_AHB1Periph_GPIOB
#define I2C_EE_SCL                      GPIO_Pin_6  //PB6
#define I2C_EE_SDA                      GPIO_Pin_7  //PB7
#define I2C_EE_WP                       GPIO_Pin_9  //PB9
#endif

// SD - SPI2
#define RCC_AHB1Periph_SD_PRESENT       RCC_AHB1Periph_GPIOD
#define SD_PRESENT_GPIO                 GPIOD
#define SD_PRESENT_GPIO_Pin             GPIO_Pin_9  //PD.09
#define GPIO_Pin_SPI_SD_CS              GPIO_Pin_12 //PB.12
#define GPIO_Pin_SPI_SD_SCK             GPIO_Pin_13 //PB.13
#define GPIO_Pin_SPI_SD_MISO            GPIO_Pin_14 //PB.14
#define GPIO_Pin_SPI_SD_MOSI            GPIO_Pin_15 //PB.15
#define GPIO_PinSource_CS               GPIO_PinSource12
#define GPIO_PinSource_SCK              GPIO_PinSource13
#define GPIO_PinSource_MISO             GPIO_PinSource14
#define GPIO_PinSource_MOSI             GPIO_PinSource15

#define GPIO_SPI_SD                     GPIOB
#define SPI_SD                          SPI2
#define GPIO_AF_SD                      GPIO_AF_SPI2
#define RCC_AHB1Periph_GPIO_SD          RCC_AHB1Periph_GPIOB
#define RCC_APBPeriphClockCmd_SPI_SD    RCC_APB1PeriphClockCmd
#define RCC_APBPeriph_SPI_SD            RCC_APB1Periph_SPI2
#define RCC_AHB1Periph_DMA_SD						RCC_AHB1Periph_DMA1
#define SPI_BaudRatePrescaler_SPI_SD  	SPI_BaudRatePrescaler_4 //10.5<20MHZ,make sure < 20MHZ

//disabled io_ctl and cp/wp
#define CARD_SUPPLY_SWITCHABLE   	0
#define SOCKET_WP_CONNECTED      	0
#define SOCKET_CP_CONNECTED      	0
/* set to 1 to provide a disk_ioctrl function even if not needed by the FatFs */
#define STM32_SD_DISK_IOCTRL_FORCE      0

//DMA
#define STM32_SD_USE_DMA //Enable the DMA for SD 

#ifdef STM32_SD_USE_DMA
#define DMA_Channel_SPI_SD_RX    	DMA1_Stream3
#define DMA_Channel_SPI_SD_TX    	DMA1_Stream4

#define DMA_FLAG_SPI_SD_TC_RX    	DMA_FLAG_TCIF3
#define DMA_FLAG_SPI_SD_TC_TX    	DMA_FLAG_TCIF4
#define DMA_Channel_SPI2_TX		DMA_Channel_0
#define DMA_Channel_SPI2_RX		DMA_Channel_0
#endif

// Audio----I2S3-----SPI3
#define CODEC_MCLK_DISABLED
#define CODEC_USE_INT
//#define CODEC_USE_DMA 
#define AudioFreq                       I2S_AudioFreq_44k 

// EEPROM and CAT5137
#define I2C_Speed                       200000
#define I2C_FLASH_PAGESIZE              64
#define I2C_EEPROM_ADDRESS              0xA2
#define I2C_CAT5137_ADDRESS             0x5C //0101110

#endif
