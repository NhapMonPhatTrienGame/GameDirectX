#pragma once

#include <d3d9.h>
#include <vector>
#include "../GameObjects/Entity/Entity.h"

class QuadTree
{
protected:

	QuadTree** Nodes;
	std::vector<Entity*> mListEntity; //danh sach cac phan tu co trong vung va cham (Bound)

	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/
	int getIndex(RECT body) const;

	void split(); //thuc hien chia ra cac node

	bool isContain(Entity* entity) const;
	int mLevel; //tuong ung voi so node
	RECT Bound;

public:

	QuadTree(int level, RECT bound);
	~QuadTree();
	void Clear() const;
	void insertEntity(Entity* entity);

	/*lay danh sach nhung Entity co kha nang xay ra va cham
	tra ve danh sach cac phan tu nam trong vung va cham */
	void getEntitiesCollideAble(std::vector<Entity*>& entitiesOut, Entity* entity);
	void getAllEntities(std::vector<Entity*>& entitiesOut);
	int getTotalEntities() const;

};
