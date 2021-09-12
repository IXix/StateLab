
#include "MachineInterface.h"
#include "CMachineState.h"

CMachineParameter const paraGlobalTest = { pt_byte, "Test", "0 = Store, 1 = Restore", 0, 127, 255, MPF_STATE, 0 };
CMachineParameter const paraTrackTest = { pt_byte, "Test", "0 = Store, 1 = Restore", 0, 127, 255, 0, 0 };

static CMachineParameter const *pParameters[] = {
	&paraGlobalTest,
	&paraTrackTest
};

CMachineAttribute attrTest = {	"Test", 0, 1, 0 };

static CMachineAttribute const *pAttributes[] =
{
	&attrTest
};

#pragma pack(1)

struct gvals
{
	byte gTest;
};

struct tvals
{
	byte tTest;
};

struct avals
{
	int aTest;
};

#pragma pack()

#define COMMAND_STRING "Store\nRestore"

CMachineInfo const MacInfo = 
{
	MT_GENERATOR,   // type
	MI_VERSION,
	MIF_LOAD_DATA_RUNTIME,   // flags
	1,              // min tracks
	1,              // max tracks
	1,              // numGlobalParameters
	1,              // numTrackParameters
	pParameters,    // param list
	1,              // numAtrributes
	pAttributes,    // attribute list
	"StateLab",
	"StateLab",
	"IX",
	COMMAND_STRING
};

class mi;

class mi : public CMachineInterface, public CMachineInterfaceEx
{
public: // CMachineInterface
	mi();
	virtual ~mi();

	virtual void Command(int const i);
	virtual void Init(CMachineDataInput * const pi);
	virtual void Tick();
	virtual void Save(CMachineDataOutput * const po);

public: // CMachineInterfaceEx

	virtual void Load(CMachineDataInput *const pi);

public :

	void LoadData(CMachineDataInput *const pi);
	void Store();
	void Restore();

public:

	gvals gval;
	tvals tval;
	avals aval;

	CMachineState m_state;
};

mi::mi()
	: m_state(this, this)
{
	GlobalVals = &gval;
	TrackVals = &tval;
	AttrVals = (int*) &aval;
}

mi::~mi()
{
}

void mi::Command(int const i)
{
	switch(i)
	{
		case 0 :
			Store();
			break;

		case 1 :
			Restore();
			break;

		default :
			break;
	}
}

void mi::Init(CMachineDataInput * const pi)
{
	pCB->SetMachineInterfaceEx(this);

	LoadData(pi);
}

void mi::Save(CMachineDataOutput * const po)
{
	po->Write("Some saved data.");
}

// pi == NULL means reset to default. NOTE: unlike Init(), this can be called at any time, so it must be synced with the audio thread
void mi::Load(CMachineDataInput *const pi)
{
	pCB->Lock();
	LoadData(pi);
	pCB->Unlock();
}

void mi::LoadData(CMachineDataInput *const pi)
{
	if(pi)
	{
		char str[32] = { 0 };
		pi->ReadString(&str[0], sizeof(str));
	}
}

void mi::Store()
{
	CMachine *pMachine = 0;

	if(!m_state.GotMachine())
		pMachine = pCB->GetMachine("Target");

	m_state.Store(pMachine);
}

void mi::Restore()
{
	m_state.Restore();
}

void mi::Tick()
{
	if(tval.tTest != paraTrackTest.NoValue)
	{
		switch(tval.tTest)
		{
			case 0:
				Store();
				break;

			case 1:
				Restore();
				break;
		}
	}
}

DLL_EXPORTS

