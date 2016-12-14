/** demo code, compile with
 *    g++ -o mss_test measurement.cpp
 */
#include <iostream>
#include "measurement.h"

int main() {
  MSS a = MSS(2, 0.5, 0.5);
  MSS b = MSS(2, 1, 1);

  MSS c = a / b;
  std::cout << (c+2).getString() << std::endl;
  std::cout << (MSS::add(a, b, 0, 1)).getString("+/-", 5) << std::endl;
  a+=b;
  std::cout << a.getStringSqSum() << std::endl;
}

