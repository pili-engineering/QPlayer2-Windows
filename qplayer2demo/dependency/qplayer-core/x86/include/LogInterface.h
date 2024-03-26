#pragma once

#include "QPlayerExport.h"
#include <string>
#include "QLogLevel.h"
namespace QMedia {
	class LogInterface {
	public:
		LogInterface() = default;

		virtual ~LogInterface() = default;

		LogInterface(const LogInterface&) = delete;

		LogInterface(LogInterface&&) = delete;

		LogInterface& operator=(const LogInterface&) = delete;

		LogInterface& operator=(LogInterface&&) = delete;

		virtual void log(QMedia::QLogLevel level, const std::string& message) = 0;
	};
}
