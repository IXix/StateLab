#pragma once

#include "MachineInterface.h"

// Copied from Buzé
class CMachineHack
{
public:
	// Jeskola Buzz compatible CMachine header.
	char _placeholder[16] = { 0 };
	const char *_internal_name = ""; // 0x14: polac's VST reads this string, set to 0
	char _placeholder2[52] = { 0 };
	CMachineInterface *interface_machine = nullptr; //scanned for by some plugins
	CMachineInterfaceEx *interface_machine_ex = nullptr; // 0x50: not scanned for?
	char _placeholder3[20] = { 0 };
	char *_internal_global_state = nullptr; // 0x68: copy of machines global state
	char *_internal_track_state = nullptr; // 0x6C: copy of machines track state
	char _placeholder4[120] = { 0 };
	int _internal_seqCommand = 0; // 0xE8: used by mooter, 0 = --, 1 = mute, 2 = thru
	char _placeholder6[17] = { 0 };
	bool hardMuted = false; // 0xFD: true when muted by user, used by mooter
	// End of Buzz compatible header

	CMachineHack()
	{
	}

	virtual ~CMachineHack()
	{
	}
};