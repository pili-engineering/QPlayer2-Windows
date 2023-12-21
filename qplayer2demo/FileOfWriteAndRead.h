#pragma once
#include <string>
#include "PlayerUrlListModel.h"
#include <list>
#include "CurrentDataModel.h"
#include <QVideoType.h>
#include <QSampleFormat.h>
#include <QChannelLayout.h>
class FileOfWriteAndRead
{
public:
	FileOfWriteAndRead() = delete;
	~FileOfWriteAndRead() = delete;


	FileOfWriteAndRead(const FileOfWriteAndRead&) = delete;

	FileOfWriteAndRead(FileOfWriteAndRead&&) = delete;

	FileOfWriteAndRead& operator=(const FileOfWriteAndRead&) = delete;

	FileOfWriteAndRead& operator=(FileOfWriteAndRead&&) = delete;
public:


	static bool write_setting_local_file(const std::string& file_name, CurrentDataModel * pmodel);

	static CurrentDataModel* read_setting_local_file(const std::string& file_name);

	static std::list<PlayerUrlListModel*> read_json_from_local_file(const std::string& file_name);


	static bool write_json_to_local_file(const std::string& file_name, std::list<PlayerUrlListModel*> model);

	static bool write_image_to_local_file(const uint8_t* pjpeg_data, uint64_t size, const std::string& file_name);

	static bool write_video_data_to_local_file(int width, int height, QMedia::QVideoType video_type, uint8_t* buffer, uint64_t size);

	static bool write_audio_data_to_local_file(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, uint8_t* audio_data, uint64_t size);

	static LONG WINAPI write_mini_dump_to_local(EXCEPTION_POINTERS* exceptionInfo);
private:
	static std::string decoder_to_string(QMedia::QPlayerSetting::QPlayerDecoder decoder);

	static QMedia::QPlayerSetting::QPlayerDecoder string_to_decoder(const std::string& decoder);

	static std::string seek_mode_to_string(QMedia::QPlayerSetting::QPlayerSeek seek_mode);

	static QMedia::QPlayerSetting::QPlayerSeek string_to_seek_mode(const std::string& seek_mode);

	static std::string play_start_to_string(QMedia::QPlayerSetting::QPlayerStart play_start);

	static QMedia::QPlayerSetting::QPlayerStart string_to_play_start(std::string play_start);

	static std::string render_radio_to_string(QMedia::QPlayerSetting::QPlayerRenderRatio render_radio);

	static QMedia::QPlayerSetting::QPlayerRenderRatio string_to_render_radio(const std::string& render_radio);

	static std::string blind_to_string(QMedia::QPlayerSetting::QPlayerBlind blind);

	static QMedia::QPlayerSetting::QPlayerBlind string_to_blind(const std::string& blind);

	static std::string quality_immediatyly_to_string(QualityImmediatyly immediatyly);

	static QualityImmediatyly string_to_quality_immediatyly(const std::string& immediatyly);

	static std::string url_type_to_string(QMedia::QUrlType url_type);

	static QMedia::QUrlType string_to_url_type(const std::string& url_type);

	static std::string render_type_to_string(QMedia::QVideoRenderType render_type);

	static QMedia::QVideoRenderType string_to_render_type(const std::string& render_type);
public:
	static std::string GB2312_To_UTF8(const std::string& str);

	static std::string UTF8_To_GB2312(const std::string& utf8_text);
};
