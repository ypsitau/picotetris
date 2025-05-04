// jxglib Adapter
#include "jxglib/USBHost.h"
#include "jxglib_adapter.h"

using namespace jxglib;

USBHost::GamePad gamePad;

extern "C" void jxglib_init()
{
	USBHost::Initialize();
}

extern "C" uint16_t jxglib_keycheck()
{
	static const int GPIO_KEYUP = 0;
	static const int GPIO_KEYLEFT = 1;
	static const int GPIO_KEYRIGHT = 2;
	static const int GPIO_KEYDOWN = 3;
	static const int GPIO_KEYSTART = 4;
	static const int GPIO_KEYFIRE = 5;
	static const uint16_t KEYUP = (1 << GPIO_KEYUP);
	static const uint16_t KEYLEFT = (1 << GPIO_KEYLEFT);
	static const uint16_t KEYRIGHT = (1 << GPIO_KEYRIGHT);
	static const uint16_t KEYDOWN = (1 << GPIO_KEYDOWN);
	static const uint16_t KEYSTART = (1 << GPIO_KEYSTART);
	static const uint16_t KEYFIRE = (1 << GPIO_KEYFIRE);
	Tickable::Tick();
	bool buttonA = gamePad.Get_ButtonA();
	bool buttonB = gamePad.Get_ButtonB();
	bool buttonX = gamePad.Get_ButtonX();
	bool buttonY = gamePad.Get_ButtonY();
	bool buttonLB = gamePad.Get_ButtonLB();
	bool buttonRB = gamePad.Get_ButtonRB();
	bool buttonLT = gamePad.Get_ButtonLT();
	bool buttonRT = gamePad.Get_ButtonRT();
	bool buttonLeft = gamePad.Get_ButtonLeft();
	bool buttonRight = gamePad.Get_ButtonRight();
	bool buttonBack = gamePad.Get_ButtonBack();
	bool buttonStart = gamePad.Get_ButtonStart();
	bool buttonHome = gamePad.Get_ButtonHome();
	float leftX = gamePad.Get_LeftX();
	float leftY = gamePad.Get_LeftY();
	float rightX = gamePad.Get_RightX();
	float rightY = gamePad.Get_RightY();
	uint32_t hat = gamePad.Get_HatSwitch();
	uint16_t rtn = 0;
	if (hat == 0 || leftY < -.5 || rightY < -.5) rtn |= KEYUP;
	if (hat == 2 || leftX > .5 || rightX > .5) rtn |= KEYRIGHT;
	if (hat == 4 || leftY > .5 || rightY > .5) rtn |= KEYDOWN;
	if (hat == 6 || leftX < -.5 || rightX < -.5) rtn |= KEYLEFT;
	if (buttonLB || buttonRB || buttonLT || buttonRT || buttonLeft || buttonRight || buttonBack || buttonStart || buttonHome) rtn |= KEYSTART;
	if (buttonA || buttonB || buttonX || buttonY) rtn |= KEYFIRE;
	return rtn;
}
