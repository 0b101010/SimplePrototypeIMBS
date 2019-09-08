#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Seat.hpp"

namespace  dataEntities {
  struct SeatMatrix;
  class Theater : public std::enable_shared_from_this<Theater> {
  public:
    Theater(const std::string & theName, int noSeatsX, int noSeatsY, const std::string & theDescription = std::string());
    virtual ~Theater();
    
    const std::string & getName() const {
      return name;
    };
    const std::string & getDescription() const {
      return description;
    };
    int getNumberOfSeats() const {
      return noSeats;
    };
    
    bool isSeatsFree(const std::vector<Seat::Position> & positionList);
    bool bookSeats(const std::vector<Seat::Position> & positionList);

    void dumpSeatMatrixRow(int row = 0);
    void dumpSeatMatrix();
  protected:
    Theater(const Theater & other);
    std::unique_ptr<SeatMatrix> cloneSeatMatrix() const;
  private:
    std::string name;
    std::string description;
    int noSeats;
    std::unique_ptr<SeatMatrix> seats;
  };
} /*dataEntities */ 
