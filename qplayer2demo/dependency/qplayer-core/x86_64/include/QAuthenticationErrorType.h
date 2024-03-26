#pragma once
#include <cstdint>
#include "QPlayerExport.h"
namespace QMedia {
	enum class QPLAYER_API QAuthenticationErrorType : uint32_t {
		NONE = 0,                //鉴权出错
		NO_BASE_AUTH = 1,		 //缺少基础功能权限
		NO_VR_AUTH = 2,			 //缺少 VR 功能权限
		NO_BLIND_AUTH = 3,		 //缺少色盲功能权限
		NO_SEI_AUTH = 4,		 //缺少 SEI 功能权限
		NO_SRT_AUTH = 5			 //缺少 SRT 功能权限
	};
}
