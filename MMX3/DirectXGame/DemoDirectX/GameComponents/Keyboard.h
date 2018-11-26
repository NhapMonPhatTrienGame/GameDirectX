#pragma once
#include <dinput.h>

class Keyboard
{
public:
	explicit Keyboard(HWND);
	~Keyboard();

	bool init();					//Cài đặt bàn phím
	void getStage();				//Lấy trạng thái bàn phím
	bool isKeyDown(int key);		//Nhận diện phím nhấn
	bool gIsKeyDown(int key);		//Kiểm tra trạng thái phím có đang down
	bool gIsKeyUp(int key);			//Kiểm tra trạng thái phím có đang up
	void killKeyboard();			//Hủy phím

private:

	LPDIRECTINPUT8 Di8;				//Đối tượng nhập xuất
	LPDIRECTINPUTDEVICE8 DiD8;		//Thiết bị nhập xuất
	char key_buffer[256];			//Buffer lưu dữ liệu lấy từ thiết bị

	/*
	 * Display programming
	 * Drawing windows handler
	 */
	HWND _hWnd;
};
