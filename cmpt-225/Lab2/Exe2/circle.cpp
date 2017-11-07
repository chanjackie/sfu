// Circle.cpp file
// Description: This class models a Circle
// Author: Jackie Chan
// Creation Date: May 18, 2017

#include <iostream>
#include "Circle.h"
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

Circle::Circle() : x(0), y(0), radius(10.0) {

}

Circle::Circle(int xcoord, int ycoord, double r) {
  if (r<=0.0)
    radius = 10.0;
  else
    radius = r;
  x = xcoord;
  y = ycoord;
}

void Circle::move(int horiz, int vert) {
  x = x + horiz;
  y = y + vert;
}

void Circle::setRadius(double r) {
  if (r < 0.0)
    radius = 10.0;
  else
    radius = r;
}

int Circle::getX() const {
  return x;
}

int Circle::getY() const {
  return y;
}

double Circle::getRadius() const {
  return radius;
}

double Circle::getArea() const {
  return M_PI*radius*radius;
}

void Circle::displayCircle() const {
  cout << "radius " << radius << " at point x = " << x << ", y = " << y << endl;
}



//
