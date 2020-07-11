#include "menu.h"
#include <stdlib.h>
#include <GL\glut.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

Button::Button(vector<string> res)
  :chosen(false)
{
  vector<string>::iterator it = res.begin();

  it = find(it, res.end(), "button_red");
  color_r = stod(*(++it));
  it = find(it + 1, res.end(), "button_green");
  color_g = stod(*(++it));
  it = find(it + 1, res.end(), "button_blue");
  color_b = stod(*(++it));

  it = find(it, res.end(), "button_text_red");
  color_text_r = stod(*(++it));
  it = find(it + 1, res.end(), "button_text_green");
  color_text_g = stod(*(++it));
  it = find(it + 1, res.end(), "button_text_blue");
  color_text_b = stod(*(++it));

  it = find(it, res.end(), "button_text_x");
  str_x = stod(*(++it));
  it = find(it + 1, res.end(), "button_text_y");
  str_y = stod(*(++it));
  it = find(it + 1, res.end(), "button_text");
  text = *(++it);

  it = find(it, res.end(), "button_pos_x_r");
  but_x_r = stod(*(++it));
  it = find(it, res.end(), "button_pos_y_u");
  but_y_u = stod(*(++it));
  it = find(it, res.end(), "button_pos_x_l");
  but_x_l = stod(*(++it));
  it = find(it, res.end(), "button_pos_y_d");
  but_y_d = stod(*(++it));

  it = find(it, res.end(), "button_goto");
  goto_window = stod(*(++it));
}

void Button::Draw() {
  glColor3f(color_r, color_g, color_b);

  glBegin(GL_QUADS);
  glVertex2d(but_x_r, but_y_u);
  glVertex2d(but_x_r, but_y_d);
  glVertex2d(but_x_l, but_y_d);
  glVertex2d(but_x_l, but_y_u);
  glEnd();

  glColor3f(color_text_r, color_text_g, color_text_b);
  glRasterPos2d(str_x, str_y);
  for each (char c in text) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
  }

  if (chosen)
    Highlight();
}

void Button::Highlight() {
  glColor3f(1, 0, 0);

  glBegin(GL_LINES);
  glVertex2f(but_x_r, but_y_u);
  glVertex2f(but_x_r, but_y_d);
  glVertex2f(but_x_r, but_y_d);
  glVertex2f(but_x_l, but_y_d);
  glVertex2f(but_x_l, but_y_d);
  glVertex2f(but_x_l, but_y_u);
  glVertex2f(but_x_l, but_y_u);
  glVertex2f(but_x_r, but_y_u);
  glEnd();
}

void Button::Choose() {
  chosen = true;
}
void Button::Unchoose() {
  chosen = false;
}

int Button::GoToWindow() {
  return goto_window;
}


Window::Window(vector<string> res)
  :cur_but(0)
{
  vector<string>::iterator it = res.begin();

  it = find(it, res.end(), "window_red");
  color_r = stod(*(++it));
  it = find(it + 1, res.end(), "window_green");
  color_g = stod(*(++it));
  it = find(it + 1, res.end(), "window_blue");
  color_b = stod(*(++it));

  while (it != res.end()) {
    vector<string>::iterator start = find(it, res.end(), "button_begin");
    vector<string>::iterator ending = find(start, res.end(), "button_end");
    if (start != res.end() && ending != res.end()) {
      buttons.push_back(Button(vector<string>(start, ending)));
      it = ending + 1;
    }
    else
      break;
  }

//  reverse(buttons.begin(), buttons.end());
}

void Window::Draw() {
  glColor3f(color_r, color_g, color_b);

  glBegin(GL_QUADS);
  glVertex2d(-1, -1);
  glVertex2d(-1, 1);
  glVertex2d(1, 1);
  glVertex2d(1, -1);
  glEnd();

  for (vector<Button>::iterator but = buttons.begin(); but != buttons.end(); ++but)
    but->Draw();
}

int Window::PressKey(int key) {
  if (buttons.size()) {
    buttons[cur_but].Unchoose();
    size_t buf = cur_but;
    switch (key) {
    case GLUT_KEY_UP:
      buttons[cur_but ? (--cur_but) : (cur_but = buttons.size() - 1)].Choose();
      break;
    case GLUT_KEY_DOWN:
      buttons[(cur_but == (buttons.size() - 1)) ? (cur_but = 0) : (++cur_but)].Choose();
      break;
    case 13:
      cur_but = 0;
      return buttons[buf].GoToWindow();
    default:
      break;
    }
  }
  return -1;
}


Menu::Menu(vector<string> res)
  :cur_w(0)
{
  vector<string>::iterator it = res.begin();

  while (it != res.end()) {
    vector<string>::iterator start = find(it, res.end(), "window_begin");
    vector<string>::iterator ending = find(start, res.end(), "window_end");
    if (start != res.end() && ending != res.end()) {
      windows.push_back(Window(vector<string>(start, ending)));
      it = ending + 1;
    }
    else
      break;
  }

//  reverse(windows.begin(), windows.end());
}

void Menu::Draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  windows[cur_w].Draw();
  glFlush();
}

void Menu::PressKey(int key) {
  int buf;
  if ((buf = windows[cur_w].PressKey(key)) != -1) {
    if (buf >= 0)
      cur_w = buf;
    else {
      buf = -buf - 2;
      glutInitWindowSize(100, 100);
      glutInitWindowPosition(100, 100);
      glutCreateWindow("Μενώ");
    }
  }
}