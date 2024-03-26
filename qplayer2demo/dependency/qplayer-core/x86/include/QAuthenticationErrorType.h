#pragma once
#include <cstdint>
#include "QPlayerExport.h"
namespace QMedia {
	enum class QPLAYER_API QAuthenticationErrorType : uint32_t {
		NONE = 0,                //��Ȩ����
		NO_BASE_AUTH = 1,		 //ȱ�ٻ�������Ȩ��
		NO_VR_AUTH = 2,			 //ȱ�� VR ����Ȩ��
		NO_BLIND_AUTH = 3,		 //ȱ��ɫä����Ȩ��
		NO_SEI_AUTH = 4,		 //ȱ�� SEI ����Ȩ��
		NO_SRT_AUTH = 5			 //ȱ�� SRT ����Ȩ��
	};
}
