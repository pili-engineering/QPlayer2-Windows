#pragma once

#include "QPlayerExport.h"
#include <vector>
#include "QStreamElement.h"
#include "QSubtitleElement.h"
namespace QMedia {
    /// <summary>
    /// 视频数据模型
    /// </summary>
    class QPLAYER_API QMediaModel {
    

    private:
        QMediaModel(std::vector<QStreamElement*> stream_elements,
            std::vector<QSubtitleElement*> subtitle_elements,
            bool is_live, bool is_reconstruct_time_line);


        QMediaModel(const QMediaModel&) = delete;

        QMediaModel(QMediaModel&&) = delete;

        QMediaModel& operator=(const QMediaModel&) = delete;

        QMediaModel& operator=(QMediaModel&&) = delete;

        friend class QMediaModelBuilder;

    public:
        ~QMediaModel();

        /// <summary>
        /// 获取视频元素
        /// </summary>
        /// <returns></returns>
        const std::vector<QStreamElement*>& get_stream_elements() const { return mStreamElements; }

        /// <summary>
        /// 获取字幕元素
        /// </summary>
        /// <returns></returns>
        const std::vector<QSubtitleElement*>& get_subtitle_elements() const { return mSubtitleElements; }

        /// <summary>
        /// 获取地址是否是直播
        /// </summary>
        /// <returns></returns>
        bool is_live() const { return mIsLive; }

        /// <summary>
        /// 获取是否重构时间轴
        /// </summary>
        /// <returns></returns>
        bool is_reconstruct_time_line() const { return mIsReconstructTimeLine; }
    private:
        std::vector<QStreamElement*> mStreamElements;
        std::vector<QSubtitleElement*> mSubtitleElements;

        bool mIsLive;

        bool mIsReconstructTimeLine;
    };
}