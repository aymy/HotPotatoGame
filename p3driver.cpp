#include "potato.h"
#include "player.h"
#include "umpire.h"
#include "PRNG.h"
#include <iostream>
#include <cstdlib>



// Global variables
int num_of_players;  // number of players in the game
int active_num;   // number of current active players in the match
unsigned int seed_=getpid();  // seed for the random number generator
PRNG prng;  // instance of the random number generator

void usage(char *argv[]){
	std::cerr<<"Usage:"<<argv[0]<<"[ players [ seed ] ] (player is 2-20 inclusive)" <<std::endl;
	exit ( 1 );
}// usage


int main( int argc, char *argv[] ){
	switch( argc ){
		case 1: 
			// number of players is set to 5 by default; seed is set by the process id by default;
			num_of_players = 5;
			prng.seed(seed_);
			break;
		case 2:
			// number of players is set by command line argument; seed is set by the process id by default;
			num_of_players = atoi(argv[1]);
			prng.seed(seed_);
			if (num_of_players > 20 || num_of_players < 2) usage(argv);   // check the type and range of the first argument
			break;
		case 3:
			// number of players and seed are set by the command line arguments;
			seed_=atoi(argv[2]);
			if (seed_ == 0 || seed_<1 ) usage(argv);    // check the type of the second argument
			prng.seed(seed_);
      		    	num_of_players = atoi(argv[1]);
          		if (num_of_players > 20 || num_of_players < 2) usage(argv);    // check the type and range of the first argument
			break;
		default:
			usage ( argv );     // wrong default number of command line arguments
	}
	
	// Creating a list of players alternating between LR player and RN player.
	Player** player_l=new Player* [num_of_players];
	for (int i=0; i<num_of_players; i+=1){
		if (i%2==0){
			player_l[i]=new LRPlayer(i, player_l);
		}
		else {
			player_l[i]=new RNPlayer(i, player_l);
		}
	}
	
	// initialize the active number of players to be the total number of players.
	active_num=num_of_players;
	
	//  creates an umpire
	Umpire u(player_l);
	
	// umpire starts the game
	u.start();
	
	// the game is over
	std::cout<<player_l[0]->getId()<<" wins the Match!"<<std::endl;
	
	//delete memories
	delete player_l[0];
	delete []player_l;
}
