#pragma once

import <iostream>;
import <vector>;
import <string>;

namespace game
{
	class Character
	{

	public:
		//TODO add skin names and actual skins
		enum class SkinType : uint8_t
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

		enum class Camp : uint8_t
		{
			WARRIORS,
			MONSTERS
		};

		std::string CampToString(Camp camp);

		std::string SkinTypeToString(SkinType skin);

	public:
		Character(const std::string& name, Camp camp, SkinType skin);
		SkinType GetSkin() const;
		Camp GetCamp() const;
		std::string GetName() const;

	private:
		std::string m_name;
		SkinType m_skin : 3;
		Camp m_camp : 1;
	};
}