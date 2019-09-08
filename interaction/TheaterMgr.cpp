#include "TheaterMgr.hpp"

#include "Theater.hpp"
#include "TheaterShow.hpp"
#include "Movie.hpp"
#include "TimeUtil.hpp"

using namespace std;
using namespace dataEntities;
using namespace util;

void TheaterMgr::init() {
  theaters.emplace_back(make_shared<Theater>( "TinyTheater", 3, 4 ));
  theaters.emplace_back(make_shared<Theater>( "SmalTheater", 9, 12 ));
  
  movies.emplace_back(make_shared<Movie>("The return of C", "A horror movie", 123));
  movies.back()->showAtTheater(*theaters[0], toTimePoint("Jan 11 2020 16:30:00"));
  movies.back()->showAtTheater(*theaters[1], toTimePoint("Jan 11 2020 19:00:00"));
  movies.back()->showAtTheater(*theaters[0], toTimePoint("Jan 11 2020 22:45:00"));
  movies.emplace_back(make_shared<Movie>("The birth of C++", "A drama documentary", 191));
  movies.back()->showAtTheater(*theaters[0], toTimePoint("Jan 11 2020 19:00:00"));
  movies.back()->showAtTheater(*theaters[1], toTimePoint("Jan 11 2020 15:30:00"));
}

