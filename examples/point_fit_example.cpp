#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/point.h"
#include "../fitters/fitter.h"

using namespace std;
using namespace figfit;

const int N = 100;            // Sample size
const double mu = 0.0;        // Noise mean value
const double std_dev = 0.5;   // Noise standard deviation
const double mean_x = 2.5;    // Expected X value
const double mean_y = -1.5;   // Expected Y value

default_random_engine random_engine;
normal_distribution<double> distribution(mu, pow(std_dev, 2.0));

double roll_dice()
{
  return distribution(random_engine);
}

Point generate_point()
{
  return Point(mean_x + roll_dice(), mean_y + roll_dice());
}

int main()
{
  cout << "Preparing random point set around original point: "
       << Point(mean_x, mean_y) << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i)
    point_set.push_back(generate_point());

  try
  {
    cout << "Fitting point set from " << N << " samples" << endl;

    Fitter fitter(point_set);
    Point point;
    double variance;
    fitter.fitPoint(point, variance);

    cout << "Obtained point: " << point << endl;
    cout << "Obtained distance variance: " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
