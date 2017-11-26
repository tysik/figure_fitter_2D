#include <iostream>

#include "figures.h"
#include "fitter.h"

using namespace std;
using namespace figfit;

int main()
{
  vector<Point> circle_point_set;
//  // x0 = 0, y0 = 0, r = 1
//  circle_point_set.push_back(Point(1.0, 0.0));
//  circle_point_set.push_back(Point(-1.0, 0.0));
//  circle_point_set.push_back(Point(0.0, -1.0));
//  circle_point_set.push_back(Point(0.0, 1.0));

//  // x0 = 5, y0 = 5, r = 1
//  circle_point_set.push_back(Point(6.0, 5.0));
//  circle_point_set.push_back(Point(4.0, 5.0));
//  circle_point_set.push_back(Point(5.0, 4.0));
//  circle_point_set.push_back(Point(5.0, 6.0));

  // x0 = 10, y0 = -5, r = 2.5
  circle_point_set.push_back(Point(12.5, -5.0));
  circle_point_set.push_back(Point(7.5, -5.0));
  circle_point_set.push_back(Point(10.0, -7.5));
  circle_point_set.push_back(Point(10.0, -2.5));

  try
  {
    Fitter circle_fit(circle_point_set);
    Circle circ = circle_fit.fitCircle();
    cout << circ.center.x << " " << circ.center.y << " " << circ.radius << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }

  return 0;
}
