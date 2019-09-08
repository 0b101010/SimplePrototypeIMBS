#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

namespace util {
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
  inline TimePoint toTimePoint(const char* timeStr) {
    std::tm tm = {};
    std::stringstream ss(timeStr);
    ss >> std::get_time(&tm, "%b %d %Y %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
  }
  inline TimePoint toTimePoint(const std::string & timeStr) {
    return toTimePoint(timeStr.c_str());
  }
} /* util */
