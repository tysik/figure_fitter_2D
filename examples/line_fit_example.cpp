#include <iostream>
#include <iomanip>
#include <random>

#include "../figures/line.h"
#include "../fitters/fitter.h"

using namespace std;
using namespace figfit;

const int N = 100;
const double mu = 0.0;
const double sigma2 = 1.0;

default_random_engine random_engine;
normal_distribution<double> distribution(mu, sigma2);

auto roll = [&](){ return distribution(random_engine); };

int main()
{
  double A = 1.0;
  double B = -1.0;
  double C = -1.0;

  cout << "Preparing random pointset" << endl;
  cout << "Original line: " << Line(A, B, C) << endl;
  cout << "Original distance variance: " << sqr(sigma2) + sqr(sigma2) << endl;

  vector<Point> point_set;
  for (size_t i = 0; i < N; ++i)
  {
    double x = double(i - N / 2) / N;
    double y = -(A * x + C) / B;

    point_set.push_back(Point(x + roll(), y + roll()));
  }

  cout << "--- " << endl;

  try
  {
    Fitter fitter(point_set);

    Line line;
    double variance;
    fitter.fitLine(line, variance);

    cout << "Fitting line" << endl;
    cout << "Obtained line: " << line << endl;
    cout << "Obtained distance variance: " << variance << endl;
  }
  catch (const exception &e)
  {
    cout << e.what();
  }
}
