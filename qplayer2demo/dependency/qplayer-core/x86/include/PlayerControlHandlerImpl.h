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
		* ��Ƶʱ�� ��λ ����
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
		* �ڲ�ʹ�õ�ע�Ქ����״̬����
		*/
		void add_player_inner_state_change_listener(QIPlayerStateChangeListener* plistener);
		/**
		* �ڲ�ʹ�õ�ɾ��������״̬����
		*/
		void remove_player_inner_state_change_listener(QIPlayerStateChangeListener* plistener);
		/**
		* �ڲ�ʹ�õ�ɾ�����в�����״̬����
		*/
		void remove_all_inner_player_state_change_listeners();

		/**
		* �л���Ƶ��ǰ����
		* @param position �л����ĸ�ʱ��� ��λ������
		*/
		bool seek(long position) override;


		/**
		* �л�������,���һ����Ƶ�ɶ�·url����ɵ�����£����԰������������������л���
		 * ����һ����Ƶ��2·url��ɣ�һ·��Ƶ��һ·��Ƶ����ô����ֻ�л���Ƶ·��url�ﵽ��Ƶ���������л���Ҳ����
		 * ֻ�л���Ƶ·��url�ﵽ��Ƶ���������л���
		 *
		 * @param userType Ҫ�л���url����userType
		 * @param urlType Ҫ�л���url����urlType
		 * @param quality Ҫ�л�����һ·������@see[QStreamElement.quality]
		 * @param immediately true: �����л���ֱ��������ã�false���޷��л���ֻ�����ڵ㲥��
		 * @return true: ���óɹ� false: ����ʧ��
		 */
		bool switch_quality(const std::string & user_type, QUrlType url_type, uint32_t quality_index, bool immediately) override;

		/**
		 * ��ͣ��Ⱦ
		 * @return true: ���óɹ� false: ����ʧ��
		 */
		bool pause_render() override;

		/**
		 * ����ͣ��Ⱦ״̬�� �ָ���Ⱦ
		 * @return true: ���óɹ� false: ����ʧ��
		 */
		bool resume_render() override;

		/**
		 * ֹͣ��ǰ��Ƶ����
		 * @return true: ���óɹ� false: ����ʧ��
		 */
		bool stop() override;

		/*** ��������Ƶ��Դ
		 * @param mediaModel ����Ƶ��Դ
		 * @param startPos ��ʱ��� ����
		 */
		bool play_media_model(QMediaModel* pmedia_model, unsigned long start_pos) override;

		/*** ����Ԥ������Դ
		 * @param mediaItem Ԥ����ʵ��
		 */
		 //bool playMediaItem(QMediaItemContext* pmedia_item);

	 /*** ���ò����ٶ�
	  * @param speed ��Ҫ���õı���
	  */
		bool set_speed(float speed) override;

		/*** ���ý��뷽ʽ
	 * @param type ���뷽ʽ
	 */
		bool set_decode_type(QPlayerSetting::QPlayerDecoder type) override;

		/*** �����𲥷�ʽ
		 * @param action �𲥷�ʽ
		 */
		bool set_start_action(QPlayerSetting::QPlayerStart action) override;

		/*** ����seek��ʽ
		 * @param mode seek��ʽ
		 */
		bool set_seek_mode(QPlayerSetting::QPlayerSeek mode) override;

		/*** ��һ�μ�Ȩǿ��ͨ�������Ȩ
		*/
		bool force_authentication_from_network() override;

		/*** ����sei�ص��Ƿ���
		 * @param enable �Ƿ���
		 */
		bool set_sei_enable(bool enable) override;

		/*** ������Ƶ�ص���ʽ
		 * @param type �ص���ʽ
		*/
		bool set_video_data_call_back_type(QVideoType type) override;
		/*** �����Ƿ���
		 * @param mute : true: ���� false ������
		 */
		bool set_mute(bool is_mute) override;

		/**
		 * ������־��¼�ȼ�
		 * @param level ��־�ȼ� see[QLogLevel]
		 */
		bool set_log_level(QLogLevel level) override;

		/**
		 * ��ͼ
		 */
		bool shoot_video() override;

		/**
		* ������Ļ�Ƿ���
		 * @param enable : true ���� false �ر�
		 */
		bool set_subtitle_enable(bool enable) override;

		/**
		 * ������Ļ
		 * @param name : �л��������
		 */
		bool set_subtitle(const std::string& name) override;

		/**
		 * ��Ӳ�����״̬����
		 * @param plistener ����
		 */
		void add_player_state_change_listener(QIPlayerStateChangeListener* plistener) override;

		/**
		 * ɾ��������״̬����
		 * @param plistener ����
		 */
		void remove_player_state_change_listener(QIPlayerStateChangeListener* plistener) override;



		/**
		 * ɾ�����в�����״̬����
		 */
		void remove_all_player_state_change_listeners() override;

		/**
		* ��Ӳ�������Ƶ���ݼ���
		* @param plistener ����
		*/
		void add_player_audio_data_listener(QIPlayerAudioDataListener* plistener) override;

		/**
		 * ɾ����������Ƶ���ݼ���
		 * @param plistener ����
		 */
		void remove_player_audio_data_listener(QIPlayerAudioDataListener* plistener) override;

		/**
		 * ɾ�����в�������Ƶ���ݼ���
		 */
		void remove_all_player_audio_data_listeners() override;

		/*
		* ��Ӳ�������������
		* @param plistener ����
		*/
		void add_player_audio_listener(QIPlayerAudioListener* plistener) override;

		/**
		 * ɾ����������������
		 * @param plistener ����
		 */
		void remove_player_audio_listener(QIPlayerAudioListener* plistener) override;

		/**
		 * ɾ�����в�������������
		 */
		void remove_all_player_audio_listeners() override;

		/*
		* ��Ӳ�������Ȩ����
		* @param plistener ����
		*/
		void add_player_authentication_listener(QIPlayerAuthenticationListener* plistener) override;

		/**
		 * ɾ����������Ȩ����
		 * @param plistener ����
		 */
		void remove_player_authentication_listener(QIPlayerAuthenticationListener* plistener) override;

		/**
		 * ɾ�����в�������Ȩ����
		 */
		void remove_all_player_authentication_listeners() override;

		/*
		* ��Ӳ��������ʼ���
		* @param plistener ����
		*/
		void add_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) override;

		/**
		 * ɾ�����������ʼ���
		 * @param plistener ����
		 */
		void remove_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) override;

		/**
		 * ɾ�����в��������ʼ���
		 */
		void remove_all_player_bite_rate_listeners() override;

		/*
		* ��Ӳ�����buffering״̬�ı����
		* @param plistener ����
		*/
		void add_player_buffering_change_listener(QIPlayerBufferingListener* plistener) override;

		/**
		 * ɾ��������buffering״̬�ı����
		 * @param plistener ����
		 */
		void remove_player_buffering_change_listener(QIPlayerBufferingListener* plistener) override;

		/**
		 * ɾ�����в�����buffering״̬�ı����
		 */
		void remove_all_player_buffering_change_listeners() override;


		/*
		* ��Ӳ�����command״̬����
		* @param plistener ����
		*/
		void add_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) override;

		/**
		 * ɾ��������command״̬����
		 * @param plistener ����
		 */
		void remove_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) override;

		/**
		 * ɾ�����в�����command״̬����
		 */
		void remove_all_player_command_not_allow_listeners() override;

		/*
		* ��Ӳ����������ٶȼ���
		* @param plistener ����
		*/
		void add_player_download_change_listener(QIPlayerDownloadListener* plistener) override;

		/**
		 * ɾ�������������ٶȼ���
		 * @param plistener ����
		 */
		void remove_player_download_change_listener(QIPlayerDownloadListener* plistener) override;

		/**
		 * ɾ�����в����������ٶȼ���
		 */
		void remove_all_player_download_change_listeners() override;

		/*
		* ��Ӳ�����ý����Դformat����
		* @param plistener ����
		*/
		void add_player_format_listener(QIPlayerFormatListener* plistener) override;

		/**
		 * ɾ��������ý����Դformat����
		 * @param plistener ����
		 */
		void remove_player_format_listener(QIPlayerFormatListener* plistener) override;

		/**
		 * ɾ�����в�����ý����Դformat����
		 */
		void remove_all_player_format_listeners() override;

		/*
		* ��Ӳ����� fps �ı����
		* @param plistener ����
		*/
		void add_player_fps_change_listener(QIPlayerFPSListener* plistener) override;

		/**
		 * ɾ�������� fps �ı����
		 * @param plistener ����
		 */
		void remove_player_fps_change_listener(QIPlayerFPSListener* plistener) override;

		/**
		 * ɾ�����в����� fps �ı����
		 */
		void remove_all_player_fps_change_listeners() override;


		/*
		* ��Ӳ�����ý����Դ����״������
		* @param plistener ����
		*/
		void add_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) override;

		/**
		 * ɾ��������ý����Դ����״������
		 * @param plistener ����
		 */
		void remove_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) override;

		/**
		 * ɾ�����в�����ý����Դ����״������
		 */
		void remove_all_player_media_network_listeners() override;

		/*
		* ��Ӳ��������ȸı����
		* @param plistener ����
		*/
		void add_player_progress_change_listener(QIPlayerProgressListener* plistener) override;

		/**
		 * ɾ�����������ȸı����
		 * @param plistener ����
		 */
		void remove_player_progress_change_listener(QIPlayerProgressListener* plistener) override;

		/**
		 * ɾ�����в��������ȸı����
		 */
		void remove_all_player_progress_change_listeners() override;

		/*
		* ��Ӳ����������ȼ���
		* @param plistener ����
		*/
		void add_player_quality_listener(QIPlayerQualityListener* plistener) override;

		/**
		 * ɾ�������������ȼ���
		 * @param plistener ����
		 */
		void remove_player_quality_listener(QIPlayerQualityListener* plistener) override;

		/**
		 * ɾ�����в����������ȼ���
		 */
		void remove_all_player_quality_listeners() override;

		/*
		* ��Ӳ����� seek ����
		* @param plistener ����
		*/
		void add_player_seek_listener(QIPlayerSeekListener* plistener) override;

		/**
		 * ɾ�������� seek ����
		 * @param plistener ����
		 */
		void remove_player_seek_listener(QIPlayerSeekListener* plistener) override;

		/**
		 * ɾ�����в����� seek ����
		 */
		void remove_all_player_seek_listeners() override;

		/*
		* ��Ӳ����� sei ���ݼ���
		* @param plistener ����
		*/
		void add_player_sei_data_listener(QIPlayerSEIDataListener* plistener) override;

		/**
		 * ɾ�������� sei ���ݼ���
		 * @param plistener ����
		 */
		void remove_player_sei_data_listener(QIPlayerSEIDataListener* plistener) override;

		/**
		 * ɾ�����в����� sei ���ݼ���
		 */
		void remove_all_player_sei_data_listeners() override;

		/*
		* ��Ӳ�������ͼ����
		* @param plistener ����
		*/
		void add_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) override;

		/**
		 * ɾ����������ͼ����
		 * @param plistener ����
		 */
		void remove_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) override;

		/**
		 * ɾ�����в�������ͼ����
		 */
		void remove_all_player_shoot_video_listeners() override;

		/*
		* ��Ӳ����������ٶȸı����
		* @param plistener ����
		*/
		void add_player_speed_change_listener(QIPlayerSpeedListener* plistener) override;

		/**
		 * ɾ�������������ٶȸı����
		 * @param plistener ����
		 */
		void remove_player_speed_change_listener(QIPlayerSpeedListener* plistener) override;

		/**
		 * ɾ�����в����������ٶȸı����
		 */
		void remove_all_player_speed_change_listeners() override;

		/*
		* ��Ӳ�������Ļ����
		* @param plistener ����
		*/
		void add_player_subtitle_listener(QIPlayerSubtitleListener* plistener) override;

		/**
		 * ɾ����������Ļ����
		 * @param plistener ����
		 */
		void remove_player_subtitle_listener(QIPlayerSubtitleListener* plistener) override;

		/**
		 * ɾ�����в�������Ļ����
		 */
		void remove_all_player_subtitle_listeners() override;

		/*
		* ��Ӳ�������Ƶ���ݼ���
		* @param plistener ����
		*/
		void add_player_video_data_listener(QIPlayerVideoDataListener* plistener) override;

		/**
		 * ɾ����������Ƶ���ݼ���
		 * @param plistener ����
		 */
		void remove_player_video_data_listener(QIPlayerVideoDataListener* plistener) override;

		/**
		 * ɾ�����в�������Ƶ���ݼ���
		 */
		void remove_all_player_video_data_listeners() override;

		/*
		* ��Ӳ�������Ƶ�������ͼ���
		* @param plistener ����
		*/
		void add_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) override;

		/**
		 * ɾ����������Ƶ�������ͼ���
		 * @param plistener ����
		 */
		void remove_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) override;

		/**
		 * ɾ�����в�������Ƶ�������ͼ���
		 */
		void remove_all_player_video_decode_type_listeners() override;

		/*
		* �����������Ƶ����仯����
		* @param plistener ����
		*/
		void add_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) override;

		/**
		 * ɾ����������Ƶ����仯����
		 * @param plistener ����
		 */
		void remove_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) override;

		/**
		 * ɾ��������������Ƶ����仯����
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

