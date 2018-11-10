#include "dxinput.h"

//Xac dinh nut nhan
#define BUTTON_DOWN(obj, key) (obj.rgbButtons[key] & 0x80)


Input::Input()
{
	m_Input = NULL;
	m_InputDevice = NULL;
	m_Keyboard = NULL;
	m_Mouse = NULL;
}

Input::~Input()
{}

bool Input::CreateInputDevice(HWND hwnd)
{
	HRESULT result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&m_Input),
		NULL
	);
	if (FAILED(result))
		return false;

	result = m_Input->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL);
	if (FAILED(result))
		return false;

	result = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
		return false;

	result = m_Keyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result))
		return false;

	result = m_Keyboard->Acquire();
	if (FAILED(result))
		return false;

	result = m_Input->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	if (FAILED(result))
		return false;

	result = m_Mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
		return false;

	result = m_Mouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result))
		return false;

	result = m_Mouse->Acquire();

	return result >= 0;
}

bool Input::ReadKeyboard()
{
	const HRESULT result = m_Keyboard->GetDeviceState(sizeof(keys), LPVOID(&keys));
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			m_Keyboard->Acquire();
		else
			return false;
	}

	return true;
}

void Input::ReleaseKeyboard()
{
	if (m_Keyboard)
	{
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = NULL;
	}
}

int Input::Key_Down(int keyCode)
{
	return (keys[keyCode] & 0x80);
}

bool Input::ReadMouse()
{
	const HRESULT result = m_Mouse->GetDeviceState(sizeof(m_MouseState), LPVOID(&m_MouseState));
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			m_Mouse->Acquire();
		else
			return false;
	}

	return true;

}

void Input::ReleaseMouse()
{
	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = NULL;
	}
}

int Input::Mouse_Button(int keyCode)
{
	return BUTTON_DOWN(m_MouseState, keyCode);
}

int Input::Mouse_X()
{
	return m_MouseState.lX;
}

int Input::Mouse_Y()
{
	return m_MouseState.lY;
}
