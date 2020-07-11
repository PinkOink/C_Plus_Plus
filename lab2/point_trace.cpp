#include "point_trace.h"
#include "labengine.h"
#include <math.h>
#include <iostream>
#include <list>

vect::vect(int x = 0, int y = 0)
  :x(x), y(y)
{}
vect::vect(const vect &a)
  :x(a.x), y(a.y)
{}
vect vect::operator + (const vect &a) const {
  return vect(x + a.x, y + a.y);
}
vect vect::operator - (const vect &a) const {
  return vect(x - a.x, y - a.y);
}
vect vect::operator * (const double &n) const {
  return vect((int)(x * n), (int)(y * n));
}
vect &vect::operator += (const vect &a) {
  x += a.x;
  y += a.y;
  return *this;
}
vect &vect::operator -= (const vect &a) {
  x -= a.x;
  y -= a.y;
  return *this;
}
vect &vect::operator *= (const double &n) {
  x = (int)(x * n);
  y = (int)(y * n);
  return *this;
}
vect &vect::operator = (const vect &a) {
  x = a.x;
  y = a.y;
  return *this;
}
unsigned vect::VectorLength() {
  return x * x + y * y;
}



point_speed::point_speed(int x = 0, int y = 0)
  : speed(x, y)
{}
point_speed::point_speed(vect &a)
  : speed(a)
{}
unsigned point_speed::SpeedLength() {
  return speed.VectorLength();
}
vect &point_speed::CurrentSpeed() {
  return speed;
}
void point_speed::IncreaseSpeed(Direction dir) {
  switch (dir)
  {
  case UP:
    if ((speed + vect(0, -accel_positive)).VectorLength() <= speed_limit * speed_limit)
      speed += vect(0, -accel_positive);
    else
      speed *= speed_limit * speed_limit / speed.VectorLength();
    break;
  case RIGHT:
    if ((speed + vect(accel_positive, 0)).VectorLength() <= speed_limit * speed_limit)
      speed += vect(accel_positive, 0);
    else
      speed *= speed_limit * speed_limit / speed.VectorLength();
    break;
  case DOWN:
    if ((speed + vect(0, accel_positive)).VectorLength() <= speed_limit * speed_limit)
      speed += vect(0, accel_positive);
    else
      speed *= speed_limit * speed_limit / speed.VectorLength();
    break;
  case LEFT:
    if ((speed + vect(-accel_positive, 0)).VectorLength() <= speed_limit * speed_limit)
      speed += vect(-accel_positive, 0);
    else
      speed *= speed_limit * speed_limit / speed.VectorLength();
    break;
  default:
    break;
  }
}
void point_speed::DecreaseSpeed() {
  if (speed.VectorLength() != 0) {
    double coef = accel_negative / sqrt(speed.VectorLength());
    if (speed.VectorLength() > (speed * coef).VectorLength())
      speed -= speed * coef;
    else
      speed = vect(0, 0);
  }
}
void point_speed::MirrorX() {
  speed.x = -speed.x;
}
void point_speed::MirrorY() {
  speed.y = -speed.y;
}
vect point_speed::SpeedChangePosition(int time) {
  return speed * (double)time;
}


point_pos::point_pos(int x = 0, int y = 0, int right_border = 0, int down_border = 0, int left_border = 0, int up_border = 0, int radius = 0)
  : pos(x, y), r_bord(right_border), l_bord(left_border), u_bord(up_border), d_bord(down_border), radius(radius)
{}
point_pos::point_pos(vect &a, int right_border, int down_border, int left_border, int up_border, int radius)
  : pos(a), r_bord(right_border), l_bord(left_border), u_bord(up_border), d_bord(down_border), radius(radius)
{}
vect &point_pos::CurrentPos() {
  return pos;
}
void point_pos::DrawPos() {
  LabDrawCircle(pos.x, pos.y, 4);
}
Direction point_pos::ChangePos(vect &move) {
  vect new_pos(pos + move);
  Direction out_borders = NONE;

  if (new_pos.x < l_bord || new_pos.x > r_bord) {
    out_borders = new_pos.x < l_bord ? LEFT : RIGHT;
    new_pos.x = new_pos.x < l_bord ? l_bord : r_bord;
  }
  if (new_pos.y < u_bord || new_pos.y > d_bord) {
    switch (out_borders)
    {
    case NONE:
      out_borders = new_pos.y < u_bord ? UP : DOWN;
      break;
    case LEFT:
      out_borders = new_pos.y < u_bord ? UP_LEFT : DOWN_LEFT;
      break;
    case RIGHT:
      out_borders = new_pos.y < u_bord ? UP_RIGHT : DOWN_RIGHT;
      break;
    default:
      break;
    }
    new_pos.y = new_pos.y < u_bord ? u_bord : d_bord;
  }
  pos = new_pos;

  return out_borders;
}


