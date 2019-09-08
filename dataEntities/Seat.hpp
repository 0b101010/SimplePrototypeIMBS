#pragma once

#include <string>
#include <memory>

namespace  dataEntities {
  class Ticket;
  class Theater;
  
  class Seat : public std::enable_shared_from_this<Seat> {
  public:
    struct Position {
      int row;
      int number;
    };

    Seat(Position thePosition);
    
    std::shared_ptr<Seat> clone();
    std::shared_ptr<Ticket> getTicket();
    void setTicket(const std::shared_ptr<Ticket> & theTicket);
    std::shared_ptr<Theater> getTheater();
    const Position & getPosition() const {
      return position;
    };
    bool isFree();
  private:
    std::shared_ptr<Ticket> ticket;
    std::shared_ptr<Theater> theater;
    Position position;

  };

  inline int SeatPositionCmp( const Seat::Position & lhs, const Seat::Position & rhs) {
    int rowDiff = lhs.row - rhs.row;
    int numberDiff = lhs.number - rhs.number;
    if(rowDiff == 0) {
      return numberDiff;
    }
    return rowDiff;
  }
  
  inline bool operator==(const Seat::Position & lhs, const Seat::Position & rhs){ return SeatPositionCmp(lhs,rhs) == 0; }
  inline bool operator!=(const Seat::Position & lhs, const Seat::Position & rhs){ return SeatPositionCmp(lhs,rhs) != 0; }
  inline bool operator< (const Seat::Position & lhs, const Seat::Position & rhs){ return SeatPositionCmp(lhs,rhs) <  0; }
  inline bool operator> (const Seat::Position & lhs, const Seat::Position & rhs){ return SeatPositionCmp(lhs,rhs) >  0; }
  inline bool operator<=(const Seat::Position & lhs, const Seat::Position & rhs){ return SeatPositionCmp(lhs,rhs) <= 0; }
  inline bool operator>=(const Seat::Position & lhs, const Seat::Position & rhs){ return SeatPositionCmp(lhs,rhs) >= 0; }

} /*dataEntities */  


