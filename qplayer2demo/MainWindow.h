#pragma once
#include "framework.h"
#include <QIPlayerListenersHeader.h>
#include "ToastWindow.h"
#include "PlayerUrlListModelManager.h"
#include "UrlSetting.h"
#include "PlayerMenuSettingModelManager.h"
#include "PlayStartPostitionWindow.h"
namespace QMedia {
    class QIPlayerContext;
    class QMediaModel;
}
class VideoRenderWindow;
class PlayerWindow;
class UrlListWindow;
class CurrentDataModelManager;
class MainWindow :
	public QMedia::QIPlayerStateChangeListener,
	QMedia::QIPlayerRenderListener,
	QMedia::QIPlayerFPSListener,
	QMedia::QIPlayerAudioDataListener,
	QMedia::QIPlayerAudioListener,
	QMedia::QIPlayerAuthenticationListener,
	QMedia::QIPlayerBiteRateListener,
	QMedia::QIPlayerBufferingListener,
	QMedia::QIPlayerCommandNotAllowListener,
	QMedia::QIPlayerDownloadListener,
	QMedia::QIPlayerFormatListener,
	QMedia::QIPlayerMediaNetworkListener,
	QMedia::QIPlayerProgressListener,
	QMedia::QIPlayerQualityListener,
	QMedia::QIPlayerSeekListener,
	QMedia::QIPlayerShootVideoListener,
	QMedia::QIPlayerSEIDataListener,
	QMedia::QIPlayerSpeedListener,
	QMedia::QIPlayerSubtitleListener,
	QMedia::QIPlayerVideoDataListener,
	QMedia::QIPlayerVideoDecodeListender,
	QMedia::QIPlayerVideoFrameSizeChangeListener
{

private:
    static LRESULT CALLBACK main_window_proc(HWND hwnd, UINT uMsg, WPARAM w_param, LPARAM l_param);
    static BOOL CALLBACK resize_child_windows_proc(HWND hwnd_child, LPARAM l_param);
   
    void url_Click_call_back(HWND hwnd, QMedia::QMediaModel* pmodel);

	void on_state_changed(QMedia::QPlayerState state) override;

    void on_first_frame_rendered(int64_t elapsed_time) override;

    void on_fps_changed(long fps) override;

	void on_audio_data(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, uint8_t* paudio_data, uint64_t size) override;

	void on_mute_changed(bool is_mute) override;

	void on_authentication_failed(QMedia::QAuthenticationErrorType error) override;

	void on_authentication_success() override;

	void on_bite_rate_changed(int bit_rate) override;

	void on_buffering_start() override;

	void on_buffering_end() override;

	void on_command_not_allow(const std::string &command_name, QMedia::QPlayerState state) override;

	void on_download_changed(int64_t download_speed, int64_t buffer_pos) override;

	void on_format_not_support() override;

	void on_reconnect_start(const std::string &user_type, QMedia::QUrlType url_type, const std::string& url, int retry_time) override;

	void on_reconnect_end(const std::string &user_type, QMedia::QUrlType url_type, const std::string& url, int retry_time, QMedia::QOpenError error) override;

	void on_open_failed(const std::string &user_type, QMedia::QUrlType url_type, const std::string& url, QMedia::QOpenError error) override;

	void on_progress_changed(int64_t progress, int64_t duration) override;

	void on_quality_switch_start(const std::string &user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) override;

	void on_quality_switch_complete(const std::string &user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) override;

	void on_quality_switch_canceled(const std::string &user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) override;

	void on_quality_switch_failed(const std::string &user_type, QMedia::QUrlType url_type, int old_quality, int new_quality) override;

	void on_quality_switch_retry_later(const std::string &user_type, QMedia::QUrlType url_type) override;
	
	void on_seek_success() override;

	void on_seek_failed() override;

	void on_shoot_video_success(uint8_t* pimage_data, uint64_t size, int width, int height, QMedia::QShootVideoType type) override;

	void on_shoot_video_failed() override;

	void on_sei_data(uint8_t* pdata, uint64_t size) override;

	void on_speed_changed(float speed) override;

	void on_subtitle_text_changed(const std::string &text) override;

	void on_subtitle_name_changed(const std::string &name) override;

	void on_subtitle_enable(bool enable) override;

	void on_subtitle_loaded(const std::string &name, bool result) override;

	void on_subtitle_decoded(const std::string &name, bool result) override;

	void on_video_data(int width, int height, QMedia::QVideoType video_type, uint8_t* pbuffer, uint64_t size) override;

	void on_video_decode_by_type(QMedia::QDecoderType type) override;

	void on_not_support_codec_format(int codec_id) override;

	void on_video_frame_size_changed(int width, int height) override;

	void add_listeners();
public:
    MainWindow(HINSTANCE instance, int n_cmd_show);

    ~MainWindow();

    MainWindow(const MainWindow&) = delete;

    MainWindow(MainWindow&&) = delete;

    MainWindow& operator=(const MainWindow&) = delete;

    MainWindow& operator=(MainWindow&&) = delete;

    HWND get_hwnd();
private:
    LRESULT on_create();
    LRESULT on_resize();
    LRESULT on_create_play_menu();
	void SaveJpgToFile(const uint8_t* jpegData, uint64_t size, const std::string& filePath);
    static int get_render_window_height(int parent_window_height);
    static int get_render_window_width(int parent_window_width);
    void button_click(int button_id);


	void seek_bar_click(long current_time);


	std::string to_date_string(int64_t time);

    bool notify_resize_to_player();


	void updata_menu_ui(int button_id);

	void update_quality_list_window();

	void quality_change_click(int item_id);
private:

    HWND mHwnd;
    HINSTANCE mHinstance;


	std::string mProgressTimeStr;


    CurrentDataModelManager* mpCurrentDataModelManger;

    static const int MAX_LOADSTRING = 100;
    WCHAR mTitle[MAX_LOADSTRING];                  // 标题栏文本
    WCHAR mWindowClass[MAX_LOADSTRING];            // 主窗口类名


	PlayerWindow* mpPlayerWindow;

	UrlListWindow* mpUrlListWindow;

	ToastWindow* mpToastWindow;

	HWND mPlayButton;

	HWND mPlayQualityButton;

	HWND mSeekBar;

	HWND mFirstFrameText;

	HWND mFPSText;

	HWND mPlayerStateText;

	HWND mPlayerDownLoadText;

	HWND mPlayerBiteRateText;

	HWND mPlayerBuffering;
	HWND mPlayerSubtitle;

	HWND mPlayerProgressAndDurationText;

	HWND mPlayerQualityChangeListWindow;

	PlayerUrlListModelManager* mpUrlListModelManger;

	UrlSetting* mpUrlSettingWindow;

	PlayerMenuSettingModelManager* mpSettingMenuManager;

	float mHeight;

	float mWidth;
};

 