#pragma once
#include <stdint.h>
#include "QPlayerExport.h"

namespace QMedia {

	namespace QPlayerSetting {
		enum class QPLAYER_API QPlayerDecoder : uint16_t
		{
			//自动选择
			QPLAYER_DECODER_SETTING_AUTO = 0,
			//硬解优先
			QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY = 1,
			//软解优先
			QPLAYER_DECODER_SETTING_SOFT_PRIORITY = 2,
			//混解优先
			QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY = 3
		};

		/**
	 * Seek 方式
	 */
		enum class  QPlayerSeek : uint16_t {
			//关键帧seek，每次seek 都seek到离目标位置向前的最近的一个关键帧，耗时少
			QPLAYER_SEEK_SETTING_NORMAL = 0,
			//精准seek，耗时比关键帧seek多，且耗时和视频的gop间隔的大小成正比
			QPLAYER_SEEK_SETTING_ACCURATE = 1
		};

		enum class  QPlayerStart : uint16_t {
			//起播播放
			QPLAYER_START_SETTING_PLAYING = 0,
			//起播暂停在首帧
			QPLAYER_START_SETTING_PAUSE = 1,
		};

		enum class  QPlayerRenderRatio : uint16_t {
			//自动
			QPLAYER_RATIO_SETTING_AUTO = 1,
			//拉升
			QPLAYER_RATIO_SETTING_STRETCH = 2,
			//铺满
			QPLAYER_RATIO_SETTING_FULL_SCREEN = 3,
			//16:9
			QPLAYER_RATIO_SETTING_16_9 = 4,
			//4:3
			QPLAYER_RATIO_SETTING_4_3 = 5

		};

		/**
	 * 色盲模式
	 */
		enum class  QPlayerBlind : uint16_t {
			//无
			QPLAYER_BLIND_SETTING_NONE = 0,
			//红色盲
			QPLAYER_BLIND_SETTING_RED = 1,
			//绿色盲
			QPLAYER_BLIND_SETTING_GREEN = 2,
			//蓝色盲
			QPLAYER_BLIND_SETTING_BLUE = 3
		};
	}
}