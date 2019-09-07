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

    Seat(std::shared_ptr<Theater> theTheater, Position thePosition);
    
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
} /*dataEntities */  
