#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {

    enum class QPLAYER_API QLogLevel : uint32_t {
        LOG_QUIT = 0,
        LOG_ERROR = 1,
        LOG_WARNING = 2,
        LOG_DEBUG = 3,
        LOG_INFO = 4,
        LOG_VERBOSE = 5
    };
}