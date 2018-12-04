#include "CarryArms.h"
#include "GameDefines/GameDefine.h"

CarryArms::CarryArms()
{
	tag = Tag::Enemy;
	allowDraw = true;
	currentState = CarryArmsState::None;
	distance = 200.0f;
	vx = 0;
	vy = 0;
	timeMoveDown = 0;
	timeMoveUp = 0;
	anim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15f, D3DCOLOR_XRGB(255, 0, 220));
	setState(CarryArmsState::Stand);

	box = new Box();
}

CarryArms::~CarryArms()
{
	delete anim;
	delete box;
}

void CarryArms::draw(Camera* camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotateCenter, D3DCOLOR color)
{
	box->Draw(camera);

	if (!allowDraw)
		return;

	anim->setPosition(getPosition());

	if(!box->getBottom()) box->setPosition(anim->getPosition().x, getBound().bottom + 15);

	if (camera) anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
	else anim->draw(anim->getPosition());
}

RECT CarryArms::getBound()
{
	RECT r = RECT();

	if (currentState == CarryArmsState::EventMoveUpTwice)
	{
		r.left = x - 43 / 2.0f;
		r.right = 43 + r.left;
		r.top = y - 59 / 2.0f;
		r.bottom = 59 + r.top;
	}
	else
	{
		r.left = x - 36 / 2.0f;
		r.right = r.left + 36;
		r.top = y - 57 / 2.0f;
		r.bottom = r.top + 57;
	}
	return r;
}

void CarryArms::update(float dt)
{
	box->update(dt);

	if (!allowDraw)
		return;

	ManageState(dt);

	anim->update(dt);
	Entity::update(dt);
}

void CarryArms::onCollision(Entity* obj)
{
	if(obj->getTag() == Tag::RockManBullet)
	{
		
	}
}

void CarryArms::CheckCollision(GameMap* map, float dt) const
{
	box->CheckCollision(map, dt);
}

void CarryArms::setState(CarryArmsState state)
{
	if (currentState == state)
		return;

	currentState = state;
	switch (state)
	{
	case CarryArmsState::Stand: case CarryArmsState::MoveDown: case CarryArmsState::MoveUp:
		anim->setAnimation(0, 10, 0.05f);
		break;
	case CarryArmsState::EventMoveUp:
		anim->setAnimation(1, 5, 0.05f);
		break;
	case CarryArmsState::EventMoveUpTwice:
		anim->setAnimation(2, 5, 0.05f);
		break;
	default:break;
	}

	setWidth(anim->getWidth());
	setHeight(anim->getHeight());
}

void CarryArms::Stand(float dt)
{
	timeMoveDown += dt;
	vx = 0;
	vy = 0;
	box->setVx(vx);
	box->setVy(vy);

	if (timeMoveDown > 0.5f)
	{
		timeMoveDown = 0;
		setState(CarryArmsState::MoveDown);
	}
}

void CarryArms::MoveDown(float dt)
{
	if (sideY != SidesCollision::Bottom)
	{
		vx = distance * dt;
		vy = distance * dt;

		addVx(50.0f);
		addVy(50.0f);

		box->setVx(vx);
		box->setVy(vy);

		if (vy > Define::ENEMY_MAX_JUMP_VELOCITY)
		{
			vy = Define::ENEMY_MAX_JUMP_VELOCITY;
			box->setVy(vy);
		}
	}

	if(box->getBottom())
	{
		box->setVy(0);
		box->setVx(0);
		setState(CarryArmsState::EventMoveUp);
	}
}

void CarryArms::MoveUp(float dt)
{
	if (sideY != SidesCollision::Top)
	{
		vx = -distance * dt;
		vy = -distance * dt;
		
		addVx(-50.0f);
		addVy(-50.0f);

		if (vy < Define::ENEMY_MIN_JUMP_VELOCITY)
		{
			vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
	else
		setState(CarryArmsState::Stand);
}

void CarryArms::EventMoveUp(float dt)
{
	timeMoveUp += dt;
	if (timeMoveUp > 0.25f)
	{
		timeMoveUp = 0;
		setState(CarryArmsState::MoveUp);
	}
}

void CarryArms::EventMoveUpTwice(float dt)
{
	timeMoveUp += dt;
	if (timeMoveUp > 0.25f)
	{
		timeMoveUp = 0;
		setState(CarryArmsState::EventMoveUp);
	}
}

void CarryArms::ManageState(float dt)
{
	switch (currentState)
	{
	case CarryArmsState::Stand:
		Stand(dt);
		break;
	case CarryArmsState::MoveDown:
		MoveDown(dt);
		break;
	case CarryArmsState::MoveUp:
		MoveUp(dt);
		break;
	case CarryArmsState::EventMoveUp:
		EventMoveUp(dt);
		break;
	case CarryArmsState::EventMoveUpTwice:
		EventMoveUpTwice(dt);
		break;
	default:break;
	}
}
