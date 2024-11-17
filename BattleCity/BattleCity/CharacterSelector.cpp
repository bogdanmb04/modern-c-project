module CharacterSelector;

#include <iostream>

CharacterSelector::CharacterSelector() : team1{}, team2{} {}

void CharacterSelector::initializeTeam1() {
    team1 = { "Dragon", "Golem", "MechBot", "Slime" };
}

void CharacterSelector::initializeTeam2() {
    team2 = { "Knight", "Viking", "Pirate", "Samurai" };
}


/*void CharacterSelector::displayTeams() const {
    std::cout << "Team 1: ";
    for (const auto& character : team1) {
        std::cout << character << " ";
    }
    std::cout << "\nTeam 2: ";
    for (const auto& character : team2) {
        std::cout << character << " ";
    }
    std::cout << '\n';*/
}
