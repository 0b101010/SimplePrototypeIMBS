#include "Ticket.hpp" 
#include "Seat.hpp"

namespace  dataEntities {
  Ticket::Ticket(const std::shared_ptr<Seat> & theSeat)
    : sold(false)
    , seat(theSeat) {
  }

 Ticket::~Ticket() {}
 
  std::shared_ptr<Seat> Ticket::getSeat() {
    return seat;
  }
} /*dataEntities */ 
