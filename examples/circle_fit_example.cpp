#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/circle.h"
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
  Point true_center(-3.0, 2.5);
  double true_radius = 4.0;
  Circle true_circle(true_center, true_radius);

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i) {
    Point random_noise(roll(), roll());
    Point circle_point(true_center.x + true_radius * cos(i),
                       true_center.y + true_radius * sin(i));

    point_set.push_back(circle_point + random_noise);
  }

  cout << "Preparing random point set around circle: " << true_circle
       << endl;

  try
  {
    cout << "Fitting circle from " << N << " samples" << endl;

    FigureFitter fitter(point_set);
    Circle fitted_circle;
    double variance;
    fitter.fitCircle(fitted_circle, variance);

    cout << "Obtained circle: " << fitted_circle << endl;
    cout << "Obtained distance variance: " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
