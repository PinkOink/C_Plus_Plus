#include "labengine.h"
#include "point_trace.h"
#include <iostream>

int main() {
  labparams_t param = { 1280, 720, 1 };
  LabInitWith(&param);
  int right = LabGetWidth();
  int down = LabGetHeight();
  int time = 1;
  int delay = 15;
  Point p(10, 10, right, down, 0, 0, 5);
  labkey_t key = LABKEY_ENTER;


  LabSetColor(LABCOLOR_GREEN);
  while (key != LABKEY_ESC) {
    if (LabInputKeyReady()) {
      key = LabInputKey();
      switch (key)
      {
      case(LABKEY_UP):
        p.MovePoint(UP, time);
        break;
      case(LABKEY_RIGHT):
        p.MovePoint(RIGHT, time);
        break;
      case(LABKEY_DOWN):
        p.MovePoint(DOWN, time);
        break;
      case(LABKEY_LEFT):
        p.MovePoint(LEFT, time);
        break;
      default:
        break;
      }
    }
    else {
      if (delay == 0) {
        p.SlowPoint(time);
        delay = 4;
      }
      else {
        p.UpdatePoint(time);
        --delay;
      }
    }
    LabDrawRectangle(0, 0, right, down);
    LabDrawFlush();
    LabDelay(11);
    LabClear();
  }

  LabTerm();

  return 0;
}