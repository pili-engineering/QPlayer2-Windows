#pragma once
#include <stdint.h>
#include "QPlayerExport.h"

namespace QMedia {

	namespace QPlayerSetting {
		enum class QPLAYER_API QPlayerDecoder : uint16_t
		{
			//�Զ�ѡ��
			QPLAYER_DECODER_SETTING_AUTO = 0,
			//Ӳ������
			QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY = 1,
			//�������
			QPLAYER_DECODER_SETTING_SOFT_PRIORITY = 2,
			//�������
			QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY = 3
		};

		/**
	 * Seek ��ʽ
	 */
		enum class  QPlayerSeek : uint16_t {
			//�ؼ�֡seek��ÿ��seek ��seek����Ŀ��λ����ǰ�������һ���ؼ�֡����ʱ��
			QPLAYER_SEEK_SETTING_NORMAL = 0,
			//��׼seek����ʱ�ȹؼ�֡seek�࣬�Һ�ʱ����Ƶ��gop����Ĵ�С������
			QPLAYER_SEEK_SETTING_ACCURATE = 1
		};

		enum class  QPlayerStart : uint16_t {
			//�𲥲���
			QPLAYER_START_SETTING_PLAYING = 0,
			//����ͣ����֡
			QPLAYER_START_SETTING_PAUSE = 1,
		};

		enum class  QPlayerRenderRatio : uint16_t {
			//�Զ�
			QPLAYER_RATIO_SETTING_AUTO = 1,
			//����
			QPLAYER_RATIO_SETTING_STRETCH = 2,
			//����
			QPLAYER_RATIO_SETTING_FULL_SCREEN = 3,
			//16:9
			QPLAYER_RATIO_SETTING_16_9 = 4,
			//4:3
			QPLAYER_RATIO_SETTING_4_3 = 5

		};

		/**
	 * ɫäģʽ
	 */
		enum class  QPlayerBlind : uint16_t {
			//��
			QPLAYER_BLIND_SETTING_NONE = 0,
			//��ɫä
			QPLAYER_BLIND_SETTING_RED = 1,
			//��ɫä
			QPLAYER_BLIND_SETTING_GREEN = 2,
			//��ɫä
			QPLAYER_BLIND_SETTING_BLUE = 3
		};
	}
}