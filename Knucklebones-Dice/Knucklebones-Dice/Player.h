#pragma once

#include <string>
#include <iostream>


namespace game
{
	class Player
	{
	public:
		Player(std::string_view name);
		Player(Player&&) = default;

		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&) = delete;

		std::string_view GetName() const;

	private:
		std::string m_name;
	};
}
