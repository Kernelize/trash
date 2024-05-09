#pragma once

#include <spdlog/spdlog.h>

#include "aiopp/log.hpp"

namespace spd {

class SpdLogger : public aiopp::LoggerBase {
public:
  void log(aiopp::LogSeverity severity, const std::string &message) override;
};

} // namespace spd
