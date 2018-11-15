#pragma once
#include <dinput.h>

class Keyboard
{
	LPDIRECTINPUT8 Di8;				//Đối tượng nhập xuất
	LPDIRECTINPUTDEVICE8 DiD8;		//Thiết bị nhập xuất
	char key_buffer[256];			//Buffer lưu dữ liệu lấy từ thiết bị

	/**
	 * \brief Display programming
	 * \brief Drawing windows handler
	 */
	HWND _hWnd;

public:
	explicit Keyboard(HWND);
	~Keyboard() = default;

	bool Init();					//Cài đặt bàn phím
	void GetStage();				//Lấy trạng thái bàn phím
	bool IsKeyDown(int key);		//Nhận diện phím nhấn
	bool GIsKeyDown(int key);		//Kiểm tra trạng thái phím có đang down
	bool GIsKeyUp(int key);			//Kiểm tra trạng thái phím có đang up
	void KillKeyboard();			//Hủy phím
};

