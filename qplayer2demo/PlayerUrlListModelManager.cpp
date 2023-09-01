#include "PlayerUrlListModelManager.h"
#include "DemoLog.h"
#include "QMediaModelBuilder.h"

#define TAG               "PlayerUrlListModelManager"

PlayerUrlListModelManager::PlayerUrlListModelManager()
{
	mUrlModels = std::list<PlayerUrlListModel *>();

	create_url_models();
}

PlayerUrlListModelManager::~PlayerUrlListModelManager()
{
}

void PlayerUrlListModelManager::add_model(QMedia::QMediaModel* model, std::string name) {
	PlayerUrlListModel* inner_model = new PlayerUrlListModel(model,name);
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

void PlayerUrlListModelManager::create_url_models() {
	QMedia::QMediaModelBuilder* bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023.mp4");

	bulder = new QMedia::QMediaModelBuilder();
	bulder->add_stream_element("", QMedia::QUrlType::QAUDIO_AND_VIDEO, 0, "http://demo-videos.qnsdk.com/qiniu-2023-720p.mp4", true);
	add_model(bulder->build(false), "1-qiniu-2023-100.mp4");
}