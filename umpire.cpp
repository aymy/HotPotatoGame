#include <iostream>
#include "PRNG.h"
#include "potato.h"
#include "player.h"
#include "umpire.h"


// global variables
extern int num_of_players;
extern int active_num;
extern PRNG prng;

/*
**********************************************************************
Constructor for umpire
**********************************************************************
*/
Umpire::Umpire (Player::PlayerList &players ){
	std::cout<<num_of_players<<" players in the match"<<std::endl;
	this->round=1;
	this->potato_type=0;
	this->active_players=players;
}
	


/*
**********************************************************************
Start the game
**********************************************************************
*/
void Umpire::start(){
	// Create two potatoes
	Mashed mp;
	Fried fp(5);
	// there should be num_of_players-1 number of rounds 
	for (int j=1; j<num_of_players; j+=1){ 
		int nextplayer;			
		unsigned int elim_id;
		// should throw mashed potato
		if (this->potato_type==0){
			// reset mashed potato
			mp.reset();
			if (j==1){
				std::cout<<"  Fried POTATO will go off after 5 tosses"<<std::endl;
			}
			std::cout<<"Set "<<this->round<<": U m";
			nextplayer=prng(active_num-1);
			Player* selected=active_players[nextplayer];
			elim_id=selected->toss(mp);
		}
		else{
			fp.reset();
			std::cout<<"Set "<<this->round<<": U f";
			nextplayer=prng(active_num-1);
			Player* selected=active_players[nextplayer];
			elim_id=selected->toss(fp);
		}
		std::cout<<" is eliminated"<<std::endl;
		int elim;   //the position of the player need to be eliminated
		int move;   //the position in the array that the rest of the players needed to be moved one 
			    //position forward

		// find the player needed to be deleted
		Player* need_del=this->active_players[0]; 
		for (elim=0; elim<active_num; elim+=1){
			if (this->active_players[elim]->getId()==elim_id){
				need_del=this->active_players[elim];
				break;
			}
		}
		// move one position forward for the rest of active players
		for (move=elim; move<active_num-1; move+=1){
			this->active_players[move]=this->active_players[move+1];
		}
		// delete the eliminated player
		delete(need_del);
		// make the last position pointing to NULL
		this->active_players[move]=NULL;
		// change the potato type
		this->potato_type=1-this->potato_type;
		// add round number by 1
		this->round+=1;
		// subtract active_num by 1
		active_num-=1;
	}
}
