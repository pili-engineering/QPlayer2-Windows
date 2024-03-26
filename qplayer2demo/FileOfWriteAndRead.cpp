#include "FileOfWriteAndRead.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <QMediaModelBuilder.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <dbghelp.h>
#include <mmsystem.h>
//����������д���ļ�
bool FileOfWriteAndRead::write_setting_local_file(const std::string& file_name, CurrentDataModel* pmodel) {
#ifdef _DEBUG
	char current_path[FILENAME_MAX];
	GetModuleFileName(NULL, current_path, FILENAME_MAX);
	//GetCurrentDirectoryA(MAX_PATH, current_path);
	std::string directory = current_path;
	size_t pos = directory.find("out");
	if (pos != std::string::npos)
	{
		directory = directory.substr(0, pos); // ���� "out" ���ڵ��ַ���
	}
	else {
		pos = directory.find("qplayer2demo.exe");
		directory = directory.substr(0, pos); // ���� "bin" ���ڵ��ַ���
	}
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
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
	return true;
}

//���ļ��ж�ȡ����������
CurrentDataModel* FileOfWriteAndRead::read_setting_local_file(const std::string& file_name) {
#ifdef _DEBUG
	char current_path[FILENAME_MAX];
	GetModuleFileName(NULL, current_path, FILENAME_MAX);
	//GetCurrentDirectoryA(MAX_PATH, current_path);
	std::string directory = current_path;
	size_t pos = directory.find("out");
	if (pos != std::string::npos)
	{
		directory = directory.substr(0, pos); // ���� "out" ���ڵ��ַ���
	}
	else {
		pos = directory.find("qplayer2demo.exe");
		directory = directory.substr(0, pos); // ���� "bin" ���ڵ��ַ���
	}
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
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
	// ��ȡ�ļ����ݵ�һ���ַ���
	std::string file_content((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// ����json����
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
//���ŵ�ַ�ļ�д��
std::list<PlayerUrlListModel*> FileOfWriteAndRead::read_json_from_local_file(const std::string& file_name) {
#ifdef _DEBUG

	char current_path[FILENAME_MAX];
	GetModuleFileName(NULL, current_path, FILENAME_MAX);
	//GetCurrentDirectoryA(MAX_PATH, current_path);
	std::string directory = current_path;
	size_t pos = directory.find("out");
	if (pos != std::string::npos)
	{
		directory = directory.substr(0, pos); // ���� "out" ���ڵ��ַ���
	}
	else {
		pos = directory.find("qplayer2demo.exe");
		directory = directory.substr(0, pos); // ���� "bin" ���ڵ��ַ���
	}
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
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
	// ��ȡ�ļ����ݵ�һ���ַ���
	std::string file_content((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// ����json����
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
			bool reconstruct_time_line = json["reconstruct_time_line"];
			QMedia::QMediaModelBuilder* pmodel_builder = new QMedia::QMediaModelBuilder;
			auto stream_ele_array = json["stream_element"];
			if (stream_ele_array.is_array())
			{
				for (auto& stream_ele : stream_ele_array) {

					QMedia::QUrlType url_type = string_to_url_type(stream_ele["url_type"]);
					std::string user_type = UTF8_To_GB2312(stream_ele["user_type"]);
					std::string url = UTF8_To_GB2312(stream_ele["url"]);
					int quality = stream_ele["quality"];
					std::string back_up_url = UTF8_To_GB2312(stream_ele["backup_url"]);
					bool is_selected = stream_ele["is_selected"];
					std::string referer = UTF8_To_GB2312(stream_ele["referer"]);
					std::string hls_drm_key = UTF8_To_GB2312(stream_ele["hls_drm_key"]);
					std::string mp4_drm_key = UTF8_To_GB2312(stream_ele["mp4_drm_key"]);
					std::string mp4_drm_com_key = UTF8_To_GB2312(stream_ele["mp4_drm_com_key"]);
					std::string mp4_drm_file_key = UTF8_To_GB2312(stream_ele["mp4_drm_file_key"]);
					QMedia::QVideoRenderType render_type = string_to_render_type(stream_ele["render_type"]);
					QMedia::QUrlMethod url_method = string_to_url_method(stream_ele["url_method"]);
					if (hls_drm_key != "")
					{
						pmodel_builder->add_stream_element_hls_drm(GB2312_To_UTF8(user_type), url_type, quality, GB2312_To_UTF8(url), is_selected, GB2312_To_UTF8(referer), GB2312_To_UTF8(back_up_url), render_type, GB2312_To_UTF8(hls_drm_key), url_method);
					}
					else if (mp4_drm_key != "")
					{
						pmodel_builder->add_stream_element_mp4_drm(GB2312_To_UTF8(user_type), url_type, quality, GB2312_To_UTF8(url), is_selected, GB2312_To_UTF8(referer), GB2312_To_UTF8(back_up_url), render_type, GB2312_To_UTF8(mp4_drm_key), url_method);
					}
					else if (mp4_drm_file_key != "" && mp4_drm_com_key != "")
					{
						pmodel_builder->add_stream_element_qn_mp4_drm(GB2312_To_UTF8(user_type), url_type, quality, GB2312_To_UTF8(url), is_selected, GB2312_To_UTF8(referer), GB2312_To_UTF8(back_up_url), render_type, GB2312_To_UTF8(mp4_drm_com_key), GB2312_To_UTF8(mp4_drm_file_key), url_method);
					}
					else
					{
						pmodel_builder->add_stream_element(GB2312_To_UTF8(user_type), url_type, quality, GB2312_To_UTF8(url), is_selected, GB2312_To_UTF8(referer), GB2312_To_UTF8(back_up_url), render_type, url_method);
					}
				}
			}

			auto subtitle_ele_array = json["subtitle_element"];
			if (subtitle_ele_array.is_array())
			{
				for (auto& subtitle_ele : subtitle_ele_array) {

					std::string subtitle_name = UTF8_To_GB2312(subtitle_ele["name"]);
					std::string subtitle_url = UTF8_To_GB2312(subtitle_ele["url"]);
					bool subtitle_is_selected = subtitle_ele["is_selelcted"];
					pmodel_builder->add_subtitle_element(GB2312_To_UTF8(subtitle_name), GB2312_To_UTF8(subtitle_url),subtitle_is_selected);
				}
			}
			PlayerUrlListModel* pmodel = new PlayerUrlListModel(pmodel_builder->build(is_live, reconstruct_time_line), name);
			model_list.emplace_back(pmodel);
			delete pmodel_builder;
			pmodel_builder = nullptr;
		}
	}
	file.close();
	return model_list;
}
//��ȡ���ŵ�ַ�ļ�
bool FileOfWriteAndRead::write_json_to_local_file(const std::string& file_name, std::list<PlayerUrlListModel*> model_list) {
#ifdef _DEBUG
	char current_path[FILENAME_MAX];
	GetModuleFileName(NULL, current_path, FILENAME_MAX);
	//GetCurrentDirectoryA(MAX_PATH, current_path);
	std::string directory = current_path;
	size_t pos = directory.find("out");
	if (pos != std::string::npos)
	{
		directory = directory.substr(0, pos); // ���� "out" ���ڵ��ַ���
	}
	else {
		pos = directory.find("qplayer2demo.exe");
		directory = directory.substr(0, pos); // ���� "bin" ���ڵ��ַ���
	}
	std::string file_path = directory + "qplayerLocalFile\\" + file_name;
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
		json["reconstruct_time_line"] = pmodel->get_media_model()->is_reconstruct_time_line();

		auto stream_ele_array = nlohmann::basic_json<>({}, false, nlohmann::json::value_t::array);
		for (QMedia::QStreamElement* pele : pmodel->get_media_model()->get_stream_elements())
		{
			nlohmann::json stream_json = nlohmann::json();
			stream_json["user_type"] = GB2312_To_UTF8(pele->get_user_type());
			stream_json["url_type"] = GB2312_To_UTF8(url_type_to_string(pele->get_url_type()));
			stream_json["url"] = GB2312_To_UTF8(pele->get_url());
			stream_json["quality"] = pele->get_quality_index();
			stream_json["is_selected"] = pele->is_selected();
			stream_json["backup_url"] = GB2312_To_UTF8(pele->get_back_url());
			stream_json["referer"] = GB2312_To_UTF8(pele->get_referer());
			stream_json["hls_drm_key"] = GB2312_To_UTF8(pele->get_hls_drm_key());
			stream_json["mp4_drm_key"] = GB2312_To_UTF8(pele->get_mp4_drm_key());
			stream_json["render_type"] = GB2312_To_UTF8(render_type_to_string(pele->get_render_type()));
			stream_json["url_method"] = GB2312_To_UTF8(url_method_to_string(pele->get_url_method()));
			stream_json["mp4_drm_com_key"] = GB2312_To_UTF8(pele->get_mp4_qn_drm_com_key());
			stream_json["mp4_drm_file_key"] = GB2312_To_UTF8(pele->get_mp4_qn_drm_file_key());
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
	std::string file_path = directory + "\\record\\" +std::to_string(1) + ".yuv";
	std::ofstream outputFile(file_path, std::ios::binary | std::ios::app);
	if (!outputFile)
	{
		std::cerr << "�޷����ļ���" << file_path << std::endl;
		return false;
	}

	// д�� Y ����
	outputFile.write(reinterpret_cast<const char*>(buffer), size );
	outputFile.close();

	std::cout << "YUV420p ������д���ļ���" << file_path << std::endl;
	//count++;

	return true;
}



bool FileOfWriteAndRead::write_audio_data_to_local_file(int sample_rate, QMedia::QSampleFormat format, int channel_num, QMedia::QChannelLayout channel_layout, uint8_t* audio_data, uint64_t size) {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + "\\record\\" + "1.pcm";
	std::ofstream outputFile(file_path, std::ios::binary | std::ios::app);
	if (!outputFile)
	{
		// �ļ���ʧ�ܣ��������
		return false;
	}
	if (count == 0)
	{
		// д�� PCM �ļ���ͷ����Ϣ
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

		// д���ļ�ͷ
		outputFile.write("RIFF", 4);
		outputFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(DWORD));
		outputFile.write("WAVEfmt ", 8);
		outputFile.write(reinterpret_cast<const char*>(&headerSize), sizeof(DWORD));
		outputFile.write(reinterpret_cast<const char*>(&waveFormat), sizeof(waveFormat));
		outputFile.write("data", 4);
		outputFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(DWORD));
	}



	// д����Ƶ����
	outputFile.write(reinterpret_cast<const char*>(audio_data), size);
	count = 1;
	// �ر��ļ�
	outputFile.close();
	return true;
}
//��������¼������
bool FileOfWriteAndRead::clear_record_dir() {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string all_file_path = directory + "\\record\\" + "*.*";
	WIN32_FIND_DATA find_file;
	HANDLE find_handle = FindFirstFile(all_file_path.c_str(), &find_file);

	if (find_handle != INVALID_HANDLE_VALUE) {
		do {
			std::string file_path = directory + "\\record\\" + find_file.cFileName;
			if (!DeleteFile(file_path.c_str())) {
				continue;
			}
		} while (FindNextFile(find_handle, &find_file));

		FindClose(find_handle);
	}
	return true;
}




/************************************������ö�����ͺ��ַ����໥ת��*****************************************************/
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
		return "�����л�";
	case IMMEDIATYLY_FALSE:
		return "�޷��л�";
	case IMMEDIATYLY_CUSTOM:
		return "ֱ�������㲥�޷�";
	default:
		return "ֱ�������㲥�޷�";
	}
}

