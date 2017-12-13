#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/circle.h"
#include "../figure_fitter.h"
#include "matplotlibcpp.h"

using namespace std;
using namespace figfit;
namespace plt = matplotlibcpp;

const int N = 100;
const double mean = 0.0;
const double std_dev = 0.2;

default_random_engine random_engine;
normal_distribution<double> distribution(mean, std_dev);

auto roll = [&](){ return distribution(random_engine); };

int main() {
  Point true_center(-3.0, 2.5);
  double true_radius = 4.0;
  Circle true_circle(true_center, true_radius);

  vector<Point> true_point_set;
  vector<Point> noisy_point_set;

  for (size_t i = 0; i < N; ++i) {
    Vec random_noise(roll(), roll());

    double theta = -M_PI + 2.0 * M_PI * (double) i / (double) N;
    Point circle_point = true_circle.createPointFromAngle(theta);

    true_point_set.push_back(circle_point);
    noisy_point_set.push_back(circle_point + random_noise);
  }

  Circle fitted_circle;
  double variance;
  try {
    FigureFitter fitter(noisy_point_set);
    fitter.fitCircle(fitted_circle, variance);
  }
  catch (const exception& e) {
    cout << e.what();
    return 1;
  }

  cout << "Results of circle fitting" << endl;
  cout << "Number of samples: " << N << endl;
  cout << "Original circle: " << true_circle << endl;
  cout << "Fitted circle: " << fitted_circle << endl;
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

  vector<double> true_circ_x_coords;
  vector<double> true_circ_y_coords;
  for (size_t i = 0; i <= 100; ++i) {
    double angle = -M_PI + 2.0 * M_PI * i / 100.0;
    Point p = true_circle.createPointFromAngle(angle);

    true_circ_x_coords.push_back(p.x);
    true_circ_y_coords.push_back(p.y);
  }

  vector<double> fitted_circ_x_coords;
  vector<double> fitted_circ_y_coords;
  for (size_t i = 0; i <= 100; ++i) {
    double angle = -M_PI + 2.0 * M_PI * (double) i / (double) N;
    Point p = fitted_circle.createPointFromAngle(angle);

    fitted_circ_x_coords.push_back(p.x);
    fitted_circ_y_coords.push_back(p.y);
  }

  double x_min = true_center.x - true_radius - 3.0 * std_dev;
  double x_max = true_center.x + true_radius + 3.0 * std_dev;

  double y_min = true_center.y - true_radius - 3.0 * std_dev;
  double y_max = true_center.y + true_radius + 3.0 * std_dev;

  plt::title("Circle fitting");
  plt::xlabel("X coordinate");
  plt::ylabel("Y coordinate");
  plt::named_plot("Sample points", noisy_x_coords, noisy_y_coords, "kx");
  plt::named_plot("True circle",
                  true_circ_x_coords,
                  true_circ_y_coords,
                  "g-");

  plt::named_plot("Fitted circle",
                  fitted_circ_x_coords,
                  fitted_circ_y_coords,
                  "r-");

  plt::named_plot("True center",
                 {true_circle.center().x},
                 {true_circle.center().y},
                 "go");

  plt::named_plot("Fitted center",
                 {fitted_circle.center().x},
                 {fitted_circle.center().y},
                 "ro");

  plt::legend();
  plt::grid(true);
  plt::xlim(x_min, x_max);
  plt::ylim(y_min, y_max);
  plt::show();
}
