// jxglib Adapter
#include "jxglib/USBHost.h"
#include "jxglib_adapter.h"

using namespace jxglib;

extern "C" void jxglib_init()
{
	GPIO16.set_function_UART0_TX();
	GPIO17.set_function_UART0_RX();
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
	USBHost::GamePad gamePad(USBHost::FindGenericHID(0x00010005));
	uint32_t hat = gamePad.Get_HatSwitch();
	uint32_t lStickHorz = gamePad.Get_LStickHorz();
	uint32_t lStickVert = gamePad.Get_LStickVert();
	uint32_t rStickHorz = gamePad.Get_RStickHorz();
	uint32_t rStickVert = gamePad.Get_RStickVert();
	uint32_t buttonStart = gamePad.Get_ButtonSTART(); 
	uint32_t buttonX = gamePad.Get_ButtonX();
	uint32_t buttonY = gamePad.Get_ButtonY();
	uint32_t buttonA = gamePad.Get_ButtonA();
	uint32_t buttonB = gamePad.Get_ButtonB();
	uint16_t rtn = 0;
	if (hat == 0 || lStickVert < 0x40 || rStickVert < 0x40) rtn |= KEYUP;
	if (hat == 2 || lStickHorz > 0xc0 || rStickHorz > 0xc0) rtn |= KEYRIGHT;
	if (hat == 4 || lStickVert > 0xc0 || rStickVert > 0xc0) rtn |= KEYDOWN;
	if (hat == 6 || lStickHorz < 0x40 || rStickHorz < 0x40) rtn |= KEYLEFT;
	if (buttonStart) rtn |= KEYSTART;
	if (buttonX || buttonY || buttonA || buttonB) rtn |= KEYUP;
	return rtn;
}
