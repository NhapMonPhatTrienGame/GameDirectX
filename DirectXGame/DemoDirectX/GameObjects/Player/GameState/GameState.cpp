#include "GameState.h"

GameState::GameState(GamePlayer* gp) : gp(gp) { }
GameState::GameState() {}
GameState::~GameState() {}

void GameState::Update(float dt) { }

void GameState::HandleKeyboard(std::map<int, bool> keys, float dt) { }

void GameState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) { } 
