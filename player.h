#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>
#include "bullet.h"

// 8x8, 1 frame(s), 18 bytes
// Example: Sprites::drawPlusMask(x, y, ship, frame);
const uint8_t PROGMEM ship[] = {
  8, 8,
  0x49, 0x49, 0x6b, 0x6b, 0x7f, 0x7f, 0x6b, 0x7f, 0x22, 0x3e, 0x36, 0x3e,
  0x1c, 0x1c, 0x08, 0x08,
};

class Player {
  private:
    Arduboy2 *ab;
    int8_t x = 3;
    int8_t y = 28;
    uint8_t frame = 0;
    Bullet bullet;
    bool bulletActive = false;
    
  public:
    Player(Arduboy2 *ab_ptr) : ab(ab_ptr), bullet(ab_ptr) {}

    void update() {
      // Movement
      if (ab->pressed(UP_BUTTON)) {
        y--;
      }
      if (ab->pressed(DOWN_BUTTON)) {
        y++;
      }

      // Shooting

    }

    void draw() {
      Sprites::drawPlusMask(x, y, ship, frame);
    }
};

#endif