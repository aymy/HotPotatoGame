#include "player.h"
#include "potato.h"
#include "umpire.h"
#include "PRNG.h"
#include <iostream>


// global variables
extern int num_of_players;
extern int active_num;
extern PRNG prng;

/*
**********************************************************************
Player constructor
**********************************************************************
*/
Player::Player( unsigned int id, Player::PlayerList &players ){
	this->playerid=id;
	this->active=players;
}

/*
**********************************************************************
RNPlayer constructor
**********************************************************************
*/
RNPlayer::RNPlayer( unsigned int id, Player::PlayerList &players ):Player(id, players){
}


/*
**********************************************************************
LRPlayer constructor
**********************************************************************
*/
LRPlayer::LRPlayer( unsigned int id, Player::PlayerList &players ):Player(id, players){
	this->times_called=0;
}


/*
**********************************************************************
Get player id
**********************************************************************
*/
unsigned int Player::getId(){
	return this->playerid;
}


/*
**********************************************************************
Potato tossed by a RNP player
**********************************************************************
*/
unsigned int RNPlayer::toss( Potato &potato ){
	unsigned int player_now=this->playerid;
	// check if time is over
	bool time_end=potato.countdown();
	if (time_end){
		std::cout<<" -rn-> "<<player_now;
		return player_now;
	}
	else{
		int next; // index of the next player in the list
		std::cout<<" -rn-> "<<player_now;
		// find the first player other than the self
		for (;;){
			next=prng(active_num-1);
			if (this->active[next]->getId() != this->playerid ){
				break;
			}
		}
		// toss potato to the next player
		return this->active[next]->toss(potato);
	}
}


/*
**********************************************************************
Potato tossed by LRPlayer 
**********************************************************************
*/

unsigned int LRPlayer::toss( Potato &potato ){
	unsigned int player_now=this->playerid;
	// check if time is over
	bool time_end=potato.countdown();
	if (time_end){
		std::cout<<" -lr-> "<<player_now;
		return player_now;
	}
	else{
		int next; // playerid desired
		int t; // index number
		std::cout<<" -lr-> "<<player_now;
		// if the LRPlayer has only passed the ball even times, the player should pass the ball to the left
		if (this->times_called==0){
			next=player_now-1;
			for(;;){
				if (next<0){ next+=num_of_players;}
				unsigned int real_id=(unsigned int) next;
				for(t=0; t<num_of_players; t+=1){
					if (this->active[t]!=NULL && this->active[t]->getId()==real_id){ goto L1;}
				}
				next-=1;
			}L1:;
		}
		// if the LRPlayer has passed the ball odd times, the player should pass the ball to the right
		else{
			next=player_now+1;
			for(;;){
				next=next%num_of_players;
				unsigned int real_id=(unsigned int) next;
				for(t=0; t<num_of_players; t+=1){
					if (this->active[t]!=NULL && this->active[t]->getId()==real_id) { goto L2;}
				}
				next+=1;
			}L2:;
		}
		this->times_called=1-this->times_called;
		// toss potato to the next player
		return this->active[t]->toss(potato);
	}
}


