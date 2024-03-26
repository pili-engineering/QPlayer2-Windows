#pragma once
#include <cstdint>

namespace QMedia {
	
	enum class QPlayerNotify : uint32_t {
        NONE = 0,
        /************** moudle screen render *******************/

        //һ����Ƶ���׸�start��־֡���������ݣ�
        NOTIFY_SCREEN_RENDER_START = 10001,
        //һ����Ƶ�ĵ�һ֡��Ⱦ��ɣ������ݣ�
        NOTIFY_SCREEN_RENDER_FIRST_FRAME = 10002,
        NOTIFY_SCREEN_RENDER_END = 10003,
        NOTIFY_SCREEN_RENDER_OVER_ONE_FRAME = 10006,

        /************** moudle video render *******************/


        NOTIFY_VIDEO_RENDER_QUALITY_CHANGED = 11004,
        NOTIFY_VIDEO_SEI_DATA = 11005,
        NOTIFY_VIDEO_SHOOT_SUCCESS = 11006,
        NOTIFY_VIDEO_SHOOT_FAILED = 11007,
        NOTIFY_VIDEO_RENDER_FRAME_SIZE_CHANGED = 11008,

		NOTIFY_VIDEO_RENDER_DATA_SUCCESS = 11009,
		NOTIFY_VIDEO_RENDER_DATA_FAILED = 11010,


        /************** moudle audio render *******************/

        NOTIFY_AUDIO_RENDER_START = 12002,
        NOTIFY_AUDIO_RENDER_END = 12003,

        NOTIFY_AUDIO_RENDER_QUALITY_CHANGED = 12007,

        NOTIFY_AUDIO_RENDER_VOLUME_CHANGED = 12008,

		NOTIFY_AUDIO_RENDER_MUTE_STATE_CHANGED = 12009,
		NOTIFY_AUDIO_RENDER_DATA = 12010,

        /************** combine render *******************/

        NOTIFY_RENDER_BUFFERRING_START = 13000,
        NOTIFY_RENDER_BUFFERRING_END = 13001,

        NOTIFY_RENDER_PROGRESS = 13002,

		/************** moudle subtitle render *******************/
		NOTIFY_SUBTITLE_RENDER_TEXT_CHANGED = 14001,
		NOTIFY_SUBTITLE_CHANGED = 14002,
		NOTIFY_SUBTITLE_CLOSE = 14003,
		NOTIFY_SUBTITLE_OPEN = 14004,

		NOTIFY_SUBTITLE_LOAD_RESULT = 14005,
		NOTIFY_SUBTITLE_DECODE_RESULT = 14006,

        /************** moudle input stream *******************/
        NOTIFY_INPUT_STREAM_INVALID_URL = 40001,

        NOTIFY_INPUT_STREAM_OPEN = 40002,

        NOTIFY_INPUT_STREAM_IO_ERROR = 40100,
        NOTIFY_INPUT_STREAM_OPEN_ERROR = 40101,
        NOTIFY_INPUT_STREAM_INVALID_DATA_ERROR = 40102,
        NOTIFY_INPUT_STREAM_RECONNECT_START = 40103,
        NOTIFY_INPUT_STREAM_RECONNECT_END = 40104,

        NOTIFY_INPUT_STREAM_HTTP_OPEN_START = 40110,
        NOTIFY_INPUT_STREAM_HTTP_OPEN_END = 40111,
        NOTIFY_INPUT_STREAM_TCP_OPEN_START = 40112,
        NOTIFY_INPUT_STREAM_TCP_OPEN_END = 40113,

        NOTIFY_INPUT_STREAM_QUALITY_SWITCH_START = 40010,
        NOTIFY_INPUT_STREAM_QUALITY_SWITCH_FAILED = 40012,
        NOTIFY_INPUT_STREAM_QUALITY_SWITCH_CANCELED = 40013,
        NOTIFY_INPUT_STREAM_QUALITY_SWITCH_RETRY_LATER = 40014,

        NOTIFY_INPUT_STREAM_NOT_SUPPORT_CODEC_FORMAT = 40120,
        /************** moudle decoder *******************/
        NOTIFY_DECODE_FINISH = 50001,
        NOTIFY_DECODE_INIT_ERROR = 50004,
        NOTIFY_DECODE_VIDEO_DECODE_TYPE = 50005,
        NOTIFY_DECODE_OPEN_CODEC_ERROR = 50007,
        NOTIFY_UNABLE_HANDLE_RECEIVE_FRAME_ERROR = 50008,
        /************** state manager *******************/
        /** error **/
        NOTIFY_STATE_MANAGER_CHANGE_STATE_NOT_ALLOW_ERROR = 60001,
        NOTIFY_STATE_SEEKING_FAILED = 61001,
        NOTIFY_STATE_SEEKING_SUCCESS = 61002,
        NOTIFY_STATE_PREPARE_START_SEEK_FAILED = 62001,

        /************** render transformer *******************/
        NOTIFY_RENDER_TRANSFORMER_INIT_ERROR = 70002,
        NOTIFY_RENDER_TRANSFORMER_NOT_SUPPORT_TRANSFORM_FORMAT = 70003,

        /************** detect *******************/
        NOTIFY_DETECT_DOWNLOADING = 80000,
        NOTIFY_DETECT_FPS = 80001,
        NOTIFY_DETECT_BITRATE = 80002,

        /************** event loop *******************/
        NOTIFY_EVENT_LOOP_COMMOND_NOT_ALLOW = 90000,

        /************** clock *******************/
        NOTIFY_EVENT_SPEED_CHANGE = 100000,

        /************** Authentication *******************/
        NOTIFY_AUTHENTICATION_FAILED = 110000,
        NOTIFY_AUTHENTICATION_SUCESS = 110001,
	};
}