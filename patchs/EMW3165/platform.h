/** @file
 * Defines peripherals available for use on EMW3165 board
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/



/******************************************************
 *                   Enumerations
 ******************************************************/

/*
EMW3165 on EMB-3165-A platform pin definitions ...
+-------------------------------------------------------------------------+
| Enum ID       |Pin | STM32| Peripheral  |    Board     |   Peripheral   |
|               | #  | Port | Available   |  Connection  |     Alias      |
|---------------+----+------+-------------+--------------+----------------|
|               | 1  | NC   |             |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_2  | 2  | B  2 |   GPIO      |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 3  |  NC  |             |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_4  | 4  | A  7 | TIM1_CH1N   |              |                |
|               |    |      | TIM3_CH2    |              |                |
|               |    |      | SPI1_MOSI   |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_5  | 5  | A  15| JTDI        |              |                |
|               |    |      | TIM2_CH1    |              |                |
|               |    |      | TIM2_ETR    |              |                |
|               |    |      | SPI1_NSS    |              |                |
|               |    |      | SPI3_NSS    |              |                |
|               |    |      | USART1_TX   |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_6  | 6  | B  3 | TIM2_CH2    |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | SPI1_SCK    |              |                |
|               |    |      | USART1_RX   |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_7  | 7  | B  4 | JTRST       |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | SDIO_D0     |              |                |
|               |    |      | TIM3_CH1    |              |                |
|               |    |      | SPI1_MISO   |              |                |
|               |    |      | SPI3_MISO   |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_8  | 8  | A  2 | TIM2_CH3    |              |                |
|               |    |      | TIM5_CH3    |              |                |
|               |    |      | TIM9_CH1    |              |                |
|               |    |      | USART2_TX   |              |                |
|               |    |      | GPIO        |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_9  | 9  | A  1 | TIM2_CH2    |EasyLink_BUTTON|               |
|               |    |      | TIM5_CH2    |              |                |
|               |    |      | USART2_RTS  |              |                |
|               |    |      | GPIO        |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 10 | VBAT |             |
|---------------+----+------+-------------+--------------+----------------|
|               | 11 | NC   |             |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_12 | 12 | A  3 | TIM2_CH4    |              |                |
|               |    |      | TIM5_CH4    |              |                |
|               |    |      | TIM9_CH2    |              |                |
|               |    |      | USART2_RX   |              |                |
|               |    |      | GPIO        |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 13 | NRST |             |              |  MICRO_RST_N   |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_14 | 14 | A 0  | WAKE_UP     |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 15 | NC   |             |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_16 | 16 | C 13 |     -       |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_17 | 17 | B 10 |  TIM2_CH3   | WICED_SYS_LED |                |
|               |    |      |  I2C2_SCL   |              |                |
|               |    |      |  GPIO       |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_18 | 18 | B  9 | TIM4_CH4    |              |                |
|               |    |      | TIM11_CH1   |              |                |
|               |    |      | I2C1_SDA    |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_19 | 19 | B 12 | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 20 | GND  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 21 | GND  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_22 | 22 | B  3 |             |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_23 | 23 | A 15 | GPIO        |              |  JTAG_TDI      |
|               |    |      | USART1_TX   |STDIO_UART_RX |  SPI1_SSN      |
|               |    |      | TIM2_CH1    |              |                |
|               |    |      | TIM2_ETR    |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_24 | 24 | B  4 |             |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_25 | 25 | A 14 | JTCK-SWCLK  |  SWCLK       |                |
|               |    |      |  GPIO       |              |                |
+---------------+----+--------------------+--------------+----------------+
|WICED_GPIO_26  | 26 | A 13 | JTMS-SWDIO  |  SWDIO       |                |
|               |    |      |  GPIO       |              |                |
+---------------+----+--------------------+--------------+----------------+
|WICED_GPIO_27  | 27 | A 12 | TIM1_ETR    |              |                |
|               |    |      | USART1_RTS  |              |                |
|               |    |      | USART6_RX   |              |                |
|               |    |      | USB_FS_DP   |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 28 | NC   |             |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_29 | 29 | A 10 | GPIO        |              |                |
|               |    |      | TIM1_CH3    |              |                |
|               |    |      | USART1_RX   |              |                |
|               |    |      | USB_FS_ID   |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_30 | 30 | B  6 | GPIO        |              |                |
|               |    |      | TIM4_CH1    |              |                |
|               |    |      | USART1_TX   |              |                |
|               |    |      | I2C1_SCL    |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_SYS_LED | 31 | B  8 | GPIO        |              |                |
|               |    |      | TIM4_CH3    |              |                |
|               |    |      | TIM10_CH1   |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 32 |  NC  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_33 | 33 | B 13 | TIM1_CH1N   |              |                |
|               |    |      | SPI2_SCK    |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_34 | 34 | A  5 | TIM2_CH1    |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_35 | 35 | A  11| TIM1_CH4    |              |                |
|               |    |      | SPI4_MISO   |              |                |
|               |    |      | USART1_CTS  |              |                |
|               |    |      | USART6_TX   |              |                |
|               |    |      | USB_FS_DM   |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_36 | 36 | B  1 | TIM1_CH3N   | BOOT_SEL     |                |
|               |    |      | TIM3_CH4    |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_37 | 37 | B  0 | TIM1_CH2N   | MFG_SEL      |                |
|               |    |      | TIM3_CH3    |              |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_38 | 38 | A  4 | USART2_CK   | WICED_RF_LED |                |
|               |    |      | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 39 | VDD  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 40 | VDD  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 41 | ANT  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
*/

