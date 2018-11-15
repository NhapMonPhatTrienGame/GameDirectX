#include "Keyboard.h"



Keyboard::Keyboard(HWND hWnd)
{
	this->Di8 = nullptr;
	this->DiD8 = nullptr;
	this->_hWnd = hWnd;
	ZeroMemory(&this->key_buffer, sizeof(this->key_buffer));
}

//Cài đặt bàn phím
bool Keyboard::Init()
{
	auto hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,					//Tham số mặc định
		IID_IDirectInput8,	
		reinterpret_cast<void**>(&this->Di8),	//Con trỏ nhận dữ liệu trả về
		nullptr);									//Tham số thêm

	if (FAILED(hr))
	{
		return false;
	}
	//Tạo bàn phím GUID_SysKeyboard
	hr = this->Di8->CreateDevice(GUID_SysKeyboard, &this->DiD8, nullptr);
	if (FAILED(hr))
	{
		return false;
	}
	//Dạng dữ liệu được nhận
	hr = this->DiD8->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}
	
	/**
	 * \brief Loai hoat dong
	 * \brief DISCL_FOREGROUND chỉ hoạt động khi của sổ hWnd đang được handle
	 */
	hr = this->DiD8->SetCooperativeLevel(this->_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	if (FAILED(hr))
		return false;

	//Yêu cầu thiết bị
	hr = this->DiD8->Acquire();

	return !(hr < 0);
}

//Lấy trạng thái bàn phím
void Keyboard::GetStage()
{
	auto hr = this->DiD8->GetDeviceState(sizeof(this->key_buffer), (LPVOID)&this->key_buffer);
	//Nếu bàn phím nhả ra yêu cầu nhập lại
	if (FAILED(hr))
	{
		while (this->DiD8->Acquire() == DIERR_INPUTLOST);
	}
}

//Nhân diện phím nhấn
bool Keyboard::IsKeyDown(int key)
{
	//Trả về phím có được nhân hay không
	return key_buffer[key] & 0x80;//0x80 xác định bit đầu tiên
}

//Kiểm tra trạng thái phím có đang down
bool Keyboard::GIsKeyDown(int key)
{
	return (IsKeyDown(key));
}

//Kiểm tra trạng thái phím có đang up
bool Keyboard::GIsKeyUp(int key)
{
	return (!(IsKeyDown(key)));
}

//Hủy phím
void Keyboard::KillKeyboard()
{
	if (DiD8 != nullptr)
	{
		this->DiD8->Unacquire();
		this->DiD8->Release();
		this->DiD8 = nullptr;
	}                                                                                                        
}