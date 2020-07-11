#ifndef POINT_TRACE_H_INCLUDED__
#define POINT_TRACE_H_INCLUDED__
#pragma once
#include <iostream>
#include <list>

enum Direction {
  NONE, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT
};


class vect {
public:
  int x;
  int y;

  vect(int, int);
  vect(const vect &);

  vect operator + (const vect &) const;
  vect operator - (const vect &) const;
  vect operator * (const double &) const;
  vect &operator += (const vect &);
  vect &operator -= (const vect &);
  vect &operator *= (const double &);
  vect &operator = (const vect &);

  unsigned VectorLength();
};


class point_pos {
private:
  vect pos;
  const int radius;
  const int r_bord;
  const int l_bord;
  const int d_bord;
  const int u_bord;

public:
  point_pos(int, int, int, int, int, int, int);
  point_pos(vect &, int, int, int, int, int);

  vect &CurrentPos();
  void DrawPos();
  Direction ChangePos(vect &);
};


class point_speed {
private:
  vect speed;
  static const int accel_positive = 5;
  static const int accel_negative = 2;
  static const int speed_limit = 20;

public:
  point_speed(int, int);
  point_speed(vect &);

  unsigned SpeedLength();
  vect &CurrentSpeed();
  void IncreaseSpeed(Direction);
  void DecreaseSpeed();
  void MirrorX();
  void MirrorY();
  vect SpeedChangePosition(int time);
};




class line {
private:
  const vect pos;
  const vect norm;
  int length;
  int brightness;
  int brightness_change; //15
  int length_change; //2

public:
  line(vect pos, vect norm, int length, int br_ch, int l_ch);
  void UpdateLine();
  void DrawLine();
  bool CheckBlack();
};


class Trace {
private:
  std::list<line> trace;

public:
  Trace();
  void AddLineTrace(vect &pos, vect &speed);
  void UpdateTrace();
  void DrawTrace();
};


class Point {
private:
  point_pos pos;
  point_speed speed;
  Trace trace;

public:
  Point(int, int, int, int, int, int, int);
  void MovePoint(Direction, int);
  void SlowPoint(int);
  void UpdatePoint(int);
};

#endif