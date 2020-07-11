#include <stdlib.h>
#include <GL/glut.h> 
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "menu.h"

using namespace std;

Menu *p;

void Draw() {
  p->Draw();
}

void ProcessSpecialKeys(int key, int x, int y) {
  p->PressKey(key);
}

void ProcessRegularKeys(unsigned char key, int x, int y) {
  p->PressKey(key);
}

int main(int argc, char **argv)
{
  ifstream in("in.txt");//(argv[1]);

  string str;
  vector<string> words;

  while (getline(in, str)) {
    istringstream strstream(str);
    string word;

    while (strstream >> word) {
      words.push_back(word);
    }
  }

  Menu m(words);
  p = &m;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Μενώ");

  glutDisplayFunc(Draw);
  glutIdleFunc(Draw);
  glutSpecialFunc(ProcessSpecialKeys);
  glutKeyboardFunc(ProcessRegularKeys);

  glutInitWindowSize(110, 100);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Μενώ2");

  glutDisplayFunc(Draw);
  glutIdleFunc(Draw);
  glutSpecialFunc(ProcessSpecialKeys);
  glutKeyboardFunc(ProcessRegularKeys);

  glutMainLoop();

  return 0;
}