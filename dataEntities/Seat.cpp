#include "Seat.hpp"
#include "Ticket.hpp"
#include "Theater.hpp"

namespace  dataEntities {

  Seat::Seat(std::shared_ptr<Theater> theTheater, Position thePosition)
    : theater(theTheater)
    , position(thePosition) {
  }
  
  std::shared_ptr<Ticket> Seat::getTicket() {
      return ticket;
  }
  
  std::shared_ptr<Theater> Seat::getTheater() {

    return theater;
  }
  
  void Seat::setTicket(const std::shared_ptr<Ticket> & theTicket) {
    ticket = theTicket;
  }
  
  bool Seat::isFree() {
    return !ticket->isSold();
  }

} /*dataEntities */   
