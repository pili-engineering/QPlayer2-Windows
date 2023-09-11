#pragma once
#include "framework.h"
#include "QMediaModel.h"
#include "QPlayerState.h"
class CurrentDataModel
{
public:
	CurrentDataModel();
	~CurrentDataModel();

public:
	long mProgressTime;

	long mDurationTime;

	QMedia::QMediaModel* mModel;

	QMedia::QPlayerState mPlayState;

	int mFPS;

	int mFirstFrameTime;

	int mDownSpeed;

	bool mIsSeeking;

};

