#include "FileOfWriteAndRead.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <QMediaModelBuilder.h>
#include <nlohmann/json.hpp>
#include <iconv.h>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <dbghelp.h>
#include <mmsystem.h>
//播放器设置写入文件
bool FileOfWriteAndRead::write_setting_local_file(const std::string& file_name, CurrentDataModel* pmodel) {
#ifdef _DEBUG
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::string file_path = currentPath.string() + "\\qplayerLocalFile\\" + file_name;
#else
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
#endif

	nlohmann::json current_json = nlohmann::json();

	current_json["play_start_positon"] = pmodel->get_player_start_position();
	current_json["decoder"] = decoder_to_string(pmodel->get_decoder());
	current_json["seek_mode"] = seek_mode_to_string(pmodel->get_seek_mode());
	current_json["player_start"] = play_start_to_string(pmodel->get_player_start());
	current_json["render_ratio"] = render_radio_to_string(pmodel->get_render_ratio());
	current_json["blind"] = blind_to_string(pmodel->get_blind());
	current_json["sei_enable"] = pmodel->get_sei_enable();
	current_json["background_enable"] = pmodel->get_background_enable();
	current_json["quality_immediatyly"] = GB2312_To_UTF8(quality_immediatyly_to_string(pmodel->get_quality_immediatyly()));
	current_json["subtitle_enable"] = pmodel->get_subtitle_enable();
	current_json["play_speed"] = pmodel->get_play_speed();
	current_json["mute_enable"] = pmodel->get_mute_enable();
	current_json["force_authentication_enable"] = pmodel->get_force_authentication_enable();

	std::ofstream file(file_path, std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		return false;
	}
	file << std::setw(4) << current_json << std::endl;
	file.close();
}

