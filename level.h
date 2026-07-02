#ifndef LEVEL_H
#define LEVEL_H

#include <Arduboy2.h>
#include "enemy.h"

const uint8_t PROGMEM opening[254][2] = {
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64},
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64},
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64},
  {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, 
  {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, 
  {18, 28}, {15, 34}, {12, 40}, {9, 46}, {6, 52}, {3, 58}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, 
  {1, 62}, {1, 62}, {1, 62}, {1, 62}
};

class Level {
  private:
    Arduboy2 *ab;
    Enemy *enemies;
    uint8_t lines[254][2];
    uint8_t sectsCompleted = 0;
    uint8_t lineCount = 0;
    uint8_t speed = 2;
    uint8_t speedCount = 4;
    int8_t topHeight = 1;
    int8_t bottomHeight = 1;
    uint8_t mood = 0;

  public:
    Level(Arduboy2 *ab_ptr, Enemy *enem) : ab(ab_ptr), enemies(enem) {
      memcpy_P(lines, opening, sizeof(lines));
    }

    void generateLevel() {
      const int8_t values[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int8_t offset = 0;
      int8_t length = 0;

      for (uint8_t i = 127; i < 254; i++) {
        topHeight += values[random(8)];
        bottomHeight += values[random(8)];

        if (topHeight <= 0) {
          topHeight = 1;
        }

        if (bottomHeight <= 0) {
          bottomHeight = 1;
        }

        if (topHeight >= 4) {
          topHeight = 3;
        }

        if (bottomHeight >= 4) {
          bottomHeight = 3;
        }

        offset = topHeight;
        length = 63 - (topHeight + bottomHeight);
        
        lines[i][0] = offset;
        lines[i][1] = length;
      }

      spawnEnemies();
    }

    void spawnEnemies() {
      for (uint8_t i = 0; i < 6; i++) {
        enemies[i].spawn(127 + (random(10) * 8), (random(5) * 8));
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
      for (uint8_t i = 0; i < 253; i++) {
        lines[i][0] = lines[i + 1][0];
        lines[i][1] = lines[i + 1][1];
      }

      // lines[254][0] = random(0, 6);
      // lines[254][1] = random(53, 58);
    }

    void scrollEnemies() {
      for (uint8_t i = 0; i < 6; i++) {
        enemies[i].setX(enemies[i].getX() - 1);
      }
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
        scrollEnemies();
        lineCount++;
        speed = speedCount;
      }

      if (lineCount >= 126) {
        generateLevel();
        lineCount = 0;
      }

      for (uint8_t i = 0; i < 6; i++) {
        if (enemies[i].isActive()) {
          enemies[i].update();
        }
      }
    }

    void draw() {
      // ab->drawFastHLine(0, 0, 128, WHITE);
      // ab->drawFastHLine(0, 63, 128, WHITE);

      for (uint8_t i = 0; i < 127; i++) {
        drawBufferLine(lines[i][0], lines[i][1], i);
      }

      for (uint8_t i = 0; i < 6; i++) {
        if (enemies[i].isActive()) {
          enemies[i].draw();
        }
      }

      ab->setCursor(90, 0);
      ab->println(lineCount);


    }
};

#endif