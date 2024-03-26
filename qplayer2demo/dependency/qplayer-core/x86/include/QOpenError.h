#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QOpenError : int64_t {
		//δ֪
		UNKNOW = 10000,
		//��ʼĬ��ֵ
		NONE = 0, 
		// IO ����
		IOERROR = -5,
		//�ж�
		INTERRUPT = -1414092869,
		//��ַ��Ч
		URL_INVALID = -875574520,
		//��ʽ��Ч
		FORMAT_INVALID = -1094995529
	};
}