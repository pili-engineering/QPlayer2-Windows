#include "FileOfWriteAndRead.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "QMediaModelBuilder.h"

CurrentDataModel* FileOfWriteAndRead::read_setting_local_file(const std::string& file_name) {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);

	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + file_name;
	std::ifstream file(file_path, std::ios::in);
	if (!file) {
		return nullptr;
	}

	CurrentDataModel* current = new CurrentDataModel();
	std::string line;
	while (std::getline(file, line)) {

		std::size_t colonPos = line.find(": ");
		std::string key = line.substr(0, colonPos);
		std::string value = line.substr(colonPos + 2);
		if (key == "playStartPositon")
		{
			current->set_player_start_position(std::stoi(value));
		}
		else if (key == "decoder")
		{
			current->set_decoder((QMedia::QPlayerSetting::QPlayerDecoder)std::stoi(value));
		}
		else if (key == "seekMode")
		{
			current->set_seek_mode((QMedia::QPlayerSetting::QPlayerSeek)std::stoi(value));
		}
		else if (key == "playerStart")
		{
			current->set_player_start((QMedia::QPlayerSetting::QPlayerStart)std::stoi(value));
		}
		else if (key == "renderRatio")
		{
			current->set_render_ratio((QMedia::QPlayerSetting::QPlayerRenderRatio)std::stoi(value));
		}
		else if (key == "blind")
		{
			current->set_blind((QMedia::QPlayerSetting::QPlayerBlind)std::stoi(value));
		}
		else if (key == "seiEnable")
		{
			current->set_sei_enable((bool)std::stoi(value));
		}
		else if (key == "backgroundEnable")
		{
			current->set_background_enable((bool)std::stoi(value));
		}
		else if (key == "qualityImmediatyly")
		{
			current->set_quality_immediatyly((QualityImmediatyly)std::stoi(value));
		}
		else if (key == "subtitleEnable")
		{
			current->set_subtitle_enable((bool)std::stoi(value));
		}
		else if (key == "subtitleName")
		{
			current->set_subtitle_name(value);
		}
		else if (key == "playSpeed")
		{
			current->set_play_speed(std::stof(value));
		}
		else if (key == "muteEnable")
		{
			current->set_mute_enable((bool)std::stoi(value));

		}
		else if (key == "forceAuthenticationEnable")
		{
			current->set_force_authentication_enable((bool)std::stoi(value));
		}

	}
	return current;
}
bool FileOfWriteAndRead::motify_setting_local_file(const std::string& file_name, const std::string& key, const std::string& value) {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);

	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + file_name;
	std::ifstream in_file(file_path);
	if (!in_file) {
		return false;
	}

	std::vector<std::string> lines;
	std::string line;

	while (std::getline(in_file, line)) {
		std::size_t colon_pos = line.find(": ");
		std::string inner_key = line.substr(0, colon_pos);
		if (inner_key == key)
		{
			std::string motify_string = key + ": " + value;
			lines.push_back(motify_string);
		}
		else
		{
			lines.push_back(line);
		}
	}

	in_file.close();

	std::ofstream out_file(file_path);
	if (!out_file) {
		return false;
	}

	// 将 vector 中的内容写回文件
	for (const std::string& line : lines) {
		out_file << line << std::endl;
	}

	out_file.close();
	return true;
}


bool FileOfWriteAndRead::delete_url_local_file_with_name(const std::string& file_name, const std::string& delete_url_name){
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);

	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + file_name;
	std::ifstream in_file(file_path); 
	if (!in_file) {
		return false;
	}

	std::vector<std::string> lines;
	std::string line;

	bool stream_start = false;
	bool subtitle_start = false;
	bool delete_start = false;
	while (std::getline(in_file, line)) {
		if (line == "{")
		{
			std::string inner_line;
			std::getline(in_file, inner_line);
			std::size_t colon_pos = inner_line.find(": ");
			std::string key = inner_line.substr(0, colon_pos);
			std::string value = inner_line.substr(colon_pos + 2);
			if (key == "name" && value == delete_url_name)
			{
				delete_start = true;
			}
			else
			{
				lines.push_back(line);
				lines.push_back(inner_line);
				delete_start = false;
			}

		}
		if (!delete_start)
		{
			if (line != "{")
			{
				lines.push_back(line);
			}
		}
	}

	in_file.close();

	std::ofstream out_file(file_path);
	if (!out_file) {
		return false;
	}

	// 将 vector 中的内容写回文件
	for (const std::string& line : lines) {
		out_file << line << std::endl;
	}

	out_file.close();
	return true;
}