// The MCU actually only supports 36 GPIOs, but this is handy.
typedef enum
{
    WICED_GPIO_1,
    WICED_GPIO_2,
    WICED_GPIO_3,
    WICED_GPIO_4,
    WICED_GPIO_5,
    WICED_GPIO_6,
    WICED_GPIO_7,
    WICED_GPIO_8,
    WICED_GPIO_9,
    WICED_GPIO_10,
    WICED_GPIO_11,
    WICED_GPIO_12,
    WICED_GPIO_13,
    WICED_GPIO_14,
    WICED_GPIO_15,
    WICED_GPIO_16,
    WICED_GPIO_17,
    WICED_GPIO_18,
    WICED_GPIO_19,
    WICED_GPIO_20,
    WICED_GPIO_21,
    WICED_GPIO_22,
    WICED_GPIO_23,
    WICED_GPIO_24,
    WICED_GPIO_25,
    WICED_GPIO_26,
    WICED_GPIO_27,
    WICED_GPIO_28,
    WICED_GPIO_29,
    WICED_GPIO_30,
    WICED_GPIO_31,
    WICED_GPIO_32,
    WICED_GPIO_33,
    WICED_GPIO_34,
    WICED_GPIO_35,
    WICED_GPIO_36,
    WICED_GPIO_37,
    WICED_GPIO_38,
    WICED_GPIO_39,
    WICED_GPIO_40,
    WICED_GPIO_41,
    WICED_GPIO_MAX, /* Denotes the total number of GPIO port aliases. Not a valid GPIO alias */
    WICED_GPIO_32BIT = 0x7FFFFFFF,
} wiced_gpio_t;

// The datasheet says up to 5 SPIs
typedef enum
{
    WICED_SPI_1,
	WICED_SPI_2,
	WICED_SPI_3,
	WICED_SPI_4,
	WICED_SPI_5,
    WICED_SPI_MAX, /* Denotes the total number of SPI port aliases. Not a valid SPI alias */
    WICED_SPI_32BIT = 0x7FFFFFFF,
} wiced_spi_t;

// The datasheet says up to 5 I2S
typedef enum 
{
    WICED_I2S_1,
	WICED_I2S_2,
	WICED_I2S_3,
	WICED_I2S_4,
	WICED_I2S_5,
    WICED_I2S_MAX,
    WICED_I2S_32BIT = 0x7FFFFFFF,
} wiced_i2s_t;

