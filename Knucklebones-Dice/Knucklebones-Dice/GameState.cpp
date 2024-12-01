#include "GameState.h"

GameState::GameState() : m_player1Board(), m_player2Board() {
    srand(static_cast<unsigned>(time(0)));
}

void GameState::AddPlayer(Player& player) {
    m_players.push_back(&player);
}

void GameState::NextPlayer() {
    m_activePlayerIndex = (m_activePlayerIndex + 1) % m_players.size();
}

Player& GameState::GetActivePlayer() {
    return *m_players[m_activePlayerIndex];
}

Player& GameState::GetOpponentPlayer() {
    return *m_players[(m_activePlayerIndex + 1) % m_players.size()];
}

Board& GameState::GetActiveBoard() {
    return (m_activePlayerIndex == 0) ? m_player1Board : m_player2Board;
}

Board& GameState::GetOpponentBoard() {
    return (m_activePlayerIndex == 0) ? m_player2Board : m_player1Board;
}

int GameState::RollDice() {
    return rand() % 6 + 1;
}

bool GameState::IsGameActive() const {
    return m_gameActive;
}

void GameState::NotifyGameStateChange() {
    NotifyOnBoardUpdate();
}

void GameState::CheckForGameOver() 
{
    if (m_player1Board.IsFull() || m_player2Board.IsFull()) {
        m_gameActive = false;
        NotifyOnGameOver();
    }
}
