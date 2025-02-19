#pragma once

// touchpad
#define TP_PIN_PIN 33
#define TP_PWR_PIN 25
#define TP_DEBOUNCE_INTERVAL 80
#define TP_HELD_DELAY 2000
// 1.5x of TP_DEBOUNCE_INTERVAL should be gud
#define TP_CLICK_DELAY 300

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define IMU_INT_PIN GPIO_NUM_38
#define RTC_INT_PIN 34
#define BATT_ADC_PIN 35
#define VBUS_PIN 36
#define LED_PIN 4
#define CHARGE_PIN GPIO_NUM_32
#define MPU_ADDR 0x69

// TFT definitions
#define TFT_LEDC_CHAN 0
#define TFT_LEDC_FREQ 5000
#define TFT_LEDC_RESOLUTION 8
#define TFT_MAX_BRIGHTNESS 255
#define TFT_MIN_BRIGHTNESS 1
#define TFT_DEFAULT_BRIGHTNESS 185
#define TFT_Y_OFFSET 26
#define TFT_X_OFFSET 1
// was 100
#define TFT_ST7735_SWRESET_DELAY 120
// was 150
#define TFT_ST7735_SLPIN_DELAY 120

// GFX definitions
#define GFX_DEFAULT_BG TFT_SKYBLUE
#define GFX_DEFAULT_FG TFT_NAVY

// Serial
#define SERIAL_BIT_RATE_DEFAULT 115200

// I2C
#define I2C_DEFAULT_CLOCK 400000

// Battery
#define BATTERY_MIN_V 2.50f
#define BATTERY_MAX_V 4.20f
// can be used somehow in calibration
#define BATTERY_DEFAULT_VREF 1100
#define BATTERY_VOLTAGE_DIVIDER_COEF 2.0F
#define BATTERY_ADC_MAX_RANGE 4095.0F
// for ADC_ATTEN_DB_11
#define BATTERY_ADC_MAX_VOLTAGE 2.45F
#define BATTERY_RANGE (BATTERY_MAX_V - BATTERY_MIN_V)
#define BATTERY_MAX_PERCENT 100
#define BATTERY_MIN_PERCENT 0