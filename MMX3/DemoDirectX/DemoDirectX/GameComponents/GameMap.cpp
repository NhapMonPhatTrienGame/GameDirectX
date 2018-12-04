#include "GameMap.h"
#include "../GameObjects/MapObjects/BrickGold.h"
#include "../GameObjects/MapObjects/BrickNormal.h"
#include "GameCollision.h"
#include "GameGlobal.h"

GameMap::GameMap(const char* filePath)
{
	pTmxMap = new Tmx::Map();
	pTmxMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->getWidth();
	r.bottom = this->getHeight();

	pQuadTree = new QuadTree(1, r);

	pCamera = new Camera(GameGlobal::getWidth(), GameGlobal::getHeight());
	LoadMap(filePath);
}

GameMap::~GameMap()
{
	delete pTmxMap;

	for (auto& mListBrick : ListBricks)
	{
		delete mListBrick;
	}
	ListBricks.clear();

	for (size_t i = 0; i < LisTileset.size(); i++)
	{
		if (LisTileset[i])
			delete LisTileset[i];
	}
	LisTileset.clear();

	delete pQuadTree;
}

void GameMap::LoadMap(const char* filePath)
{
	
	for (size_t i = 0; i < pTmxMap->GetNumTilesets(); i++)
	{
		const auto tileSet = pTmxMap->GetTileset(i);

		auto sprite = new Sprite(tileSet->GetImage()->GetSource().c_str());
		LisTileset.insert(std::pair<int, Sprite*>(i, sprite));
	}

	//Initialize the bricks
#pragma region -BRICK AND COIN LAYER-
	for (size_t i = 0; i < getMap()->GetNumTileLayers(); i++)
	{
		const auto layer = pTmxMap->GetTileLayer(i);

		if (layer->IsVisible())
			continue;

		//Identify the hidden Brick layer to create brick in the game, the brick is not a physic static cannot be destroyed

		if (layer->GetName() == "brick" || layer->GetName() == "coin")
		{
			for (size_t j = 0; j < pTmxMap->GetNumTilesets(); j++)
			{
				const auto tileSet = pTmxMap->GetTileset(j);

				const auto tileWidth = pTmxMap->GetTileWidth();
				const auto tileHeight = pTmxMap->GetTileHeight();

				const auto tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
				auto tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

				for (size_t m = 0; m < layer->GetHeight(); m++)
				{
					for (size_t n = 0; n < layer->GetWidth(); n++)
					{
						if (layer->GetTileTilesetIndex(n, m) != -1)
						{
							const int tileID = layer->GetTileId(n, m);

							const auto y = tileID / tileSetWidth;
							const auto x = tileID - y * tileSetWidth;

							RECT sourceRECT;
							sourceRECT.top = y * tileHeight;
							sourceRECT.bottom = sourceRECT.top + tileHeight;
							sourceRECT.left = x * tileWidth;
							sourceRECT.right = sourceRECT.left + tileWidth;

							RECT bound;
							bound.left = n * tileWidth;
							bound.top = m * tileHeight;
							bound.right = bound.left + tileWidth;
							bound.bottom = bound.top + tileHeight;

							const D3DXVECTOR3 position(n * tileWidth + tileWidth / 2.0f,
							                           m * tileHeight + tileHeight / 2.0f, 0);

							Brick* brick = nullptr;

							if (layer->GetName() == "coin")
							{
								brick = new BrickGold(position);
								brick->setTag(Tag::BrickGoldNormal);
								ListBricks.push_back(brick);
							}
							else
							{
								brick = new BrickNormal(position);
								brick->setTag(Tag::Brick);
								ListBricks.push_back(brick);
							}
							if (brick)
								pQuadTree->insertEntity(brick);
						}
					}
				}
			}
		}
	}

#pragma endregion

#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < pTmxMap->GetNumObjectGroups(); i++)
	{
		const auto objectGroup = pTmxMap->GetObjectGroup(i);

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			//Get the object group rather than layer. The object group contains the body
			const auto object = objectGroup->GetObjects().at(j);

			auto* entity = new Entity();
			entity->setPosition(object->GetX() + object->GetWidth() / 2.0f,
			                    object->GetY() + object->GetHeight() / 2.0f);

			entity->setWidth(object->GetWidth());
			entity->setHeight(object->GetHeight());

			entity->setTag(Tag::Static);

			pQuadTree->insertEntity(entity);
		}
	}
