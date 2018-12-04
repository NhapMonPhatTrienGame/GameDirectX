#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->row = rows;
	this->cols = columns;

	this->currentRow = 0;
	this->currentIndex = 0;

	this->framePerRow = columns;

	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;

	this->timePerFrame = timePerFrame;

	this->isLoopAnimation = true;
	this->isPause = false;
	this->isShoot = false;
}

void Animation::setFrames(int frameW, int frameH)
{
	this->frameWidth = frameW;
	this->frameHeight = frameH;
	this->setWidth(frameW);
	this->setHeight(frameH);
}

void Animation::setAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	this->currentRow = currentRow;
	this->framePerRow = framePerRow;

	this->timePerFrame = timePerFrame;

	this->isLoopAnimation = loopAnimation;

	currentTotalTime = 0;
	this->currentIndex = 0;
	isPause = false;
}

void Animation::update(float dt)
{
	rect.left = currentIndex * frameWidth;
	rect.right = rect.left + frameWidth;
	rect.top = (currentRow + isShoot) * frameHeight;
	rect.bottom = rect.top + frameHeight;

	setSourceRect(rect);

	if (framePerRow <= 1 || isPause)
		return;

	currentTotalTime += dt;
	if (currentTotalTime >= timePerFrame)
	{
		currentTotalTime = 0;
		if (++currentIndex >= framePerRow)
		{
			if (isLoopAnimation)
				currentIndex = 0;
			else
			{
				currentIndex = framePerRow - 1;
				isPause = true;
			}
		}
	}
}

void Animation::draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform,
	float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::draw(D3DXVECTOR2 translate)
{
	Sprite::draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}