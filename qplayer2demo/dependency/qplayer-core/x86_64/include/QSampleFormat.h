#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QSampleFormat : uint32_t {
		NONE = 0,
		SIGN_INT_16
	};
}