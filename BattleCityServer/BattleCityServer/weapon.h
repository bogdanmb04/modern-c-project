#pragma once
import <iostream>;
import <cstdlib>;
using std::uint16_t;
using std::uint32_t;

class Weapon
{
public:
	Weapon(uint32_t id, uint32_t bulletWaitTime, uint16_t bulletSpeed, uint32_t userID);

public:
	uint16_t GetSpeed() const;
	uint32_t GetWaitTime() const;
	uint32_t GetID() const;
	uint32_t GetUserID() const;

	void SetSpeed(uint16_t speed);
	void SetWaitTime(uint32_t waitTime);
	void SetID(uint32_t id);
	void SetUserID(uint32_t userID);
private:
	uint32_t m_id; //PK
	uint32_t m_bulletWaitTime;
	uint16_t m_bulletSpeed;
	uint32_t m_userID; //FK
};

