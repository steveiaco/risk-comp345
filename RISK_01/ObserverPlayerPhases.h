#include <string>
class ObserverPlayerPhases{
    private:
        std::string description; //description of phase
        int phaseNumber; //number of the phase
        int playerNumber;
        std::string header; //includes player number and phase title
        void setPhaseMessage();

    public:
        ~ObserverPlayerPhases();
        ObserverPlayerPhases();
        std::string getWholeMessage();//includes header, description
        
        void update(int phaseNumber2, int playerNumber);//includes the phase number and the player number
        

};