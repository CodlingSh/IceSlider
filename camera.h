#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  private:
    int16_t map_scroll_x;
    int16_t map_scroll_y;

  public:
    Camera(uint16_t scroll_x, uint16_t scroll_y)
      : map_scroll_x(scroll_x), map_scroll_y(scroll_y) {}

    // Getters
    uint16_t get_scroll_x() {
      return map_scroll_x;
    }

    uint16_t get_scroll_y() {
      return map_scroll_y;
    }

    // Setters
    uint16_t set_scroll_x(uint16_t scroll_x) {
      map_scroll_x = scroll_x;
    }

    uint16_t set_scroll_y(uint16_t  scroll_y) {
      map_scroll_y = scroll_y;
    }

    void update(uint16_t target_x, uint16_t target_y) {
      map_scroll_x = target_x - 60;
      map_scroll_y = target_y - 28;
    }
};

#endif