#pragma endregion
}

void GameMap::setCamera(Camera* camera)
{
	pCamera = camera;
}

Tmx::Map* GameMap::getMap() const
{
	return pTmxMap;
}

RECT GameMap::getWorldMapBound() const
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = getWidth();
	bound.bottom = getHeight();

	return bound;
}

int GameMap::getWidth() const
{
	return pTmxMap->GetWidth() * pTmxMap->GetTileWidth();
}

int GameMap::getHeight() const
{
	return pTmxMap->GetHeight() * pTmxMap->GetTileHeight();
}

int GameMap::getTileWidth() const
{
	return pTmxMap->GetTileWidth();
}

int GameMap::getTileHeight() const
{
	return pTmxMap->GetTileHeight();
}

bool GameMap::IsBoundLeft() const
{
	return (pCamera->getBound().left == 0);
}

bool GameMap::IsBoundRight() const
{
	return (pCamera->getBound().right == this->getWidth());
}

bool GameMap::IsBoundTop() const
{
	return (pCamera->getBound().top == 0);
}

bool GameMap::IsBoundBottom() const
{
	return (pCamera->getBound().bottom == this->getHeight());
}

void GameMap::update(float dt)
{
	for (auto& mListBrick : ListBricks)
	{
		mListBrick->update(dt);
	}
}

void GameMap::draw()
{
	const auto trans = D3DXVECTOR2(GameGlobal::getWidth() / 2.0f - pCamera->getPosition().x,
	                               GameGlobal::getHeight() / 2.0f - pCamera->getPosition().y);

#pragma region DRAW TILESET
	for (size_t i = 0; i < pTmxMap->GetNumTileLayers(); i++)
	{
		const auto layer = pTmxMap->GetTileLayer(i);

		if (!layer->IsVisible())
			continue;

		for (size_t j = 0; j < pTmxMap->GetNumTilesets(); j++)
		{
			const auto tileSet = pTmxMap->GetTileset(j);

			RECT sourceRECT;

			const auto tileWidth = pTmxMap->GetTileWidth();
			const auto tileHeight = pTmxMap->GetTileHeight();

			const auto tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			auto tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t m = 0; m < layer->GetHeight(); m++)
			{
				for (size_t n = 0; n < layer->GetWidth(); n++)
				{
					if (layer->GetTileTilesetIndex(n, m) != -1)
					{
						const int tileID = layer->GetTileId(n, m);

						const auto y = tileID / tileSetWidth;
						const auto x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						auto sprite = LisTileset[j];

						const D3DXVECTOR3 position(n * tileWidth + tileWidth / 2.0f, m * tileHeight + tileHeight / 2.0f, 0);

						if (pCamera != nullptr)
						{
							RECT objRECT;
							objRECT.left = position.x - tileWidth / 2.0f;
							objRECT.top = position.y - tileHeight / 2.0f;
							objRECT.right = objRECT.left + tileWidth;
							objRECT.bottom = objRECT.top + tileHeight;

							if(!GameCollision::isCollision(pCamera->getBound(), objRECT))
								continue;
						}

						sprite->setWidth(tileWidth);
						sprite->setHeight(tileHeight);

						sprite->draw(position, sourceRECT, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region DRAW BRICK

	for (auto& mListBrick : ListBricks)
	{
		mListBrick->drawSprite(trans);
	}

#pragma endregion
}

std::map<int, Sprite*> GameMap::getListTileSet() const
{
	return LisTileset;
}

std::vector<Brick*> GameMap::getListBrick() const
{
	return ListBricks;
}

QuadTree* GameMap::getQuadTree() const
{
	return pQuadTree;
}
