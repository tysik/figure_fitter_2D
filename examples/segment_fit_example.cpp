#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/segment.h"
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
  Point first_point(-2.0, 1.0);
  Point second_point(3.0, 7.0);
  Segment true_segment(first_point, second_point);

  vector<Point> noisy_point_set;

  for (size_t i = 0; i < N; ++i) {
    Vec random_noise(roll(), roll());

    double t = (double)i / (double)N;
    Point segment_point = true_segment.createPointFromParam(t);

    noisy_point_set.push_back(segment_point + random_noise);
  }

  Segment fitted_segment;
  double variance;
  try {
    FigureFitter fitter(noisy_point_set);
    fitter.fitSegment(fitted_segment, variance);
  }
  catch (const exception& e) {
    cout << e.what();
  }

  cout << "Results of segment fitting" << endl;
  cout << "Number of samples: " << N << endl;
  cout << "Original segment: " << true_segment << endl;
  cout << "Fitted segment: " << fitted_segment << endl;
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

  double x_min = fitted_segment.startPoint().x - 3.0 * std_dev;
  double x_max = fitted_segment.endPoint().x + 3.0 * std_dev;

  double y_min = fitted_segment.startPoint().y - 3.0 * std_dev;
  double y_max = fitted_segment.endPoint().y + 3.0 * std_dev;

  plt::title("Segment fitting");
  plt::xlabel("X coordinate");
  plt::ylabel("Y coordinate");
  plt::named_plot("Sample points", noisy_x_coords, noisy_y_coords, "kx");
  plt::named_plot("True segment",
               {true_segment.startPoint().x, true_segment.endPoint().x},
               {true_segment.startPoint().y, true_segment.endPoint().y},
               "g-");

  plt::named_plot("Fitted segment",
              {fitted_segment.startPoint().x, fitted_segment.endPoint().x},
              {fitted_segment.startPoint().y, fitted_segment.endPoint().y},
              "r-");

  plt::legend();
  plt::grid(true);
  plt::xlim(x_min, x_max);
  plt::ylim(y_min, y_max);
  plt::show();
}
