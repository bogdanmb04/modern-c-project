#pragma once
#include <iostream>
#include <cstdint>
#include <chrono>
using std::uint16_t;
using std::uint32_t;

class Weapon
{
public:
	static constexpr double kDefaultBulletSpeed{ 0.25 };
	static constexpr uint16_t kDefaultBulletWaitTime{ 4000 };

public:
	Weapon(uint32_t id, uint16_t bulletWaitTime, double bulletSpeed, uint32_t userID);
	Weapon(uint32_t userID);
	Weapon(const Weapon&) = default;
	Weapon() = default;
	Weapon(Weapon&&) noexcept = default;
	Weapon& operator = (Weapon&&) noexcept = default;

public:
	double GetBulletSpeed() const;
	uint16_t GetBulletWaitTime() const;
	uint32_t GetID() const;
	uint32_t GetUserID() const;
	std::chrono::milliseconds GetBulletWaitTimeMilliseconds() const;

	void SetBulletSpeed(double speed);
	void SetBulletWaitTime(uint16_t waitTime);
	void SetID(uint32_t id);
	void SetUserID(uint32_t userID);
private:
	uint32_t m_id; //PK
	uint16_t m_bulletWaitTime;
	double m_bulletSpeed;
	uint32_t m_userID; //FK
};

