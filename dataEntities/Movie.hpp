#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>

namespace  dataEntities {
  class Theater;
  class TheaterShow;
  class Movie : public std::enable_shared_from_this<Movie> {
  public:
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    using TheaterShowPtr = std::shared_ptr<TheaterShow>;
    using TheaterShowList = std::vector<TheaterShowPtr>;
    
    Movie(const std::string & theTitle, const std::string & theDescription, int theLength);
    virtual ~Movie();

    const std::string & getTitle() const {
        return title;
    }
    void showAtTheater(const Theater & theater, const TimePoint & start);
    const TheaterShowList & getShows() const;
    TheaterShowList findShows(const std::string & fromTime, const std::string & at = std::string());
  private:
    std::string title;
    std::string description;
    int length;
    TheaterShowList shows;
  };
} /*dataEntities */
