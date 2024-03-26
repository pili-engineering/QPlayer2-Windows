#pragma once
#include <string>
#include "QMediaModel.h"
#include "QLogLevel.h"
#include "QMediaEnumHeader.h"
#include "QPlayerSetting.h"
#include "QIPlayerControlHandler.h"
#include "QPlayerNotify.h"
#include <list>
#include <map>
#include <any>
#include "LogInterface.h"
namespace QMedia {
	class QWindowsPlayer;
	class  PlayerControlHandlerImpl : public QIPlayerControlHandler, public LogInterface {
	private:
		/*
		* 视频时长 单位 毫秒
		*/
		int64_t mDuration;

	public:
	
		PlayerControlHandlerImpl(QWindowsPlayer* pinner_player);

		~PlayerControlHandlerImpl() override;

		PlayerControlHandlerImpl(const PlayerControlHandlerImpl&) = delete;

		PlayerControlHandlerImpl(PlayerControlHandlerImpl&&) = delete;

		PlayerControlHandlerImpl& operator=(const PlayerControlHandlerImpl&) = delete;

		PlayerControlHandlerImpl& operator=(PlayerControlHandlerImpl&&) = delete;

		/**
		* 内部使用的注册播放器状态监听
		*/
		void add_player_inner_state_change_listener(QIPlayerStateChangeListener* plistener);
		/**
		* 内部使用的删除播放器状态监听
		*/
		void remove_player_inner_state_change_listener(QIPlayerStateChangeListener* plistener);
		/**
		* 内部使用的删除所有播放器状态监听
		*/
		void remove_all_inner_player_state_change_listeners();

		/**
		* 切换视频当前进度
		* @param position 切换到哪个时间点 单位：毫秒
		*/
		bool seek(long position) override;


		/**
		* 切换清晰度,针对一个视频由多路url流组成的情况下，可以按找流来进行清晰度切换，
		 * 比如一个视频由2路url组成，一路视频，一路音频，那么可以只切换音频路的url达到音频的清晰度切换，也可以
		 * 只切换视频路的url达到视频的清晰度切换。
		 *
		 * @param userType 要切换的url流的userType
		 * @param urlType 要切换的url流的urlType
		 * @param quality 要切换到哪一路清晰度@see[QStreamElement.quality]
		 * @param immediately true: 立即切换，直播情况下用，false：无缝切换，只能用在点播，
		 * @return true: 调用成功 false: 调用失败
		 */
		bool switch_quality(const std::string & user_type, QUrlType url_type, uint32_t quality_index, bool immediately) override;

		/**
		 * 暂停渲染
		 * @return true: 调用成功 false: 调用失败
		 */
		bool pause_render() override;

		/**
		 * 在暂停渲染状态下 恢复渲染
		 * @return true: 调用成功 false: 调用失败
		 */
		bool resume_render() override;

		/**
		 * 停止当前视频播放
		 * @return true: 调用成功 false: 调用失败
		 */
		bool stop() override;

		/*** 播放音视频资源
		 * @param mediaModel 音视频资源
		 * @param startPos 起播时间戳 毫秒
		 */
		bool play_media_model(QMediaModel* pmedia_model, unsigned long start_pos) override;

		/*** 播放预加载资源
		 * @param mediaItem 预加载实例
		 */
		 //bool playMediaItem(QMediaItemContext* pmedia_item);

	 /*** 设置播放速度
	  * @param speed 需要设置的倍速
	  */
		bool set_speed(float speed) override;

		/*** 设置解码方式
	 * @param type 解码方式
	 */
		bool set_decode_type(QPlayerSetting::QPlayerDecoder type) override;

		/*** 设置起播方式
		 * @param action 起播方式
		 */
		bool set_start_action(QPlayerSetting::QPlayerStart action) override;

		/*** 设置seek方式
		 * @param mode seek方式
		 */
		bool set_seek_mode(QPlayerSetting::QPlayerSeek mode) override;

