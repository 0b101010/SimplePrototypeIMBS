#pragma once

#include "TheaterMgr.hpp"

#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <thread>

#include <boost/asio/io_context.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include "Movie.hpp"
#include "Seat.hpp"
#include "TheaterShow.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class TheaterMgrServer {
public:
  TheaterMgrServer();
  using CallbackFun = std::function<void(json)>;
  void getMovies(const CallbackFun & fun);
  void findShows(const CallbackFun & fun, const std::string & movieTitle, const std::string & fromTime, const std::string & at);
  void seats(const CallbackFun & fun, const std::string & TheaterShowId);
  void isSeatsFree(const CallbackFun & fun, const std::string & TheaterShowId, const json & positionList);
  void bookSeats(const CallbackFun & fun, const std::string & TheaterShowId, const json & positionList);
private:
  boost::asio::io_context context;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work;
  std::thread worker;
  TheaterMgr theaterMgr;
}
