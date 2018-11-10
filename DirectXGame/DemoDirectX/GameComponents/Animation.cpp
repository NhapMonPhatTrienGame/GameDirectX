#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->mRows = rows;
	this->mColumns = columns;
	this->mFramePerRow = columns;
	this->mFrameWidth = frameWidth;
	this->mFrameHeight = frameHeight;
	this->mTimePerFrame = timePerFrame;

	this->mCurrentRow = 0;
	this->mCurrentIndex = 0;
	this->mCurrentTotalTime = 0;

	this->mShoot = false;
}

Animation::Animation() {}

int Animation::getCurrentColumn() const
{
	return mCurrentIndex;
}
void Animation::setCurrentColumn(int index)
{
	mCurrentIndex = index;
}

void Animation::SetShoot(bool shoot)
{
	this->mShoot = shoot;
}

void Animation::SetAnimation(int currentRow, int framePerRow, float timePerFrame)
{
	this->mCurrentRow = currentRow;
	this->mFramePerRow = framePerRow;
	this->mTimePerFrame = timePerFrame;
	this->mCurrentTotalTime = 0;
	this->mCurrentIndex = 0;
}

void Animation::setAnimation(int currentRow, int framePerRow, float timePerFrame, int currentColumn)
{
	this->mCurrentRow = currentRow;
	this->mFramePerRow = framePerRow;
	this->mTimePerFrame = timePerFrame;
	this->mCurrentTotalTime = 0;
	this->mCurrentIndex = currentColumn;

	mRect.left = mCurrentIndex * mFrameWidth;
	mRect.right = mRect.left + mFrameWidth;
	mRect.top = mCurrentRow * mFrameHeight;
	mRect.bottom = mRect.top + mFrameHeight;

	SetSourceRect(mRect);
}

void Animation::Update(float dt)
{
	if (mFramePerRow <= 1 || mCurrentRow > mRows || mFramePerRow > mColumns)
		return;

	mCurrentTotalTime += dt;
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;

		if (mCurrentIndex >= mFramePerRow)
			mCurrentIndex = 0;

		mRect.left = mCurrentIndex * mFrameWidth;
		mRect.right = mRect.left + mFrameWidth;
		mRect.top = mCurrentRow * mFrameHeight;
		mRect.bottom = mRect.top + mFrameHeight;

		SetSourceRect(mRect);
	}
}

void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale,
	D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Draw(D3DXVECTOR2 translate)
{
	Sprite::Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}

Animation::~Animation() {}
