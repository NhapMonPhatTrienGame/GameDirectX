#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "QuadTree.h"
#include "../GameObjects/MapObjects/Brick.h"

class GameMap
{
	void LoadMap(const char* filePath);

	Tmx::Map                        *pTmxMap;
	std::map<int, Sprite*>          LisTileset;
	Camera                          *pCamera;
	QuadTree                        *pQuadTree;
	std::vector<Brick*>             ListBricks;

public:
	explicit GameMap(const char* filePath);
    void SetCamera(Camera* camera);
    void Update(float dt);
    void Draw();
    Tmx::Map* GetMap() const;
    RECT GetWorldMapBound() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetTileWidth() const;
    int GetTileHeight() const;
    std::map<int, Sprite*> getListTileSet() const;

    bool IsBoundLeft() const;		//Check this camera on the left side with the world map
    bool IsBoundRight() const;	//Check this camera on the right side with the world map
    bool IsBoundTop() const;		//Check this camera on the Top side with the world map
    bool IsBoundBottom() const;	//Check this camera on the bottom side with the world map
    ~GameMap();

    std::vector<Brick*> GetListBrick() const;

    QuadTree* GetQuadTree() const;
};

#endif

