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
    uint8_t x = 64;
    uint8_t y = 32;
    uint8_t *spr = nullox;zx
    bool active = true;
  public:

    bool isActive() {
      return active;
    }

    void update() {

    }

    void draw() {
      Sprites::drawPlusMask(x, y, nullox, 0);
    }
};

#endif