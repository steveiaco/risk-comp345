#include "ObserverPlayerPhases.h"
#include <iostream>


//call this method by indicating which phase the player's turn is at (1 - Reinforcement,
//2 - Attack Phase, 3 - Fortification Phase) and the number attributed to the player
void ObserverPlayerPhases::update(int phaseNumber2, int playerNumber2){
    phaseNumber = phaseNumber2;
    playerNumber = playerNumber2;
    setPhaseMessage();
}

void ObserverPlayerPhases::setPhaseMessage(){
    switch(phaseNumber){
        case 1: header = "Player "+std::to_string(playerNumber)+": Reinforcement Phase";
                description = "Place a number of armies in your countries";break;
        case 2: header = "Player "+std::to_string(playerNumber)+": Attack Phase";
                description = "Declare a series of attacks to try to gain control of additional countries.";break;
        case 3: header = "Player "+std::to_string(playerNumber)+": Fortification Phase";
                description = "Move a number of armies from one of your countries to one of your neighbor countries";break;
        default: header = "Unknown";
                description = "Unknown";
    }

    std::cout<<getWholeMessage()<<std::endl;
}

std::string ObserverPlayerPhases::getWholeMessage(){
    return header+"\n"+description;
}