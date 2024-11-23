#include "playermovement.h"
import "movable.h";

PlayerMovement::PlayerMovement(int line, int column) :
	m_line(line), m_column(column), m_playerPosition({ 0,0 }), m_direction(Direction::UP)
{
	m_board.resize(line, std::vector<char>(column, '.')); 
	m_board[m_playerPosition.first][m_playerPosition.second] = 'P';
}



void PlayerMovement::Move(const Direction& direction)
{
    int newLine = m_playerPosition.first;
    int newColumn = m_playerPosition.second;
    if (direction == Direction::UP) { // Compara cu enum-ul Direction
        newLine--;
    }
    else if (direction == Direction::DOWN) {
        newLine++;
    }
    else if (direction == Direction::LEFT) {
        newColumn--;
    }
    else if (direction == Direction::RIGHT) {
        newColumn++;
    }
    else {
        std::cout << "Invalid direction!\n";
        return;
    }

    if (newLine >= 0 && newLine< m_line&& newColumn >= 0 && newColumn < m_column) {
        UpdatePlayerPosition(newLine, newColumn);
    }
    else {
        std::cout << "Cannot move outside the board!\n";
    }

}

void PlayerMovement::ChangeDirection(const Direction& newDirection)
{
    if (newDirection == Direction::UP || newDirection == Direction::DOWN ||
        newDirection == Direction::LEFT || newDirection == Direction::RIGHT) {
        m_direction = newDirection;
        std::cout << "Direction changed to " << static_cast<int>(m_direction) << ".\n"; //static_cast pentru  direcția
    }
    else {
        std::cout << "Invalid direction change!\n";
    }
}

    void PlayerMovement::UpdatePlayerPosition(int newLine, int newColumn)
    {
        m_board[m_playerPosition.first][m_playerPosition.second] = '.'; 
        m_playerPosition = { newLine, newColumn }; 
        m_board[newLine][newColumn] = 'P'; 
        DisplayBoard(); 
    }
  
    void PlayerMovement::DisplayBoard() const
    {
        std::cout << "Game Board:\n";
        for (const auto& row : m_board) {
            for (const auto& cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "Player position: (" << m_playerPosition.first << ", " << m_playerPosition.second << "), facing " << static_cast<int>(m_direction) << ".\n";
    }

    std::ostream& operator<<(std::ostream& os, const PlayerMovement& playerMovement)
    {
        os << "Game Board:\n";
        for (const auto& row : playerMovement.m_board) {
            for (const auto& cell : row) {
                os << cell << ' ';
            }
            os << '\n';
        }
        os << "Player position: (" << playerMovement.m_playerPosition.first << ", " << playerMovement.m_playerPosition.second << "), facing " << static_cast<int>(playerMovement.m_direction) << ".\n";
        return os;
    }
