#pragma once

#include <memory>
#include <vector>

namespace  dataEntities {
  class Movie;
  class Theater;
} /*dataEntities */ 

class TheaterMgr {
public:
  using MovieList = std::vector<std::shared_ptr<dataEntities::Movie>>;
  using TheaterList = std::vector<std::shared_ptr<dataEntities::Theater>>;
  void init();
  
  const MovieList & getMovies() {
    return movies;
  };
  
private:
  MovieList movies;
  TheaterList theaters;
};
