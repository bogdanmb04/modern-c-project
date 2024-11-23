#pragma once
import std;
import <cstdint>;
using std::uint16_t;
using std::uint32_t;

class Weapon
{
public:
	Weapon(uint32_t id, const std::chrono::milliseconds& bulletWaitTime, uint16_t bulletSpeed, std::optional<uint32_t> userID);
	uint16_t GetSpeed() const;
	const std::chrono::milliseconds& GetWaitTime() const;
	uint16_t GetID() const;
	const std::optional<uint32_t>& GetUserID() const;
	void SetSpeed(uint16_t speed);
	void SetWaitTime(const std::chrono::milliseconds time);
	void SetID(uint32_t id);
	void SetUserID(uint32_t userID);
private:
	uint32_t m_id; //PK
	std::chrono::milliseconds m_bulletWaitTime;
	uint16_t m_bulletSpeed;
	std::optional<uint32_t> m_userID; //FK
};