		/*** 下一次鉴权强制通过网络鉴权
		*/
		bool force_authentication_from_network() override;

		/*** 设置sei回调是否开启
		 * @param enable 是否开启
		 */
		bool set_sei_enable(bool enable) override;

		/*** 设置视频回调格式
		 * @param type 回调格式
		*/
		bool set_video_data_call_back_type(QVideoType type) override;
		/*** 设置是否静音
		 * @param mute : true: 静音 false 不静音
		 */
		bool set_mute(bool is_mute) override;

		/**
		 * 设置日志记录等级
		 * @param level 日志等级 see[QLogLevel]
		 */
		bool set_log_level(QLogLevel level) override;

		/**
		 * 截图
		 */
		bool shoot_video() override;

		/**
		* 设置字幕是否开启
		 * @param enable : true 开启 false 关闭
		 */
		bool set_subtitle_enable(bool enable) override;

		/**
		 * 设置字幕
		 * @param name : 切换后的名称
		 */
		bool set_subtitle(const std::string& name) override;

		/**
		 * 添加播放器状态监听
		 * @param plistener 监听
		 */
		void add_player_state_change_listener(QIPlayerStateChangeListener* plistener) override;

		/**
		 * 删除播放器状态监听
		 * @param plistener 监听
		 */
		void remove_player_state_change_listener(QIPlayerStateChangeListener* plistener) override;



		/**
		 * 删除所有播放器状态监听
		 */
		void remove_all_player_state_change_listeners() override;

		/**
		* 添加播放器音频数据监听
		* @param plistener 监听
		*/
		void add_player_audio_data_listener(QIPlayerAudioDataListener* plistener) override;

		/**
		 * 删除播放器音频数据监听
		 * @param plistener 监听
		 */
		void remove_player_audio_data_listener(QIPlayerAudioDataListener* plistener) override;

		/**
		 * 删除所有播放器音频数据监听
		 */
		void remove_all_player_audio_data_listeners() override;

		/*
		* 添加播放器声音监听
		* @param plistener 监听
		*/
		void add_player_audio_listener(QIPlayerAudioListener* plistener) override;

		/**
		 * 删除播放器声音监听
		 * @param plistener 监听
		 */
		void remove_player_audio_listener(QIPlayerAudioListener* plistener) override;

		/**
		 * 删除所有播放器声音监听
		 */
		void remove_all_player_audio_listeners() override;

		/*
		* 添加播放器鉴权监听
		* @param plistener 监听
		*/
		void add_player_authentication_listener(QIPlayerAuthenticationListener* plistener) override;

		/**
		 * 删除播放器鉴权监听
		 * @param plistener 监听
		 */
		void remove_player_authentication_listener(QIPlayerAuthenticationListener* plistener) override;

		/**
		 * 删除所有播放器鉴权监听
		 */
		void remove_all_player_authentication_listeners() override;

		/*
		* 添加播放器码率监听
		* @param plistener 监听
		*/
		void add_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) override;

