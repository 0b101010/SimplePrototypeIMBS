#include "TheaterMgrServer.hpp" 

#include <boost/asio.hpp>
#include <boost/bind.hpp>

TheaterMgrServer::TheaterMgr()
  : work(boost::asio::make_work_guard(context))
  , worker(boost::bind(&boost::asio::io_context::run, &context)) {
    theaterMgr.init();
  }
  
  
void TheaterMgrServer::getMovies(const CallbackFun & fun) {
  context.dispatch([fun, this]() {
    auto & movies = theaterMgr.getMovies();
    json moviesJson;
    // serialize movies => moviesJson
    fun(moviesJson);
  });
}

void TheaterMgrServer::bookSeats(const CallbackFun & fun, const std::string & TheaterShowId, const json & positionList) {
  std::vector<Seat::Position> seats
  // deserialize seats <= serialize
  unsigned showId;
  // deserialize showId <= TheaterShowId
  context.dispatch([fun, seats, showId, this]() {
    auto show = theaterMgr.getShow(showId);
    auto tickets = show->bookSeats(seats);
    auto & movies = theaterMgr.getMovies();
    json ticketsJson;
    // serialize tickets => ticketsJson
    fun(ticketsJson);
  });  
}
