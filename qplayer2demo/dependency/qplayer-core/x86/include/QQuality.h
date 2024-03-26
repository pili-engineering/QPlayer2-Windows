#pragma once
#include <string>
#include "QUrlType.h"
#include <stdint.h>
namespace QMedia {

    class QQuality {
    
    public:
        QQuality(const std::string& user_type, QUrlType url_type, uint32_t quality_index) :
            mUserType(user_type),
            mUrlType(url_type),
            mQualityIndex(quality_index) {}

        ~QQuality() {}

        QQuality(const QQuality&) = delete;

        QQuality(QQuality&&) = delete;

        QQuality& operator=(const QQuality&) = delete;

        QQuality& operator=(QQuality&&) = delete;

        const std::string& get_user_type() const { return mUserType; }

        QUrlType get_url_type() const { return mUrlType; }

        uint32_t get_quality_index() const { return mQualityIndex; }

    private:
        std::string mUserType;
        QUrlType mUrlType;
        uint32_t mQualityIndex;
    
    };
}