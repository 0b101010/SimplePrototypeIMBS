#include "Seat.hpp"
#include "Ticket.hpp"
#include "Theater.hpp"

namespace  dataEntities {

  Seat::Seat(Position thePosition)
    : position(thePosition) {
  }
  
  std::shared_ptr<Seat> Seat::clone() {
      return std::make_shared<Seat>(position);
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
