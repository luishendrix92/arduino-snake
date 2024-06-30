#ifndef SNAKE_H
#define SNAKE_H

#include "../../../.platformio/packages/toolchain-atmelavr/avr/include/stdint.h"
#include "constants.h"

enum Direction : uint8_t { NONE = 0, UP, RIGHT, DOWN, LEFT };

struct Vec2 {
  int8_t x;
  int8_t y;
  void operator+=(const Direction dir) {
    if (dir == RIGHT) x += 1;
    else if (dir == LEFT) x -= 1;
    else if (dir == UP) y -= 1;
    else if (dir == DOWN) y += 1;
  }
};

class Snake {
public:
  explicit Snake() : dir_(), head_(), tail_(), apple_() {}
  void changeDir(Direction dir);
  void onReset(void (*handler)(const Vec2 &));
  void onMove(void (*handler)(const Vec2 &, const Vec2 *));
  void onAppleSpawn(void (*handler)(const Vec2 &, const Vec2 *));
  void move();
  void reset();

private:
  Direction body_[BOARD_HEIGHT][BOARD_WIDTH]{};
  Direction dir_;
  Vec2 head_;
  Vec2 tail_;
  Vec2 apple_;
  void (*resetHandler_)(const Vec2 &) = nullptr;
  void (*moveHandler_)(const Vec2 &, const Vec2 *) = nullptr;
  void (*appleSpawnHandler_)(const Vec2 &, const Vec2 *) = nullptr;

  void spawnApple(bool firstTime);
  bool wallCollision() const;
  bool selfCollision() const;
};

#endif // SNAKE_H
