#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QOpenError : int64_t {
		//未知
		UNKNOW = 10000,
		//初始默认值
		NONE = 0, 
		// IO 错误
		IOERROR = -5,
		//中断
		INTERRUPT = -1414092869,
		//地址无效
		URL_INVALID = -875574520,
		//格式无效
		FORMAT_INVALID = -1094995529
	};
}