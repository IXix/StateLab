#pragma once

#include <vector>

#include "MachineInterface.h"

using namespace std;

class CMachineState : public CMachineDataOutput, public CMachineDataInput
{
public:

	CMachineState(CMachineInterface *pInterface, CMachineInterfaceEx *pInterfaceEx)
		: m_pInterface(pInterface), m_pInterfaceEx(pInterfaceEx), m_pMachine(0), m_gotState(false)
	{
	}

	virtual ~CMachineState() { }

public: // CMachineDataOutput

	virtual void Write(void *pbuf, int const numbytes);

public: // CMachineDataInput

	virtual void Read(void *pbuf, int const numbytes);

public:

	inline bool GotMachine() { return m_pMachine != 0; }
	void Store(CMachine *pMachine);
	void Restore();

private:

	CMachineInterface const *m_pInterface;
	CMachineInterfaceEx const *m_pInterfaceEx;

	bool m_gotState;
	CMachine *m_pMachine;
	vector<char> m_data;
	vector<char>::iterator m_readHead;
};