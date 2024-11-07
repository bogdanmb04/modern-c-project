export module characters;

#include <iostream>
#include <vector>
#include <string>

enum class SkinType
{
	SKIN1,
	SKIN2,
	SKIN3,
	SKIN4,
	SKIN5,
	SKIN6,
	SKIN7,
	SKIN8
};

std::string skinTypeToString(SkinType skin)
{
	switch (skin)
	{
	case SkinType::SKIN1: return "SKIN1";
	case SkinType::SKIN2: return "SKIN2";
	case SkinType::SKIN3: return "SKIN3";
	case SkinType::SKIN4: return "SKIN4";
	case SkinType::SKIN5: return "SKIN5";
	case SkinType::SKIN6: return "SKIN6";
	case SkinType::SKIN7: return "SKIN7";
	case SkinType::SKIN8: return "SKIN8";
	default: return "Unknown";
	}
}

enum class CampSelect
{
	WARRIORS,
	MONSTERS
};

std::string CampToString(CampSelect camp)
{
	switch (camp)
	{
	case CampSelect::WARRIORS:return "WARRIORS";
	case CampSelect::MONSTERS:return "MONSTERS";
	default: return "Unknown";
	}
}

class Character
{
private:
	std::string m_name;
	std::vector <SkinType> skins;
	CampSelect m_camp;

public:
	Character(const std::string& name, CampSelect camp)
		:m_name(name), m_camp(camp) {}

	void displaySkin() const
	{
		std::cout << " Camp: " << CampToString(m_camp) << "\n" << " Available skins" << m_name << std::endl;
		for (const auto& skin : skins)
		{
			std::cout << "  " << skinTypeToString(skin) << std::endl;
		}
	}
	void displayCamp() const
	{
		std::cout << "Camp select: " << CampToString(m_camp) << std::endl;
	}

};