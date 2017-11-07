class Circle {
private:
  int x;
  int y;
  double radius;
public:
  Circle();
  Circle(int xcoord, int ycoord, double r);
  void move(int horiz, int vert);
  void setRadius(double r);
  int getX() const;
  int getY() const;
  double getRadius() const;
  double getArea() const;
  void displayCircle() const;
}; // Circle