line::line(vect pos, vect norm, int length, int br_change, int l_change) 
  :pos(pos), norm(norm), brightness(255), length(length / 4), brightness_change(br_change), length_change(l_change)
{}
void line::DrawLine() {
  int x1 = pos.x - (int)(length / 2.0 * norm.y / sqrt(norm.y * norm.y + norm.x * norm.x));
  int x2 = pos.x + (int)(length / 2.0 * norm.y / sqrt(norm.y * norm.y + norm.x * norm.x));
  int y1 = pos.y + (int)(length / 2.0 * norm.x / sqrt(norm.y * norm.y + norm.x * norm.x));
  int y2 = pos.y - (int)(length / 2.0 * norm.x / sqrt(norm.y * norm.y + norm.x * norm.x));

  LabSetColorRGB(0, (brightness - brightness_change < 0 ? brightness = 0 : brightness -= brightness_change), 0);
  LabDrawLine(x1, y1, x2, y2);
  LabSetColorRGB(0, 255, 0);
}
bool line::CheckBlack() {
  return brightness ? false : true;
}
void line::UpdateLine() {
  length += length_change;
}


Trace::Trace()
  :trace()
{}
void Trace::AddLineTrace(vect &pos, vect &speed) {
  trace.insert(trace.begin(), line(pos, speed, 2, 17, 2));
}
void Trace::UpdateTrace() {
  for (std::list<line>::iterator it = trace.begin(); it != trace.end(); ++it) {
    it->UpdateLine();
    if (it->CheckBlack()) {
      trace.erase(it, trace.end());
      break;
    }
  }
}
void Trace::DrawTrace() {
  for (std::list<line>::iterator it = trace.begin(); it != trace.end(); ++it)
    it->DrawLine();
}


Point::Point(int x, int y, int right, int down, int left, int up, int radius)
  :pos(x, y, right, down, left, up, radius), speed(0, 0), trace()
{}
void Point::MovePoint(Direction dir, int time) {
  speed.IncreaseSpeed(dir);
  UpdatePoint(time);
}
void Point::SlowPoint(int time) {
  speed.DecreaseSpeed();
  UpdatePoint(time);
}
void Point::UpdatePoint(int time) {
  if (speed.SpeedLength() != 0) {
    int leng = (int)sqrt((double)speed.SpeedChangePosition(time).VectorLength());
    for (int i = 1; i <= leng; ++i) {
      if ((speed.SpeedChangePosition(time) * (i / (double)leng)).VectorLength() != 0)
        trace.AddLineTrace(pos.CurrentPos() + speed.SpeedChangePosition(time) * (i / (double)leng), speed.SpeedChangePosition(time));
    }
  }

  trace.UpdateTrace();
  trace.DrawTrace();

  Direction out_bord = pos.ChangePos(speed.SpeedChangePosition(time));
  if (out_bord != NONE) {
    switch (out_bord)
    {
    case UP:
    case DOWN:
      speed.MirrorY();
      break;
    case RIGHT:
    case LEFT:
      speed.MirrorX();
      break;
    case UP_LEFT:
    case UP_RIGHT:
    case DOWN_LEFT:
    case DOWN_RIGHT:
      speed.MirrorX();
      speed.MirrorY();
      break;
    default:
      break;
    }
  }
  pos.DrawPos();
}