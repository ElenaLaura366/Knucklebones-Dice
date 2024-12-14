#pragma once

#include <string>
#include <iostream>


namespace game
{
	//! Class representing a player.
	class Player
	{
	public:
		//! Player class constructor
		/*!
		*   \param name sets the name of the player.
		*/
		Player(std::string_view name);
		Player(Player&&) = default;

		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&) = delete;

		//! \return Returns the name of the player.
		std::string_view GetName() const;

	private:
		std::string m_name;
	};
}
