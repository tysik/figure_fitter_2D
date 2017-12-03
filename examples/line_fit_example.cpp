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

int main()
{
  Point first_point(0.0, -0.5);
  Point second_point(2.0, 3.0);
  Line original_line(first_point, second_point);

  cout << "Preparing random pointset for line created from\n";
  cout << "points: " << first_point << " and " << second_point << endl;
  cout << "Original line: " << original_line << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i)
  {
    double x_coord = (double(i) - N / 2.0) / N;

    Point line_point = original_line.createPointFromX(x_coord);
    Point random_noise(roll(), roll());

    point_set.push_back(line_point + random_noise);
  }

  cout << "Fitting line from " << N << " samples" << endl;
  Line fitted_line;
  double variance;
  try {
    FigureFitter fitter(point_set);
    fitter.fitLine(fitted_line, variance);
  }
  catch (const exception &e) {
    cout << e.what();
    return 1;
  }

  cout << "Obtained line: " << fitted_line << endl;
  cout << "Obtained distance variance: " << variance << endl;

  //
  // Plot
  //
  vector<double> x_coords;
  vector<double> y_coords;
  for (auto &p : point_set) {
    x_coords.push_back(p.x);
    y_coords.push_back(p.y);
  }

  double x_min = -0.5 - 3.0 * std_dev;
  double x_max =  0.5 + 3.0 * std_dev;

  double y_min = original_line.createPointFromX(x_min).y - 3.0 * std_dev;
  double y_max = original_line.createPointFromX(x_max).y + 3.0 * std_dev;

  plt::title("Line fitting");
  plt::xlabel("X coordinate");
  plt::ylabel("Y coordinate");
  plt::named_plot("Sample points", x_coords, y_coords, "kx");
  plt::named_plot("Original line", {x_min, x_max},
                  {original_line.createPointFromX(x_min).y,
                   original_line.createPointFromX(x_max).y},
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
