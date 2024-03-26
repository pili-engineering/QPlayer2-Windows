#pragma once
#include "QPlayerExport.h"
#include "QUrlType.h"
#include "QPlayerSetting.h"
#include "QMediaModel.h"
#include "QIPlayerListenersHeader.h"
#include "QLogLevel.h"

namespace QMedia {

	/// <summary>
	/// ���������ƾ��
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
		/// ��ȡ��ǰ��Ƶ�����ٶ�
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_download_speed() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ��ʱ��
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_duration() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ���Ž���
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_current_positon() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ����״̬
		/// </summary>
		/// <returns></returns>
		virtual QMedia::QPlayerState get_current_player_state() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ�����С
		/// </summary>
		/// <returns></returns>
		virtual int64_t get_buffer_position() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ fps
		/// </summary>
		/// <returns></returns>
		virtual int get_fps() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ bit rate
		/// </summary>
		/// <returns></returns>
		virtual int get_bit_rate() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ�����ٶ�
		/// </summary>
		/// <returns></returns>
		virtual float get_player_speed() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ�Ƿ���
		/// </summary>
		/// <returns></returns>
		virtual bool get_is_mute() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ��Ļ�ı�
		/// </summary>
		/// <returns></returns>
		virtual std::string& get_subtitle_text() = 0;

		/// <summary>
		/// ��ȡ��ǰ��Ƶ��Ļ����
		/// </summary>
		/// <returns></returns>
		virtual std::string& get_subtitle_name() = 0;

		/// <summary>
		/// ��ȡ��ǰ״̬�Ƿ����ڻ���
		/// </summary>
		/// <returns></returns>
		virtual bool get_is_buffering() = 0;

		/// <summary>
		/// seek
		/// </summary>
		/// <param name="position"> seek ��λ�� ��λ ms </param>
		/// <returns></returns>
		virtual bool seek(long position) = 0;

		/// <summary>
		/// �л�������,���һ����Ƶ�ɶ�·url����ɵ�����£����԰������������������л���
		/// ����һ����Ƶ��2·url��ɣ�һ·��Ƶ��һ·��Ƶ����ô����ֻ�л���Ƶ·��url�ﵽ��Ƶ���������л���Ҳ����
		/// ֻ�л���Ƶ·��url�ﵽ��Ƶ���������л���
		/// </summary>
		/// <param name="user_type"> Ҫ�л���url����userType </param>
		/// <param name="url_type"> Ҫ�л���url����urlType </param>
		/// <param name="quality_index"> Ҫ�л�����һ·������ </param>
		/// <param name="immediately"> true: �����л���ֱ��������ã�false���޷��л���ֻ�����ڵ㲥 </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool switch_quality(const std::string& user_type, QUrlType url_type, uint32_t quality_index, bool immediately) = 0;

		/// <summary>
		/// ��ȡ��ǰ���ڲ��ŵ���Ƶ�����ȣ��������л�ģʽ��
		/// </summary>
		/// <param name="user_type"> ��Ƶ�� user_type </param>
		/// <param name="url_type"> ��Ƶ�� url_type </param>
		/// <returns></returns>
		virtual int get_current_quality(const std::string& user_type, QUrlType url_type) = 0;

		/// <summary>
		/// ��ȡ�����л��������ȣ��������л�ģʽ��
		/// </summary>
		/// <param name="user_type"> ��Ƶ�� user_type </param>
		/// <param name="url_type"> ��Ƶ�� url_type  </param>
		/// <returns></returns>
		virtual int get_switching_quality(const std::string& user_type, QUrlType url_type) = 0;
		/// <summary>
		/// ��ͣ��Ⱦ
		/// </summary>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool pause_render() = 0;

		/// <summary>
		/// ����ͣ��Ⱦ״̬�� �ָ���Ⱦ
		/// </summary>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool resume_render() = 0;

		/// <summary>
		/// ֹͣ��ǰ��Ƶ����
		/// </summary>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool stop() = 0;

		/// <summary>
		/// ��������Ƶ��Դ
		/// </summary>
		/// <param name="pmedia_model"> ����Ƶ��Դ </param>
		/// <param name="start_pos"> ��ʱ��� ���� </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool play_media_model(QMediaModel* pmedia_model, unsigned long start_pos) = 0;

		/// <summary>
		/// ���ò����ٶ�
		/// </summary>
		/// <param name="speed"> ��Ҫ���õı��� </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_speed(float speed) = 0;

		/// <summary>
		/// ���ý��뷽ʽ
		/// </summary>
		/// <param name="type"> ���뷽ʽ </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_decode_type(QPlayerSetting::QPlayerDecoder type) = 0;

