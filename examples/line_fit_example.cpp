#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/line.h"
#include "../fitters/fitter.h"

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
  Point first_point(0.0, 1.0);
  Point last_point(1.0, 2.0);
  Line line(first_point, last_point);

  cout << "Preparing random pointset for line created from\n";
  cout << "points: " << first_point << " and " << last_point << endl;
  cout << "Original line: " << line << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i)
  {
    double x_coord = (double(i) - N / 2.0);

    Point line_point = line.createPointFromX(x_coord);
    Point random_noise(roll(), roll());

    point_set.push_back(line_point + random_noise);
  }

  try
  {
    Fitter fitter(point_set);
    Line fitted_line;
    double variance;

    cout << "Fitting line" << endl;
    fitter.fitLine(fitted_line, variance);

    cout << "Obtained line: " << fitted_line << endl;
    cout << "Obtained distance variance: " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
