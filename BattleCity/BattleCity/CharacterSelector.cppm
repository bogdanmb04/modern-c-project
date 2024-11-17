export module CharacterSelector;

#include <vector>
#include <string>

export class CharacterSelector {
private:
    std::vector<std::string> team1; // Echipa 1: Monștri/Roboti
    std::vector<std::string> team2; // Echipa 2: Războinici/Pirați

public:
    CharacterSelector();

    // Metode pentru selectarea echipelor
    //void initializeTeam1(); 
    //void initializeTeam2(); 
    //void displayTeams() const; 
};
