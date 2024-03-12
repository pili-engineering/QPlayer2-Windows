#include "PlayerMenuSettingModelManager.h"
#include "../DemoLog.h"
#include <QIPlayerControlHandler.h>
#include <QIPlayerRenderHandler.h>
#include <QIPlayerContext.h>
#define CLASS_NAME          "PlayerMenuSettingModelManager"

PlayerMenuSettingModelManager::PlayerMenuSettingModelManager(HWND hwnd, PlayerWindow* pplayer_window, CurrentDataModelManager* pcurrent_data_model_manager):
	mHwnd(hwnd),
	mpMenuSettingModels(new std::list<PlayerMenuSettingModel*>()),
	mpPlayerWindow(pplayer_window),
	mpCurrentDataModelManager(pcurrent_data_model_manager)
{
	add_setting_model("���ſ���", ID_PLAY_CHONTROL);
	add_setting_child_model(create_play_control_list(), ID_PLAY_CHONTROL);

	add_setting_model("���뷽ʽ", ID_DECODER);
	add_setting_child_model(create_decoder_list(), ID_DECODER);

	add_setting_model("seek��ʽ", ID_SEEK);
	add_setting_child_model(create_seek_list(), ID_SEEK);

	add_setting_model("�𲥷�ʽ", ID_SEEK_START);
	add_setting_child_model(create_start_seek_list(), ID_SEEK_START);

	add_setting_model("��Ȩ��ʽ", ID_AURHENTICATION);
	add_setting_child_model(create_authentication_list(), ID_AURHENTICATION);

	add_setting_model("��Ⱦ����", ID_RENDER_RADIO);
	add_setting_child_model(create_render_radio_list(), ID_RENDER_RADIO);

	add_setting_model("ɫ���仯", ID_BLIND);
	add_setting_child_model(create_blind_list(), ID_BLIND);

	add_setting_model("SEI�ص�", ID_SEI);
	add_setting_child_model(create_sei_list(), ID_SEI);

	add_setting_model("�������л�", ID_QUALITY_CHANGE);
	add_setting_child_model(create_quality_change_list(), ID_QUALITY_CHANGE);

	add_setting_model("��Ļ����", ID_SUBTITLE);
	add_setting_child_model(create_subtitle_list(), ID_SUBTITLE);

	add_setting_model("���ٲ���", ID_PLAY_SPEED);
	add_setting_child_model(create_play_speed_list(), ID_PLAY_SPEED);

	add_setting_model("��������", ID_MUTE);
	add_setting_child_model(create_mute_list(), ID_MUTE);

	add_setting_model("��ͼ", ID_SHOOT_IMAGE);
	add_setting_child_model(create_shoot_list(), ID_SHOOT_IMAGE);

	add_setting_model("��ʱ��", ID_PLAY_START_POSITION);
	add_setting_child_model(create_player_start_list(), ID_PLAY_START_POSITION);

	add_setting_model("¼��", ID_RECORD);
	add_setting_child_model(create_player_record_list(), ID_RECORD);
}



PlayerMenuSettingModelManager::~PlayerMenuSettingModelManager()
{
	if (mpMenuSettingModels != nullptr)
	{
		for (auto it = mpMenuSettingModels->begin(); it != mpMenuSettingModels->end(); ++it) {
			delete* it;
		}

		delete mpMenuSettingModels;
		mpMenuSettingModels = nullptr;

	}
}

void PlayerMenuSettingModelManager::add_setting_model(const std::string& menu_name, int id) {
	PlayerMenuSettingModel* pinner_model = new PlayerMenuSettingModel();
	pinner_model->set_id(id);
	pinner_model->set_name(menu_name);
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
		DemoLog::log_string(CLASS_NAME, __LINE__, "add_setting_child_model :inner_model is nil");
		return;
	}
	HMENU child_menu_hmenu = CreatePopupMenu();

	PlayerChildMenuModel* pchild_menu_model = new PlayerChildMenuModel();
	pchild_menu_model->set_menu(child_menu_hmenu);
	pchild_menu_model->set_child_menus_list(std::move(pchild_menu));
	pinner_model->set_child_menu_model(pchild_menu_model);

}


