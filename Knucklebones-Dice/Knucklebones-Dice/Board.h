#pragma once

#include "IGameListener.h"
#include "BasicObservable.h"

#include <vector>
#include <iostream>


namespace game
{
	//! Class representing the game board.
	class Board : public IObservable
	{
	public:
		//!	Board class constructor
		/*!
		*	Initializes a board wit the specified size.
		*	\param rows sets the number of rows the board will have.
		*	If not specified, it will be set on 3.
		*	\param cols sets the number of columns the board will have.
		*	If not specified, it will be set on 3.
		*/
		Board(int rows = Board::DefaultRows, int cols = Board::DefaultCols);
		Board(Board&&) = default;

		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;
		Board& operator=(Board&&) = delete;

		//! Handles the move of a player
		/*!
		*	Takes as input the place of the move and make it, if it is valid.
		*	\param col is the index of the column.
		*	\param value is the value the player rolled.
		*/
		void MakeMove(int col, int value);
		//! Cancels the values in a column
		/*!
		*	Makes all the values in a column equal to 0 if the value is equal to the one specified.
		*   \param col is the index of the column.
		*   \param value is the value to be canceled.
		*/
		void CancelValuesInColumn(int col, int value);
		//! Calculates the total score of the board
		/*!
		*   \return Returns the total score of the board.
		*/
		int CalculateTotalScore() const;

		//! Checks if the board is full
		/*!
		*   \return Returns true if the board is full, false otherwise.
		*/
		bool IsFull() const;
		//! Checks if a column is full
		/*!
		*   \param col is the index of the column.
		*   \return Returns true if the column is full, false otherwise.
		*/
		bool IsColumnFull(int col) const;

		int GetRows() const;
		int GetCols() const;
		const std::vector<int>& operator[](int row) const;

		/*!
		*	Adds a listener to the game's list of listeners.
		*	\param listener is the listener to be added to the list.
		*	\sa game::BasicObservable::AddListener
		*/
		void AddListener(IGameListener* listener) override;
		/*!
		*	Removes a listener from the game's list of listeners.
		*	\param listener is the listener to be removed from the list.
		*	\sa game::BasicObservable::RemoveListener
		*/
		void RemoveListener(IGameListener* listener) override;
		/*!
		*	Notifies all the listeners that the board has been updated.
		*	\sa game::BasicObservable::NotifyOnBoardUpdate
		*/
		void NotifyOnBoardUpdate() override;
		/*!
		*	Notifies all the listeners that the game is over.
		*	\sa game::BasicObservable::NotifyOnGameOver
		*/
		void NotifyOnGameOver() override;

	private:
		int CalculateColumnScore(int col) const;
		void CheckColumn(int col) const;

	public:
		//! Default number of rows
		static constexpr int DefaultRows = 3;
		//! Default number of columns
		static constexpr int DefaultCols = 3;

	private:
		std::vector<std::vector<int>> m_matrix;
		BasicObservable m_observableComponent;
	};
}
