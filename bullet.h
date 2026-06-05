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

    void set_x(int8_t newX) {
      x = newX;
    }

    void set_y(int8_t newY) {
      y = newY;
    }

    void respawn() {
      
    }

    void update() {
      if (isActive) {
        switch(dir) {
          case 0:
            x--;
            break;
          case 1:
            y++;
            break;
          case 2:
            x++;
            break;
          case 3:
            y--;
            break;
        }

        if (x > 67 || x < 0 || y > 124 || y < 0) {}
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