std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_play_control_list() {

	std::list<ChildMenu*>* pplay_control = new std::list<ChildMenu*>;
	
	pplay_control->emplace_back(create_child_menu("�ָ�����", ID_RESUME_BUTTON, false));
	pplay_control->emplace_back(create_child_menu("��ͣ����", ID_PAUSE_BUTTON, false));
	pplay_control->emplace_back(create_child_menu("ֹͣ����", ID_STOP_BUTTON, false));
	pplay_control->emplace_back(create_child_menu("�ͷŲ�����", ID_RELEASE_BUTTON, false));

	return pplay_control;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_decoder_list() {
	std::list<ChildMenu*>* pdecoder_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_decode_type(mpCurrentDataModelManager->get_decoder());
	switch (mpCurrentDataModelManager->get_decoder())
	{
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO: {
		pdecoder_list->emplace_back(create_child_menu("�Զ�", ID_AUTO_DECODER_BUTTON, true));
		pdecoder_list->emplace_back(create_child_menu("���", ID_SOFT_DECODER_BUTTON, false));
		pdecoder_list->emplace_back(create_child_menu("Ӳ��", ID_HARD_DECODER_BUTTON, false));
		break;
	}
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_SOFT_PRIORITY: {
		pdecoder_list->emplace_back(create_child_menu("�Զ�", ID_AUTO_DECODER_BUTTON, false));
		pdecoder_list->emplace_back(create_child_menu("���", ID_SOFT_DECODER_BUTTON, true));
		pdecoder_list->emplace_back(create_child_menu("Ӳ��", ID_HARD_DECODER_BUTTON, false));
		break;
	}
	case QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_HARDWARE_PRIORITY: {
		pdecoder_list->emplace_back(create_child_menu("�Զ�", ID_AUTO_DECODER_BUTTON, false));
		pdecoder_list->emplace_back(create_child_menu("���", ID_SOFT_DECODER_BUTTON, false));
		pdecoder_list->emplace_back(create_child_menu("Ӳ��", ID_HARD_DECODER_BUTTON, true));
		break;
	}
	default: {

		pdecoder_list->emplace_back(create_child_menu("�Զ�", ID_AUTO_DECODER_BUTTON, true));
		pdecoder_list->emplace_back(create_child_menu("���", ID_SOFT_DECODER_BUTTON, false));
		pdecoder_list->emplace_back(create_child_menu("Ӳ��", ID_HARD_DECODER_BUTTON, false));
		break;
	}
	}

	return pdecoder_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_seek_list() {
	std::list<ChildMenu*>* pseek_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_seek_mode(mpCurrentDataModelManager->get_seek_mode());
	switch (mpCurrentDataModelManager->get_seek_mode())
	{
	case QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL: {
		pseek_list->emplace_back(create_child_menu("�ؼ�֡seek", ID_SEEK_NORMAL_BUTTON, true));
		pseek_list->emplace_back(create_child_menu("��׼seek", ID_SEEK_ACCURATE_BUTTON, false));
		break;

	}
	case QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_ACCURATE: {
		pseek_list->emplace_back(create_child_menu("�ؼ�֡seek", ID_SEEK_NORMAL_BUTTON, false));
		pseek_list->emplace_back(create_child_menu("��׼seek", ID_SEEK_ACCURATE_BUTTON, true));
		break;

	}
	default: {

		pseek_list->emplace_back(create_child_menu("�ؼ�֡seek", ID_SEEK_NORMAL_BUTTON, true));
		pseek_list->emplace_back(create_child_menu("��׼seek", ID_SEEK_ACCURATE_BUTTON, false));
		break;
	}
	}

	return pseek_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_start_seek_list() {
	std::list<ChildMenu*>* pstart_seek_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_start_action(mpCurrentDataModelManager->get_player_start());
	switch (mpCurrentDataModelManager->get_player_start())
	{
	case QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING: {
		pstart_seek_list->emplace_back(create_child_menu("�𲥲���", ID_SEEK_START_PLAYING_BUTTON, true));
		pstart_seek_list->emplace_back(create_child_menu("����ͣ", ID_SEEK_START_PAUSE_BUTTON, false));
		break;

	}
	case QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PAUSE: {
		pstart_seek_list->emplace_back(create_child_menu("�𲥲���", ID_SEEK_START_PLAYING_BUTTON, false));
		pstart_seek_list->emplace_back(create_child_menu("����ͣ", ID_SEEK_START_PAUSE_BUTTON, true));
		break;

	}
	default: {

		pstart_seek_list->emplace_back(create_child_menu("�𲥲���", ID_SEEK_START_PLAYING_BUTTON, true));
		pstart_seek_list->emplace_back(create_child_menu("����ͣ", ID_SEEK_START_PAUSE_BUTTON, false));
		break;
	}
	}

	return pstart_seek_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_authentication_list() {
	std::list<ChildMenu*>* pauthentication_list = new std::list<ChildMenu*>;
	switch (mpCurrentDataModelManager->get_force_authentication_enable())
	{
	case true: {
		mpPlayerWindow->get_control_handler()->force_authentication_from_network();
		pauthentication_list->emplace_back(create_child_menu("��һ��ˢ�¼�Ȩ��Ϣ", ID_AURHENTICATION_BUTTON, true));
		break;

	}
	case false: {
		pauthentication_list->emplace_back(create_child_menu("��һ��ˢ�¼�Ȩ��Ϣ", ID_AURHENTICATION_BUTTON, false));
		break;

	}
	default: {

		pauthentication_list->emplace_back(create_child_menu("��һ��ˢ�¼�Ȩ��Ϣ", ID_AURHENTICATION_BUTTON, false));
		break;
	}
	}

	return pauthentication_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_render_radio_list() {
	std::list<ChildMenu*>* prender_radio_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_render_handler()->set_render_ratio(mpCurrentDataModelManager->get_render_ratio());
	switch (mpCurrentDataModelManager->get_render_ratio())
	{
	case QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO: {
		prender_radio_list->emplace_back(create_child_menu("�Զ�", ID_RENDER_RADIO_AUTO_BUTTON, true));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;

	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_16_9: {
		prender_radio_list->emplace_back(create_child_menu("�Զ�", ID_RENDER_RADIO_AUTO_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, true));
		prender_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_4_3: {
		prender_radio_list->emplace_back(create_child_menu("�Զ�", ID_RENDER_RADIO_AUTO_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, true));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_FULL_SCREEN: {
		prender_radio_list->emplace_back(create_child_menu("�Զ�", ID_RENDER_RADIO_AUTO_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, true));
		prender_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_STRETCH: {
		prender_radio_list->emplace_back(create_child_menu("�Զ�", ID_RENDER_RADIO_AUTO_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_STRETCH_BUTTON, true));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	default: {
		prender_radio_list->emplace_back(create_child_menu("�Զ�", ID_RENDER_RADIO_AUTO_BUTTON, true));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_STRETCH_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("����", ID_RENDER_RADIO_FULL_SCREEN_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("16:9", ID_RENDER_RADIO_16_9_BUTTON, false));
		prender_radio_list->emplace_back(create_child_menu("4:3", ID_RENDER_RADIO_4_3_BUTTON, false));
		break;
	}
	}

	return prender_radio_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_blind_list() {
	std::list<ChildMenu*>* pblind_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_render_handler()->set_blind_type(mpCurrentDataModelManager->get_blind());
	switch (mpCurrentDataModelManager->get_blind())
	{
	case QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_NONE: {
		pblind_list->emplace_back(create_child_menu("���˾�", ID_BLIND_NONE_BUTTON, true));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_RED_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_GREEN_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_BLUE_BUTTON, false));
		break;

	}
	case  QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_BLUE: {
		pblind_list->emplace_back(create_child_menu("���˾�", ID_BLIND_NONE_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_RED_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_GREEN_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_BLUE_BUTTON, true));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_GREEN: {
		pblind_list->emplace_back(create_child_menu("���˾�", ID_BLIND_NONE_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_RED_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_GREEN_BUTTON, true));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_BLUE_BUTTON, false));
		break;
	}
	case  QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_RED: {
		pblind_list->emplace_back(create_child_menu("���˾�", ID_BLIND_NONE_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_RED_BUTTON, true));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_GREEN_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_BLUE_BUTTON, false));
		break;
	}
	default: {
		pblind_list->emplace_back(create_child_menu("���˾�", ID_BLIND_NONE_BUTTON, true));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_RED_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_GREEN_BUTTON, false));
		pblind_list->emplace_back(create_child_menu("��/���˾�", ID_BLIND_BLUE_BUTTON, false));
		break;
	}
	}

	return pblind_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_sei_list() {
	std::list<ChildMenu*>* psei_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_sei_enable(mpCurrentDataModelManager->get_sei_enable());
	switch (mpCurrentDataModelManager->get_sei_enable())
	{
	case true: {
		psei_list->emplace_back(create_child_menu("����SEI�ص�", ID_SEI_OPEN_BUTTON, true));
		psei_list->emplace_back(create_child_menu("�ر�SEI�ص�", ID_SEI_CLOSE_BUTTON, false));
		break;

	}
	case  false: {
		psei_list->emplace_back(create_child_menu("����SEI�ص�", ID_SEI_OPEN_BUTTON, false));
		psei_list->emplace_back(create_child_menu("�ر�SEI�ص�", ID_SEI_CLOSE_BUTTON, true));
		break;
	}
	default: {
		psei_list->emplace_back(create_child_menu("����SEI�ص�", ID_SEI_OPEN_BUTTON, true));
		psei_list->emplace_back(create_child_menu("�ر�SEI�ص�", ID_SEI_CLOSE_BUTTON, false));
		break;
	}
	}

	return psei_list;
}



std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_quality_change_list() {
	std::list<ChildMenu*>* pquality_change_list = new std::list<ChildMenu*>;
	switch (mpCurrentDataModelManager->get_quality_immediatyly())
	{
	case QualityImmediatyly::IMMEDIATYLY_TRUE: {
		pquality_change_list->emplace_back(create_child_menu("�����л�", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, true));
		pquality_change_list->emplace_back(create_child_menu("�޷��л���ֻʹ�õ㲥��", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, false));
		pquality_change_list->emplace_back(create_child_menu("ֱ������&�㲥�޷�", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, false));
		break;

	}
	case  QualityImmediatyly::IMMEDIATYLY_FALSE: {
		pquality_change_list->emplace_back(create_child_menu("�����л�", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, false));
		pquality_change_list->emplace_back(create_child_menu("�޷��л���ֻʹ�õ㲥��", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, true));
		pquality_change_list->emplace_back(create_child_menu("ֱ������&�㲥�޷�", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, false));
		break;
	}
	case  QualityImmediatyly::IMMEDIATYLY_CUSTOM: {
		pquality_change_list->emplace_back(create_child_menu("�����л�", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, false));
		pquality_change_list->emplace_back(create_child_menu("�޷��л���ֻʹ�õ㲥��", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, false));
		pquality_change_list->emplace_back(create_child_menu("ֱ������&�㲥�޷�", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, true));
		break;
	}
	default: {
		pquality_change_list->emplace_back(create_child_menu("�����л�", ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON, true));
		pquality_change_list->emplace_back(create_child_menu("�޷��л���ֻʹ�õ㲥��", ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON, false));
		pquality_change_list->emplace_back(create_child_menu("ֱ������&�㲥�޷�", ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON, false));
		break;
	}
	}

	return pquality_change_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_subtitle_list() {
	std::list<ChildMenu*>* psubtitle_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_subtitle_enable(mpCurrentDataModelManager->get_subtitle_enable());
	//mpPlayerWindow->get_control_handler()->set_subtitle(mpCurrentDataModelManager->get_subtitle_name());
	switch (mpCurrentDataModelManager->get_subtitle_enable())
	{
	case false: {
		psubtitle_list->emplace_back(create_child_menu("�ر�", ID_SUBTITLE_CLOSE_BUTTON, true));
		break;

	}
	case  true: {
		psubtitle_list->emplace_back(create_child_menu("�ر�", ID_SUBTITLE_CLOSE_BUTTON, false));
		break;
	}
	default: {
		break;
	}
	}

	return psubtitle_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_play_speed_list() {
	std::list<ChildMenu*>* pplay_speed_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_speed(mpCurrentDataModelManager->get_play_speed());
	if (mpCurrentDataModelManager->get_play_speed() == 0.5)
	{
		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, true));
	}
	else if (mpCurrentDataModelManager->get_play_speed() == 0.75)
	{
		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, true));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (mpCurrentDataModelManager->get_play_speed() == 1.0)
	{
		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, true));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (mpCurrentDataModelManager->get_play_speed() == 1.25)
	{
		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, true));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (mpCurrentDataModelManager->get_play_speed() == 1.5)
	{
		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, true));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else if (mpCurrentDataModelManager->get_play_speed() == 2.0)
	{
		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, true));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	else
	{

		pplay_speed_list->emplace_back(create_child_menu("2.0x", ID_PLAY_SPEED_2_0_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.5x", ID_PLAY_SPEED_1_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.25x", ID_PLAY_SPEED_1_2_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("1.0x", ID_PLAY_SPEED_1_0_BUTTON, true));
		pplay_speed_list->emplace_back(create_child_menu("0.75x", ID_PLAY_SPEED_0_7_5_BUTTON, false));
		pplay_speed_list->emplace_back(create_child_menu("0.5x", ID_PLAY_SPEED_0_5_BUTTON, false));
	}
	return pplay_speed_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_mute_list() {
	std::list<ChildMenu*>* pmute_list = new std::list<ChildMenu*>;
	mpPlayerWindow->get_control_handler()->set_mute(mpCurrentDataModelManager->get_mute_enable());
	switch (mpCurrentDataModelManager->get_mute_enable())
	{
	case true: {

		pmute_list->emplace_back(create_child_menu("�Ǿ���", ID_MUTE_CLOSE_BUTTON, false));
		pmute_list->emplace_back(create_child_menu("����", ID_MUTE_OPEN_BUTTON, true));
		break;
	}
	case false: {

		pmute_list->emplace_back(create_child_menu("�Ǿ���", ID_MUTE_CLOSE_BUTTON, true));
		pmute_list->emplace_back(create_child_menu("����", ID_MUTE_OPEN_BUTTON, false));
		break;
	}
	default:
		pmute_list->emplace_back(create_child_menu("�Ǿ���", ID_MUTE_CLOSE_BUTTON, true));
		pmute_list->emplace_back(create_child_menu("����", ID_MUTE_OPEN_BUTTON, false));
		break;
	}

	return pmute_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_shoot_list() {

	std::list<ChildMenu*>* pshoot_list = new std::list<ChildMenu*>;
	pshoot_list->emplace_back(create_child_menu("��ͼ", ID_SHOOT_IMAGE_BUTTON, false));
	return pshoot_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_player_start_list() {
	std::list<ChildMenu*>* pplay_start_position_list = new std::list<ChildMenu*>;
	pplay_start_position_list->emplace_back(create_child_menu(std::to_string(mpCurrentDataModelManager->get_player_start_position()), ID_PLAY_START_POSITION_BUTTON, false));
	return pplay_start_position_list;
}

std::list<ChildMenu*>* PlayerMenuSettingModelManager::create_player_record_list() {
	std::list<ChildMenu*>* precord_list = new std::list<ChildMenu*>;
	precord_list->emplace_back(create_child_menu("¼��", ID_RECORD_BUTTON, false));
	return precord_list;
}

ChildMenu* PlayerMenuSettingModelManager::create_child_menu(const std::string& name, int id, bool is_selected) {
	ChildMenu* pinner_child_menu = new ChildMenu();
	pinner_child_menu->set_id(id);
	pinner_child_menu->set_name(name);
	pinner_child_menu->set_is_selected(is_selected);
	return pinner_child_menu;
}


std::list<PlayerMenuSettingModel*>* PlayerMenuSettingModelManager::get_menu_setting_model() {
	return mpMenuSettingModels;
}


HMENU PlayerMenuSettingModelManager::get_child_menu_for_name(const std::string& name) {
	std::list<PlayerMenuSettingModel*>* setting_model = get_menu_setting_model();

	for (int parent_index = 0; parent_index < setting_model->size(); parent_index++) {
		auto parent_it = setting_model->begin();
		std::advance(parent_it, parent_index);
		if ((*parent_it)->get_name() == name)
		{
			return (*parent_it)->get_child_menu_model()->get_menus();
		}
	}

	return nullptr;
}
void PlayerMenuSettingModelManager::update_play_start_position_menu_text(long start_position, HMENU position_hmenu) {
	ModifyMenu(position_hmenu, ID_PLAY_START_POSITION_BUTTON, MF_STRING, ID_PLAY_START_POSITION_BUTTON, std::to_string(start_position).c_str());
	
}

void PlayerMenuSettingModelManager::update_subtitle_menu_text(QMedia::QMediaModel* pmodel, HMENU subtitle_hmenu) {
	int item_count = GetMenuItemCount(subtitle_hmenu);
	for (int i = item_count - 1; i >= 0; --i) {
		DeleteMenu(subtitle_hmenu, i, MF_BYPOSITION);
	}
	std::list<ChildMenu*>* psubtitle_list = new std::list<ChildMenu*>();
	if (mpCurrentDataModelManager->get_subtitle_enable())
	{
		psubtitle_list->emplace_back(create_child_menu("�ر�", ID_SUBTITLE_CLOSE_BUTTON, false));
	}
	else {
		psubtitle_list->emplace_back(create_child_menu("�ر�", ID_SUBTITLE_CLOSE_BUTTON, true));
	}
	for (int index = 0; index < pmodel->get_subtitle_elements().size(); index++)
	{
		QMedia::QSubtitleElement* psub_ele = pmodel->get_subtitle_elements()[index];
		if (mpCurrentDataModelManager->get_subtitle_enable() && psub_ele->is_selected())
		{
			psubtitle_list->emplace_back(create_child_menu(psub_ele->get_name(), ID_SUBTITLE_CLOSE_BUTTON + 1 + index, true));
		}
		else
		{
			psubtitle_list->emplace_back(create_child_menu(psub_ele->get_name(), ID_SUBTITLE_CLOSE_BUTTON + 1 + index, false));
		}
	}

	for (int index = 0; index < psubtitle_list->size(); index++)
	{

		auto child_it = psubtitle_list->begin();
		std::advance(child_it, index);
		//���������˵���ť
		AppendMenu(subtitle_hmenu, MF_STRING, (*child_it)->get_id(), (*child_it)->get_name().c_str());
		if ((*child_it)->get_is_selected())
		{
			CheckMenuItem(subtitle_hmenu, (*child_it)->get_id(), MF_CHECKED);
		}
		
	}
	PlayerMenuSettingModel* pinner_model = nullptr;
	for (int index = 0; index < mpMenuSettingModels->size(); index++)
	{
		auto it = mpMenuSettingModels->begin();
		std::advance(it, index);
		if ((*it)->get_id() == ID_SUBTITLE)
		{
			pinner_model = *it;
			break;
		}
	}
	if (pinner_model == nullptr)
	{
		DemoLog::log_string(CLASS_NAME, __LINE__, "update_subtitle_menu_text :inner_model is nil");
		return;
	}

	PlayerChildMenuModel* pchild_menu_model = new PlayerChildMenuModel();
	pchild_menu_model->set_menu(subtitle_hmenu);
	pchild_menu_model->set_child_menus_list(std::move(psubtitle_list));
	pinner_model->set_child_menu_model(pchild_menu_model);
}
