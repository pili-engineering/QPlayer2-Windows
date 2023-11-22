#include "PlayerMenuSettingModelManager.h"
#include "../DemoLog.h"
#include "CurrentDataModelManager.h"
#include "QIPlayerControlHandler.h"
#include "QIPlayerRenderHandler.h"
#include "QIPlayerContext.h"
#define TAG          "PlayerMenuSettingModelManager"

PlayerMenuSettingModelManager::PlayerMenuSettingModelManager(HWND hwnd, PlayerWindow* pplayer_window):
	mHwnd(hwnd),
	mpMenuSettingModels(new std::list<PlayerMenuSettingModel*>()),
	mpPlayerWindow(pplayer_window)
{
	//mHwnd = hwnd;
	//mpMenuSettingModels = new std::list<PlayerMenuSettingModel*>();
	add_setting_model("播放控制", ID_PLAY_CHONTROL);
	add_setting_child_model(create_play_control_list(), ID_PLAY_CHONTROL);

	add_setting_model("解码方式", ID_DECODER);
	add_setting_child_model(create_decoder_list(), ID_DECODER);

	add_setting_model("seek方式", ID_SEEK);
	add_setting_child_model(create_seek_list(), ID_SEEK);

	add_setting_model("起播方式", ID_SEEK_START);
	add_setting_child_model(create_start_seek_list(), ID_SEEK_START);

	add_setting_model("鉴权方式", ID_AURHENTICATION);
	add_setting_child_model(create_authentication_list(), ID_AURHENTICATION);

	add_setting_model("渲染比例", ID_RENDER_RADIO);
	add_setting_child_model(create_render_radio_list(), ID_RENDER_RADIO);

	add_setting_model("色觉变化", ID_BLIND);
	add_setting_child_model(create_blind_list(), ID_BLIND);

	add_setting_model("SEI回调", ID_SEI);
	add_setting_child_model(create_sei_list(), ID_SEI);

	add_setting_model("后台播放", ID_BACKGROUND);
	add_setting_child_model(create_background_play_list(), ID_BACKGROUND);

	add_setting_model("清晰度切换", ID_QUALITY_CHANGE);
	add_setting_child_model(create_quality_change_list(), ID_QUALITY_CHANGE);

	add_setting_model("字幕设置", ID_SUBTITLE);
	add_setting_child_model(create_subtitle_list(), ID_SUBTITLE);

	add_setting_model("倍速播放", ID_PLAY_SPEED);
	add_setting_child_model(create_play_speed_list(), ID_PLAY_SPEED);

	add_setting_model("静音设置", ID_MUTE);
	add_setting_child_model(create_mute_list(), ID_MUTE);

	add_setting_model("截图", ID_SHOOT_IMAGE);
	add_setting_child_model(create_shoot_list(), ID_SHOOT_IMAGE);
}



PlayerMenuSettingModelManager::~PlayerMenuSettingModelManager()
{
	if (mpMenuSettingModels != nullptr)
	{
		delete mpMenuSettingModels;
		mpMenuSettingModels = nullptr;

	}
}

void PlayerMenuSettingModelManager::add_setting_model(const std::string& menu_name, int id) {
	PlayerMenuSettingModel* pinner_model = new PlayerMenuSettingModel();
	pinner_model->set_id(id);
	pinner_model->set_name(menu_name);
	//HMENU play_menu = CreatePopupMenu();
	//pinner_model->set_child_menu_model(play_menu);
	mpMenuSettingModels->emplace_back(pinner_model);
}

void PlayerMenuSettingModelManager::add_setting_child_model(std::list<ChildMenu*>* pchild_menu, int parent_menu_id) {
	PlayerMenuSettingModel* pinner_model = nullptr;
	for (int index = 0; index < mpMenuSettingModels->size();index++)
	{
		auto it = mpMenuSettingModels->begin();
		std::advance(it, index);
		if ((*it)->get_id() == parent_menu_id)
		{
			pinner_model = *it;
			break;
		}
	}
	if (pinner_model == nullptr)
	{
		DemoLog::log_string(TAG, __LINE__, "add_setting_child_model :inner_model is nil");
		return;
	}
	HMENU child_menu_hmenu = CreatePopupMenu();

	PlayerChildMenuModel* pchild_menu_model = new PlayerChildMenuModel();
	pchild_menu_model->set_menu(child_menu_hmenu);
	pchild_menu_model->set_child_menus_list(std::move(pchild_menu));
	pinner_model->set_child_menu_model(pchild_menu_model);
	

}


