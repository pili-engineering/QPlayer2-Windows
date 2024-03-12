#pragma once
#include "PlayerUrlListModel.h"
#include <string>
#include <list>
#include <functional>
#include "../FileOfWriteAndRead.h"
using urlUpdateCallBackFunction = std::function<void()>;

class PlayerUrlListModelManager
{
private:
	void create_url_models();

	void add_model(QMedia::QMediaModel* pmodel, const std::string& name);

	void motify_model(QMedia::QMediaModel* pmodel, const std::string& name, int index);
public:
	PlayerUrlListModelManager();
	~PlayerUrlListModelManager();

	std::list<PlayerUrlListModel*> get_url_models();

	int get_url_models_count();

	void delete_url_model_index(int index);

	std::string get_url_with_index(int model_index, int element_index);

	std::string get_subtitle_url_with_index(int model_index, int element_index);

	QMedia::QUrlType get_url_type_with_index(int model_index, int element_index);

	std::string get_user_type_with_index(int model_index, int element_index);

	int get_quality_with_index(int model_index, int element_index);

	bool get_is_selected_with_index(int model_index, int element_index);

	std::string get_back_url_with_index(int model_index, int element_index);

	std::string get_refere_with_index(int model_index, int element_index);

	bool get_is_live_with_index(int model_index);

	std::string get_url_name_with_index(int model_index);

	int get_url_element_count_index(int model_index);

	int get_subtitle_element_count_index(int model_index);

	PlayerUrlListModel* get_url_model_for_index(int index);

	void set_url_update_call_back(urlUpdateCallBackFunction call_back);

	void add_stream_element(const std::string& user_type, QMedia::QUrlType url_type, uint32_t  quality_index,
		const std::string& url, bool is_default, const std::string& referer, const std::string& backup_url,
		QMedia::QVideoRenderType video_render_type, const std::string& hls_drm_key, const std::string& mp4_drm_key, QMedia::QUrlMethod url_method);

	void add_subtitle_element(const std::string& name, const std::string& url, bool is_selected);

	void build(bool is_live, bool mReconstructTimeLine, const std::string& name , int index = -1);

	void url_update();
private:
	std::list<PlayerUrlListModel*> mUrlModels;

	std::list <urlUpdateCallBackFunction> mUrlCallBack;

	QMedia::QMediaModelBuilder* mpBulder;
};

