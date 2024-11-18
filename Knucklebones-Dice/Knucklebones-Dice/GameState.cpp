#include "GameState.h"

GameState::GameState() : m_activePlayerIndex(-1), m_gameActive(true) {}

GameState::~GameState() {}

void GameState::addPlayer(const Player& player) {
    m_players.push_back(player);
    if (m_players.size() == 1) {
        m_activePlayerIndex = 0; 
    }
}

void GameState::setActivePlayer(int playerIndex) {
    if (playerIndex >= 0 && playerIndex < m_players.size()) {
        m_activePlayerIndex = playerIndex;
    }
}

Player GameState::getActivePlayer() const {
    return m_players[m_activePlayerIndex];
}

void GameState::nextPlayer() {
    if (!m_players.empty()) {
        m_activePlayerIndex = (m_activePlayerIndex + 1) % m_players.size();
    }
}

bool GameState::isGameActive() const {
    return m_gameActive;
}

void GameState::endGame() {
    m_gameActive = false;
}

bool GameState::checkGameOver(int winningScore) {
    for (const auto& player : m_players) {
        if (player.getScore() >= winningScore) {
            m_gameActive = false;
            return true;
        }
    }
    return false;
}

Player GameState::getWinner() const {
    Player winner = m_players[0];
    for (const auto& player : m_players) {
        if (player.getScore() > winner.getScore()) {
            winner = player;
        }
    }
    return winner;
}
