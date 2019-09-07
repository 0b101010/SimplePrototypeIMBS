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
  struct hash<shared_ptr<dataEntities::Seat>>
  {
      std::size_t operator()(const shared_ptr<dataEntities::Seat> & seat) const
      {
          std::size_t seed = 0;
          boost::hash_combine(seed, seat->getPosition().row);
          boost::hash_combine(seed, seat->getPosition().number);
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
          identity<std::shared_ptr<Seat>>,
          std::hash<std::shared_ptr<Seat>>
        >
      >
    > data;    
  };
  
  Theater::Theater(const std::string & theName,
                   int noSeatsX,
                   int noSeatsY,
                   const std::string & theDescription)
    : name()
    , description(theDescription)
    , noSeats(noSeatsX * noSeatsY)
    , seats(std::make_unique<SeatMatrix>()) {
      for(int x = 0; x < noSeatsX; ++x ) {
        for(int y = 0; y < noSeatsY; ++y ) {
          auto s = std::make_shared<Seat>(nullptr, Seat::Position{ x, y } );
          auto t = std::make_shared<Ticket>(s);
          s->setTicket(t);
          seats->data.insert(s);
        }
      }
  }
  
  Theater::~Theater() {}
  
  void Theater::dumpSeatMatrix(int row) {
    auto r = seats->data.get<tags::x_asc>().equal_range(row);
    for (auto& seat : boost::make_iterator_range(r)) {
      auto & pos = seat->getPosition();
      std::cout << boost::format("Seat %d at row %d is %s")
        % pos.number
        % pos.row
        % (seat->isFree() ?  "Free" : "Occupied")
        << std::endl;
    }
  }
} /*dataEntities */   

