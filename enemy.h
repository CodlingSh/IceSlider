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
    uint8_t y = 100;
    uint8_t width = 7;
    uint8_t height = 8;
    uint8_t *spr = nullox;
    uint8_t highest = 0;
    uint8_t lowest = 0;
    bool active = false;
    bool moving = false;
    int8_t dir = 1;
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

    uint8_t getHighest() {
      return highest;
    }

    uint8_t getLowest() {
      return lowest;
    }

    uint8_t isMoving() {
      return moving;
    }

    int8_t getDir() {
      return dir;
    }

    void setX(uint8_t newX) {
      x = newX;
    }

    void setY(uint8_t newY) {
      y = newY;
    }

    void setHighest(uint8_t newH) {
      highest = newH;
    }

    void setLowest(uint8_t newL) {
      lowest = newL;
    }

    void setActive(bool isActive) {
      active = isActive;
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
      setActive(false);
      moving = false;
    }

    void spawn(uint8_t newH, uint8_t newL) {
      setX(140);
      setY(random(newH, newL));
      setHighest(newH);
      setLowest(newL);
      setActive(true);
      moving = false;
      dir = 1;
    }

    void update() {
      if (!active) {
        return;
      }

      if (getX() <= 10) {
        die();
      }

      if (getX() <= 100) {
        moving = true;
      }

      if (moving) {
        if (y <= highest) {
          dir = 1;
        } 
        
        if (y + height >= lowest) {
          dir = -1;
        }

        y += dir;
      }
    }

    void draw() {
      Sprites::drawPlusMask(x, y, nullox, 0);
          
    }
};

#endif