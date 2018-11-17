#include "GameState.h"

GameState::GameState(GamePlayer* gp) : gp(gp) { }

void GameState::update(float dt) { }

void GameState::handlerKeyBoard(std::map<int, bool> keys, float dt) { }

void GameState::onCollision(Entity::SideCollisions side) { }
