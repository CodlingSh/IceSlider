#include <Arduboy2.h>
#include "player.h"
#include "bullet.h"
#include "level.h"
#include "fuelGage.h"
#include "enemy.h"
#include "score.h"

Arduboy2 ab;
Player player(&ab);
Enemy enemies[13](&player);
Level level(&ab, enemies);
Score score;
uint8_t lives = 3;

// 7x64, 1 frame(s), 58 bytes
// Example: Sprites::drawOverwrite(x, y, gage, frame);
const uint8_t PROGMEM gage[] = {
  7, 64,
  0x00, 0x3e, 0x0a, 0x0a, 0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x00, 0x7c, 0x54, 0x54, 0x44, 0x00, 0xff,
};

void setup() {
  ab.begin();
  ab.setFrameRate(60);
  ab.initRandomSeed();

  lives = 3;

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

  for (uint8_t enemy = 0; enemy < 13; enemy++) {
    if (enemyHit(player.getBullet(), enemies[enemy])) {
      enemies[enemy].die();
      player.getBullet().respawn();
      score.incScore(25);
    }
  }

  level.draw();
  player.draw();

  
  // ab.fillRect(106, 0, 24, 64, BLACK);
  // ab.drawBitmap(106, 0, gage, 22, 64, BLACK);
  Sprites::drawOverwrite(0, 0, gage, 0);
  ab.fillRect(121, 0, 7, 64, BLACK);
  ab.drawFastVLine(121, 0, 64, WHITE);

  score.draw(lives);

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
