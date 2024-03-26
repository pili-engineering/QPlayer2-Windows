#pragma once
#include <cstdint>
#include "QPlayerExport.h"


namespace QMedia {

       enum class QPLAYER_API QVideoRenderType : uint32_t {
           NONE = -1,
           //普通视频
            PLANE = 0,
           //ANGULAR类 VR视频
            PANORAMA_EQUIRECT_ANGULAR = 1
       };
    
}