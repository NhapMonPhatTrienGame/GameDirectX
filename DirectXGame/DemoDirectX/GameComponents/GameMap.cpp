#include "GameMap.h"
#include "../GameObjects/MapObjects/BrickGold.h"
#include "../GameObjects/MapObjects/BrickNormal.h"
#include "GameCollision.h"
#include "GameGlobal.h"

GameMap::GameMap(const char* filePath)
{
	pCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
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
	pTmxMap = new Tmx::Map();
	pTmxMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	pQuadTree = new QuadTree(1, r);

	for (size_t i = 0; i < pTmxMap->GetNumTilesets(); i++)
	{
		const auto tileSet = pTmxMap->GetTileset(i);

		auto sprite = new Sprite(tileSet->GetImage()->GetSource().c_str());
		LisTileset.insert(std::pair<int, Sprite*>(i, sprite));
	}

	//Initialize the bricks
#pragma region -BRICK AND COIN LAYER-
	for (size_t i = 0; i < GetMap()->GetNumTileLayers(); i++)
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

							Brick *brick = nullptr;

							if (layer->GetName() == "coin")
							{
								brick = new BrickGold(position);
								brick->Tag = Entity::EntityTypes::BrickGoldNormal;
								ListBricks.push_back(brick);
							}
							else
							{
								brick = new BrickNormal(position);
								brick->Tag = Entity::EntityTypes::Brick;
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

			auto*entity = new Entity();
			entity->setPosition(object->GetX() + object->GetWidth() / 2.0f,
				object->GetY() + object->GetHeight() / 2.0f);

			entity->setWidth(object->GetWidth());
			entity->setHeight(object->GetHeight());

			entity->Tag = Entity::EntityTypes::Static;

			pQuadTree->insertEntity(entity);
		}
	}
#pragma endregion
}

void GameMap::SetCamera(Camera* camera)
{
	pCamera = camera;
}

Tmx::Map* GameMap::GetMap() const
{
	return pTmxMap;
}

RECT GameMap::GetWorldMapBound() const
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = GetWidth();
	bound.bottom = GetHeight();

	return bound;
}

int GameMap::GetWidth() const
{
	return pTmxMap->GetWidth() * pTmxMap->GetTileWidth();
}

int GameMap::GetHeight() const
{
	return pTmxMap->GetHeight() * pTmxMap->GetTileHeight();
}

int GameMap::GetTileWidth() const
{
	return pTmxMap->GetTileWidth();
}

int GameMap::GetTileHeight() const
{
	return pTmxMap->GetTileHeight();
}

bool GameMap::IsBoundLeft() const
{
	return (pCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight() const
{
	return (pCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop() const
{
	return (pCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom() const
{
	return (pCamera->GetBound().bottom == this->GetHeight());
}

void GameMap::Update(float dt)
{
	for (auto& mListBrick : ListBricks)
	{
		mListBrick->Update(dt);
	}
}

void GameMap::Draw()
{
	const auto trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2.0f - pCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2.0f - pCamera->GetPosition().y);

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

							if (!GameCollision::RectAndRect(pCamera->GetBound(), objRECT).IsCollided)
								continue;
						}

						sprite->SetWidth(tileWidth);
						sprite->SetHeight(tileHeight);

						sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region DRAW BRICK

	for (auto& mListBrick : ListBricks)
	{
		mListBrick->Draw(trans);
	}

#pragma endregion
}

std::map<int, Sprite*> GameMap::getListTileSet() const
{
	return LisTileset;
}

std::vector<Brick*> GameMap::GetListBrick() const
{
	return ListBricks;
}

QuadTree * GameMap::GetQuadTree() const
{
	return pQuadTree;
}
