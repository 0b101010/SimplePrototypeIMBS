#pragma once

#include <string>
#include <memory>

namespace  dataEntities {
  class Seat;
  
  class Ticket : public std::enable_shared_from_this<Ticket> {
  public:
    Ticket(const std::shared_ptr<Seat> & theSeat);
    virtual ~Ticket();
    
    std::shared_ptr<Seat> getSeat();
    bool isSold() {
      return sold;
    };
    void setSold(bool b) {
      sold = b;
    };
    
  private:
    bool sold;
    std::shared_ptr<Seat> seat;
  };
} /*dataEntities */ 
