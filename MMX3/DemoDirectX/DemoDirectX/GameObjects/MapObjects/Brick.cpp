#include "Brick.h"
#include "../../GameComponents/GameGlobal.h"
#include "../../GameDefines/GameDefine.h"


bool Brick::Init(D3DXVECTOR3 position)
{
	try
	{
		pBrickAnimation = new Animation(fileName(), row(), column(), 32, 32, timePerFrame());

		setPosition(position);
		this->setWidth(pBrickAnimation->getWidth());
		this->setHeight(pBrickAnimation->getHeight());
	}
	catch (...) { return false; }
	
	return true;
}

void Brick::onSetPosition(D3DXVECTOR3 pos)
{
	pBrickAnimation->setPosition(pos);
}

Brick::~Brick()
{
	SAFE_DELETE(pBrickAnimation);
}

void Brick::update(float dt)
{
	pBrickAnimation->update(dt);
}

void Brick::drawSprite(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) const
{
	pBrickAnimation->draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Brick::drawSprite(D3DXVECTOR2 transform) const
{
	pBrickAnimation->draw(D3DXVECTOR2(transform));
}
