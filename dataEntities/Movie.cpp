#include "Movie.hpp"

#include "Theater.hpp"
#include "TheaterShow.hpp"
#include "TimeUtil.hpp"

#include <algorithm>

using namespace std;
using namespace util;

namespace  dataEntities {

  Movie::Movie(const std::string & theTitle, const std::string & theDescription, int theLength)
    : title(theTitle)
    , description(theDescription)
    , length(theLength) {
    }
  Movie::~Movie() {
  }
  
  void Movie::showAtTheater(const Theater & theater, const TimePoint & start) {
    shows.emplace_back(make_shared<TheaterShow>(theater, shared_from_this(), start));
  }

  const Movie::TheaterShowList &  Movie::getShows() const {
    return shows;
  }
  
  Movie::TheaterShowList Movie::findShows(const std::string & fromTime, const std::string & at) {
    auto t = toTimePoint(fromTime);
    TheaterShowList to;
    copy_if(
      shows.begin(),
      shows.end(),
      back_inserter(to),
      [&t, &at] (auto & p) { return (p->getStartTime() >= t) && (at.empty() || p->getName() == at);}
    );
    return to;
  }
} /*dataEntities */   
