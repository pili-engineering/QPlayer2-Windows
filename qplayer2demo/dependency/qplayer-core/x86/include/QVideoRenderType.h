#pragma once
#include <cstdint>
#include "QPlayerExport.h"


namespace QMedia {

       enum class QPLAYER_API QVideoRenderType : uint32_t {
           NONE = -1,
           //��ͨ��Ƶ
            PLANE = 0,
           //ANGULAR�� VR��Ƶ
            PANORAMA_EQUIRECT_ANGULAR = 1
       };
    
}