// The datasheet says up to 3 I2C
typedef enum
{
    WICED_I2C_1,
	WICED_I2C_2,
	WICED_I2C_3,
    WICED_I2C_MAX,
    WICED_I2C_32BIT = 0x7FFFFFFF,
} wiced_i2c_t;

// The datasheet says all 16 timers support PWM
typedef enum
{
    WICED_PWM_1,
    WICED_PWM_2,
    WICED_PWM_3,
    WICED_PWM_4,
    WICED_PWM_5,
    WICED_PWM_6,
    WICED_PWM_7,
    WICED_PWM_8,
    WICED_PWM_9,
	WICED_PWM_10,
	WICED_PWM_11,
	WICED_PWM_12,
	WICED_PWM_13,
	WICED_PWM_14,
	WICED_PWM_15,
	WICED_PWM_16,
    WICED_PWM_MAX, /* Denotes the total number of PWM port aliases. Not a valid PWM alias */
    WICED_PWM_32BIT = 0x7FFFFFFF,
} wiced_pwm_t;

// The datasheet says up to 10 ADCs with the WLCSP49 package
typedef enum
{
    WICED_ADC_1,
    WICED_ADC_2,
    WICED_ADC_3,
    WICED_ADC_4,
    WICED_ADC_5,
    WICED_ADC_6,
    WICED_ADC_7,
    WICED_ADC_8,
    WICED_ADC_9,
    WICED_ADC_10,
    WICED_ADC_MAX, /* Denotes the total number of ADC port aliases. Not a valid ADC alias */
    WICED_ADC_32BIT = 0x7FFFFFFF,
} wiced_adc_t;

// The datasheet says up to 3 USARTs, numbered 1, 2 and 6 for some reason...
typedef enum
{
    WICED_UART_1,
    WICED_UART_2,
	WICED_UART_6,
    WICED_UART_MAX, /* Denotes the total number of UART port aliases. Not a valid UART alias */
    WICED_UART_32BIT = 0x7FFFFFFF,
} wiced_uart_t;

/******************************************************
 *                    Constants
 ******************************************************/

/* UART port used for standard I/O */
#define STDIO_UART ( WICED_UART_2 ) // WICED_UART_2 is STM32F411CE USART2 (defined in platform.c)
									// Connected to the USB-UART chip on the MXCHIP devboard

/* SPI flash is present on EMW3165 */
#define WICED_PLATFORM_INCLUDES_SPI_FLASH
#define WICED_SPI_FLASH_CS ( WICED_GPIO_5 )

/* Components connected to external I/Os */
#define WICED_LED1         ( WICED_GPIO_17 )    // system led on dev board
#define WICED_LED2         ( WICED_GPIO_38 )    // rf led on dev board

#define WICED_BUTTON1      ( WICED_GPIO_9 )		// Easylink button on dev board

#define WICED_SWITCH1      ( WICED_GPIO_36 )	// BOOT switch on dev board
#define WICED_SWITCH2      ( WICED_GPIO_37 )	// STATUS switch on dev board

/*  Bootloader OTA/OTA2 LED to flash while "Factory Reset" button held */
#define PLATFORM_FACTORY_RESET_LED_GPIO      ( WICED_LED1 )
#define PLATFORM_FACTORY_RESET_LED_ON_STATE  ( WICED_ACTIVE_HIGH )

/* Bootloader OTA and OTA2 factory reset during settings */
#define PLATFORM_FACTORY_RESET_BUTTON_GPIO      ( WICED_BUTTON1 )
#define PLATFORM_FACTORY_RESET_PRESSED_STATE    (   0  )
#define PLATFORM_FACTORY_RESET_CHECK_PERIOD     (  100 )
#define PLATFORM_FACTORY_RESET_TIMEOUT          ( 5000 )

#ifdef __cplusplus
} /*extern "C" */
#endif
