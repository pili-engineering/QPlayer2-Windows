#pragma once
#include <cstdint>
namespace QMedia {
        enum class QUrlType : uint32_t {
            QAUDIO_AND_VIDEO = 0,
            //��������Ƶ
            QAUDIO = 1,
            //��������Ƶ
            QVIDEO = 2,
            //��
            NONE = 3
        };
}
