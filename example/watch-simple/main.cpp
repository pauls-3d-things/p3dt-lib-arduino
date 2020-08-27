#include <FakeArduino.h>
#include <SDLWindow.h>
#include <stdint.h>

#include <iostream>

#include "../../anim/p3dt_anim_doom_fire.h"
#include "../../gfx/p3dt_gfx_2d.h"
#include "../../gfx/p3dt_gfx_util.h"
#include "../../math/p3dt_math_angles.h"
using namespace std;

#define BUF_W 240
#define BUF_H 240
uint16_t screenBuffer[BUF_W * BUF_H];

Graphics2D gfx2d(BUF_W, BUF_H, 16);

uint8_t badBitmap[] = {0b10101010, 0b01010101, 0b00001111, 0b10000001};

class WatchSimpleWindow : public SDLWindowRGB565 {
 public:
  WatchSimpleWindow(Graphics2D* gfx2d, int w, int h) : SDLWindowRGB565(gfx2d, w, h) {}
  void setup() {}

  void loop() {
    delay(1000 / 30);  // 30FPS
    static uint x = 0;
    x++;

    uint8_t cx = 119;
    uint8_t cy = 119;

    gfx2d.fill(rgb565(1, 1, 1));

    gfx2d.drawWatchFace(BUF_W / 2, BUF_H / 2, 100, rgb565(255, 255, 255));
    // hour
    gfx2d.drawLine(cx, cy, rpx(cx, 33, h2d(x)), rpy(cy, 33, h2d(x)), rgb565(255, 255, 255));
    // // minute
    gfx2d.drawLine(cx, cy, rpx(cx, 66, m2d(x)), rpy(cy, 66, m2d(x)), rgb565(0, 255, 0));
    // // second
    gfx2d.drawLine(cx, cy, rpx(cx, 15, s2d(x) + 180), rpy(cy, 15, s2d(x) + 180), rgb565(255, 0, 0));  // short backwards
    gfx2d.drawLine(cx, cy, rpx(cx, 90, s2d(x)), rpy(cy, 90, s2d(x)), rgb565(255, 0, 0));              // long front
  }
};

int main(int argc, char* argv[]) {
  WatchSimpleWindow wsw(&gfx2d, BUF_W, BUF_H);
  wsw.run();
  return 0;
}
