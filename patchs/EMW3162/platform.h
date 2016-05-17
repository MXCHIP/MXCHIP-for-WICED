
/** @file
 * Defines peripherals available for use on EMW3162 board
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
EMW3162 on EMB-380-S platform pin definitions ...
+-------------------------------------------------------------------------+
| Enum ID       |Pin | STM32| Peripheral  |    Board     |   Peripheral   |
|               | #  | Port | Available   |  Connection  |     Alias      |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_1  | 1  | B  6 | GPIO        |              |                |
|               |    |      | TIM4_CH1    |              |                |
|               |    |      | CAN2_TX     |              |                |
|               |    |      | USART1_TX   |              |                |
|               |    |      | I2C1_SCL    |              |                |
|               |    |      | CAN2_TX     |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_2  | 2  | B  7 | GPIO        |              |                |
|               |    |      | I2C1_SCL    |              |                |
|               |    |      | USART1_RX   |              |                |
|               |    |      | TIM4_CH2    |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 3  | A  13| SWDIO       |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_4  | 4  | C  7 | USART2_RX   |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | TIM8_CH2    |              |                |
|               |    |      | TIM3_CH2    |              |                |
|               |    |      | I2S3_MCK    |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_5  | 5  | A  3 | ADC123_IN3  |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | TIM2_CH4    |              |                |
|               |    |      | TIM5_CH4    |              |                |
|               |    |      | TIM9_CH2    |              |                |
|               |    |      | UART2_RX    |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_6  | 6  | A  4 | SPI1_NSS    |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | SPI3_NSS    |              |                |
|               |    |      | I2S3_WS     |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_7  | 7  | B  3 | JTDO        |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | I2S3_SCK    |              |                |
|               |    |      | TIM2_CH2    |              |                |
|               |    |      | SPI1_SCK    |              |                |
|               |    |      | SPI3_SCK    |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_8  | 8  | B  4 | NJRST       |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | SPI3_MISO   |              |                |
|               |    |      | SPI1_MISO   |              |                |
|               |    |      | TIM3_CH1    |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_9  | 9  | B  5 | I2C1_SMBA   |              |                |
|               |    |      | GPIO        |              |                |
|               |    |      | CAN2_RX     |              |                |
|               |    |      | SPI1_MOSI   |              |                |
|               |    |      | SPI3_MOSI   |              |                |
|               |    |      | TIM3_CH2    |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_10 | 10 | B  8 | GPIO        |              |                |
|               |    |      | TIM4_CH3    |              |                |
|               |    |      | TIM10_CH1   |              |                |
|               |    |      | I2C1_SCL    |              |                |
|               |    |      | CAN1_RX     |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_11 | 11 | A  1 | GPIO        |EasyLink_BUTTON |              |
|               |    |      | TIM5_CH2    |              |                |
|               |    |      | TIM2_CH2    |              |                |
|               |    |      | ADC123_IN1  |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_12 | 12 | C  2 | GPIO        |              |                |
|               |    |      | ADC123_ IN12|              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_13 | 13 | B 14 | GPIO        |              |                |
|               |    |      | TIM1_CH2N   |              |                |
|               |    |      | TIM12_CH1   |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_14 | 14 | C  6 | GPIO        |              |                |
|               |    |      | TIM3_CH1    |              |                |
|               |    |      | TIM8_CH1    |              |                |
|               |    |      | USART6_TX   |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 15 | GND  |             |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_1  | 16 | B 1  | GPIO        |  RF_LED      |                |
|               |    |      | TIM3_CH4    |              |                |
|               |    |      | TIM8_CH3N   |              |                |
|               |    |      | TIM1_CH4N   |              |                |
|---------------+----+------+-------------+--------------+----------------|
|               | 17 |nReset|             |              |                |
|---------------+----+------+-------------+--------------+----------------|
| WICED_GPIO_18 | 18 | A 15 | GPIO        |              |                |
|               |    |      | JTDI        |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_19 | 19 | B 11 | GPIO        |              |                |
|               |    |      | TIM2_CH4    |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_20 | 20 | A 12 | GPIO        |              |                |
|               |    |      | USART1_RTS  |              |                |
|               |    |      | CAN1_TX     |              |                |
|               |    |      | TIM1_ETR    |              |                |
|               |    |      | OTG_FS_DP   |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_21 | 21 | A 11 | GPIO        |              |                |
|               |    |      | USART1_CTS  |              |                |
|               |    |      | CAN1_RX     |              |                |
|               |    |      | TIM1_CH4    |              |                |
|               |    |      | OTG_FS_DM   |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_22 | 22 | A  9 | GPIO        |              |                |
|               |    |      | USART1_TX   |STDIO_UART_TX |                |
|               |    |      | TIM1_CH2    |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_23 | 23 | A 10 | GPIO        |              |                |
|               |    |      | USART1_RX   |STDIO_UART_RX |                |
|               |    |      | TIM1_CH3    |              |                |
|               |    |      | OTG_FS_ID   |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 24 | VCC  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 25 | GND  |             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 26 | NC   |             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 27 | BOOT0|             |              |                |
+---------------+----+--------------------+--------------+----------------+
|               | 28 | A 14 | JTCK-SWCLK  |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_29 | 29 | A  0 | GPIO        |StandBy/WakeUp|                |
|               |    |      | TIM2_CH1_ETR|              |                |
|               |    |      | TIM5_CH1    |              |                |
|               |    |      | TIM8_ETR    |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_GPIO_30 | 30 | B  9 | GPIO        | Status_Sel   |                |
|               |    |      | TIM4_CH4    |              |                |
|               |    |      | TIM11_CH1   |              |                |
|               |    |      | I2C1_SDA    |              |                |
|               |    |      | CAN1_TX     |              |                |
+---------------+----+--------------------+--------------+----------------+
| WICED_SYS_LED |    | B  0 | GPIO        |              |                |
+---------------+----+--------------------+--------------+----------------+
*
*/

