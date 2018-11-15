#include "GameState.h"

GameState::GameState(GamePlayer* gp) : gp(gp) { }

void GameState::Update(float dt) { }

void GameState::HandleKeyboard(std::map<int, bool> keys, float dt) { }

void GameState::OnCollision(Entity::SideCollisions side) { }
