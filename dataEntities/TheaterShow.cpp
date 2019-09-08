#include "TheaterShow.hpp"


namespace  dataEntities {

  TheaterShow::TheaterShow(const Theater & theTheater,const std::shared_ptr<Movie> & theMovie, const TimePoint & theStart)
    : Theater(theTheater)
    , movie(theMovie)
    , start(theStart) {
  }

  TheaterShow::~TheaterShow() {}

} /*dataEntities */ 
