#include "Theater.hpp"

#include <iostream>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

int main() {

  dataEntities::Theater t01( "TestTheater01", 3, 4 );
  t01.dumpSeatMatrix(2);

  return 0;
}
