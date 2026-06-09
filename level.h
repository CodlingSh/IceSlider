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
    uint8_t lines[255][2];
    uint8_t sectsCompleted = 0;
    uint8_t count = 0;
    uint8_t speed = 2;
    uint8_t speedCount = 4;

  public:
    Level(Arduboy2 *ab_ptr) : ab(ab_ptr) {}

    void generateLevel() {
      for (uint8_t i = 0; i < 255; i++) {
        // int8_t segment = 0b00000000;
        int8_t offset = random(0, 6);
        int8_t length = random(53, 58);
        
        lines[i][0] = offset;
        lines[i][1] = length;
      }
    }

    void drawBufferLine(uint8_t offset, uint8_t height, uint8_t x) {
      uint8_t *buffer = ab->getBuffer();
      uint8_t line1end = offset;
      uint8_t line2start = offset + height;

      // // Drawing the top lines
      int8_t toDraw1 = offset / 8 - 1;
      uint8_t excess1 = offset % 8;

      if (toDraw1 >= 0) {
        for (uint8_t i = 0; i <= toDraw1; i++) {
          buffer[x + i * 128] = 0b11111111;
        }
      }

      if (excess1 > 0) {
        buffer[x + (toDraw1 + 1) * 128] = determineExcess(excess1, false);
      }

      // // Drawing the bottom lines
      int8_t toDraw2 = line2start / 8;
      uint8_t excess2 = line2start % 8;

      if (toDraw2 >= 0) {
        for (uint8_t i = toDraw2; i < 8; i++) {
          buffer[x + i * 128] = 0b11111111;
        }
      }

      if (excess2 > 0) {
        buffer[x + toDraw2 * 128] = determineExcess(excess2, true);
      }
      
    }

    uint8_t determineExcess(uint8_t num, bool flipped) {
      uint8_t byte = 0;
      
      if (num == 0) {
        return 0b00000000;  
      }

      byte = 0b11111111 >> (8 - num);

      if (flipped) {
        byte ^= 0b11111111;
      }

      return byte;
    }

    void scrollLevel() {
      for (uint8_t i = 0; i < 254; i++) {
        lines[i][0] = lines[i + 1][0];
        lines[i][1] = lines[i + 1][1];
      }

      lines[254][0] = random(0, 6);
      lines[254][1] = random(53, 58);
    }

    void update() {

      if (ab->pressed(LEFT_BUTTON) || ab->pressed(B_BUTTON)) {
        speedCount = 6;
      } else if (ab->pressed(RIGHT_BUTTON)) {
        speedCount = 1;
      } else {
        speedCount = 2;
      }

      speed -= 1;

      if (speed == 0) {
        scrollLevel();
        speed = speedCount;
      }
      count++;

      // generateLevel();
      // if (ab->pressed(A_BUTTON) || ab->pressed(B_BUTTON)) {
      //   offset++;
      // }
    }

    void draw() {
      ab->drawFastHLine(0, 0, 128, WHITE);
      ab->drawFastHLine(0, 63, 128, WHITE);

      for (uint8_t i = 0; i < 127; i++) {
        drawBufferLine(lines[i][0], lines[i][1], i);
      }

      ab->setCursor(90, 0);
      ab->println(count);
    }
};

#endif