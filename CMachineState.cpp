#include "CMachineState.h"
#include "CMachineHack.h"

// Dodgy fix for linker errors
void CMachineDataOutput::Write(void *, const int) { }
void CMachineDataInput::Read(void *, const int) { }

void CMachineState::Store(CMachine *pMachine)
{
	if(pMachine)
		m_pMachine = pMachine;


	m_data.clear();
	m_gotState = false;

	if(m_pMachine)
	{
		CMICallbacks *pCB = m_pInterface->pCB;
		CMachineHack *pHack = (CMachineHack*)(m_pMachine);
		m_readHead = m_data.begin();

		pCB->Lock();
		pHack->interface_machine->Save(this);
		pCB->Unlock();

		m_gotState = true;
	}
}

void CMachineState::Restore()
{
	if(m_pMachine && m_gotState)
	{
		CMICallbacks *pCB = m_pInterface->pCB;
		CMachineHack *pHack = (CMachineHack*)(m_pMachine);
		m_readHead = m_data.begin();

		pCB->Lock();
		pHack->interface_machine_ex->Load(this);
		pCB->Unlock();
	}
}

void CMachineState::Read(void *pbuf, int const numbytes)
{
	char *p = (char*) pbuf;
	if(p)
	{
		for(int i = 0; i < numbytes; i++)
		{
			*p = *m_readHead;
			p++;
			m_readHead++;
		}
	}
}

void CMachineState::Write(void *pbuf, int const numbytes)
{
	char *p = (char *) pbuf;
	if(p)
	{
		for(int i = 0; i < numbytes; i++)
		{
			m_data.push_back(p[i]);
		}
	}
}