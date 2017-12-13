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

int main() {
  Point true_point(2.5, -1.3);

  vector<Point> noisy_point_set;

  for (size_t i = 0; i < N; ++i) {
    Vec random_noise(roll(), roll());

    noisy_point_set.push_back(true_point + random_noise);
  }

  Point fitted_point;
  double variance;
  try {
    FigureFitter fitter(noisy_point_set);
    fitter.fitPoint(fitted_point, variance);
  }
  catch (const exception& e) {
    cout << e.what();
    return 1;
  }

  cout << "Results of point fitting" << endl;
  cout << "Number of samples: " << N << endl;
  cout << "Original point: " << true_point << endl;
  cout << "Fitted point: " << fitted_point << endl;
  cout << "Distance variance: " << variance << endl;

  //
  // Plot
  //
  vector<double> noisy_x_coords;
  vector<double> noisy_y_coords;
  for (auto& p : noisy_point_set) {
    noisy_x_coords.push_back(p.x);
    noisy_y_coords.push_back(p.y);
  }

  plt::title("Point fitting");
  plt::xlabel("X coordinate");
  plt::ylabel("Y coordinate");
  plt::named_plot("Sample points", noisy_x_coords, noisy_y_coords, "kx");
  plt::named_plot("True point", {true_point.x}, {true_point.y}, "go");
  plt::named_plot("Fitted point", {fitted_point.x}, {fitted_point.y}, "ro");
  plt::legend();
  plt::grid(true);
  plt::xlim(true_point.x - 3.0 * std_dev, true_point.x + 3.0 * std_dev);
  plt::ylim(true_point.y - 3.0 * std_dev, true_point.y + 3.0 * std_dev);
  plt::show();
}
