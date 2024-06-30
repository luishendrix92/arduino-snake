#include "Snake.h"
#include <Arduino.h>

void Snake::move() {
  Vec2 oldTail = tail_;
  bool ateApple = false;

  body_[head_.y][head_.x] = dir_;
  head_ += dir_;
  if (wallCollision()) {
    reset();
    return;
  }

  if (head_.x == apple_.x && head_.y == apple_.y) {
    spawnApple(false);
    ateApple = true;
  } else {
    const Direction tailDir = body_[tail_.y][tail_.x];
    body_[tail_.y][tail_.x] = NONE;
    tail_ += tailDir;
  }
  if (selfCollision()) {
    reset();
    return;
  }

  if (moveHandler_ != nullptr)
    moveHandler_(head_, ateApple ? nullptr : &oldTail);
}

void Snake::changeDir(const Direction dir) {
  const bool isOpposite =
      (dir_ == UP && dir == DOWN) || (dir_ == DOWN && dir == UP) ||
      (dir_ == RIGHT && dir == LEFT) || (dir_ == LEFT && dir == RIGHT);

  if (!isOpposite) dir_ = dir;
}

void Snake::reset() {
  for (auto &row : body_)
    for (auto &cell : row)
      cell = NONE;

  dir_ = RIGHT;
  head_.x = BOARD_WIDTH / 2;
  head_.y = BOARD_HEIGHT / 2;
  tail_.x = head_.x;
  tail_.y = head_.y;
  if (resetHandler_ != nullptr) resetHandler_(head_);
  spawnApple(true);
}

void Snake::spawnApple(const bool firstTime) {
  const Vec2 oldApple = apple_;
  apple_.x = static_cast<int8_t>(random(BOARD_WIDTH));
  apple_.y = static_cast<int8_t>(random(BOARD_HEIGHT));
  if (appleSpawnHandler_ != nullptr)
    appleSpawnHandler_(apple_, firstTime ? nullptr : &oldApple);
}

bool Snake::wallCollision() const {
  return head_.x >= BOARD_WIDTH || head_.x < 0 || head_.y >= BOARD_HEIGHT ||
         head_.y < 0;
}

bool Snake::selfCollision() const { return body_[head_.y][head_.x] != NONE; }

void Snake::onReset(void (*handler)(const Vec2 &)) { resetHandler_ = handler; }

void Snake::onMove(void (*handler)(const Vec2 &, const Vec2 *)) {
  moveHandler_ = handler;
}

void Snake::onAppleSpawn(void (*handler)(const Vec2 &, const Vec2 *)) {
  appleSpawnHandler_ = handler;
}