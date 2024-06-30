#ifndef CONSTANTS_H
#define CONSTANTS_H

/* ILI9341 | a-Si TFT LCD Single Chip Driver
 * 240RGBx320 Resolution and 262K color
 * https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf */
constexpr uint16_t TFT_DRIVER_ID = 0x9341;

constexpr uint8_t BOARD_HEIGHT = 24;
constexpr uint8_t BOARD_WIDTH = 32;
constexpr uint8_t BLOCK_SIZE = 10;
constexpr uint8_t INTERVAL = 100;

constexpr uint16_t BLACK = 0x0000;
constexpr uint16_t BLUE = 0x001F;
constexpr uint16_t WHITE = 0xFFFF;

constexpr uint8_t JOYSTICK_PIN_X = 15;
constexpr uint8_t JOYSTICK_PIN_Y = 14;
constexpr uint16_t JOYSTICK_THRESHOLD = 300;

#endif // CONSTANTS_H
