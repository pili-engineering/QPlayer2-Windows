#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QDecoderType : uint32_t {
		NONE = 0,
		SOFTWARE = 1,
		HARDWARE = 31
	};
}