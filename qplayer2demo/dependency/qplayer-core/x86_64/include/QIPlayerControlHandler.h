#pragma once
#include "QPlayerExport.h"
#include "QUrlType.h"
#include "QPlayerSetting.h"
#include "QMediaModel.h"
#include "QIPlayerListenersHeader.h"
#include "QLogLevel.h"

namespace QMedia {

	/// <summary>
	/// 播放器控制句柄
	/// </summary>
	class QPLAYER_API QIPlayerControlHandler {

	public:
		QIPlayerControlHandler() = default;

		virtual ~QIPlayerControlHandler() = default;

		QIPlayerControlHandler(const QIPlayerControlHandler&) = delete;

		QIPlayerControlHandler(QIPlayerControlHandler&&) = delete;

		QIPlayerControlHandler& operator=(const QIPlayerControlHandler&) = delete;

		QIPlayerControlHandler& operator=(QIPlayerControlHandler&&) = delete;

		/// <summary>
		/// 获取当前视频下载速度
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_download_speed() = 0;

		/// <summary>
		/// 获取当前视频总时长
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_duration() = 0;

		/// <summary>
		/// 获取当前视频播放进度
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_current_positon() = 0;

		/// <summary>
		/// 获取当前视频播放状态
		/// </summary>
		/// <returns></returns>
		virtual QMedia::QPlayerState get_current_player_state() = 0;

		/// <summary>
		/// 获取当前视频缓冲大小
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_buffer_position() = 0;

		/// <summary>
		/// 获取当前视频 fps
		/// </summary>
		/// <returns></returns>
		virtual int get_fps() = 0;

		/// <summary>
		/// 获取当前视频 bit rate
		/// </summary>
		/// <returns></returns>
		virtual int get_bit_rate() = 0;

		/// <summary>
		/// 获取当前视频播放速度
		/// </summary>
		/// <returns></returns>
		virtual float get_player_speed() = 0;

		/// <summary>
		/// 获取当前视频是否静音
		/// </summary>
		/// <returns></returns>
		virtual bool get_is_mute() = 0;

		/// <summary>
		/// 获取当前视频字幕文本
		/// </summary>
		/// <returns></returns>
		virtual std::string& get_subtitle_text() = 0;

		/// <summary>
		/// 获取当前视频字幕名称
		/// </summary>
		/// <returns></returns>
		virtual std::string& get_subtitle_name() = 0;

		/// <summary>
		/// 获取当前状态是否正在缓存
		/// </summary>
		/// <returns></returns>
		virtual bool get_is_buffering() = 0;

		/// <summary>
		/// seek
		/// </summary>
		/// <param name="position"> seek 的位置 单位 ms </param>
		/// <returns></returns>
		virtual bool seek(long position) = 0;

		/// <summary>
		/// 切换清晰度,针对一个视频由多路url流组成的情况下，可以按找流来进行清晰度切换，
		/// 比如一个视频由2路url组成，一路视频，一路音频，那么可以只切换音频路的url达到音频的清晰度切换，也可以
		/// 只切换视频路的url达到视频的清晰度切换。
		/// </summary>
		/// <param name="user_type"> 要切换的url流的userType </param>
		/// <param name="url_type"> 要切换的url流的urlType </param>
		/// <param name="quality_index"> 要切换到哪一路清晰度 </param>
		/// <param name="immediately"> true: 立即切换，直播情况下用，false：无缝切换，只能用在点播 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool switch_quality(const std::string& user_type, QUrlType url_type, uint32_t quality_index, bool immediately) = 0;

		/// <summary>
		/// 获取当前正在播放的视频清晰度（非立即切换模式）
		/// </summary>
		/// <param name="user_type"> 视频的 user_type </param>
		/// <param name="url_type"> 视频的 url_type </param>
		/// <returns></returns>
		virtual int get_current_quality(const std::string& user_type, QUrlType url_type) = 0;

		/// <summary>
		/// 获取正在切换的清晰度（非立即切换模式）
		/// </summary>
		/// <param name="user_type"> 视频的 user_type </param>
		/// <param name="url_type"> 视频的 url_type  </param>
		/// <returns></returns>
		virtual int get_switching_quality(const std::string& user_type, QUrlType url_type) = 0;
		/// <summary>
		/// 暂停渲染
		/// </summary>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool pause_render() = 0;

		/// <summary>
		/// 在暂停渲染状态下 恢复渲染
		/// </summary>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool resume_render() = 0;

		/// <summary>
		/// 停止当前视频播放
		/// </summary>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool stop() = 0;

