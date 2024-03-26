#pragma once
#include <cstdint>
namespace QMedia {
    enum class QUrlMethod : uint32_t {
        NORMAL = 0,
        RTSP_TCP = 1,
        RTSP_UDP = 2,
    };
}
