#include <Arduboy2.h>
#include "player.h"
#include "bullet.h"
#include "level.h"
#include "fuelGage.h"
#include "enemy.h"

Arduboy2 ab;
Player player(&ab);
Enemy enemies[20](&player);
Level level(&ab, enemies);
uint16_t score;

// 9x64, 1 frame(s), 74 bytes
// Example: Sprites::drawOverwrite(x, y, gage, frame);
const uint8_t PROGMEM gage[] = {
  9, 64,
  0xe3, 0xe3, 0xe3, 0xff, 0xc1, 0xf5, 0xf5, 0xfd, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xc7, 0xc7, 0xc7, 0xff, 0x83, 0xab, 0xab, 0xbb, 0xff,
};

void setup() {
  ab.begin();
  ab.setFrameRate(60);

  ab.initRandomSeed();
  score = 0;
  Serial.begin(9600);
}

void loop() {
  if (!ab.nextFrame()) return;

  ab.pollButtons();
  ab.clear();

  // ab.fillScreen(WHITE);

  // for (uint8_t i = 0; i < 64; i += 1) {
  //   uint8_t xVar = random(1, 34);
  //   ab.drawFastHLine(20 + xVar, i, 90, BLACK);
  //   // ab.fillRect(20 + xVar, i, 90, 8, BLACK);
  // }

  level.update();
  player.update();

  for (uint8_t enemy = 0; enemy < 20; enemy++) {
    if (enemyHit(player.getBullet(), enemies[enemy])) {
      enemies[enemy].die();
      player.getBullet().respawn();
    }
  }

  level.draw();
  player.draw();
  
  // ab.fillRect(106, 0, 24, 64, BLACK);
  // ab.drawBitmap(106, 0, gage, 22, 64, BLACK);
  Sprites::drawOverwrite(0, 0, gage, 0);

  ab.setCursor(0, 0);
  ab.print(ab.cpuLoad());
  ab.print("%");

  ab.display();
}

bool enemyHit(Bullet& blt, Enemy& nme) {
  if (
    blt.getX() + 3 >= nme.getX() &&
    blt.getX() <= nme.getX() + nme.getWidth() &&
    blt.getY() >= nme.getY() &&
    blt.getY() <= nme.getY() + nme.getHeight()
  ) {
    return true;
  } else {
    return false;
  }
}