//从文件中读取播放器设置
CurrentDataModel* FileOfWriteAndRead::read_setting_local_file(const std::string& file_name) {
#ifdef _DEBUG
	std::filesystem::path current_path = std::filesystem::current_path();
	std::string file_path = current_path.string() + "\\qplayerLocalFile\\" + file_name;
#else
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
#endif
	std::ifstream file(file_path);
	CurrentDataModel* pcurrent = new CurrentDataModel();
	if (!file.is_open()) {
		return pcurrent;
	}
	// 读取文件内容到一个字符串
	std::string file_content((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// 解析json数据
	nlohmann::json json_data;
	try {
		json_data = nlohmann::json::parse(file_content);
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
		return pcurrent;
	}
	pcurrent->set_background_enable(json_data["background_enable"]);
	pcurrent->set_blind(string_to_blind(json_data["blind"]));
	pcurrent->set_decoder(string_to_decoder(json_data["decoder"]));
	pcurrent->set_force_authentication_enable(json_data["force_authentication_enable"]);
	pcurrent->set_mute_enable(json_data["mute_enable"]);
	pcurrent->set_player_start(string_to_play_start(json_data["player_start"]));
	pcurrent->set_player_start_position(json_data["play_start_positon"]);
	pcurrent->set_play_speed(json_data["play_speed"]);
	pcurrent->set_quality_immediatyly(string_to_quality_immediatyly(UTF8_To_GB2312(json_data["quality_immediatyly"])));
	pcurrent->set_render_ratio(string_to_render_radio(json_data["render_ratio"]));
	pcurrent->set_seek_mode(string_to_seek_mode(json_data["seek_mode"]));
	pcurrent->set_sei_enable(json_data["sei_enable"]);
	pcurrent->set_subtitle_enable(json_data["subtitle_enable"]);

	return pcurrent;
}
//播放地址文件写入
std::list<PlayerUrlListModel*> FileOfWriteAndRead::read_json_from_local_file(const std::string& file_name) {
#ifdef _DEBUG
	std::filesystem::path current_path = std::filesystem::current_path();
	std::string file_path = current_path.string() + "\\qplayerLocalFile\\" + file_name;
#else
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
#endif
	std::list<PlayerUrlListModel*> model_list = std::list<PlayerUrlListModel*>();
	std::ifstream file(file_path);
	if (!file.is_open()) {
		return model_list;
	}
	// 读取文件内容到一个字符串
	std::string file_content((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// 解析json数据
	nlohmann::json json_data;
	try {
		json_data = nlohmann::json::parse(file_content);
	}
	catch (const std::exception& e) {
		std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
		return model_list;
	}
	if (json_data.is_array())
	{
		for (auto& json : json_data) {
			std::string name = UTF8_To_GB2312(json["name"]);
			bool is_live = json["is_live"];

			QMedia::QMediaModelBuilder* pmodel_builder = new QMedia::QMediaModelBuilder;
			auto stream_ele_array = json["stream_element"];
			if (stream_ele_array.is_array())
			{
				for (auto& stream_ele : stream_ele_array) {

					QMedia::QUrlType url_type = string_to_url_type(stream_ele["url_type"]);
					std::string user_type = stream_ele["user_type"];
					std::string url = UTF8_To_GB2312(stream_ele["url"]);
					int quality = stream_ele["quality"];
					std::string back_up_url = stream_ele["backup_url"];
					bool is_selected = stream_ele["is_selected"];
					std::string referer = stream_ele["referer"];
					std::string hls_drm_key = stream_ele["hls_drm_key"];
					std::string mp4_drm_key = stream_ele["mp4_drm_key"];
					QMedia::QVideoRenderType render_type = string_to_render_type(stream_ele["render_type"]);
					pmodel_builder->add_stream_element(user_type, url_type, quality, url, is_selected, referer, back_up_url, render_type, hls_drm_key, mp4_drm_key);
				}
			}

			auto subtitle_ele_array = json["subtitle_element"];
			if (subtitle_ele_array.is_array())
			{
				for (auto& subtitle_ele : subtitle_ele_array) {

					std::string subtitle_name = UTF8_To_GB2312(subtitle_ele["name"]);
					std::string subtitle_url = UTF8_To_GB2312(subtitle_ele["url"]);
					bool subtitle_is_selected = subtitle_ele["is_selelcted"];
					pmodel_builder->add_subtitle_element(subtitle_name,subtitle_url,subtitle_is_selected);
				}
			}
			PlayerUrlListModel* pmodel = new PlayerUrlListModel(pmodel_builder->build(is_live), name);
			model_list.emplace_back(pmodel);
			delete pmodel_builder;

		}
	}
	file.close();
	return model_list;
}
//读取播放地址文件
bool FileOfWriteAndRead::write_json_to_local_file(const std::string& file_name, std::list<PlayerUrlListModel*> model_list) {
	//$(ProjectDir)dependency\qplayer-iconv
#ifdef _DEBUG
	std::filesystem::path current_path = std::filesystem::current_path();
	std::string file_path = current_path.string() + "\\qplayerLocalFile\\" + file_name;
#else
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
#endif
	auto pjson_array = nlohmann::basic_json<>({}, false, nlohmann::json::value_t::array);
	for (PlayerUrlListModel* pmodel : model_list)
	{
		nlohmann::json json = nlohmann::json();
		json["name"] = GB2312_To_UTF8(pmodel->get_name());
		json["is_live"] = pmodel->get_media_model()->is_live();

		auto stream_ele_array = nlohmann::basic_json<>({}, false, nlohmann::json::value_t::array);
		for (QMedia::QStreamElement* pele : pmodel->get_media_model()->get_stream_elements())
		{
			nlohmann::json stream_json = nlohmann::json();
			stream_json["user_type"] = pele->get_user_type();
			stream_json["url_type"] = url_type_to_string(pele->get_url_type());
			stream_json["url"] = GB2312_To_UTF8(pele->get_url());
			stream_json["quality"] = pele->get_quality_index();
			stream_json["is_selected"] = pele->is_selected();
			stream_json["backup_url"] = pele->get_back_url();
			stream_json["referer"] = pele->get_referer();
			stream_json["hls_drm_key"] = pele->get_hls_drm_key();
			stream_json["mp4_drm_key"] = pele->get_mp4_drm_key();
			stream_json["render_type"] = render_type_to_string(pele->get_render_type());
			stream_ele_array.push_back(stream_json);
		}
		json["stream_element"] = stream_ele_array;

		auto subtitle_ele_array = nlohmann::basic_json<>({}, false, nlohmann::json::value_t::array);
		for (QMedia::QSubtitleElement * pele : pmodel->get_media_model()->get_subtitle_elements())
		{
			nlohmann::json subtitle_json = nlohmann::json();
			subtitle_json["name"] = GB2312_To_UTF8(pele->get_name());
			subtitle_json["url"] = GB2312_To_UTF8(pele->get_url());
			subtitle_json["is_selelcted"] = pele->is_selected();
			subtitle_ele_array.push_back(subtitle_json);
		}
		json["subtitle_element"] = subtitle_ele_array;
		pjson_array.push_back(json);
	}
	std::ofstream file(file_path, std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		return false;
	}
	file << std::setw(4) << pjson_array << std::endl;
	file.close();
	return true;
}
bool FileOfWriteAndRead::write_image_to_local_file(const uint8_t* pjpeg_data, uint64_t size, const std::string& file_name)
{
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "\\shootImage\\" + file_name;
	std::ofstream outputFile(file_path, std::ios::binary);
	if (outputFile)
	{
		outputFile.write(reinterpret_cast<const char*>(pjpeg_data), size);
		outputFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

int count = 0;
bool FileOfWriteAndRead::write_video_data_to_local_file(int width, int height, QMedia::QVideoType video_type, uint8_t* buffer, uint64_t size) {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "\\shootImage\\" +std::to_string(1) + ".yuv";
	std::ofstream outputFile(file_path, std::ios::binary | std::ios::app);
	if (!outputFile)
	{
		std::cerr << "无法打开文件：" << file_path << std::endl;
		return false;
	}

	// 写入 Y 分量
	outputFile.write(reinterpret_cast<const char*>(buffer), size );
	outputFile.close();

	std::cout << "YUV420p 数据已写入文件：" << file_path << std::endl;
	//count++;

	return true;
}



bool FileOfWriteAndRead::write_audio_data_to_local_file(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, uint8_t* audio_data, uint64_t size) {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "\\shootImage\\" + "1.pcm";
	std::ofstream outputFile(file_path, std::ios::binary | std::ios::app);
	if (!outputFile)
	{
		// 文件打开失败，处理错误
		return false;
	}
	if (count == 0)
	{
		// 写入 PCM 文件的头部信息
		WAVEFORMATEX waveFormat;
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nChannels = channel_num;
		waveFormat.nSamplesPerSec = sample_rate;
		waveFormat.nAvgBytesPerSec = sample_rate * channel_num * sizeof(short);
		waveFormat.nBlockAlign = channel_num * sizeof(short);
		waveFormat.wBitsPerSample = sizeof(short) * 8;
		waveFormat.cbSize = 0;

		DWORD headerSize = sizeof(waveFormat) + sizeof(DWORD);
		DWORD dataSize = size * sizeof(short);
		DWORD fileSize = headerSize + dataSize - 8;

		// 写入文件头
		outputFile.write("RIFF", 4);
		outputFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(DWORD));
		outputFile.write("WAVEfmt ", 8);
		outputFile.write(reinterpret_cast<const char*>(&headerSize), sizeof(DWORD));
		outputFile.write(reinterpret_cast<const char*>(&waveFormat), sizeof(waveFormat));
		outputFile.write("data", 4);
		outputFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(DWORD));
	}



	// 写入音频数据
	outputFile.write(reinterpret_cast<const char*>(audio_data), size);
	count = 1;
	// 关闭文件
	outputFile.close();
	return true;
}






/************************************播放器枚举类型和字符串相互转换*****************************************************/
std::string FileOfWriteAndRead::decoder_to_string(QMedia::QPlayerSetting::QPlayerDecoder decoder) {
	switch (decoder)
	{
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO:
		return "QPLAYER_DECODER_SETTING_AUTO";
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY:
		return "QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY";
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_SOFT_PRIORITY:
		return "QPLAYER_DECODER_SETTING_SOFT_PRIORITY";
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY:
		return "QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY";
	default:
		return "QPLAYER_DECODER_SETTING_AUTO";
	}
}

QMedia::QPlayerSetting::QPlayerDecoder FileOfWriteAndRead::string_to_decoder(const std::string& decoder) {
	if (decoder == "QPLAYER_DECODER_SETTING_AUTO")
	{
		return QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO;
	}
	else if (decoder == "QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY")
	{
		return QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY;
	}
	else if (decoder == "QPLAYER_DECODER_SETTING_SOFT_PRIORITY")
	{
		return QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_SOFT_PRIORITY;
	}
	else if(decoder == "QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY")
	{
		return QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY;
	}
	else
	{
		return QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO;
	}
}

std::string FileOfWriteAndRead::seek_mode_to_string(QMedia::QPlayerSetting::QPlayerSeek seek_mode) {
	switch (seek_mode)
	{
	case QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL:
		return "QPLAYER_SEEK_SETTING_NORMAL";
	case QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_ACCURATE:
		return "QPLAYER_SEEK_SETTING_ACCURATE";
	default:
		return "QPLAYER_SEEK_SETTING_NORMAL";
	}
}

QMedia::QPlayerSetting::QPlayerSeek FileOfWriteAndRead::string_to_seek_mode(const std::string& seek_mode) {
	if (seek_mode == "QPLAYER_SEEK_SETTING_NORMAL")
	{
		return QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL;
	}
	else if (seek_mode == "QPLAYER_SEEK_SETTING_ACCURATE")
	{
		return QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_ACCURATE;
	}
	else
	{
		return QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL;
	}
}

std::string FileOfWriteAndRead::play_start_to_string(QMedia::QPlayerSetting::QPlayerStart play_start) {
	switch (play_start)
	{
	case QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING:
		return "QPLAYER_START_SETTING_PLAYING";
	case QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PAUSE:
		return "QPLAYER_START_SETTING_PAUSE";
	default:
		return "QPLAYER_START_SETTING_PLAYING";
	}
}

QMedia::QPlayerSetting::QPlayerStart FileOfWriteAndRead::string_to_play_start(std::string play_start) {
	if (play_start == "QPLAYER_START_SETTING_PLAYING")
	{
		return QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING;
	}
	else if (play_start == "QPLAYER_START_SETTING_PAUSE")
	{
		return QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PAUSE;
	}
	else
	{
		return QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING;
	}
}

std::string FileOfWriteAndRead::render_radio_to_string(QMedia::QPlayerSetting::QPlayerRenderRatio render_radio) {
	switch (render_radio)
	{
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO:
		return "QPLAYER_RATIO_SETTING_AUTO";
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_STRETCH:
		return "QPLAYER_RATIO_SETTING_STRETCH";
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_FULL_SCREEN:
		return "QPLAYER_RATIO_SETTING_FULL_SCREEN";
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_16_9:
		return "QPLAYER_RATIO_SETTING_16_9";
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_4_3:
		return "QPLAYER_RATIO_SETTING_4_3";
	default:
		return "QPLAYER_RATIO_SETTING_AUTO";
	}
}

QMedia::QPlayerSetting::QPlayerRenderRatio FileOfWriteAndRead::string_to_render_radio(const std::string& render_radio) {
	if (render_radio == "QPLAYER_RATIO_SETTING_AUTO")
	{
		return QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO;
	}
	else if (render_radio == "QPLAYER_RATIO_SETTING_STRETCH")
	{
		return QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_STRETCH;
	}
	else if (render_radio == "QPLAYER_RATIO_SETTING_FULL_SCREEN")
	{
		return QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_FULL_SCREEN;
	}
	else if (render_radio == "QPLAYER_RATIO_SETTING_16_9")
	{
		return QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_16_9;
	}
	else if (render_radio == "QPLAYER_RATIO_SETTING_4_3")
	{
		return QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_4_3;
	}
	else
	{
		return QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO;
	}
}

std::string FileOfWriteAndRead::blind_to_string(QMedia::QPlayerSetting::QPlayerBlind blind) {
	switch (blind)
	{
	case QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_NONE:
		return "QPLAYER_BLIND_SETTING_NONE";
	case QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_RED:
		return "QPLAYER_BLIND_SETTING_RED";
	case QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_GREEN:
		return "QPLAYER_BLIND_SETTING_GREEN";
	case QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_BLUE:
		return "QPLAYER_BLIND_SETTING_BLUE";
	default:
		return "QPLAYER_BLIND_SETTING_NONE";
	}
}

QMedia::QPlayerSetting::QPlayerBlind FileOfWriteAndRead::string_to_blind(const std::string& blind) {
	if (blind == "QPLAYER_BLIND_SETTING_RED")
	{
		return QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_RED;
	}
	else if (blind == "QPLAYER_BLIND_SETTING_GREEN")
	{
		return QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_GREEN;
	}
	else if (blind == "QPLAYER_BLIND_SETTING_BLUE")
	{
		return QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_BLUE;
	}
	else
	{
		return QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_NONE;
	}
}

std::string FileOfWriteAndRead::quality_immediatyly_to_string(QualityImmediatyly immediatyly) {
	switch (immediatyly)
	{
	case IMMEDIATYLY_TRUE:
		return "立即切换";
	case IMMEDIATYLY_FALSE:
		return "无缝切换";
	case IMMEDIATYLY_CUSTOM:
		return "直播立即点播无缝";
	default:
		return "直播立即点播无缝";
	}
}

QualityImmediatyly FileOfWriteAndRead::string_to_quality_immediatyly(const std::string& immediatyly) {
	if (immediatyly == "立即切换")
	{
		return IMMEDIATYLY_TRUE;
	}
	else if (immediatyly == "无缝切换")
	{
		return IMMEDIATYLY_FALSE;
	}
	else if (immediatyly == "直播立即点播无缝")
	{
		return IMMEDIATYLY_CUSTOM;
	}
	else
	{
		return IMMEDIATYLY_CUSTOM;
	}
}

std::string FileOfWriteAndRead::url_type_to_string(QMedia::QUrlType url_type) {
	switch (url_type)
	{
	case QMedia::QUrlType::QAUDIO_AND_VIDEO:
		return "QAUDIO_AND_VIDEO";
	case QMedia::QUrlType::QAUDIO:
		return "QAUDIO";
	case QMedia::QUrlType::QVIDEO:
		return "QVIDEO";
	default:
		return "NONE";
	}
}

QMedia::QUrlType FileOfWriteAndRead::string_to_url_type(const std::string& url_type) {
	if (url_type == "QAUDIO_AND_VIDEO")
	{
		return QMedia::QUrlType::QAUDIO_AND_VIDEO;
	}
	else if (url_type == "QAUDIO") {
		return QMedia::QUrlType::QAUDIO;
	}
	else if (url_type == "QVIDEO") {
		return QMedia::QUrlType::QVIDEO;
	}
	else {
		return QMedia::QUrlType::NONE;
	}
}

QMedia::QVideoRenderType FileOfWriteAndRead::string_to_render_type(const std::string& render_type) {
	if (render_type == "PLANE")
	{
		return QMedia::QVideoRenderType::PLANE;
	}

	else if (render_type == "PANORAMA_EQUIRECT_ANGULAR") {
		return QMedia::QVideoRenderType::PANORAMA_EQUIRECT_ANGULAR;
	}
	else
	{
		return QMedia::QVideoRenderType::NONE;
	}
}

std::string FileOfWriteAndRead::render_type_to_string(QMedia::QVideoRenderType render_type) {
	switch (render_type)
	{
	case QMedia::QVideoRenderType::PLANE:
		return "PLANE";
	case QMedia::QVideoRenderType::PANORAMA_EQUIRECT_ANGULAR:
		return "PANORAMA_EQUIRECT_ANGULAR";
	default:
		return "NONE";
	}
}

/********************************字符串 GB2312 和 UTF8 编码格式相互转换*************************************************/
std::string FileOfWriteAndRead::GB2312_To_UTF8(const std::string& input)
{
	std::string output;

	// 打开转换句柄
	iconv_t converter = iconv_open("UTF-8", "GB2312");
	if (converter == (iconv_t)-1) {
		std::cerr << "无法打开编码转换句柄" << std::endl;
		return output;
	}

	// 输入和输出缓冲区
	const char* pin_buf = const_cast<char*>(input.c_str());
	size_t in_bytes_left = input.length();
	size_t out_buf_size = input.length() * 4;  // 根据实际情况估计输出缓冲区大小
	char* pout_buf = new char[out_buf_size];
	char* pout_ptr = pout_buf;
	size_t out_bytes_left = out_buf_size;

	// 进行编码转换
	size_t result = iconv(converter, &pin_buf, &in_bytes_left, &pout_ptr, &out_bytes_left);
	if (result == (size_t)-1) {
		std::cerr << "编码转换失败" << std::endl;
		delete[] pout_buf;
		iconv_close(converter);
		return output;
	}

	// 关闭转换句柄
	iconv_close(converter);

	// 构造输出字符串
	output.assign(pout_buf, out_buf_size - out_bytes_left);

	// 释放内存
	delete[] pout_buf;

	return output;
}

std::string FileOfWriteAndRead::UTF8_To_GB2312(const std::string& utf8_text) {
	// 创建转换句柄
	iconv_t iconv_handle = iconv_open("GB2312", "UTF-8");
	if (iconv_handle == (iconv_t)(-1)) {
		perror("iconv_open");
		return "";
	}

	// 准备输入和输出缓冲区
	size_t input_length = strlen(utf8_text.c_str());
	size_t output_length = input_length * 2;  // 假设输出缓冲区足够大
	char* output = new char[output_length];
	memset(output, 0, output_length);

	const char* pinput_ptr = const_cast<char*>(utf8_text.c_str());
	char* poutput_ptr = output;
	size_t converted_bytes = iconv(iconv_handle, &pinput_ptr, &input_length, &poutput_ptr, &output_length);
	if (converted_bytes == (size_t)(-1)) {
		perror("iconv");
		delete[] output;
		iconv_close(iconv_handle);
		return "";
	}

	std::string output_string = std::string(output);
	iconv_close(iconv_handle);
	delete[] output;
	return output_string;
}


LONG WINAPI FileOfWriteAndRead::write_mini_dump_to_local(EXCEPTION_POINTERS* exceptionInfo)
{
	auto currentTime = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());
	std::ostringstream oss;
	oss << timestamp.count();
	std::string timestamp_string = oss.str();
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + timestamp_string + ".dmp";
	HANDLE hDumpFile = CreateFile(
		file_path.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hDumpFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ExceptionPointers = exceptionInfo;
		dumpInfo.ClientPointers = TRUE;

		MiniDumpWriteDump(
			GetCurrentProcess(),
			GetCurrentProcessId(),
			hDumpFile,
			MiniDumpNormal,
			&dumpInfo,
			NULL,
			NULL
		);

		// 关闭文件句柄
		CloseHandle(hDumpFile);
	}

	// 执行默认的异常处理
	return EXCEPTION_EXECUTE_HANDLER;
}