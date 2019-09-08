#include "Theater.hpp"
#include "TheaterShow.hpp"
#include "Movie.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace dataEntities;

int main() {

  Theater t01( "TestTheater01", 3, 4 );
  t01.dumpSeatMatrix();
  cout << "********************************************" << endl;

  auto m1 = std::make_shared<Movie>(Movie{"The return of C", "A hooror movie", 123});  
  std::tm tm = {};
  std::stringstream ss("Jan 11 2020 17:35:00");
  ss >> std::get_time(&tm, "%b %d %Y %H:%M:%S");
  auto start = chrono::system_clock::from_time_t(std::mktime(&tm));
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
