#include <string>
class ObserverPlayerPhases{
    private:
        std::string description; //description of phase
        int phaseNumber; //number of the phase
        std::string playerName;
        std::string header; //includes player number and phase title
        void setPhaseMessage();

    public:
        ~ObserverPlayerPhases();
        ObserverPlayerPhases();
        std::string getWholeMessage();//includes header, description
        
        void update(int phaseNumber2, std::string playerName);//includes the phase number and the player number
        

};