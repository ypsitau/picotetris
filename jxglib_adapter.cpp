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
	int GPIO_KEYUP = 0;
	int GPIO_KEYLEFT = 1;
	int GPIO_KEYRIGHT = 2;
	int GPIO_KEYDOWN = 3;
	int GPIO_KEYSTART = 4;
	int GPIO_KEYFIRE = 5;
	uint16_t KEYUP = (1 << GPIO_KEYUP);
	uint16_t KEYLEFT = (1 << GPIO_KEYLEFT);
	uint16_t KEYRIGHT = (1 << GPIO_KEYRIGHT);
	uint16_t KEYDOWN = (1 << GPIO_KEYDOWN);
	uint16_t KEYSTART = (1 << GPIO_KEYSTART);
	uint16_t KEYFIRE = (1 << GPIO_KEYFIRE);
	Tickable::Tick();
	USBHost::GamePad& gamePad = USBHost::GetGamePad();
	uint32_t hat = gamePad.GetReportValue(0x00010039);
	uint32_t stickX = gamePad.GetReportValue(0x00010030);		// X
	uint32_t stickY = gamePad.GetReportValue(0x00010031);		// Y
	uint32_t stickZ = gamePad.GetReportValue(0x00010032);		// Z
	uint32_t stickRz = gamePad.GetReportValue(0x00010035);		// Rz
	uint32_t buttonStart = gamePad.GetReportValue(0x0009000c);	// START 
	uint32_t buttonX = gamePad.GetReportValue(0x00090001);		// X
	uint32_t buttonY = gamePad.GetReportValue(0x00090002);		// Y
	uint32_t buttonA = gamePad.GetReportValue(0x00090003);		// A
	uint32_t buttonB = gamePad.GetReportValue(0x00090004);		// B
	uint16_t rtn = 0;
	if (hat == 0 || stickY < 0x40 || stickZ < 0x40) rtn |= KEYUP;
	if (hat == 2 || stickX > 0xc0 || stickRz > 0xc0) rtn |= KEYRIGHT;
	if (hat == 4 || stickY > 0xc0 || stickZ > 0xc0) rtn |= KEYDOWN;
	if (hat == 6 || stickX < 0x40 || stickRz < 0x40) rtn |= KEYLEFT;
	if (buttonStart) rtn |= KEYSTART;
	if (buttonX || buttonY || buttonA || buttonB) rtn |= KEYUP;
	return rtn;
}
