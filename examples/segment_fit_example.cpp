#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/segment.h"
#include "../fitters/figure_fitter.h"

using namespace std;
using namespace figfit;

const int N = 100;
const double mu = 0.0;
const double var = 0.01;

default_random_engine random_engine;
normal_distribution<double> distribution(mu, var);

auto roll = [&](){ return distribution(random_engine); };

int main()
{
  Point first_point(-2.0, 1.0);
  Point second_point(3.0, 7.0);
  Segment segment(first_point, second_point);

  cout << "Preparing random pointset for segment" << endl;
  cout << "Original segment: " << segment << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i)
  {
    double x_coord = i * (second_point.x - first_point.x) / N + first_point.x;

    Point line_point = segment.createPointFromX(x_coord);
    Point random_noise(roll(), roll());

    point_set.push_back(line_point + random_noise);
  }

  try
  {
    FigureFitter fitter(point_set);
    Segment fitted_segment;
    double variance;

    cout << "Fitting segment from " << N << " samples" << endl;
    fitter.fitSegment(fitted_segment, variance);

    cout << "Obtained segment: " << fitted_segment << endl;
    cout << "Obtained distance variance: " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