bool FileOfWriteAndRead::write_to_local_file(const std::string& file_name, PlayerUrlListModel* pmodel) {
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);

	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + file_name;
	std::ofstream file(file_path, std::ios::out | std::ios::app);
	if (!file.is_open()) {
		return false;
	}

	file << "\n";
	file << "{\n";

	file << "name: " << pmodel->get_name() << "\n";
	file << "isLive: " << pmodel->get_media_model()->is_live() << "\n";

	file << "streamElements: {\n";
	for (const auto& pinner_model : pmodel->get_media_model()->get_stream_elements()) {
		file << "[\n";
		file << "userType: " << pinner_model->get_user_type() << "\n";
		file << "urlType: " << (int)pinner_model->get_url_type() << "\n";
		file << "url: " << pinner_model->get_url() << "\n";
		file << "quality: " << pinner_model->get_quality_index() << "\n";
		file << "isSelected: " << pinner_model->is_selected() << "\n";
		file << "backupUrl: " << pinner_model->get_back_url() << "\n";
		file << "referer: " << pinner_model->get_referer() << "\n";
		file << "hlsDrmKey: " << pinner_model->get_hls_drm_key() << "\n";
		file << "mp4DrmKey: " << pinner_model->get_mp4_drm_key() << "\n";
		file << "renderType: " << (int)pinner_model->get_render_type() << "\n";
		file << "]\n";
	}
	file << "}\n";
	file << "subtitleElements: {\n";
	for (const auto& pinner_model : pmodel->get_media_model()->get_subtitle_elements()) {
		file << "[\n";
		file << "name: " << pinner_model->get_name() << "\n";
		file << "url: " << pinner_model->get_url() << "\n";
		file << "isSelected: " << pinner_model->is_selected() << "\n";
		file << "]\n";
	}

	file << "}\n";

	file << "}\n";
	file.close();
	return true;
}


std::list<PlayerUrlListModel*> FileOfWriteAndRead::read_from_url_local_file(const std::string& file_name) {
	std::list<PlayerUrlListModel*> model_list = std::list<PlayerUrlListModel*>();
	char path[MAX_PATH];
	DWORD length = ::GetModuleFileName(nullptr, path, MAX_PATH);
	std::string directory = path;
	size_t pos = directory.find_last_of("\\");
	directory = directory.substr(0, pos + 1);
	std::string file_path = directory + file_name;
	std::ifstream file(file_path, std::ios::in);
	if (!file.is_open()) {
		return model_list;
	}
	std::string line;
	std::list<std::string> read_string = std::list<std::string>();

	
	bool start = false;
	bool stream_start = false;
	bool subtitle_start = false;
	while (std::getline(file, line)) {
		if (line == "{")
		{
			start = true;
		}
		if (line == "streamElements: {")
		{
			stream_start = true;
		}
		if (line == "subtitleElements: {")
		{
			subtitle_start = true;
		}
		
		if (stream_start == true && line == "}")
		{
			stream_start = false;
		}
		else if (subtitle_start == true && line == "}")
		{
			subtitle_start = false;
		}
		else if (line == "}")
		{
			read_string.emplace_back(line);
			start = false;
			model_list.emplace_back(FileOfWriteAndRead::url_data_to_url_model(read_string));
			read_string = std::list<std::string>();
			continue;
			
		}
		if (start == true)
		{
			read_string.emplace_back(line);
		}

	}
	return model_list;
}

