#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/point.h"
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
  Point point(2.5, -1.3);

  cout << "Preparing random point set around original point: " << point << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i) {
    Point random_noise(roll(), roll());
    point_set.push_back(point + random_noise);
  }

  try
  {
    cout << "Fitting point from " << N << " samples" << endl;

    Fitter fitter(point_set);
    Point fitted_point;
    double variance;
    fitter.fitPoint(fitted_point, variance);

    cout << "Obtained point: " << fitted_point << endl;
    cout << "Obtained distance variance: " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