std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_play_control_list() {

	std::list<ChildMenu*>* play_control = new std::list<ChildMenu*>;
	
	play_control->emplace_back(create_child_menu("恢复播放", ID_RESUME_BUTTON, false));
	play_control->emplace_back(create_child_menu("暂停播放", ID_PAUSE_BUTTON, false));
	play_control->emplace_back(create_child_menu("停止播放", ID_STOP_BUTTON, false));

	return play_control;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_decoder_list() {
	std::list<ChildMenu*>* decoder_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_decode_type(CurrentDataModelManager::get_instance()->get_decoder());
	switch (CurrentDataModelManager::get_instance()->get_decoder())
	{
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO: {
		decoder_list->emplace_back(create_child_menu("自动", ID_AUTO_DECODER_BUTTON, true));
		decoder_list->emplace_back(create_child_menu("软解", ID_SOFT_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("硬解", ID_HARD_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("混解", ID_MIX_DECODER_BUTTON, false));
		break;
	}
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_SOFT_PRIORITY: {
		decoder_list->emplace_back(create_child_menu("自动", ID_AUTO_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("软解", ID_SOFT_DECODER_BUTTON, true));
		decoder_list->emplace_back(create_child_menu("硬解", ID_HARD_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("混解", ID_MIX_DECODER_BUTTON, false));
		break;
	}
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY: {
		decoder_list->emplace_back(create_child_menu("自动", ID_AUTO_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("软解", ID_SOFT_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("硬解", ID_HARD_DECODER_BUTTON, true));
		decoder_list->emplace_back(create_child_menu("混解", ID_MIX_DECODER_BUTTON, false));
		break;
	}
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_FIRST_FRAME_ACCEL_PRIORITY: {
		decoder_list->emplace_back(create_child_menu("自动", ID_AUTO_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("软解", ID_SOFT_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("硬解", ID_HARD_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("混解", ID_MIX_DECODER_BUTTON, true));
		break;
	}
	default: {

		decoder_list->emplace_back(create_child_menu("自动", ID_AUTO_DECODER_BUTTON, true));
		decoder_list->emplace_back(create_child_menu("软解", ID_SOFT_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("硬解", ID_HARD_DECODER_BUTTON, false));
		decoder_list->emplace_back(create_child_menu("混编", ID_MIX_DECODER_BUTTON, false));
		break;
	}
	}

	return decoder_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_seek_list() {
	std::list<ChildMenu*>* seek_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_seek_mode(CurrentDataModelManager::get_instance()->get_seek_mode());
	switch (CurrentDataModelManager::get_instance()->get_seek_mode())
	{
	case QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL: {
		seek_list->emplace_back(create_child_menu("关键帧seek", ID_SEEK_NORMAL_BUTTON, true));
		seek_list->emplace_back(create_child_menu("精准seek", ID_SEEK_ACCURATE_BUTTON, false));
		break;

	}
	case QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_ACCURATE: {
		seek_list->emplace_back(create_child_menu("关键帧seek", ID_SEEK_NORMAL_BUTTON, false));
		seek_list->emplace_back(create_child_menu("精准seek", ID_SEEK_ACCURATE_BUTTON, true));
		break;

	}
	default: {

		seek_list->emplace_back(create_child_menu("关键帧seek", ID_SEEK_NORMAL_BUTTON, true));
		seek_list->emplace_back(create_child_menu("精准seek", ID_SEEK_ACCURATE_BUTTON, false));
		break;
	}
	}

	return seek_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_start_seek_list() {
	std::list<ChildMenu*>* start_seek_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_start_action(CurrentDataModelManager::get_instance()->get_player_start());
	switch (CurrentDataModelManager::get_instance()->get_player_start())
	{
	case QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING: {
		start_seek_list->emplace_back(create_child_menu("起播播放", ID_SEEK_START_PLAYING_BUTTON, true));
		start_seek_list->emplace_back(create_child_menu("起播暂停", ID_SEEK_START_PAUSE_BUTTON, false));
		break;

	}
	case QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PAUSE: {
		start_seek_list->emplace_back(create_child_menu("起播播放", ID_SEEK_START_PLAYING_BUTTON, false));
		start_seek_list->emplace_back(create_child_menu("起播暂停", ID_SEEK_START_PAUSE_BUTTON, true));
		break;

	}
	default: {

		start_seek_list->emplace_back(create_child_menu("起播播放", ID_SEEK_START_PLAYING_BUTTON, true));
		start_seek_list->emplace_back(create_child_menu("起播暂停", ID_SEEK_START_PAUSE_BUTTON, false));
		break;
	}
	}

	return start_seek_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_authentication_list() {
	std::list<ChildMenu*>* authentication_list = new std::list<ChildMenu*>;
	switch (CurrentDataModelManager::get_instance()->get_force_authentication_enable())
	{
	case true: {
		mpPlayerWindow->get_control_handler()->force_authentication_from_network();
		authentication_list->emplace_back(create_child_menu("下一次刷新鉴权信息", ID_AURHENTICATION_BUTTON, true));
		break;

	}
	case false: {
		authentication_list->emplace_back(create_child_menu("下一次刷新鉴权信息", ID_AURHENTICATION_BUTTON, false));
		break;

	}
	default: {

		authentication_list->emplace_back(create_child_menu("下一次刷新鉴权信息", ID_AURHENTICATION_BUTTON, false));
		break;
	}
	}

	return authentication_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_render_radio_list() {
	std::list<ChildMenu*>* render_radio_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_render_handler()->set_render_ratio(CurrentDataModelManager::get_instance()->get_render_ratio());
	switch (CurrentDataModelManager::get_instance()->get_render_ratio())
	{
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO: {
		render_radio_list->emplace_back(create_child_menu("自动", ID_RENDER_RADIO_AUTO_BUTTON, true));
		render_radio_list->emplace_back(create_child_menu("拉伸", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("铺满", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;

	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_16_9: {
		render_radio_list->emplace_back(create_child_menu("自动", ID_RENDER_RADIO_AUTO_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("拉伸", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("铺满", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, true));
		render_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_4_3: {
		render_radio_list->emplace_back(create_child_menu("自动", ID_RENDER_RADIO_AUTO_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("拉伸", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("铺满", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, true));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_FULL_SCREEN: {
		render_radio_list->emplace_back(create_child_menu("自动", ID_RENDER_RADIO_AUTO_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("拉伸", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("铺满", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, true));
		render_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_STRETCH: {
		render_radio_list->emplace_back(create_child_menu("自动", ID_RENDER_RADIO_AUTO_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("拉伸", ID_RENDER_RADIO_STRETCH_BUTTON, true));
		render_radio_list->emplace_back(create_child_menu("铺满", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	default: {
		render_radio_list->emplace_back(create_child_menu("自动", ID_RENDER_RADIO_AUTO_BUTTON, true));
		render_radio_list->emplace_back(create_child_menu("拉伸", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("铺满", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		render_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	}

	return render_radio_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_blind_list() {
	std::list<ChildMenu*>* blind_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_render_handler()->set_blind_type(CurrentDataModelManager::get_instance()->get_blind());
	switch (CurrentDataModelManager::get_instance()->get_blind())
	{
	case QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_NONE: {
		blind_list->emplace_back(create_child_menu("无滤镜", ID_BLIND_NONE_BUTTON, true));
		blind_list->emplace_back(create_child_menu("红/绿滤镜", ID_BLIND_RED_BUTTON, false));
		blind_list->emplace_back(create_child_menu("绿/红滤镜", ID_BLIND_GREEN_BUTTON, false));
		blind_list->emplace_back(create_child_menu("蓝/黄滤镜", ID_BLIND_BLUE_BUTTON, false));
		break;

	}
	case  QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_BLUE: {
		blind_list->emplace_back(create_child_menu("无滤镜", ID_BLIND_NONE_BUTTON, false));
		blind_list->emplace_back(create_child_menu("红/绿滤镜", ID_BLIND_RED_BUTTON, false));
		blind_list->emplace_back(create_child_menu("绿/红滤镜", ID_BLIND_GREEN_BUTTON, false));
		blind_list->emplace_back(create_child_menu("蓝/黄滤镜", ID_BLIND_BLUE_BUTTON, true));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_GREEN: {
		blind_list->emplace_back(create_child_menu("无滤镜", ID_BLIND_NONE_BUTTON, false));
		blind_list->emplace_back(create_child_menu("红/绿滤镜", ID_BLIND_RED_BUTTON, false));
		blind_list->emplace_back(create_child_menu("绿/红滤镜", ID_BLIND_GREEN_BUTTON, true));
		blind_list->emplace_back(create_child_menu("蓝/黄滤镜", ID_BLIND_BLUE_BUTTON, false));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_RED: {
		blind_list->emplace_back(create_child_menu("无滤镜", ID_BLIND_NONE_BUTTON, false));
		blind_list->emplace_back(create_child_menu("红/绿滤镜", ID_BLIND_RED_BUTTON, true));
		blind_list->emplace_back(create_child_menu("绿/红滤镜", ID_BLIND_GREEN_BUTTON, false));
		blind_list->emplace_back(create_child_menu("蓝/黄滤镜", ID_BLIND_BLUE_BUTTON, false));
		break;
	}
	default: {
		blind_list->emplace_back(create_child_menu("无滤镜", ID_BLIND_NONE_BUTTON, true));
		blind_list->emplace_back(create_child_menu("红/绿滤镜", ID_BLIND_RED_BUTTON, false));
		blind_list->emplace_back(create_child_menu("绿/红滤镜", ID_BLIND_GREEN_BUTTON, false));
		blind_list->emplace_back(create_child_menu("蓝/黄滤镜", ID_BLIND_BLUE_BUTTON, false));
		break;
	}
	}

	return blind_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_sei_list() {
	std::list<ChildMenu*>* sei_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_sei_enable(CurrentDataModelManager::get_instance()->get_sei_enable());
	switch (CurrentDataModelManager::get_instance()->get_sei_enable())
	{
	case true: {
		sei_list->emplace_back(create_child_menu("开启SEI回调", ID_SEI_OPEN_BUTTON, true));
		sei_list->emplace_back(create_child_menu("关闭SEI回调", ID_SEI_CLOSE_BUTTON, false));
		break;

	}
	case  false: {
		sei_list->emplace_back(create_child_menu("开启SEI回调", ID_SEI_OPEN_BUTTON, false));
		sei_list->emplace_back(create_child_menu("关闭SEI回调", ID_SEI_CLOSE_BUTTON, true));
		break;
	}
	default: {
		sei_list->emplace_back(create_child_menu("开启SEI回调", ID_SEI_OPEN_BUTTON, true));
		sei_list->emplace_back(create_child_menu("关闭SEI回调", ID_SEI_CLOSE_BUTTON, false));
		break;
	}
	}

	return sei_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_background_play_list() {
	std::list<ChildMenu*>* background_play_list = new std::list<ChildMenu*>;
	switch (CurrentDataModelManager::get_instance()->get_background_enable())
	{
	case true: {
		background_play_list->emplace_back(create_child_menu("开启后台播放", ID_BACKGROUND_OPEN_BUTTON, true));
		background_play_list->emplace_back(create_child_menu("关闭后台播放", ID_BACKGROUND_CLOSE_BUTTON, false));
		break;

	}
	case  false: {
		background_play_list->emplace_back(create_child_menu("开启后台播放", ID_BACKGROUND_OPEN_BUTTON, false));
		background_play_list->emplace_back(create_child_menu("关闭后台播放", ID_BACKGROUND_CLOSE_BUTTON, true));
		break;
	}
	default: {
		background_play_list->emplace_back(create_child_menu("开启后台播放", ID_BACKGROUND_OPEN_BUTTON, true));
		background_play_list->emplace_back(create_child_menu("关闭后台播放", ID_BACKGROUND_CLOSE_BUTTON, false));
		break;
	}
	}

	return background_play_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_quality_change_list() {
	std::list<ChildMenu*>* quality_change_list = new std::list<ChildMenu*>;
	switch (CurrentDataModelManager::get_instance()->get_quality_immediatyly())
	{
	case QualityImmediatyly::IMMEDIATYLY_TRUE: {
		quality_change_list->emplace_back(create_child_menu("立即切换", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, true));
		quality_change_list->emplace_back(create_child_menu("无缝切换（只使用点播）", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, false));
		quality_change_list->emplace_back(create_child_menu("直播立即&点播无缝", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, false));
		break;

	}
	case  QualityImmediatyly::IMMEDIATYLY_FALSE: {
		quality_change_list->emplace_back(create_child_menu("立即切换", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, false));
		quality_change_list->emplace_back(create_child_menu("无缝切换（只使用点播）", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, true));
		quality_change_list->emplace_back(create_child_menu("直播立即&点播无缝", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, false));
		break;
	}
	case  QualityImmediatyly::IMMEDIATYLY_CUSTOM: {
		quality_change_list->emplace_back(create_child_menu("立即切换", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, false));
		quality_change_list->emplace_back(create_child_menu("无缝切换（只使用点播）", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, false));
		quality_change_list->emplace_back(create_child_menu("直播立即&点播无缝", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, true));
		break;
	}
	default: {
		quality_change_list->emplace_back(create_child_menu("立即切换", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, true));
		quality_change_list->emplace_back(create_child_menu("无缝切换（只使用点播）", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, false));
		quality_change_list->emplace_back(create_child_menu("直播立即&点播无缝", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, false));
		break;
	}
	}

	return quality_change_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_subtitle_list() {
	std::list<ChildMenu*>* subtitle_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_subtitle_enable(CurrentDataModelManager::get_instance()->get_subtitle_enable());
	mpPlayerWindow->get_control_handler()->set_subtitle(CurrentDataModelManager::get_instance()->get_subtitle_name());
	switch (CurrentDataModelManager::get_instance()->get_subtitle_enable())
	{
	case false: {
		subtitle_list->emplace_back(create_child_menu("关闭", ID_SUBTITLE_CLOSE_BUTTON, true));
		subtitle_list->emplace_back(create_child_menu("中文", ID_SUBTITLE_CHINESE_BUTTON, false));
		subtitle_list->emplace_back(create_child_menu("英文", ID_SUBTITLE_ENGLISH_BUTTON, false));
		break;

	}
	case  true: {
		if (CurrentDataModelManager::get_instance()->get_subtitle_name() == "中文") {

			subtitle_list->emplace_back(create_child_menu("关闭", ID_SUBTITLE_CLOSE_BUTTON, false));
			subtitle_list->emplace_back(create_child_menu("中文", ID_SUBTITLE_CHINESE_BUTTON, true));
			subtitle_list->emplace_back(create_child_menu("英文", ID_SUBTITLE_ENGLISH_BUTTON, false));
		}
		else if (CurrentDataModelManager::get_instance()->get_subtitle_name() == "英文")
		{
			subtitle_list->emplace_back(create_child_menu("关闭", ID_SUBTITLE_CLOSE_BUTTON, false));
			subtitle_list->emplace_back(create_child_menu("中文", ID_SUBTITLE_CHINESE_BUTTON, true));
			subtitle_list->emplace_back(create_child_menu("英文", ID_SUBTITLE_ENGLISH_BUTTON, false));
		}
		break;
	}
	default: {
		subtitle_list->emplace_back(create_child_menu("关闭", ID_SUBTITLE_CLOSE_BUTTON, true));
		subtitle_list->emplace_back(create_child_menu("中文", ID_SUBTITLE_CHINESE_BUTTON, false));
		subtitle_list->emplace_back(create_child_menu("英文", ID_SUBTITLE_ENGLISH_BUTTON, false));
		break;
	}
	}

	return subtitle_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_play_speed_list() {
	std::list<ChildMenu*>* play_speed_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_speed(CurrentDataModelManager::get_instance()->get_play_speed());
	if (CurrentDataModelManager::get_instance()->get_play_speed() == 0.5)
	{
		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, true));
	}
	else if (CurrentDataModelManager::get_instance()->get_play_speed() == 0.75)
	{
		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, true));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (CurrentDataModelManager::get_instance()->get_play_speed() == 1.0)
	{
		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, true));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (CurrentDataModelManager::get_instance()->get_play_speed() == 1.25)
	{
		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, true));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (CurrentDataModelManager::get_instance()->get_play_speed() == 1.5)
	{
		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, true));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (CurrentDataModelManager::get_instance()->get_play_speed() == 2.0)
	{
		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, true));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else
	{

		play_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, true));
		play_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		play_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	return play_speed_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_mute_list() {
	std::list<ChildMenu*>* mute_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_mute(CurrentDataModelManager::get_instance()->get_mute_enable());
	switch (CurrentDataModelManager::get_instance()->get_mute_enable())
	{
	case true: {

		mute_list->emplace_back(create_child_menu("非静音", ID_SUBTITLE_CLOSE_BUTTON, false));
		mute_list->emplace_back(create_child_menu("静音", ID_SUBTITLE_CHINESE_BUTTON, true));
		break;
	}
	case false: {

		mute_list->emplace_back(create_child_menu("非静音", ID_SUBTITLE_CLOSE_BUTTON, true));
		mute_list->emplace_back(create_child_menu("静音", ID_SUBTITLE_CHINESE_BUTTON, false));
		break;
	}
	default:
		mute_list->emplace_back(create_child_menu("非静音", ID_SUBTITLE_CLOSE_BUTTON, true));
		mute_list->emplace_back(create_child_menu("静音", ID_SUBTITLE_CHINESE_BUTTON, false));
		break;
	}

	return mute_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_shoot_list() {

	std::list<ChildMenu*>* shoot_list = new std::list<ChildMenu*>;
	shoot_list->emplace_back(create_child_menu("截图", ID_SHOOT_IMAGE_BUTTON, false));
	return shoot_list;
}

ChildMenu* PlayerMenuSettingModelManager::create_child_menu(const std::string& name, int id, bool is_selected) {
	ChildMenu* inner_child_menu = new ChildMenu();
	inner_child_menu->set_id(id);
	inner_child_menu->set_name(name);
	inner_child_menu->set_is_selected(is_selected);
	return inner_child_menu;
}


std::list<PlayerMenuSettingModel*>* PlayerMenuSettingModelManager::get_menu_setting_model() {
	return mpMenuSettingModels;
}