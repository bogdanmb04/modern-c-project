export module bomb;

import <iostream>;
using std::uint16_t;

export class Bomb {

public:
	Bomb(const std::pair<uint16_t, uint16_t>& position);
private:
	std::pair<uint16_t, uint16_t> m_position;
};