#include <iostream>
#include "PRNG.h"
#include "potato.h"


// global variable
extern PRNG prng;

/*
**********************************************************************
Mashed potato constructor
**********************************************************************
*/

Mashed::Mashed( unsigned int maxTicks ){
	this->maxticks=maxTicks;
	this->ticks=10;
}

/*
**********************************************************************
Mashed potato reset
**********************************************************************
*/

void Mashed::reset(){
	this->ticks=prng( 1, this->maxticks );
	std::cout<<"  Mashed POTATO will go off after "<<this->ticks<<" tosses"<<std::endl;	
}


/*
**********************************************************************
Mashed potato countdown
**********************************************************************
*/
bool Mashed::countdown(){
	this->ticks-=1;
	return this->ticks == 0;
}

/*
**********************************************************************
Fried potato constructor
**********************************************************************
*/
Fried::Fried( unsigned int maxTicks ){
	this->ticks=maxTicks;
}


/*
**********************************************************************
Fried potato reset
**********************************************************************
*/
void Fried::reset(){
	this->ticks=5;
	std::cout<<"  Fried POTATO will go off after "<<this->ticks<<" tosses"<<std::endl;	
}


/*
**********************************************************************
Fried potato countdown
**********************************************************************
*/
bool Fried::countdown(){
	this->ticks-=1;
	return this->ticks==0;
}
