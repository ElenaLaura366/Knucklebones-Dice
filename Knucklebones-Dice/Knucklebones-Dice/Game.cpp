#include "Game.h"

void Game::MakeMove(int col, int value) {
    if (m_gameActive) {
        m_moves++;
        NotifyOnBoardUpdate();
    }
}

int Game::GetMoves() const {
    return m_moves;
}

void Game::EndGame() {
    m_gameActive = false;
    NotifyOnGameOver();
}

void Game::AddListener(IGameListener* listener) {
    if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
        m_listeners.push_back(listener);
    }
}

void Game::RemoveListener(IGameListener* listener) {
    m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
}

void Game::NotifyOnBoardUpdate() {
    for (auto listener : m_listeners) {
        if (listener) {
            listener->OnBoardUpdate();
        }
    }
}

void Game::NotifyOnGameOver() {
    for (auto listener : m_listeners) {
        if (listener) {
            listener->OnGameOver();
        }
    }
}