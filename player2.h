#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>
#include "cloudMap.h"

// 8x8, 1 frame(s)
// Image: 10 bytes, Mask: 8 bytes
// Example: Sprites::drawExternalMask(x, y, hero, heroMask, frame, 0);
const uint8_t PROGMEM heroRight[] = {
  8, 8,
  0x20, 0x10, 0xff, 0xb5, 0x37, 0xfd, 0x90, 0x20,
};

const uint8_t PROGMEM heroMaskRight[] = {
  0x20, 0x10, 0xff, 0xbf, 0x3f, 0xff, 0x90, 0x20,
};

// 8x8, 4 frame(s)
// Image: 34 bytes, Mask: 32 bytes
// Example: Sprites::drawExternalMask(x, y, playerWalk, playerWalkMask, frame, 0);
const uint8_t PROGMEM playerWalkRight[] = {
  8, 8,
  // Frame 0
  0x20, 0x10, 0x7f, 0x75, 0x37, 0xfd, 0x90, 0x20,
  // Frame 1
  0x20, 0x10, 0xff, 0xb5, 0x37, 0xfd, 0x90, 0x20,
  // Frame 2
  0x20, 0x10, 0xff, 0xb5, 0x37, 0x7d, 0x50, 0x20,
  // Frame 3
  0x20, 0x10, 0xff, 0xb5, 0x37, 0xfd, 0x90, 0x20,
};

const uint8_t PROGMEM playerWalkRightMask[] = {
  // Frame 0
  0x20, 0x10, 0x7f, 0x7f, 0x3f, 0xff, 0x90, 0x20,
  // Frame 1
  0x20, 0x10, 0xff, 0xbf, 0x3f, 0xff, 0x90, 0x20,
  // Frame 2
  0x20, 0x10, 0xff, 0xbf, 0x3f, 0x7f, 0x50, 0x20,
  // Frame 3
  0x20, 0x10, 0xff, 0xbf, 0x3f, 0xff, 0x90, 0x20,
};

// 8x8, 1 frame(s)
// Image: 10 bytes, Mask: 8 bytes
// Example: Sprites::drawExternalMask(x, y, player, playerMask, frame, 0);
const uint8_t PROGMEM heroLeft[] = {
  8, 8,
  0x20, 0x90, 0xfd, 0x37, 0xb5, 0xff, 0x10, 0x20,
};

const uint8_t PROGMEM heroMaskLeft[] = {
  0x20, 0x90, 0xff, 0x3f, 0xbf, 0xff, 0x10, 0x20,
};

// 8x8, 4 frame(s)
// Image: 34 bytes, Mask: 32 bytes
// Example: Sprites::drawExternalMask(x, y, playerWalk, playerWalkMask, frame, 0);
const uint8_t PROGMEM playerWalk[] = {
  8, 8,
  // Frame 0
  0x20, 0x90, 0xfd, 0x37, 0x75, 0x7f, 0x10, 0x20,
  // Frame 1
  0x20, 0x90, 0xfd, 0x37, 0xb5, 0xff, 0x10, 0x20,
  // Frame 2
  0x20, 0x50, 0x7d, 0x37, 0xb5, 0xff, 0x10, 0x20,
  // Frame 3
  0x20, 0x90, 0xfd, 0x37, 0xb5, 0xff, 0x10, 0x20,
};

const uint8_t PROGMEM playerWalkMask[] = {
  // Frame 0
  0x20, 0x90, 0xff, 0x3f, 0x7f, 0x7f, 0x10, 0x20,
  // Frame 1
  0x20, 0x90, 0xff, 0x3f, 0xbf, 0xff, 0x10, 0x20,
  // Frame 2
  0x20, 0x50, 0x7f, 0x3f, 0xbf, 0xff, 0x10, 0x20,
  // Frame 3
  0x20, 0x90, 0xff, 0x3f, 0xbf, 0xff, 0x10, 0x20,
};

// 8x8, 5 frame(s), 42 bytes
// Example: Sprites::drawOverwrite(x, y, playerDeath, frame);
const uint8_t PROGMEM playerDeath[] = {
  8, 8,
  // Frame 0
  0x20, 0x90, 0xfd, 0x37, 0xb5, 0xff, 0x10, 0x20,
  // Frame 1
  0x36, 0x24, 0xbd, 0x7e, 0x24, 0x3c, 0x28, 0x3c,
  // Frame 2
  0x04, 0x08, 0xff, 0xad, 0xec, 0xbf, 0x09, 0x04,
  // Frame 3
  0x3c, 0x14, 0x3c, 0x24, 0x7e, 0xbd, 0x24, 0x6c,
  // Frame 4
  0xd8, 0x90, 0xf0, 0xfc, 0xf0, 0xfc, 0xf0, 0xf0,
};

