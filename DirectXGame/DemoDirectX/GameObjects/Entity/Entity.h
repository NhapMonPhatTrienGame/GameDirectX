#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Entity
{
protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void onSetPosition(D3DXVECTOR3 pos);

	//vi tri tam position x va y
	float x, y;

	//phan toc vx, vy
	float vx, vy;

	//size cua entity
	float width, height;

public:
	virtual ~Entity() = default;

	Entity();

    enum SideCollisions
    {
        Left, //0
        Right, //1
        Top, //2
        Bottom, //3
        TopLeft, //4
        TopRight, //5
        BottomLeft, //6
        BottomRight, //7
        Unknown
    };

    struct CollisionReturn
    {
        bool IsCollided;
        RECT RegionCollision;
    };

    enum EntityTypes
    {
        None,
    	Brick,
    	Enemy,
    	Mario,
    	Static,
    	BrickGoldNormal,
    	BrickGoldBeEaten
    };

	enum TheKindOfEntity
	{
		
	};

	//To confirm type of Entity
    EntityTypes Tag;

    virtual RECT getBound();

	virtual D3DXVECTOR3 getPosition();
    virtual void setPosition(float x, float y);
    virtual void setPosition(D3DXVECTOR2 pos);
    virtual void setPosition(D3DXVECTOR3 pos);

	virtual void addPosition(float x, float y);
	virtual void addPosition(D3DXVECTOR2 pos);
    virtual void addPosition(D3DXVECTOR3 pos);

    virtual void setWidth(int width);
    virtual int getWidth();

    virtual void setHeight(int height);
    virtual int getHeight();

    virtual float getVx();
    virtual void setVx(float vx);
    virtual void addVx(float vx);

    virtual float getVy();
    virtual void setVy(float vy);
    virtual void addVy(float vy);

    virtual void Update(float dt);

    //Control collision
	//When entity collide, this function will be called
    virtual void OnCollision(CollisionReturn data, SideCollisions side);

};