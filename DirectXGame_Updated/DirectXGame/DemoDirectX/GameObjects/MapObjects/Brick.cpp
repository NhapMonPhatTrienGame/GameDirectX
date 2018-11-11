#include "Brick.h"
#include "../../GameComponents/GameGlobal.h"


bool Brick::Init(D3DXVECTOR3 position)
{
	pBrickAnimation = new Animation(FileName(), Row(), Column(), 32, 32, TimePerFrame());

    setPosition(position);

	Entity::setWidth(pBrickAnimation->GetWidth());
	Entity::setHeight(pBrickAnimation->GetHeight());

    return true;
}

void Brick::onSetPosition(D3DXVECTOR3 pos)
{
	pBrickAnimation->SetPosition(pos);
}

void Brick::Update(float dt)
{
	pBrickAnimation->Update(dt);
}

void Brick::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) const
{
	pBrickAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Brick::Draw(D3DXVECTOR2 transform) const
{
	pBrickAnimation->Draw(D3DXVECTOR2(transform));
}
