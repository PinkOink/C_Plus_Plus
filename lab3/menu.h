#ifndef MENU_H_INCLUDED__
#define MENU_H_INCLUDED__
#pragma once
#include <stdlib.h>
#include <GL\glut.h>
#include <vector>
#include <string>

using namespace std;

class Button {
private:
  GLfloat color_r;
  GLfloat color_g;
  GLfloat color_b;

  GLfloat but_x_r;
  GLfloat but_y_u;
  GLfloat but_x_l;
  GLfloat but_y_d;

  GLfloat color_text_r;
  GLfloat color_text_g;
  GLfloat color_text_b;
  GLfloat str_x;
  GLfloat str_y;
  string text;

  int goto_window;

  bool chosen;

public:
  Button(&vector<string> res);
  void Draw(void);
  void Highlight(void);
  void Choose(void);
  void Unchoose(void);
  int GoToWindow();
};


class Window {
private:
  GLfloat color_r;
  GLfloat color_g;
  GLfloat color_b;

  vector<Button> buttons;

  int cur_but;

public:
  Window(&vector<string> res);
  void Draw(void);
  int PressKey(int key);
};


class Menu {
private:
  vector<Window> windows;
  size_t cur_w;

public:
  Menu(&vector<string> res);
  void Draw(void);
  void PressKey(int key);
};

#endif // !MENU_H_INCLUDED__