class Player {
  private:
    Arduboy2 *ab;
    CloudMap *clouds;
    int8_t x = 27;
    int8_t y = 27;
    uint8_t height = 7;
    uint8_t width = 7;
    uint8_t xMin = 1;
    uint8_t xMax = 55;
    uint8_t yMin = 1;
    uint8_t yMax = 55;
    bool lastDirLeft = true;
    bool isDead = false;
    const uint8_t *currSpr = heroRight;
    const uint8_t *currMask = heroMaskRight;
    uint8_t deadFrames[25] = {0,0,1,1,2,2,3,3,0,0,1,1,2,2,3,3,0,0,1,1,2,2,3,3,4};
    uint8_t deadFrameIndex = 0;
    uint8_t walkFrame = 0;
    uint8_t walkTimer = 0;
    bool isWalking = false;
  public:
    Player(Arduboy2 *ab_ptr, CloudMap *cloud_ptr) : ab(ab_ptr), clouds(cloud_ptr) {}

    void update() {
      if (isDead == true) {
        return;
      } else {
        deadFrameIndex = 0;
      }

      isWalking = false;

      int8_t oldX = x;
      int8_t oldY = y;

      move();

      isWalking = (x != oldX || y != oldY);

      if (isWalking) {
        walkTimer++;

        if (walkTimer >= 6) {   // lower = faster animation
          walkTimer = 0;
          walkFrame = (walkFrame + 1) % 4;
        }
      } else {
        walkTimer = 0;
        walkFrame = 1; // your neutral standing frame
      }

      if (ab->pressed(LEFT_BUTTON)) {
        lastDirLeft = true;
      } else if (ab->pressed(RIGHT_BUTTON)) {
        lastDirLeft = false;
      }

      if (collideAt(x, y)) {
        int8_t dx = clouds->getDx();
        int8_t dy = clouds->getDy();

        // Push if hitting a cloud, but not moving
        if (dx != 0 && !collideAt(x - dx, y)) {
          x -= dx;
        }

        if (dy != 0 && !collideAt(x, y - dy)) {
          y -= dy;
        }
      }

      if (
        x < xMin ||
        x > xMax ||
        y < yMin ||
        y > yMax
      ) {
        isDead = true;
      }
    }

    void draw() {
      if (isDead) {
        Sprites::drawOverwrite(x, y, playerDeath, deadFrames[deadFrameIndex]);

        if (deadFrameIndex < 24) {
          deadFrameIndex++;
        }

        return;
      }

      if (lastDirLeft) {
        if (isWalking) {
          Sprites::drawExternalMask(x, y, playerWalk, playerWalkMask, walkFrame, 0);
        } else {
          Sprites::drawExternalMask(x, y, heroLeft, heroMaskLeft, 0, 0);
        }
      } else {
        if (isWalking) {
          Sprites::drawExternalMask(x, y, playerWalkRight, playerWalkRightMask, walkFrame, 0);
        } else {
          Sprites::drawExternalMask(x, y, heroRight, heroMaskRight, 0, 0);
        }
      }
    }

    int8_t getX() {
      return x;
    }

    int8_t getY() {
      return y;
    }

    bool getIsDead() {
      return isDead;
    }

    void setX(uint8_t newX) {
      x = newX;
    }

    void setY(uint8_t newY) {
      y = newY;
    } 
    
    int8_t getWidth() {
      return width;
    }

    int8_t getHeight() {
      return height;
    }

    void spawn() {
      x = 27;
      y = 27;
      isDead = false;
    }

    bool collideAt(int8_t px, int8_t py) {
      return clouds->cloudCollide(px + 1, py + 1);
    }

    void move() {
      if (ab->pressed(LEFT_BUTTON) && x > xMin) {
        if (!collideAt(x - 1, y)) {
          x--;
        }
      }

      if (ab->pressed(RIGHT_BUTTON) && x < xMax) {
        if (!collideAt(x + 1, y)) {
          x++;
        }
      }

      if (ab->pressed(UP_BUTTON) && y > yMin) {
        if (!collideAt(x, y - 1)) {
          y--;
        }
      }

      if (ab->pressed(DOWN_BUTTON) && y < yMax) {
        if (!collideAt(x, y + 1)) {
          y++;
        }
      }
    }
};

#endif