		/**
		 * 删除播放器码率监听
		 * @param plistener 监听
		 */
		void remove_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) override;

		/**
		 * 删除所有播放器码率监听
		 */
		void remove_all_player_bite_rate_listeners() override;

		/*
		* 添加播放器buffering状态改变监听
		* @param plistener 监听
		*/
		void add_player_buffering_change_listener(QIPlayerBufferingListener* plistener) override;

		/**
		 * 删除播放器buffering状态改变监听
		 * @param plistener 监听
		 */
		void remove_player_buffering_change_listener(QIPlayerBufferingListener* plistener) override;

		/**
		 * 删除所有播放器buffering状态改变监听
		 */
		void remove_all_player_buffering_change_listeners() override;


		/*
		* 添加播放器command状态监听
		* @param plistener 监听
		*/
		void add_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) override;

		/**
		 * 删除播放器command状态监听
		 * @param plistener 监听
		 */
		void remove_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) override;

		/**
		 * 删除所有播放器command状态监听
		 */
		void remove_all_player_command_not_allow_listeners() override;

		/*
		* 添加播放器下载速度监听
		* @param plistener 监听
		*/
		void add_player_download_change_listener(QIPlayerDownloadListener* plistener) override;

		/**
		 * 删除播放器下载速度监听
		 * @param plistener 监听
		 */
		void remove_player_download_change_listener(QIPlayerDownloadListener* plistener) override;

		/**
		 * 删除所有播放器下载速度监听
		 */
		void remove_all_player_download_change_listeners() override;

		/*
		* 添加播放器媒体资源format监听
		* @param plistener 监听
		*/
		void add_player_format_listener(QIPlayerFormatListener* plistener) override;

		/**
		 * 删除播放器媒体资源format监听
		 * @param plistener 监听
		 */
		void remove_player_format_listener(QIPlayerFormatListener* plistener) override;

		/**
		 * 删除所有播放器媒体资源format监听
		 */
		void remove_all_player_format_listeners() override;

		/*
		* 添加播放器 fps 改变监听
		* @param plistener 监听
		*/
		void add_player_fps_change_listener(QIPlayerFPSListener* plistener) override;

		/**
		 * 删除播放器 fps 改变监听
		 * @param plistener 监听
		 */
		void remove_player_fps_change_listener(QIPlayerFPSListener* plistener) override;

		/**
		 * 删除所有播放器 fps 改变监听
		 */
		void remove_all_player_fps_change_listeners() override;


		/*
		* 添加播放器媒体资源网络状况监听
		* @param plistener 监听
		*/
		void add_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) override;

		/**
		 * 删除播放器媒体资源网络状况监听
		 * @param plistener 监听
		 */
		void remove_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) override;

		/**
		 * 删除所有播放器媒体资源网络状况监听
		 */
		void remove_all_player_media_network_listeners() override;

		/*
		* 添加播放器进度改变监听
		* @param plistener 监听
		*/
		void add_player_progress_change_listener(QIPlayerProgressListener* plistener) override;

		/**
		 * 删除播放器进度改变监听
		 * @param plistener 监听
		 */
		void remove_player_progress_change_listener(QIPlayerProgressListener* plistener) override;

		/**
		 * 删除所有播放器进度改变监听
		 */
		void remove_all_player_progress_change_listeners() override;

		/*
		* 添加播放器清晰度监听
		* @param plistener 监听
		*/
		void add_player_quality_listener(QIPlayerQualityListener* plistener) override;

		/**
		 * 删除播放器清晰度监听
		 * @param plistener 监听
		 */
		void remove_player_quality_listener(QIPlayerQualityListener* plistener) override;

		/**
		 * 删除所有播放器清晰度监听
		 */
		void remove_all_player_quality_listeners() override;

		/*
		* 添加播放器 seek 监听
		* @param plistener 监听
		*/
		void add_player_seek_listener(QIPlayerSeekListener* plistener) override;

		/**
		 * 删除播放器 seek 监听
		 * @param plistener 监听
		 */
		void remove_player_seek_listener(QIPlayerSeekListener* plistener) override;

		/**
		 * 删除所有播放器 seek 监听
		 */
		void remove_all_player_seek_listeners() override;

		/*
		* 添加播放器 sei 数据监听
		* @param plistener 监听
		*/
		void add_player_sei_data_listener(QIPlayerSEIDataListener* plistener) override;

		/**
		 * 删除播放器 sei 数据监听
		 * @param plistener 监听
		 */
		void remove_player_sei_data_listener(QIPlayerSEIDataListener* plistener) override;

		/**
		 * 删除所有播放器 sei 数据监听
		 */
		void remove_all_player_sei_data_listeners() override;

		/*
		* 添加播放器截图监听
		* @param plistener 监听
		*/
		void add_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) override;

		/**
		 * 删除播放器截图监听
		 * @param plistener 监听
		 */
		void remove_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) override;

		/**
		 * 删除所有播放器截图监听
		 */
		void remove_all_player_shoot_video_listeners() override;

		/*
		* 添加播放器播放速度改变监听
		* @param plistener 监听
		*/
		void add_player_speed_change_listener(QIPlayerSpeedListener* plistener) override;

		/**
		 * 删除播放器播放速度改变监听
		 * @param plistener 监听
		 */
		void remove_player_speed_change_listener(QIPlayerSpeedListener* plistener) override;

		/**
		 * 删除所有播放器播放速度改变监听
		 */
		void remove_all_player_speed_change_listeners() override;

		/*
		* 添加播放器字幕监听
		* @param plistener 监听
		*/
		void add_player_subtitle_listener(QIPlayerSubtitleListener* plistener) override;

		/**
		 * 删除播放器字幕监听
		 * @param plistener 监听
		 */
		void remove_player_subtitle_listener(QIPlayerSubtitleListener* plistener) override;

		/**
		 * 删除所有播放器字幕监听
		 */
		void remove_all_player_subtitle_listeners() override;

		/*
		* 添加播放器视频数据监听
		* @param plistener 监听
		*/
		void add_player_video_data_listener(QIPlayerVideoDataListener* plistener) override;

		/**
		 * 删除播放器视频数据监听
		 * @param plistener 监听
		 */
		void remove_player_video_data_listener(QIPlayerVideoDataListener* plistener) override;

		/**
		 * 删除所有播放器视频数据监听
		 */
		void remove_all_player_video_data_listeners() override;

		/*
		* 添加播放器视频解码类型监听
		* @param plistener 监听
		*/
		void add_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) override;

		/**
		 * 删除播放器视频解码类型监听
		 * @param plistener 监听
		 */
		void remove_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) override;

		/**
		 * 删除所有播放器视频解码类型监听
		 */
		void remove_all_player_video_decode_type_listeners() override;

		/*
		* 添加推流端视频长宽变化监听
		* @param plistener 监听
		*/
		void add_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) override;

		/**
		 * 删除推流端视频长宽变化监听
		 * @param plistener 监听
		 */
		void remove_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) override;

		/**
		 * 删除所有推流端视频长宽变化监听
		 */
		void remove_all_player_video_frame_size_change_listeners() override;


		void on_state_changed_sync(QMedia::QPlayerState state);

		void on_stream_open_duration_sync(int64_t duration);

		void on_open_failed_sync(const std::string & user_type, QMedia::QUrlType url_type,const char* purl, QMedia::QOpenError error);

		void on_stream_connect_start_sync(const std::string & user_type, QMedia::QUrlType url_type, const char * purl, int retry_time);

		void on_stream_connect_end_sync(const std::string & user_type, QMedia::QUrlType url_type, const char* purl, int retry_time, QMedia::QOpenError error);

		void on_render_pragress_sync(int64_t prograss);

		void on_render_buffering_start_sync();

		void on_render_buffering_end_sync();

		void on_fps_change_sync(int fps);

		void on_bit_rate_changed_sync(int bit_rate);

		void on_download_process_sync(int64_t download_speed, int64_t buffer_pos);

		void on_event_loop_not_allow_sync(const std::string & command_name, QMedia::QPlayerState state);

		void on_quality_switch_start_sync(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality);

		void on_quality_switch_changed_sync(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality);

		void on_quality_switch_failed_sync(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality);

		void on_quality_switch_cancel_sync(const std::string & user_type, QMedia::QUrlType url_type, int old_quality, int new_quality);

		void on_quality_switch_retry_later_sync(const std::string & user_type, QMedia::QUrlType url_type, int new_quality);

		void on_play_speed_change_sync(float speed);

		void on_video_decode_type_sync(QMedia::QDecoderType type);

		void on_not_support_codec_format(int codec_id);

		void on_authentication_failed_sync(QMedia::QAuthenticationErrorType error);

		void on_authentication_success_sync();

		void on_format_not_support_sync();

		void on_sei_data_sync(uint8_t* data, uint64_t size);

		void on_shoot_success_sync(uint8_t* image_data, uint64_t size, int width, int height, QMedia::QShootVideoType type);

		void on_shoot_failed_sync();

		void on_seek_success_sync();

		void on_seek_failed_sync();

		void on_video_render_frame_size_change_sync(int width, int height);

		void on_audio_render_mute_state_change_sync(bool is_mute);

		//void on_subtitle_render_text_change_sync(const std::string & text);
		void on_subtitle_render_text_change_sync(const char* ptext);

		void on_subtitile_change_sync(const char* pname);

		void on_subtitle_enable_sync(bool enable);

		void on_subtitle_load_result_sync(const char* pname, bool result);

		void on_subtitle_decode_result_sync(const char* pname, bool result);

		void on_audio_render_data_sync(int sample_rate, int format, int channel_num, int channel_layout, uint8_t* data, uint64_t size);

		void on_video_render_data_sync(int width, int height, int video_type, uint8_t* buffer, uint64_t size);

		void on_decode_failed();

		void on_notify_sync(QMedia::QPlayerNotify notify_id, std::map<std::string, std::any>* pbundle);


		void log(QMedia::QLogLevel level, const std::string& message) override;

	private:
		bool replay(bool forece_soft_decode);

		QMedia::QMediaModel* copy_qmedia_model(QMedia::QMediaModel* pmedia_model);

		void update_current_quality(const std::string& user_type, QUrlType url_type, int old_quality, int new_quality);

	private:
		QWindowsPlayer* mpInnerPlayer;

		QMedia::QMediaModel* mpCurrentMediaModel;

		std::list<QIPlayerAudioDataListener*> mPlayerAudioDataListeners;

		std::list<QIPlayerAudioListener*> mPlayerAudioListeners;

		std::list<QIPlayerAuthenticationListener*> mPlayerAuthenticationeListeners;

		std::list<QIPlayerBiteRateListener*> mPlayerBiteRateListeners;

		std::list<QIPlayerBufferingListener*> mPlayerBufferingListeners;

		std::list<QIPlayerCommandNotAllowListener*> mPlayerCommandNotAllowListeners;

		std::list<QIPlayerDownloadListener*> mPlayerDownloadListeners;

		std::list<QIPlayerFormatListener*> mPlayerFormatListeners;

		std::list<QIPlayerFPSListener*> mPlayerFPSListeners;

		std::list<QIPlayerMediaNetworkListener*> mPlayerMediaNetworkListeners;

		std::list<QIPlayerProgressListener*> mPlayerProgressListeners;

		std::list<QIPlayerQualityListener*> mPlayerQualityListeners;

		std::list<QIPlayerSeekListener*> mPlayerSeekListeners;

		std::list<QIPlayerSEIDataListener*> mPlayerSEIDataListeners;

		std::list<QIPlayerShootVideoListener*> mPlayerShootVideoListeners;

		std::list<QIPlayerSpeedListener*> mPlayerSpeedListeners;

		std::list<QIPlayerStateChangeListener*> mPlayerStateChangeListeners;

		std::list<QIPlayerSubtitleListener*> mPlayerSubtitleListeners;

		std::list<QIPlayerVideoDataListener*> mPlayerVideoDataListeners;

		std::list<QIPlayerVideoDecodeListender*> mPlayerVideoDecodeListeners;

		std::list<QIPlayerVideoFrameSizeChangeListener*> mPlayerVideoFrameSizeChangeListeners;

		std::list<QIPlayerStateChangeListener*> mInnerPlayerStateChangeListeners;
	};
}

