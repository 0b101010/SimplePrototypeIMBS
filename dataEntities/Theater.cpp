#include "Theater.hpp"
#include "Ticket.hpp" 

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/range.hpp>
#include <boost/format.hpp>
#include <iostream>

namespace std {
  template <>
  struct hash<dataEntities::Seat::Position>
  {
      std::size_t operator()(const dataEntities::Seat::Position & pos) const
      {
          std::size_t seed = 0;
          boost::hash_combine(seed, pos.row);
          boost::hash_combine(seed, pos.number);
          return seed;
      }
  };  
} /* std */

using namespace boost::multi_index;

namespace  dataEntities {

  namespace tags {
    struct x_asc {};
    struct y_asc {};
    struct unordered {};
  } /* tags */

  Seat::Position getSeatPos(const std::shared_ptr<Seat> & seat) {
      return seat->getPosition();
  }
  
  int getSeatXPos(const std::shared_ptr<Seat> & seat) {
      return seat->getPosition().row;
  }

  int getSeatYPos(const std::shared_ptr<Seat> & seat) {
      return seat->getPosition().number;
  }

  struct SeatMatrix {
    multi_index_container<
      std::shared_ptr<Seat>,
      indexed_by<
        ordered_non_unique<
          tag<tags::x_asc>,
          global_fun<const std::shared_ptr<Seat>&, int, getSeatXPos>
        >,
        ordered_non_unique<
          tag<tags::y_asc>,
          global_fun<const std::shared_ptr<Seat>&, int, getSeatYPos>
        >,
        hashed_unique<
          tag<tags::unordered>,
          global_fun<const std::shared_ptr<Seat>&, Seat::Position, getSeatPos>,
          std::hash<Seat::Position>
        >
      >
    > data;    
  };
  
  Theater::Theater(const std::string & theName,
                   int noSeatsX,
                   int noSeatsY,
                   const std::string & theDescription)
    : name(theName)
    , description(theDescription)
    , noSeats(noSeatsX * noSeatsY)
    , seats(std::make_unique<SeatMatrix>()) {
      for(int x = 0; x < noSeatsX; ++x ) {
        for(int y = 0; y < noSeatsY; ++y ) {
          auto s = std::make_shared<Seat>( Seat::Position{ x, y } );
          auto t = std::make_shared<Ticket>(s);
          s->setTicket(t);
          seats->data.insert(s);
        }
      }
  }

  Theater::Theater(const Theater & other)
    : name(other.name)
    , description(other.description)
    , noSeats(other.noSeats)
    , seats(other.cloneSeatMatrix()) {
  }

  Theater::~Theater() {}
  
  std::unique_ptr<SeatMatrix> Theater::cloneSeatMatrix() const {
    auto newSeatMatrix = std::make_unique<SeatMatrix>();
    auto && view = seats->data.get<tags::unordered>();
    for(auto & seat : view) {
      auto && s = seat->clone();
      auto t = std::make_shared<Ticket>(s);
      s->setTicket(t);
      newSeatMatrix->data.insert(s);
    }
    return newSeatMatrix;
  }
  
  bool Theater::isSeatsFree(const std::vector<Seat::Position> & positionList) {
    bool allFree = true;
    auto && view = seats->data.get<tags::unordered>();
    for(auto & p : positionList) {
      auto it = view.find(p);
      if(it != view.end() && !(*it)->isFree()) {
        allFree = false;
        break;
      }
    }
    return allFree;
  }

  bool Theater::bookSeats(const std::vector<Seat::Position> & positionList) {
    if(!isSeatsFree(positionList)) {
        return false;
    }
    auto && view = seats->data.get<tags::unordered>();
    for(auto & p : positionList) {
      auto it = view.find(p);
      if(it != view.end()) {
        auto ticket = (*it)->getTicket();
        ticket->setSold(true);
      }
    }
    return true;
  }
  
  void Theater::dumpSeatMatrixRow(int row) {
    auto r = seats->data.get<tags::x_asc>().equal_range(row);
    for (auto & seat : boost::make_iterator_range(r)) {
      auto & pos = seat->getPosition();
      std::cout << boost::format("Seat %d at row %d is %s")
        % pos.number
        % pos.row
        % (seat->isFree() ?  "Free" : "Occupied")
        << std::endl;
    }
  }

  void Theater::dumpSeatMatrix() {
    auto && view = seats->data.get<tags::unordered>();
    for (auto & seat : view) {
      auto & pos = seat->getPosition();
      std::cout << boost::format("Seat %d at row %d is %s")
        % pos.number
        % pos.row
        % (seat->isFree() ?  "Free" : "Occupied")
        << std::endl;
    }
  }
} /*dataEntities */   

