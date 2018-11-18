#include "Animation.h"

//------------------------------------------------------------------------------------------------------------//

Animation::Animation(const char* filePath, int frameWidth, int frameHeight, int cols)
	:Sprite(filePath, RECT(), frameWidth, frameHeight)
{
	startFrames = 0;
	endFrames = 0;
	currentFrame = 0;

	animComplete = false;
	isLoop = true;

	animTimer = 0.0f;
	frameDelay = 1.0f;

	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->cols = cols;
}

void Animation::updateAnimation(float dt)
{
	rect.left = (currentFrame % cols) * frameWidth;
	rect.top = (currentFrame / cols) * frameHeight;
	rect.right = rect.left + frameWidth;
	rect.bottom = rect.top + frameHeight;

	this->setSourceRect(rect);

	if (endFrames - startFrames > 0)          // if animated sprite
	{
		animTimer += dt;					// total elapsed time
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			++currentFrame;
			if (currentFrame < startFrames || currentFrame > endFrames)
			{
				if (isLoop)							// if looping animation
					currentFrame = startFrames;
				else								// not looping animation
				{
					currentFrame = endFrames;
					animComplete = true;			// animation complete
				}
			}			
		}
	}
}
//------------------------------------------------------------------------------------------------------------//

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

void Animation::drawSprite(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform,
	float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	Sprite::drawSprite(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::drawSprite(D3DXVECTOR2 translate)
{
	Sprite::drawSprite(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}