#include "Controller.h"
#include <random>

Controller::Controller(Player** players, int sizePlayers){
    /*No need for deep copy; just take the pointer*/
    allPlayers= new Player*[sizePlayers];
    sizeAllPlayers= sizePlayers;
    for(int i=0;i<sizePlayers;i++){
        allPlayers[i]=players[i];//do shallow copy, so do not delete the array passed before
    }

    turn=0;
    startOfGame=true;
    exchanges=0;
    troopsExchanged=4;

    //set the order of play
    orderOfPlay();
    //you have to set the pointer "players" to NULL after this
}

void Controller::orderOfPlay(){

    int random;
    for(int i=0;i<sizeAllPlayers;i++){

        random = (rand()%(sizeAllPlayers-i))+i;
        //swap the values
        //if i is the same value as random, then the player element belongs just where it is
        if(i==random){
            continue;
        }
        //otherwise must do swapping with the other element
        Player* temp = allPlayers[i];
        allPlayers[i]=allPlayers[random];
        allPlayers[random]=temp;

        //delete temp
        delete temp;
        temp=NULL;
    }

    //we have the right order for the turns in the game after this method
}

void Controller::assignArmies(){
    /*switch(sizeAllPlayers){
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        default: 
    }*/

}

void Controller::endOfTurn(){
    turn+=1;
}