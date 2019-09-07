#pragma once

#include <string>
#include <memory>
#include "Seat.hpp"

namespace  dataEntities {
  struct SeatMatrix;
  class Theater : public std::enable_shared_from_this<Theater> {
  public:
    Theater(const std::string & theName, int noSeatsX, int noSeatsY, const std::string & theDescription = std::string());
    
    virtual ~Theater();
    
    std::string getName() {
      return name;
    };
    std::string getDescription() {
      return description;
    };
    int getNumberOfSeats() {
      return noSeats;
    };
    void dumpSeatMatrix(int row = 0);
  private:
    std::string name;
    std::string description;
    int noSeats;
    std::unique_ptr<SeatMatrix> seats;
  };
} /*dataEntities */ 