		/// <summary>
		/// �����𲥷�ʽ
		/// </summary>
		/// <param name="action"> �𲥷�ʽ </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_start_action(QPlayerSetting::QPlayerStart action) = 0;

		/// <summary>
		/// ����seek��ʽ
		/// </summary>
		/// <param name="mode"> seek��ʽ </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_seek_mode(QPlayerSetting::QPlayerSeek mode) = 0;

		/// <summary>
		/// ��һ�μ�Ȩǿ��ͨ�������Ȩ
		/// </summary>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool force_authentication_from_network() = 0;

		/// <summary>
		/// ����sei�ص��Ƿ���
		/// </summary>
		/// <param name="enable"> �Ƿ��� </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_sei_enable(bool enable) = 0;

		/// <summary>
		/// �����Ƿ���
		/// </summary>
		/// <param name="is_mute"> true: ���� false ������ </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_mute(bool is_mute) = 0;

		/// <summary>
		/// ������־��¼�ȼ�
		/// </summary>
		/// <param name="level"> ��־�ȼ� </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_log_level(QLogLevel level) = 0;

		/// <summary>
		/// ������Ƶ�ص���ʽ
		/// </summary>
		/// <param name="type"> �ص���ʽ </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_video_data_call_back_type(QVideoType type) = 0;

		/// <summary>
		/// ��ͼ
		/// </summary>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool shoot_video() = 0;

		/// <summary>
		/// ������Ļ�Ƿ���
		/// </summary>
		/// <param name="enable"> true ���� false �ر�</param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_subtitle_enable(bool enable) = 0;

		/// <summary>
		/// ������Ļ
		/// </summary>
		/// <param name="name"> �л�������� </param>
		/// <returns> true: ���óɹ� false: ����ʧ�� </returns>
		virtual bool set_subtitle(const std::string& name) = 0;

		/// <summary>
		/// ��Ӳ�����״̬����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_state_change_listener(QIPlayerStateChangeListener * plistener) = 0;

		/// <summary>
		/// ɾ��������״̬����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_state_change_listener(QIPlayerStateChangeListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�����״̬����
		/// </summary>
		virtual void remove_all_player_state_change_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������Ƶ���ݼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_audio_data_listener(QIPlayerAudioDataListener* plistener) = 0;

		/// <summary>
		/// ɾ����������Ƶ���ݼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_audio_data_listener(QIPlayerAudioDataListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������Ƶ���ݼ���
		/// </summary>
		virtual void remove_all_player_audio_data_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������������
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_audio_listener(QIPlayerAudioListener* plistener) = 0;

		/// <summary>
		/// ɾ����������������
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_audio_listener(QIPlayerAudioListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������������
		/// </summary>
		virtual void remove_all_player_audio_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������Ȩ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_authentication_listener(QIPlayerAuthenticationListener* plistener) = 0;

		/// <summary>
		///  ɾ����������Ȩ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_authentication_listener(QIPlayerAuthenticationListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������Ȩ����
		/// </summary>
		virtual void remove_all_player_authentication_listeners() = 0;

		/// <summary>
		/// ��Ӳ��������ʼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) = 0;

		/// <summary>
		/// ɾ�����������ʼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_bite_rate_listener(QIPlayerBiteRateListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в��������ʼ���
		/// </summary>
		virtual void remove_all_player_bite_rate_listeners() = 0;

		/// <summary>
		/// ��Ӳ�����buffering״̬�ı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_buffering_change_listener(QIPlayerBufferingListener* plistener) = 0;

		/// <summary>
		/// ɾ��������buffering״̬�ı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_buffering_change_listener(QIPlayerBufferingListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�����buffering״̬�ı����
		/// </summary>
		virtual void remove_all_player_buffering_change_listeners() = 0;

		/// <summary>
		/// ��Ӳ�����command״̬����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) = 0;

		/// <summary>
		/// ɾ��������command״̬����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_command_not_allow_listener(QIPlayerCommandNotAllowListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�����command״̬����
		/// </summary>
		virtual void remove_all_player_command_not_allow_listeners() = 0;

		/// <summary>
		/// ��Ӳ����������ٶȼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_download_change_listener(QIPlayerDownloadListener* plistener) = 0;

		/// <summary>
		/// ɾ�������������ٶȼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_download_change_listener(QIPlayerDownloadListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в����������ٶȼ���
		/// </summary>
		virtual void remove_all_player_download_change_listeners() = 0;

		/// <summary>
		/// ��Ӳ�����ý����Դformat����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_format_listener(QIPlayerFormatListener* plistener) = 0;

		/// <summary>
		/// ɾ��������ý����Դformat����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_format_listener(QIPlayerFormatListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�����ý����Դformat����
		/// </summary>
		virtual void remove_all_player_format_listeners() = 0;

		/// <summary>
		/// ��Ӳ����� fps �ı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_fps_change_listener(QIPlayerFPSListener* plistener) = 0;

		/// <summary>
		/// ɾ�������� fps �ı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_fps_change_listener(QIPlayerFPSListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в����� fps �ı����
		/// </summary>
		virtual void remove_all_player_fps_change_listeners() = 0;

		/// <summary>
		/// ��Ӳ�����ý����Դ����״������
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) = 0;

