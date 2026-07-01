#ifndef ENEMY_H
#define ENEMY_H

// 7x8, 1 frame(s), 16 bytes
// Example: Sprites::drawPlusMask(x, y, Nullox, frame);
const uint8_t PROGMEM nullox[] = {
  7, 8,
  0x11, 0x7f, 0x5e, 0x7f, 0x3a, 0x7f, 0x6e, 0x7f, 0x3a, 0x7f, 0x5e, 0x7f,
  0x11, 0x7f,
};

class Enemy {
  private:
    uint8_t x = 200;
    uint8_t y = 32;
    uint8_t width = 7;
    uint8_t height = 8;
    uint8_t *spr = nullox;
    bool active = true;
  public:

    bool isActive() {
      return active;
    }

    uint8_t getX() {
      return x;
    }

    uint8_t getY() {
      return y;
    }

    void setX(int8_t newX) {
      x = newX;
    }

    void setY(int8_t newY) {
      y = newY;
    }

    uint8_t getWidth() {
      return width;
    }

    uint8_t getHeight() {
      return height;
    }

    void die() {
      setX(222);
      setY(222);

    }

    void update() {

    }

    void draw() {
      Sprites::drawPlusMask(x, y, nullox, 0);
    }
};

#endif