PlayerUrlListModel* FileOfWriteAndRead::url_data_to_url_model(std::list<std::string> file_string) {
	std::string name = "";
	bool is_live = false;
	QMedia::QUrlType url_type = QMedia::QUrlType::QAUDIO_AND_VIDEO;
	std::string user_type = "";
	std::string url = "";
	int quality = 0;
	std::string back_up_url = "";
	bool is_selected = false;
	std::string referer = "";
	std::string hls_drm_key = "";
	std::string mp4_drm_key = "";
	QMedia::QVideoRenderType render_type = QMedia::QVideoRenderType::PLANE;
	bool stream_start = false;
	bool subtitle_start = false;

	std::string subtitle_name = "";
	std::string subtitle_url = "";
	bool subtitle_is_selected = false;
	QMedia::QMediaModelBuilder* model_builder = nullptr;
	PlayerUrlListModel* url_model = nullptr;
	for (std::string inner : file_string) {
		if (inner == "{") {
			model_builder = new QMedia::QMediaModelBuilder();
		}
		if (inner == "]" && stream_start)
		{
			/*model_builder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 1080,
				url, true, "", "", QMedia::QVideoRenderType::PLANE, "", "");*/
			model_builder->add_stream_element(user_type, url_type, quality, url, is_selected, referer, back_up_url, render_type, hls_drm_key, mp4_drm_key);
		}
		if (inner == "]" && subtitle_start)
		{
			model_builder->add_subtitle_element(subtitle_name,subtitle_url,subtitle_is_selected);
			
		}
		if (inner == "}" && !stream_start && !subtitle_start)
		{
			url_model = new PlayerUrlListModel(model_builder->build(is_live), name);
			delete model_builder;
			model_builder = nullptr;
			return url_model;
		}
		else if(inner == "}" && stream_start)
		{
			stream_start = false;
		}
		else if (inner == "}" && subtitle_start)
		{
			subtitle_start = false;
		}
		std::size_t colonPos = inner.find(": ");
		std::string key = inner.substr(0, colonPos);
		std::string value = inner.substr(colonPos + 2);
		if (stream_start)
		{
			if(key == "userType")
 			{
				user_type = value;
			}
			else if (key == "urlType") 
			{
				if (value == "0") {
					url_type = QMedia::QUrlType::QAUDIO_AND_VIDEO;
				}
				else if(value == "1")
				{
					url_type = QMedia::QUrlType::QAUDIO;
				}
				else if (value == "2")
				{
					url_type = QMedia::QUrlType::QVIDEO;
				}
				else if (value == "3")
				{
					url_type = QMedia::QUrlType::NONE;
				}
			}
			else if(key == "url")
 			{
				url = value;
			}
			else if (key == "quality")
			{
				quality = std::stoi(value);
			}
			else if (key == "backupUrl")
			{
				back_up_url = value;
			}
			else if (key == "isSelected")
			{
				if (value == "0") {
					is_selected = false;
				}
				else if (value == "1")
				{
					is_selected = true;
				}
			}
			else if (key == "referer")
			{
				referer = value;
			}
			else if (key == "hlsDrmKey")
			{
				hls_drm_key = value;
			}
			else if (key == "mp4DrmKey")
			{
				mp4_drm_key = value;
			}
			else if (key == "renderType")
			{
				if (value == "-1")
				{
					render_type = QMedia::QVideoRenderType::NONE;
				}
				else if (value == "0")
				{
					render_type = QMedia::QVideoRenderType::PLANE;
				}
				else if (value == "1")
				{
					render_type = QMedia::QVideoRenderType::PANORAMA_EQUIRECT_ANGULAR;
				}
			}
		}
		else if (subtitle_start)
		{
			if (key == "name") {
				subtitle_name = value;
			}
			else if (key == "url")
			{
				subtitle_url = value;
			}
			else if (key == "isSelected")
			{
				if (value == "1")
				{
					subtitle_is_selected = true;
				}
				else if(value == "0")
				{
					subtitle_is_selected = false;

				}
			}
		}
		else if (key == "name")
		{
			name = value;
		}
		else if(key == "isLive")
		{
			if (value == "0") {
				is_live = false;
			}
			else if (value == "1")
			{
				is_live = true;
			}
		}
		else if (key == "streamElements")
		{
			stream_start = true;
		}
		else if (key == "subtitleElements")
		{
			subtitle_start = true;
		}
	}
	return nullptr;
}