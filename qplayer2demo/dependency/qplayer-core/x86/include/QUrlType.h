#pragma once
#include <cstdint>
namespace QMedia {
        enum class QUrlType : uint32_t {
            QAUDIO_AND_VIDEO = 0,
            //仅包含音频
            QAUDIO = 1,
            //仅包含视频
            QVIDEO = 2,
            //无
            NONE = 3
        };
}
