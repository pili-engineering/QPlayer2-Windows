#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QShootVideoType : uint32_t {
		//初始默认值
		NONE = 0,
		//jepg 格式
		JEPG = 1
	};
}