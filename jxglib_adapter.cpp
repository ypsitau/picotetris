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
	uint32_t hat = gamePad.Get_HatSwitch();
	float lStickHorz = gamePad.Get_LStickHorz();
	float lStickVert = gamePad.Get_LStickVert();
	float rStickHorz = gamePad.Get_RStickHorz();
	float rStickVert = gamePad.Get_RStickVert();
	uint32_t button1 = gamePad.Get_Button1();
	uint32_t button2 = gamePad.Get_Button2();
	uint32_t button3 = gamePad.Get_Button3();
	uint32_t button4 = gamePad.Get_Button4();
	uint32_t button5 = gamePad.Get_Button5();
	uint32_t button6 = gamePad.Get_Button6();
	uint32_t button7 = gamePad.Get_Button7();
	uint32_t button8 = gamePad.Get_Button8();
	uint32_t button9 = gamePad.Get_Button9();
	uint32_t button10 = gamePad.Get_Button10();
	uint32_t button11 = gamePad.Get_Button11();
	uint32_t button12 = gamePad.Get_Button12();
	uint32_t button13 = gamePad.Get_Button13();
	uint16_t rtn = 0;
	if (hat == 0 || lStickVert < -.5 || rStickVert < -.5) rtn |= KEYUP;
	if (hat == 2 || lStickHorz > .5 || rStickHorz > .5) rtn |= KEYRIGHT;
	if (hat == 4 || lStickVert > .5 || rStickVert > .5) rtn |= KEYDOWN;
	if (hat == 6 || lStickHorz < -.5 || rStickHorz < -.5) rtn |= KEYLEFT;
	if (button5 || button6 || button7 || button8 || button9 || button10 || button11 || button12 || button13) rtn |= KEYSTART;
	if (button1 || button2 || button3 || button4) rtn |= KEYFIRE;
	return rtn;
}
