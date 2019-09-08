#include "Theater.hpp"
#include "TheaterShow.hpp"
#include "Movie.hpp"
#include "TimeUtil.hpp"

#include <iostream>
#include <memory>
#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace dataEntities;
using namespace util;

int main() {

  Theater t01( "TestTheater01", 3, 4 );
  t01.dumpSeatMatrix();
  cout << "********************************************" << endl;

  auto m1 = std::make_shared<Movie>("The return of C", "A horror movie", 123);  
  auto start = toTimePoint("Jan 11 2020 17:35:00");
  TheaterShow ts01(t01, m1, start);
  
  std::vector<Seat::Position> seats;
  seats.push_back(Seat::Position{1,1});
  seats.push_back(Seat::Position{1,2});
  seats.push_back(Seat::Position{2,2});
  ts01.bookSeats(seats);
  ts01.dumpSeatMatrix();
  cout << "********************************************" << endl;
  
  t01.dumpSeatMatrix();
  return 0;
}
