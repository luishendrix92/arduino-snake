#include <Arduino.h>
#include <Elegoo_TFTLCD.h>
#include <Snake.h>
#include <constants.h>

Elegoo_TFTLCD tft(A3, A2, A1, A0, A4);
Snake snake;

uint16_t neutralX, neutralY;
uint16_t joystickX, joystickY;

void drawBlock(int8_t x, int8_t y, uint16_t color) {
  tft.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A6));
  tft.reset();
  tft.begin(TFT_DRIVER_ID);
  tft.setRotation(3); // Landscape
  neutralX = analogRead(JOYSTICK_PIN_X);
  neutralY = analogRead(JOYSTICK_PIN_Y);

  snake.onReset([](const Vec2 &head) {
    tft.fillScreen(BLACK);
    drawBlock(head.x, head.y, WHITE);
  });
  snake.onMove([](const Vec2 &head, const Vec2 *oldTail) {
    if (oldTail != nullptr) drawBlock(oldTail->x, oldTail->y, BLACK);
    drawBlock(head.x, head.y, WHITE);
  });
  snake.onAppleSpawn([](const Vec2 &newApple, const Vec2 *oldApple) {
    if (oldApple != nullptr) drawBlock(oldApple->x, oldApple->y, BLACK);
    drawBlock(newApple.x, newApple.y, BLUE);
  });

  snake.reset();
}

void loop() {
  joystickX = analogRead(JOYSTICK_PIN_X);
  joystickY = analogRead(JOYSTICK_PIN_Y);

  if (joystickX > neutralX + JOYSTICK_THRESHOLD) snake.changeDir(RIGHT);
  else if (joystickX < neutralX - JOYSTICK_THRESHOLD) snake.changeDir(LEFT);
  else if (joystickY > neutralY + JOYSTICK_THRESHOLD) snake.changeDir(DOWN);
  else if (joystickY < neutralY - JOYSTICK_THRESHOLD) snake.changeDir(UP);

  snake.move();
  delay(INTERVAL);
}