		/// <summary>
		/// 播放音视频资源
		/// </summary>
		/// <param name="pmedia_model"> 音视频资源 </param>
		/// <param name="start_pos"> 起播时间戳 毫秒 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool play_media_model(QMediaModel* pmedia_model, unsigned long start_pos) = 0;

		/// <summary>
		/// 设置播放速度
		/// </summary>
		/// <param name="speed"> 需要设置的倍速 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_speed(float speed) = 0;

		/// <summary>
		/// 设置解码方式
		/// </summary>
		/// <param name="type"> 解码方式 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_decode_type(QPlayerSetting::QPlayerDecoder type) = 0;

		/// <summary>
		/// 设置起播方式
		/// </summary>
		/// <param name="action"> 起播方式 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_start_action(QPlayerSetting::QPlayerStart action) = 0;

		/// <summary>
		/// 设置seek方式
		/// </summary>
		/// <param name="mode"> seek方式 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_seek_mode(QPlayerSetting::QPlayerSeek mode) = 0;

		/// <summary>
		/// 下一次鉴权强制通过网络鉴权
		/// </summary>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool force_authentication_from_network() = 0;

		/// <summary>
		/// 设置sei回调是否开启
		/// </summary>
		/// <param name="enable"> 是否开启 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_sei_enable(bool enable) = 0;

		/// <summary>
		/// 设置是否静音
		/// </summary>
		/// <param name="is_mute"> true: 静音 false 不静音 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_mute(bool is_mute) = 0;

		/// <summary>
		/// 设置日志记录等级
		/// </summary>
		/// <param name="level"> 日志等级 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_log_level(QLogLevel level) = 0;

		/// <summary>
		/// 设置视频回调格式
		/// </summary>
		/// <param name="type"> 回调格式 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_video_data_call_back_type(QVideoType type) = 0;

		/// <summary>
		/// 截图
		/// </summary>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool shoot_video() = 0;

		/// <summary>
		/// 设置字幕是否开启
		/// </summary>
		/// <param name="enable"> true 开启 false 关闭</param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_subtitle_enable(bool enable) = 0;

		/// <summary>
		/// 设置字幕
		/// </summary>
		/// <param name="name"> 切换后的名称 </param>
		/// <returns> true: 调用成功 false: 调用失败 </returns>
		virtual bool set_subtitle(const std::string& name) = 0;

		/// <summary>
		/// 添加播放器状态监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_state_change_listener(QIPlayerStateChangeListener * plistener) = 0;

		/// <summary>
		/// 删除播放器状态监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_state_change_listener(QIPlayerStateChangeListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器状态监听
		/// </summary>
		virtual void remove_all_player_state_change_listeners() = 0;

		/// <summary>
		/// 添加播放器音频数据监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_audio_data_listener(QIPlayerAudioDataListener* plistener) = 0;

		/// <summary>
		/// 删除播放器音频数据监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_audio_data_listener(QIPlayerAudioDataListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器音频数据监听
		/// </summary>
		virtual void remove_all_player_audio_data_listeners() = 0;

		/// <summary>
		/// 添加播放器声音监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_audio_listener(QIPlayerAudioListener* plistener) = 0;

		/// <summary>
		/// 删除播放器声音监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_audio_listener(QIPlayerAudioListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器声音监听
		/// </summary>
		virtual void remove_all_player_audio_listeners() = 0;

		/// <summary>
		/// 添加播放器鉴权监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_authentication_listener(QIPlayerAuthenticationListener* plistener) = 0;

		/// <summary>
		///  删除播放器鉴权监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_authentication_listener(QIPlayerAuthenticationListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器鉴权监听
		/// </summary>
		virtual void remove_all_player_authentication_listeners() = 0;

		/// <summary>
		/// 添加播放器码率监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) = 0;

		/// <summary>
		/// 删除播放器码率监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器码率监听
		/// </summary>
		virtual void remove_all_player_bite_rate_listeners() = 0;

		/// <summary>
		/// 添加播放器buffering状态改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_buffering_change_listener(QIPlayerBufferingListener* plistener) = 0;

		/// <summary>
		/// 删除播放器buffering状态改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_buffering_change_listener(QIPlayerBufferingListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器buffering状态改变监听
		/// </summary>
		virtual void remove_all_player_buffering_change_listeners() = 0;

		/// <summary>
		/// 添加播放器command状态监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) = 0;

		/// <summary>
		/// 删除播放器command状态监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器command状态监听
		/// </summary>
		virtual void remove_all_player_command_not_allow_listeners() = 0;

		/// <summary>
		/// 添加播放器下载速度监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_download_change_listener(QIPlayerDownloadListener* plistener) = 0;

