#pragma once

#include "Theater.hpp"
#include "Movie.hpp"
#include <memory>
#include <chrono>

namespace  dataEntities {
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

  class TheaterShow : public Theater {
  public:
  TheaterShow(const Theater & theTheater, const std::shared_ptr<Movie> & theMovie, const TimePoint & theStart);
  virtual ~TheaterShow();
  
  private:
    std::shared_ptr<Movie> movie;
    TimePoint start;
  };
} /*dataEntities */
 
