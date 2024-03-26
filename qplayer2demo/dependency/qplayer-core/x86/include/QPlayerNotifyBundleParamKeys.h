#pragma once
#include "QPlayerExport.h"

namespace QMedia {
    namespace QPlayerNotifyBundleKeys {
        static constexpr const char* const STREAM_DURATION = "stream_duration";
        static constexpr const char* const CURRENT_RENDER_PROGRESS = "current_progress";
        static constexpr const char* const FPS = "fps";
		static constexpr const char* const DOWNLOAD_BIT = "download_bits";
		static constexpr const char* const DOWNLOAD_SPEED = "download_speed";
		static constexpr const char* const BUFFER_POS = "buffer_pos";
        static constexpr const char* const BUFFER_PROGRESS = "buffer_progress";
        static constexpr const char* const BITE_RATE = "bite_rate";
        static constexpr const char* const SCREEN_RENDER_FIRST_FRAME_ELAPSED_TIME = "screen_render_first_frame_time";

        static constexpr const char* const COMMAND_NAME = "command_name";
        static constexpr const char* const PLAYER_STATE = "player_state";
        static constexpr const char* const MEDIA_ITEM_STATE = "media_item_state";


        static constexpr const char* const USER_TYPE = "user_type";
        static constexpr const char* const URL_TYPE = "url_type";
        static constexpr const char* const OLD_QUALITY = "old_quality";
        static constexpr const char* const NEW_QUALITY = "new_quality";
        static constexpr const char* const QUALITY = "quality";


		static constexpr const char* const OPEN_ERROR = "open_error";

        static constexpr const char* const QUALITY_SERIAL = "quality_serial";
        static constexpr const char* const NETWORK_ERROR = "network_error";
        static constexpr const char* const CONNECT_RETRY_TIME = "retry_time";
        static constexpr const char* const URL = "url";

        static constexpr const char* const SPEED = "speed";
        static constexpr const char* const DECODE_TYPE = "decode_type";

        static constexpr const char* const CODEC_ID = "codec_id";

		static constexpr const char* const SEI_DATA = "sei_data";
		static constexpr const char* const SEI_DATA_SIZE = "sei_data_size";

        static constexpr const char* const AUTHENTICATION_ERROR_TYPE = "authentication_error_type";

		static constexpr const char* const SHOOT_VIDEO_IMAGE = "shoot_image";
		static constexpr const char* const SHOOT_VIDEO_IMAGE_SIZE = "shoot_image_size";

        static constexpr const char* const SHOOT_VIDEO_WIDTH = "shoot_width";

        static constexpr const char* const SHOOT_VIDEO_HEIGHT = "shoot_height";

        static constexpr const char* const SHOOT_VIDEO_TYPE = "shoot_type";

        static constexpr const char* const AUDIO_VOLUME = "audio_volume";

        static constexpr const char* const VIDEO_WIDTH = "video_width";

        static constexpr const char* const VIDEO_HEIGHT = "video_height";

        static constexpr const char* const MUTE_STATE = "mute_state";

		static constexpr const char* const SUBTITLE_NAME = "subtitle_name";
        static constexpr const char* const SUBTITLE_TEXT = "subtitle_text";
		static constexpr const char* const SUBTITLE_RESULT = "subtitle_result";

		static constexpr const char* const AUDIO_DATA_SAMPLE_RATE = "audio_data_sample_rate";
		static constexpr const char* const AUDIO_DATA_FORMAT = "audio_data_format";
		static constexpr const char* const AUDIO_DATA_CHANNEL_NUM = "audio_data_channel_num";
		static constexpr const char* const AUDIO_DATA_CHANNEL_LAYOUT = "audio_data_channel_layout";
		static constexpr const char* const AUDIO_DATA = "audio_data";
		static constexpr const char* const AUDIO_DATA_SIZE = "audio_data_size";

		static constexpr const char* const VIDEO_DATA_HEIGHT = "video_data_height";
		static constexpr const char* const VIDEO_DATA_WIDTH = "video_data_width";
		static constexpr const char* const VIDEO_DATA = "video_data";
		static constexpr const char* const VIDEO_DATA_SIZE = "video_data_size";
        static constexpr const char* const VIDEO_DATA_TYPE = "video_data_type";

        static constexpr const char* const DECODE_CODEC_TYPE = "decode_codec_type";
        static constexpr const char* const DECODE_ERROR_CODE = "decode_error_code";
    }
}