typedef enum
{
    WICED_GPIO_0,
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
    WICED_GPIO_42,
    WICED_GPIO_43,
    WICED_GPIO_44,
    WICED_GPIO_MAX, /* Denotes the total number of GPIO port aliases. Not a valid GPIO alias */
    WICED_GPIO_32BIT = 0x7FFFFFFF,
} wiced_gpio_t;

typedef enum
{
    WICED_SPI_1,
    WICED_SPI_MAX, /* Denotes the total number of SPI port aliases. Not a valid SPI alias */
    WICED_SPI_32BIT = 0x7FFFFFFF,
} wiced_spi_t;

typedef enum
{
    WICED_I2C_1,
    WICED_I2C_MAX,
    WICED_I2C_32BIT = 0x7FFFFFFF,
} wiced_i2c_t;

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
    WICED_PWM_MAX, /* Denotes the total number of PWM port aliases. Not a valid PWM alias */
    WICED_PWM_32BIT = 0x7FFFFFFF,
} wiced_pwm_t;

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

typedef enum
{
    WICED_UART_1,
    WICED_UART_2,
    WICED_UART_MAX, /* Denotes the total number of UART port aliases. Not a valid UART alias */
    WICED_UART_32BIT = 0x7FFFFFFF,
} wiced_uart_t;

/******************************************************
 *                    Constants
 ******************************************************/

/* UART port used for standard I/O */
#define STDIO_UART ( WICED_UART_1 )

/* SPI flash is NOT present on EMW3162 */
//#define WICED_PLATFORM_INCLUDES_SPI_FLASH
#define WICED_SPI_FLASH_CS ( WICED_GPIO_6 )

/* Components connected to external I/Os */
#define WICED_LED1         ( WICED_GPIO_0 ) // green led on wifi model
#define WICED_LED2         ( WICED_GPIO_16) // red led on wifi model

#define WICED_BUTTON1      ( WICED_GPIO_5 ) // WPS button on dev board
#define WICED_BUTTON2      ( WICED_GPIO_11) // EASYLINK button on dev board

#define WICED_SWITCH1      ( WICED_GPIO_16) // BOOT switch on dev board
#define WICED_SWITCH2      ( WICED_GPIO_30) // STATUS switch on dev board
#define WICED_SWITCH3      ( WICED_GPIO_29) // STANDBY switch on dev board
#define WICED_SWITCH4      ( WICED_GPIO_14) // SLEEP switch on dev board

/* Bootloader OTA and OTA2 factory reset during settings */
#define PLATFORM_FACTORY_RESET_CHECK_PERIOD     (  100 )
#define PLATFORM_FACTORY_RESET_TIMEOUT          ( 5000 )

#ifdef __cplusplus
} /*extern "C" */
#endif
