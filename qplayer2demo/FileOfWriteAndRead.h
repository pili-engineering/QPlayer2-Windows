#pragma once
#include <string>
#include "PlayerUrlListModel.h"
#include <list>
#include "CurrentDataModel.h"
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
	static bool write_to_local_file(const std::string& file_name, PlayerUrlListModel* pmodel);

	static std::list<PlayerUrlListModel*> read_from_url_local_file(const std::string& file_name);

	static bool delete_url_local_file_with_name(const std::string& file_name, const std::string& delete_url_name);

	static bool motify_setting_local_file(const std::string& file_name, const std::string& key, const std::string& value);


	static CurrentDataModel* read_setting_local_file(const std::string& file_name);
private:

	static PlayerUrlListModel* url_data_to_url_model(std::list<std::string> file_string);

};
