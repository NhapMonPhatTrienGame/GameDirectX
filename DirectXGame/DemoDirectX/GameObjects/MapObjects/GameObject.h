#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <d3d9.h>
#include <d3dx9.h>

//vien gach
class GameObject
{
public:
    ~GameObject() = default;
    GameObject() = default;

	static void Update(float dt);
	static void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(),
		D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(),
		D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void Draw(D3DXVECTOR2 transform) const;
};      

#endif
