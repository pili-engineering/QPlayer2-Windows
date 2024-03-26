#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QVideoType : uint32_t {
		NONE = 0,
		YUV_420P = 1,
		RGBA = 2,
		NV21 = 3
	};
}