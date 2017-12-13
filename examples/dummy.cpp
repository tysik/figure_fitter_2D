#include <iostream>

#include "../figures/vec.h"

using namespace std;
using namespace figfit;

int main() {
  Vec v1(1.0, -1.0);
  Vec v2(1.0, 1.0);
  Vec normal(0.0, 1.0);

  cout << "v1: " << v1 << endl;
  cout << "v2: " << v2 << endl;
  cout << "normal: " << normal << endl;

  cout << endl;

  cout << "dot(v1, v2) " << dot(v1, v2) << endl;
  cout << "cross(v1, v2) " << cross(v1, v2) << endl;

  cout << "v1.dot(v2) " << v1.dot(v2) << endl;
  cout << "v1.cross(v2) " << v1.cross(v2) << endl;

  cout << endl;

  cout << "normalized(v1) " << normalized(v1) << endl;
  cout << "normalized(v2) " << normalized(v2) << endl;

  cout << "v1.normalized() " << v1.normalized() << endl;
  cout << "v2.normalized() " << v2.normalized() << endl;

  cout << endl;

  cout << "rotated(v1, pi/4) " << rotated(v1, M_PI / 4.0) << endl;
  cout << "rotated(v2, pi/4) " << rotated(v2, M_PI / 4.0) << endl;

  cout << "v1.rotated(pi/4) " << v1.rotated(M_PI / 4.0) << endl;
  cout << "v2.rotated(pi/4) " << v2.rotated(M_PI / 4.0) << endl;

  cout << endl;

  cout << "rotated90(v1) " << rotated90(v1) << endl;
  cout << "rotated90(v2) " << rotated90(v2) << endl;

  cout << "v1.rotated90() " << v1.rotated90() << endl;
  cout << "v2.rotated90() " << v2.rotated90() << endl;

  cout << endl;

  cout << "reflected(v1, normal) " << reflected(v1, normal) << endl;
  cout << "reflected(v2, normal) " << reflected(v2, normal) << endl;

  cout << "v1.reflected(normal) " << v1.reflected(normal) << endl;
  cout << "v2.reflected(normal) " << v2.reflected(normal) << endl;

  return 0;
}
