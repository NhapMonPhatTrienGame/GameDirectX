#include "Animation.h"


Animation::Animation(const char* filePath, int rows, int columns, int frameWidth, int frameHeight, float timePerFrame, D3DCOLOR colorKey) : Sprite(filePath, RECT(), frameWidth, frameHeight, colorKey)
{
	this->m_Rows = rows;
	this->m_Columns = columns;
	this->m_CurrentRow = 0;
	this->m_CurrentIndex = 0;
	this->m_framePerRow = columns;
	this->m_FrameWidth = frameWidth;
	this->m_FrameHeight = frameHeight;
	this->m_TimePerFrame = timePerFrame;

	this->m_LoopAnimation = true;
	this->m_Pause = false;
	this->m_Shoot = false;
}

int Animation::getCurrentColumn() const
{
	return this->m_CurrentIndex;
}

void Animation::setShoot(bool shoot)
{
	this->m_Shoot = shoot;
}

void Animation::setPause(bool pause)
{
	this->m_Pause = pause;
}

void Animation::setLoopAnimation(bool allowLoopAnimation)
{
	this->m_LoopAnimation = allowLoopAnimation;
}

void Animation::setAnimation(int currentRow, int framePerRow, float timePerFrame, bool loopAnimation)
{
	this->m_CurrentRow = currentRow;
	this->m_framePerRow = framePerRow;
	this->m_TimePerFrame = timePerFrame;
	this->m_LoopAnimation = loopAnimation;
	m_CurrentTotalTime = 0;
	this->m_CurrentIndex = 0;
	m_Pause = false;
}

void Animation::Update(float dt)
{
	m_Rect.left = m_CurrentIndex * m_FrameWidth;
	m_Rect.right = m_Rect.left + m_FrameWidth;
	m_Rect.top = (m_CurrentRow + m_Shoot) * m_FrameHeight;
	m_Rect.bottom = m_Rect.top + m_FrameHeight;

	setSourceRect(m_Rect);

	if (m_framePerRow <= 1 || m_Pause)
		return;

	m_CurrentTotalTime += dt;
	if (m_CurrentTotalTime >= m_TimePerFrame)
	{
		m_CurrentTotalTime = 0;
		if (++m_CurrentIndex >= m_framePerRow)
		{
			if (m_LoopAnimation)
				m_CurrentIndex = 0;
			else
			{
				m_CurrentIndex = m_framePerRow - 1;
				m_Pause = true;
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
