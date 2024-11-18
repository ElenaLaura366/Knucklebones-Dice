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

bool GameState::isGameActive() const {
    return m_gameActive;
}

void GameState::endGame() {
    m_gameActive = false;
}