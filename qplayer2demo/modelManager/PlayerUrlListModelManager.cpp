#include "PlayerUrlListModelManager.h"
#include "../DemoLog.h"
#include "QMediaModelBuilder.h"

#include "../FileOfWriteAndRead.h"

#define TAG               "PlayerUrlListModelManager"
#define URL_LOCAL_FILE_NAME "url.txt"
PlayerUrlListModelManager::PlayerUrlListModelManager():mUrlModels(), mUrlCallBack(),mpBulder(nullptr)
{
	create_url_models();
}

PlayerUrlListModelManager::~PlayerUrlListModelManager()
{
}

void PlayerUrlListModelManager::add_model(QMedia::QMediaModel* pmodel, const std::string& name) {
	PlayerUrlListModel* inner_model = new PlayerUrlListModel(pmodel,name);
	if (FileOfWriteAndRead::write_to_local_file(URL_LOCAL_FILE_NAME, inner_model))
	{
	}
	else
	{
		DemoLog::log_string(TAG, __LINE__, "write data to local file false");
	}
	mUrlModels.emplace_back(inner_model);
}

std::list<PlayerUrlListModel*>  PlayerUrlListModelManager::get_url_models() {
	return mUrlModels;
}


int PlayerUrlListModelManager::get_url_models_count() {
	return mUrlModels.size();
}

PlayerUrlListModel* PlayerUrlListModelManager::get_url_model_for_index(int index) {
	auto it = mUrlModels.begin();
	if (mUrlModels.size() < index) {
		return nullptr;
	}
	std::advance(it, index);
	if (it != mUrlModels.end())
	{
		return *it;
	}
	else
	{
		DemoLog::log_string(TAG, __LINE__, "get_url_model_for_index  index >= get_url_models_count");
		return nullptr;
	}
}

void PlayerUrlListModelManager::delete_url_model_index(int index) {
	if (!mUrlModels.empty() && index < mUrlModels.size())
	{
		auto it = mUrlModels.begin();
		std::advance(it, index);
		bool delete_flag = FileOfWriteAndRead::delete_url_local_file_with_name(URL_LOCAL_FILE_NAME,(*it)->get_name());

		mUrlModels.erase(it);
	}
}
std::string PlayerUrlListModelManager::get_url_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->get_url();
		}
	}
	return "error";
}
std::string PlayerUrlListModelManager::get_subtitle_url_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QSubtitleElement*> ele = (*pit)->get_media_model()->get_subtitle_elements();
			return ele[element_index]->get_url();
		}
	}
	return "error";
}
QMedia::QUrlType PlayerUrlListModelManager::get_url_type_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->get_url_type();
		}
	}
	return QMedia::QUrlType::NONE;
}

std::string PlayerUrlListModelManager::get_user_type_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->get_user_type();
		}
	}
	return "error";
}

int PlayerUrlListModelManager::get_quality_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->get_quality_index();
		}
	}
	return -1;
}

bool PlayerUrlListModelManager::get_is_selected_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->is_selected();
		}
	}
	return false;
}

std::string PlayerUrlListModelManager::get_back_url_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->get_back_url();
		}
	}
	return "error";
}

std::string PlayerUrlListModelManager::get_refere_with_index(int model_index, int element_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);

		if (element_index < (*pit)->get_media_model()->get_stream_elements().size())
		{
			std::vector<QMedia::QStreamElement*> ele = (*pit)->get_media_model()->get_stream_elements();
			return ele[element_index]->get_referer();
		}
	}
	return "error";
}

bool PlayerUrlListModelManager::get_is_live_with_index(int model_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);
		return (*pit)->get_media_model()->is_live();
	}
	return false;
}

std::string PlayerUrlListModelManager::get_url_name_with_index(int model_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);
		return (*pit)->get_name();
	}
	return "error";
}

int PlayerUrlListModelManager::get_url_element_count_index(int model_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);
		return (*pit)->get_media_model()->get_stream_elements().size();
	}
	return 0;
}
int PlayerUrlListModelManager::get_subtitle_element_count_index(int model_index) {
	if (!mUrlModels.empty() && model_index < mUrlModels.size())
	{
		auto pit = mUrlModels.begin();
		std::advance(pit, model_index);
		return (*pit)->get_media_model()->get_subtitle_elements().size();
	}
	return 0;
}
void PlayerUrlListModelManager::add_stream_element(const std::string& user_type, QMedia::QUrlType url_type, uint32_t  quality_index,
	const std::string& url, bool is_default, const std::string& referer, const std::string& backup_url,
	QMedia::QVideoRenderType video_render_type, const std::string& hls_drm_key, const std::string& mp4_drm_key) {
	if (mpBulder == nullptr)
	{
		mpBulder = new QMedia::QMediaModelBuilder();
	}
	mpBulder->add_stream_element(user_type, url_type, quality_index, url, is_default, referer, backup_url, video_render_type, hls_drm_key, mp4_drm_key);
}

void PlayerUrlListModelManager::add_subtitle_element(const std::string& name, const std::string& url, bool is_selected) {
	if (mpBulder == nullptr)
	{
		mpBulder = new QMedia::QMediaModelBuilder();
	}
	mpBulder->add_subtitle_element(name, url, is_selected);
}
void PlayerUrlListModelManager::build(bool is_live, const std ::string& name) {
	if (mpBulder != nullptr)
	{
		add_model(mpBulder->build(is_live), name);
		delete mpBulder;
		mpBulder = nullptr;
	}
}
void PlayerUrlListModelManager::create_url_models() {
	
	mUrlModels = FileOfWriteAndRead::read_from_url_local_file(URL_LOCAL_FILE_NAME);

}


void PlayerUrlListModelManager::set_url_update_call_back(urlUpdateCallBackFunction call_back) {
	mUrlCallBack.emplace_back(call_back);
}

void PlayerUrlListModelManager::url_update() {
	if (!mUrlCallBack.empty())
	{
		for (auto it : mUrlCallBack)
		{
			it();
		}
	}
}