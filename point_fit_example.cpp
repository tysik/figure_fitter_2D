#include <iostream>

#include "figures.h"
#include "fitter.h"

using namespace std;
using namespace figfit;

int main()
{
  vector<Point> point_set;

  point_set.push_back(Point(1.0, 0.0));
  point_set.push_back(Point(-1.0, 0.0));
  point_set.push_back(Point(0.0, -1.0));
  point_set.push_back(Point(0.0, 1.0));

//  point_set.push_back(Point(1.5, 0.0));
//  point_set.push_back(Point(-1.5, 0.0));
//  point_set.push_back(Point(0.0, -1.5));
//  point_set.push_back(Point(0.0, 1.5));

//  point_set.push_back(Point(0.5, 0.0));
//  point_set.push_back(Point(-0.5, 0.0));
//  point_set.push_back(Point(0.0, -0.5));
//  point_set.push_back(Point(0.0, 0.5));

  try
  {
    Fitter fitter(point_set);

    Point point;
    double variance;

    fitter.fitPoint(point, variance);

    cout << point.x << " " << point.y << " " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