QualityImmediatyly FileOfWriteAndRead::string_to_quality_immediatyly(const std::string& immediatyly) {
	if (immediatyly == "�����л�")
	{
		return IMMEDIATYLY_TRUE;
	}
	else if (immediatyly == "�޷��л�")
	{
		return IMMEDIATYLY_FALSE;
	}
	else if (immediatyly == "ֱ�������㲥�޷�")
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

std::string FileOfWriteAndRead::url_method_to_string(QMedia::QUrlMethod url_method) {
	switch (url_method)
	{
	case QMedia::QUrlMethod::NORMAL:
		return "NORMAL";
	case QMedia::QUrlMethod::RTSP_TCP:
		return "RTSP_TCP";
	case QMedia::QUrlMethod::RTSP_UDP:
		return "RTSP_UDP";
	default:
		return "NORMAL";
	}
}

QMedia::QUrlMethod FileOfWriteAndRead::string_to_url_method(const std::string& url_method) {
	if (url_method == "RTSP_TCP")
	{
		return QMedia::QUrlMethod::RTSP_TCP;
	}
	else if (url_method == "RTSP_UDP") {
		return QMedia::QUrlMethod::RTSP_UDP;
	}
	else
	{
		return QMedia::QUrlMethod::NORMAL;
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

/********************************�ַ��� GB2312 �� UTF8 �����ʽ�໥ת��*************************************************/
std::string FileOfWriteAndRead::GB2312_To_UTF8(const std::string& input)
{
	if (input == "")
	{
		return "";
	}
	int len = MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) {
		delete[] wstr;
		wstr = NULL;
	}
	std::string str_utf8(str);
	if (str) {
		delete[] str;
		str = NULL;
	}
	return str_utf8;

}

std::string FileOfWriteAndRead::UTF8_To_GB2312(const std::string& utf8_text) {
	if (utf8_text == "")
	{
		return "";
	}
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8_text.c_str(), -1, NULL, 0);

	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);

	MultiByteToWideChar(CP_UTF8, 0, utf8_text.c_str(), -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);

	char* str = new char[len + 1];
	memset(str, 0, len + 1);

	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);

	if (wstr) {
		delete[] wstr;
		wstr = NULL;
	}
	std::string str_gb2312(str);
	if (str) {
		delete[] str;
		str = NULL;
	}
	return str_gb2312;
	
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

		// �ر��ļ����
		CloseHandle(hDumpFile);
	}

	// ִ��Ĭ�ϵ��쳣����
	return EXCEPTION_EXECUTE_HANDLER;
}