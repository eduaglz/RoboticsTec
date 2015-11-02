// SearchOilRig.h

#ifndef _SEARCHOILRIG_h
#define _SEARCHOILRIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "State.h"

class SearchOilRig : public State
{
	//variables
public:
protected:
private:
	int pos = 0;
	//functions
public:
	virtual void Enter(Robot* robot);
	virtual void Execute(Robot* robot);
	virtual void Exit(Robot* robot);
	~SearchOilRig();
	SearchOilRig() {};
protected:
private:

	SearchOilRig(const SearchOilRig &c);
	SearchOilRig& operator=(const SearchOilRig &c);

}; //SearchOilRig

extern SearchOilRig SearchOilRigInstance;
#endif

