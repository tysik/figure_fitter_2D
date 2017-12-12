#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/point.h"
#include "../figure_fitter.h"
#include "matplotlibcpp.h"

using namespace std;
using namespace figfit;

namespace plt = matplotlibcpp;

const int N = 100;
const double mean = 0.0;
const double std_dev = 0.1;

default_random_engine random_engine;
normal_distribution<double> distribution(mean, std_dev);

auto roll = [&](){ return distribution(random_engine); };

int main()
{
  Point original_point(2.5, -1.3);

  cout << "Preparing random point set around original point: " <<
          original_point << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i) {
    Point random_noise(roll(), roll());
    point_set.push_back(original_point + random_noise);
  }

  cout << "Fitting point from " << N << " samples" << endl;
  Point fitted_point;
  double variance;
  try
  {
    FigureFitter fitter(point_set);
    fitter.fitPoint(fitted_point, variance);
  }
  catch (const exception& e)
  {
    cout << e.what();
    return 1;
  }

  cout << "Obtained point: " << fitted_point << endl;
  cout << "Obtained distance variance: " << variance << endl;

  //
  // Plot
  //
  vector<double> x_coords;
  vector<double> y_coords;
  for (auto& p : point_set) {
    x_coords.push_back(p.x);
    y_coords.push_back(p.y);
  }

  plt::title("Point fitting");
  plt::xlabel("X coordinate");
  plt::ylabel("Y coordinate");
  plt::named_plot("Sample points", x_coords, y_coords, "kx");
  plt::named_plot("Original point", {original_point.x}, {original_point.y}, "go");
  plt::named_plot("Fitted point", {fitted_point.x}, {fitted_point.y}, "ro");
  plt::legend();
  plt::grid(true);
  plt::xlim(original_point.x - 3.0 * std_dev, original_point.x + 3.0 * std_dev);
  plt::ylim(original_point.y - 3.0 * std_dev, original_point.y + 3.0 * std_dev);
  plt::show();
}
