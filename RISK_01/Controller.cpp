#include "Controller.h"
#include <random>

//NOTE: Waiting on a troops parameter from Player to do the method assignArmies()
//and complete the playerTurn method, as well as organizeStartOfGame method

Controller::Controller(Player** players, int sizePlayers, Map* controllerMap){
    /*No need for deep copy; just take the pointer*/
    allPlayers= new Player*[sizePlayers];
    sizeAllPlayers= sizePlayers;
    for(int i=0;i<sizePlayers;i++){
        allPlayers[i]=players[i];//do shallow copy, so do not delete the array passed before
    }
    std::cout << "Players of controller set"<<std::endl;

    //assign a map. FOR NOW ONLY
    theControllerMap = new Map();
    theControllerMap = controllerMap;

    std::cout << "Map of controller set"<<std::endl;

    turn=0;
    startOfGame=true;
    exchanges=0;
    troopsExchanged=4;


    //set the order of play
    orderOfPlay();
    //assign troops to each player to start the game
    assignArmies();
    //you have to set the pointer "players" to NULL after this
}

Controller::~Controller(){

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
    std::cout<<"Order of play set"<<std::endl;
    //we have the right order for the turns in the game after this method
}

void Controller::assignArmies(){
    //to give each player the right armies at the beginning of the game
    switch(sizeAllPlayers){
        case 2:
            for(int i=0;i<sizeAllPlayers;i++){
                allPlayers[i]->setTroops(40);
            }break;
        case 3:
            for(int i=0;i<sizeAllPlayers;i++){
                allPlayers[i]->setTroops(35);
            }break;
        case 4:
            for(int i=0;i<sizeAllPlayers;i++){
                allPlayers[i]->setTroops(30);
            }break;
        case 5:
            for(int i=0;i<sizeAllPlayers;i++){
                allPlayers[i]->setTroops(25);
            }break;
        case 6:
            for(int i=0;i<sizeAllPlayers;i++){
                allPlayers[i]->setTroops(20);
            }break;
        default:
            for(int i=0;i<sizeAllPlayers;i++){
                allPlayers[i]->setTroops(20);
            } 
    }
    std::cout<<"Armies have been assigned to each player"<<std::endl;
    organizeStartOfGame();
}
void Controller::ownACountry(int indexPlayer, Country* country){
    //owns a country for the player
    //only happens after the country have been attacked/ at the start of game
    allPlayers[indexPlayer]->addCountry(country);
    if(country->getOccupant()!=NULL){//remove the country to the player
        country->getOccupant()->removeCountry(country);
    }
    country->changeOccupant(allPlayers[indexPlayer]);
    //allPlayers[indexPlayer]->decrementTroops(1);
    country->addTroops(1);
}

void Controller::assignCountries(){
    std::cout<<"Turn "<<turn<<std::endl;

    int indexPlayer = turn%sizeAllPlayers;
    if(MapCountries.size()==0)
        return;
    int random = rand()%MapCountries.size();
    int i=0;
    for(Country* country: MapCountries){
        //std::cout<<country->getName()<<std::endl;
        if(random==i){
            ownACountry(indexPlayer, country);
            MapCountries.erase(country);//erases the country so next random value is not going to assign this country
            std::cout<<"Assigned "<<country->getName()<<" to player "<<indexPlayer<<std::endl;
            break;
        }
        i++;
    }
    endOfTurn();//goes to next player
       
}

void Controller::playerTurn(){
    std::cout<<"Turn "<<turn<<std::endl;

    int indexPlayer = turn%sizeAllPlayers;

    std::cout<<"Player "<<indexPlayer<<", it is your turn."<<std::endl;
    

    //assign countries randomly to each player in round robin fashion
    bool countryFound = false;
    bool countryOccupied = false;
    std::string locationPlacedUnit;
    while(!countryFound){
        std::cout<<"Input the location where you would place 1 unit."<<std::endl;
        std::cin>>locationPlacedUnit;

        std::unordered_set<Country*> MapCountries = theControllerMap->getCountryList();
        for(Country* country: MapCountries){
            if(country->getName().compare(locationPlacedUnit)==0){
                /*if(country->getTroops()==0 && country->getOccupant()==NULL){
                    ownACountry(indexPlayer, country);
                    countryFound = true;
                }*/
                if(allPlayers[indexPlayer]->ownsCountry(country)){
                    //if player owns the country he inputted, add 1 unit to the country.
                    country->addTroops(1);
                    allPlayers[indexPlayer]->removeTroops();//removes 1 unit
                    std::cout<<"Troops left for player "<<indexPlayer<<": "<<allPlayers[indexPlayer]->getTroops()<<std::endl;
                    countryFound=true;
                }
                else{
                    countryOccupied=true;
                }
                break;
            }
        }

        if(countryOccupied){
            countryOccupied=false;
            std::cout<<"That country is occupied by someone else. Please enter one of your countries."<<std::endl;
        }
        else if(!countryFound){
            std::cout<<"That country has not been found in the Map. Please enter another"<< 
            "country's name."<<std::endl;
        }
    }

    std::cout<<"You have been assigned one extra unit at "<<locationPlacedUnit<<"."<<std::endl<<std::endl;
    endOfTurn();
}

void Controller::endOfTurn(){
    turn+=1;
}

void Controller::organizeStartOfGame(){
    int i=0;

    MapCountries = theControllerMap->getCountryList();
    //assigns each player a country
    while(i<theControllerMap->getCountryList().size()){
        assignCountries();
        i++;
    }

    std::cout<<"Countries have been assigned"<<std::endl;

    //once all the countries have been assigned, then players select where to
    //put their troops
    while(allPlayers[sizeAllPlayers-1]->getTroops()>0){
        playerTurn();
    }

}