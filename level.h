#ifndef LEVEL_H
#define LEVEL_H

#include <Arduboy2.h>

// 8x8, 1 frame(s), 10 bytes
// Example: Sprites::drawOverwrite(x, y, ground, frame);
const uint8_t PROGMEM ground[] = {
  8, 8,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

class Level {
  private:
    Arduboy2 *ab;
    uint8_t lines[64];
    uint8_t sectsCompleted = 0;
    uint8_t offset = 0;

  public:
    Level(Arduboy2 *ab_ptr) : ab(ab_ptr) {}

    void generateLevel() {
      for (uint8_t i = 0; i < 64; i++) {
        int8_t segment = 0b00000000;
        int8_t top = random(0, 4);
        int8_t bottom = random(0, 4);
        
        for (int8_t i = 0; i <= top; i++) {
          if (top != 0) {segment |= (1 << (7 - (i - 1)));}
        }
        for (int8_t i = 0; i <= bottom; i++) {
          if (bottom != 0) {segment |= (1 << (i - 1));} 
        }


        lines[i] = segment;
      }
    }

    // void draw() {
    //   uint8_t *buffer = ab->getBuffer();
    //   static uint16_t i = 0;

    //   i++;

    //   if (i > 1000) {
    //     i = 0;
    //   }

    //   buffer[i] = 0b11111111;


    // }

    void drawTile(uint8_t tileX, uint8_t tileY) {
      uint8_t *buffer = ab->getBuffer();

      uint16_t index = ((uint16_t)tileY * 128) + ((uint16_t)tileX * 8);

      buffer[index + 0 - offset] = 0b11111111;
      buffer[index + 1 - offset] = 0b11111111;
      buffer[index + 2 - offset] = 0b11111111;
      buffer[index + 3 - offset] = 0b11111111;
      buffer[index + 4 - offset] = 0b11111111;
      buffer[index + 5 - offset] = 0b11111111;
      buffer[index + 6 - offset] = 0b11111111;
      buffer[index + 7 - offset] = 0b11111111;
    }

    void update() {
      // generateLevel();
      if (ab->pressed(A_BUTTON) || ab->pressed(B_BUTTON)) {
        offset++;
      }
    }

    void draw() {
      ab->drawFastHLine(0, 0, 128, WHITE);
      ab->drawFastHLine(0, 63, 128, WHITE);

      for (uint8_t x = 0; x < 16; x++) {
        uint8_t segment = lines[x];

        for (uint8_t y = 0; y < 8; y++) {
          if (segment & (1 << (7 - y))) {
            drawTile(x, y);
          }
        }
      }
      ab->setCursor(32, 0);z
      ab->println(offset);
    }
};

#endif