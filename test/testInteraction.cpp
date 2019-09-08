#include "TheaterMgr.hpp"

#include <iostream>
#include <memory>
#include <algorithm>

#include "Movie.hpp"
#include "Seat.hpp"
#include "TheaterShow.hpp"

using namespace std;
using namespace dataEntities;

int main() {

  string movieName1("The birth of C++");
  string movieName2("The return of C");
  TheaterMgr mgr;
  mgr.init();
  auto & movies = mgr.getMovies();
  auto it = find_if(
      movies.begin(),
      movies.end(),
      [&movieName1] (auto & p) { return p->getTitle() == movieName1;}
    );
  auto shows1 = (*it)->findShows("Jan 11 2020 18:00:00");
  std::vector<Seat::Position> seats;
  seats.push_back(Seat::Position{1,1});
  seats.push_back(Seat::Position{1,2});
  seats.push_back(Seat::Position{2,2});
  bool isFree = shows1.front()->isSeatsFree(seats);
  if(isFree) {
    bool booked = shows1.front()->bookSeats(seats);
  }
  
  cout << movieName1 << " at " << shows1.front()->getName() << endl;
  shows1.front()->dumpSeatMatrix();
  cout << "********************************************" << endl;
  
  auto it2 = find_if(
    movies.begin(),
    movies.end(),
    [&movieName2] (auto & p) { return p->getTitle() == movieName2;}
  );
  
  auto shows2 = (*it2)->findShows("Jan 11 2020 18:00:00", "SmalTheater");
  std::vector<Seat::Position> seats2;
  seats2.push_back(Seat::Position{3,6});
  seats2.push_back(Seat::Position{3,7});
  bool isFree2 = shows2.front()->isSeatsFree(seats2);
  if(isFree2) {
    bool booked = shows2.front()->bookSeats(seats2);
  }
  
  cout << movieName2 << " at " << shows2.front()->getName() << endl;
  shows2.front()->dumpSeatMatrixRow(3);
  cout << "********************************************" << endl;
  return 0;
}
