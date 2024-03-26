#pragma once
#include <cstdint>
#include "QPlayerExport.h"

namespace QMedia {
	enum class QPLAYER_API QPlayerState : uint32_t {
		NONE = 0,//初始状态
		INIT = 1,//播放器开始创建各种对象 没有对应的state 创建完对象就上报这个状态
		PREPARE = 2,//开始拉视频数据解码变换等，重新换地址后，都走这个状态
		PLAYING = 4,//播放中
		PAUSED_RENDER = 6,//用户暂停
		COMPLETED = 7,//播放完成
		SEEKING = 8, //SEEK

		STOPPED = 9,//播放器停止中
		MISTAKE = 10,//播放出错（是否需要分 可恢复 和 不可恢复 ）
		END = 11,//播放器释放各种对象完成
		MEDIA_ITEM_PREPARE = 12, //开始拉视频数据解码变换等，重新换地址后，都走这个状态 针对Media Item的play 方式
		RELEASE = 13 //播放器结束，且释放各类资源
	};
}