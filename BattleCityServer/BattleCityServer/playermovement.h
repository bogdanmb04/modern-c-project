export module playermovement;
import std;
export import "movable.h";


class PlayerMovement : public IMovable {
public:
	PlayerMovement(int line, int column);
private:
	void Move(const Direction& direction);
	void ChangeDirection(const Direction& newDirection);
	void DisplayBoard() const ;

	void UpdatePlayerPosition(int newLine, int newColumn);
private:
	int m_line, m_column;
	std::vector<std::vector<char>> m_board;
	std::pair<int, int> m_playerPosition;
	Direction m_direction;
	friend std::ostream& operator<<(std::ostream& os, const PlayerMovement& playerMovement);
	
};