		/// <summary>
		/// 删除播放器下载速度监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_download_change_listener(QIPlayerDownloadListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器下载速度监听
		/// </summary>
		virtual void remove_all_player_download_change_listeners() = 0;

		/// <summary>
		/// 添加播放器媒体资源format监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_format_listener(QIPlayerFormatListener* plistener) = 0;

		/// <summary>
		/// 删除播放器媒体资源format监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_format_listener(QIPlayerFormatListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器媒体资源format监听
		/// </summary>
		virtual void remove_all_player_format_listeners() = 0;

		/// <summary>
		/// 添加播放器 fps 改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_fps_change_listener(QIPlayerFPSListener* plistener) = 0;

		/// <summary>
		/// 删除播放器 fps 改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_fps_change_listener(QIPlayerFPSListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器 fps 改变监听
		/// </summary>
		virtual void remove_all_player_fps_change_listeners() = 0;

		/// <summary>
		/// 添加播放器媒体资源网络状况监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) = 0;

		/// <summary>
		/// 删除播放器媒体资源网络状况监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器媒体资源网络状况监听
		/// </summary>
		virtual void remove_all_player_media_network_listeners() = 0;

		/// <summary>
		/// 添加播放器进度改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_progress_change_listener(QIPlayerProgressListener* plistener) = 0;

		/// <summary>
		/// 删除播放器进度改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_progress_change_listener(QIPlayerProgressListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器进度改变监听
		/// </summary>
		virtual void remove_all_player_progress_change_listeners() = 0;

		/// <summary>
		/// 添加播放器清晰度监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_quality_listener(QIPlayerQualityListener* plistener) = 0;

		/// <summary>
		/// 删除播放器清晰度监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_quality_listener(QIPlayerQualityListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器清晰度监听
		/// </summary>
		virtual void remove_all_player_quality_listeners() = 0;

		/// <summary>
		/// 添加播放器 seek 监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_seek_listener(QIPlayerSeekListener* plistener) = 0;

		/// <summary>
		/// 删除播放器 seek 监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_seek_listener(QIPlayerSeekListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器 seek 监听
		/// </summary>
		virtual void remove_all_player_seek_listeners() = 0;

		/// <summary>
		/// 添加播放器 sei 数据监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_sei_data_listener(QIPlayerSEIDataListener* plistener) = 0;

		/// <summary>
		/// 删除播放器 sei 数据监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_sei_data_listener(QIPlayerSEIDataListener* plistener) = 0;

		/// <summary>
		///  删除所有播放器 sei 数据监听
		/// </summary>
		virtual void remove_all_player_sei_data_listeners() = 0;

		/// <summary>
		/// 添加播放器截图监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) = 0;

		/// <summary>
		/// 删除播放器截图监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器截图监听
		/// </summary>
		virtual void remove_all_player_shoot_video_listeners() = 0;

		/// <summary>
		/// 添加播放器播放速度改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_speed_change_listener(QIPlayerSpeedListener* plistener) = 0;

		/// <summary>
		/// 删除播放器播放速度改变监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_speed_change_listener(QIPlayerSpeedListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器播放速度改变监听
		/// </summary>
		virtual void remove_all_player_speed_change_listeners() = 0;

		/// <summary>
		/// 添加播放器字幕监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_subtitle_listener(QIPlayerSubtitleListener* plistener) = 0;

		/// <summary>
		/// 删除播放器字幕监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_subtitle_listener(QIPlayerSubtitleListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器字幕监听
		/// </summary>
		virtual void remove_all_player_subtitle_listeners() = 0;

		/// <summary>
		/// 添加播放器视频数据监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_video_data_listener(QIPlayerVideoDataListener* plistener) = 0;

		/// <summary>
		/// 删除播放器视频数据监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_video_data_listener(QIPlayerVideoDataListener* plistener) = 0;

		/// <summary>
		/// 删除所有播放器视频数据监听
		/// </summary>
		virtual void remove_all_player_video_data_listeners() = 0;

		/// <summary>
		/// 添加播放器视频解码类型监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) = 0;

		/// <summary>
		/// 删除播放器视频解码类型监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) = 0;

		/// <summary>
		/// 删除所有播放器视频解码类型监听
		/// </summary>
		virtual void remove_all_player_video_decode_type_listeners() = 0;

		/// <summary>
		/// 添加推流端视频长宽变化监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void add_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) = 0;

		/// <summary>
		/// 删除推流端视频长宽变化监听
		/// </summary>
		/// <param name="plistener"> 监听 </param>
		virtual void remove_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) = 0;

		/// <summary>
		/// 删除所有推流端视频长宽变化监听
		/// </summary>
		virtual void remove_all_player_video_frame_size_change_listeners() = 0;
	};
}

