#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->mRows = rows;
	this->mColumns = columns;
	this->mCurrentRow = 0;
	this->mCurrentIndex = 0;
	this->mframePerRow = columns;
	this->mFrameWidth = frameWidth;
	this->mFrameHeight = frameHeight;
	this->mTimePerFrame = timePerFrame;

	this->mLoopAnimation = true;
	this->mPause = false;
	this->mShoot = false;
}

Animation::~Animation()
{

}

int Animation::GetCurrentColumn() const
{
	return this->mCurrentIndex;
}

void Animation::SetShoot(bool shoot)
{
	this->mShoot = shoot;
}

void Animation::SetPause(bool pause)
{
	this->mPause = pause;
}

void Animation::SetLoopAnimation(bool allowLoopAnimation)
{
	this->mLoopAnimation = allowLoopAnimation;
}

void Animation::SetAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	this->mCurrentRow = currentRow;
	this->mframePerRow = framePerRow;
	this->mTimePerFrame = timePerFrame;
	this->mLoopAnimation = loopAnimation;
	mCurrentTotalTime = 0;
	this->mCurrentIndex = 0;
	mPause = false;
}

void Animation::Update(float dt)
{
	mRect.left = mCurrentIndex * mFrameWidth;
	mRect.right = mRect.left + mFrameWidth;
	mRect.top = (mCurrentRow + mShoot) * mFrameHeight;
	mRect.bottom = mRect.top + mFrameHeight;

	SetSourceRect(mRect);

	if (mframePerRow <= 1 || mPause)
		return;

	mCurrentTotalTime += dt;
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;

		if (mCurrentIndex >= mframePerRow)
		{
			if (mLoopAnimation)
				mCurrentIndex = 0;
			else
			{
				mCurrentIndex = mframePerRow - 1;
				mPause = true;
			}
		}
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
