export module player;
export import characters;
export import bullet;

import movable;
import <iostream>;
using std::uint16_t;
using std::uint8_t;

 export class Player : public IMovable
{
public:
	void Shoot();
	void Move();
	uint16_t GetScore() const;
	uint8_t GetLives() const;
	void AddScore(uint8_t points) const;
	void GetShoot();

public:
	Player(Player&&) noexcept = default;
	Player& operator =(Player&&) noexcept = default;
private:
	//game::Character m_character;
	uint16_t m_score;
	uint8_t m_lives;
	uint8_t m_direction : 2;
};