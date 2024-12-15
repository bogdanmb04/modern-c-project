#include "Characters.h"

using namespace game;

std::string Character::CampToString(Character::Camp camp)
{
	switch (camp)
	{
	case Camp::Police:
		return "Police";
	case Camp::Zombies:
		return "Zombies";
	default: 
		return "Unknown";
	}
}

std::string Character::SkinTypeToString(Character::SkinType skin)
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

Character::Character(const std::string& name, Camp camp, SkinType skin)
	: m_name {name}
	, m_camp {camp}
	, m_skin {skin}
{}

Character::SkinType Character::GetSkin() const
{
	return SkinType();
}

Character::Camp Character::GetCamp() const
{
	return Camp();
}

std::string Character::GetName() const
{
	return std::string();
}
