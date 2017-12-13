#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/line.h"
#include "../figure_fitter.h"
#include "matplotlibcpp.h"

using namespace std;
using namespace figfit;
namespace plt = matplotlibcpp;

const int N = 100;
const double mean = 0.0;
const double std_dev = 0.05;

default_random_engine random_engine;
normal_distribution<double> distribution(mean, std_dev);

auto roll = [&](){ return distribution(random_engine); };

int main() {
  Point first_point(0.0, -0.5);
  Point second_point(2.0, 3.0);
  Line true_line(first_point, second_point);

  vector<Point> noisy_point_set;

  for (size_t i = 0; i < N; ++i) {
    Vec random_noise(roll(), roll());

    double x_coord = (double(i) - N / 2.0) / N;
    Point line_point = true_line.createPointFromX(x_coord);

    noisy_point_set.push_back(line_point + random_noise);
  }

  Line fitted_line;
  double variance;
  try {
    FigureFitter fitter(noisy_point_set);
    fitter.fitLine(fitted_line, variance);
  }
  catch (const exception& e) {
    cout << e.what();
    return 1;
  }

  cout << "Results of line fitting" << endl;
  cout << "Number of samples: " << N << endl;
  cout << "Original line: " << true_line << endl;
  cout << "Fitted line: " << fitted_line << endl;
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

  double x_min = -0.5 - 3.0 * std_dev;
  double x_max =  0.5 + 3.0 * std_dev;

  double y_min = true_line.createPointFromX(x_min).y - 3.0 * std_dev;
  double y_max = true_line.createPointFromX(x_max).y + 3.0 * std_dev;

  plt::title("Line fitting");
  plt::xlabel("X coordinate");
  plt::ylabel("Y coordinate");
  plt::named_plot("Sample points", noisy_x_coords, noisy_y_coords, "kx");
  plt::named_plot("True line", {x_min, x_max},
                  {true_line.createPointFromX(x_min).y,
                   true_line.createPointFromX(x_max).y},
                  "g-");

  plt::named_plot("Fitted line", {x_min, x_max},
                  {fitted_line.createPointFromX(x_min).y,
                   fitted_line.createPointFromX(x_max).y},
                  "r-");

  plt::legend();
  plt::grid(true);
  plt::xlim(x_min, x_max);
  plt::ylim(y_min, y_max);
  plt::show();
}