		/// <summary>
		/// ɾ��������ý����Դ����״������
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_media_network_listener(QIPlayerMediaNetworkListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�����ý����Դ����״������
		/// </summary>
		virtual void remove_all_player_media_network_listeners() = 0;

		/// <summary>
		/// ��Ӳ��������ȸı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_progress_change_listener(QIPlayerProgressListener* plistener) = 0;

		/// <summary>
		/// ɾ�����������ȸı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_progress_change_listener(QIPlayerProgressListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в��������ȸı����
		/// </summary>
		virtual void remove_all_player_progress_change_listeners() = 0;

		/// <summary>
		/// ��Ӳ����������ȼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_quality_listener(QIPlayerQualityListener* plistener) = 0;

		/// <summary>
		/// ɾ�������������ȼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_quality_listener(QIPlayerQualityListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в����������ȼ���
		/// </summary>
		virtual void remove_all_player_quality_listeners() = 0;

		/// <summary>
		/// ��Ӳ����� seek ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_seek_listener(QIPlayerSeekListener* plistener) = 0;

		/// <summary>
		/// ɾ�������� seek ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_seek_listener(QIPlayerSeekListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в����� seek ����
		/// </summary>
		virtual void remove_all_player_seek_listeners() = 0;

		/// <summary>
		/// ��Ӳ����� sei ���ݼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_sei_data_listener(QIPlayerSEIDataListener* plistener) = 0;

		/// <summary>
		/// ɾ�������� sei ���ݼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_sei_data_listener(QIPlayerSEIDataListener* plistener) = 0;

		/// <summary>
		///  ɾ�����в����� sei ���ݼ���
		/// </summary>
		virtual void remove_all_player_sei_data_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������ͼ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) = 0;

		/// <summary>
		/// ɾ����������ͼ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_shoot_video_listener(QIPlayerShootVideoListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������ͼ����
		/// </summary>
		virtual void remove_all_player_shoot_video_listeners() = 0;

		/// <summary>
		/// ��Ӳ����������ٶȸı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_speed_change_listener(QIPlayerSpeedListener* plistener) = 0;

		/// <summary>
		/// ɾ�������������ٶȸı����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_speed_change_listener(QIPlayerSpeedListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в����������ٶȸı����
		/// </summary>
		virtual void remove_all_player_speed_change_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������Ļ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_subtitle_listener(QIPlayerSubtitleListener* plistener) = 0;

		/// <summary>
		/// ɾ����������Ļ����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_subtitle_listener(QIPlayerSubtitleListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������Ļ����
		/// </summary>
		virtual void remove_all_player_subtitle_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������Ƶ���ݼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_video_data_listener(QIPlayerVideoDataListener* plistener) = 0;

		/// <summary>
		/// ɾ����������Ƶ���ݼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_video_data_listener(QIPlayerVideoDataListener* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������Ƶ���ݼ���
		/// </summary>
		virtual void remove_all_player_video_data_listeners() = 0;

		/// <summary>
		/// ��Ӳ�������Ƶ�������ͼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) = 0;

		/// <summary>
		/// ɾ����������Ƶ�������ͼ���
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_video_decode_type_listener(QIPlayerVideoDecodeListender* plistener) = 0;

		/// <summary>
		/// ɾ�����в�������Ƶ�������ͼ���
		/// </summary>
		virtual void remove_all_player_video_decode_type_listeners() = 0;

		/// <summary>
		/// �����������Ƶ����仯����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void add_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) = 0;

		/// <summary>
		/// ɾ����������Ƶ����仯����
		/// </summary>
		/// <param name="plistener"> ���� </param>
		virtual void remove_player_video_frame_size_change_listener(QIPlayerVideoFrameSizeChangeListener* plistener) = 0;

		/// <summary>
		/// ɾ��������������Ƶ����仯����
		/// </summary>
		virtual void remove_all_player_video_frame_size_change_listeners() = 0;
	};
}

