/* 
* SearchOilRig.h
*
* Created: 10/10/2015 2:35:04 PM
* Author: edua_
*/


#ifndef __SEARCHOILRIG_H__
#define __SEARCHOILRIG_H__
#include "../Headers/State.h"

class SearchOilRig: public State
{
//variables
public:
protected:
private:

//functions
public:
	static SearchOilRig* Instance();
	virtual void Enter(Robot* robot);
	virtual void Execute(Robot* robot);
	virtual void Exit(Robot* robot);
	~SearchOilRig();
	SearchOilRig(){};
protected:
private:
	
	SearchOilRig( const SearchOilRig &c );
	SearchOilRig& operator=( const SearchOilRig &c );

}; //SearchOilRig

#endif //__SEARCHOILRIG_H__
