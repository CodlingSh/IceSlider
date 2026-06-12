#ifndef BULLET_H 
#define BULLET_H

class Bullet {
  private:
    Arduboy2 *ab;
    int8_t x = -22;
    int8_t y = -22;
    bool isVert;
    int8_t dir;
    bool isActive = false;

  public:
    Bullet(
      Arduboy2 *ab_ptr
    ) 
      : ab(ab_ptr) {}

    void setX(int8_t newX) {
      x = newX;
    }

    void setY(int8_t newY) {
      y = newY;
    }

    uint8_t getX() {
      return x;
    }

    uint8_t getY() {
      return y;
    }

    void respawn() {
      isActive = false;
      x = -22;
      y = -22;
    }

    void activate() {
      isActive = true;
      dir = 2;
    }

    bool getActive() {
      return isActive;
    }

    void update() {
      if (isActive) {
        switch(dir) {
          case 0:
            x -= 2;
            break;
          case 1:
            y += 2;
            break;
          case 2:
            x += 2;
            break;
          case 3:
            y -= 2;
            break;
        }

        if (x > 120 || x < 0 || y > 67 || y < 0) {
          respawn();
        }
      }
    }

    void draw() {
      uint8_t length, width;
      if (isVert) {
        ab->fillRect(x, y, 1, 3);
      } else {
        ab->fillRect(x, y, 3, 1);
      }
    }
};

#endif