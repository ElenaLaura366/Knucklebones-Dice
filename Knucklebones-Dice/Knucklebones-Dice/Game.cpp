#include "Game.h"

void Game::MakeMove(int col, int value)
{
    if (m_gameActive) 
    {
        m_moves++;
        NotifyOnBoardUpdate();
    }
}

int Game::GetMoves() const
{
    return m_moves;
}

void Game::EndGame()
{
    m_gameActive = false;
    NotifyOnGameOver();
}

void Game::AddListener(IGameListenerPtr listener)
{
    m_listeners.push_back(listener);
}

void Game::RemoveListener(IGameListener* listener)
{
    for (auto it = m_listeners.begin(); it != m_listeners.end(); )
    {
        if (auto sp = it->lock()) 
        {
            if (sp.get() == listener)
                it = m_listeners.erase(it);
            else
                ++it;
        }
        else {
            it = m_listeners.erase(it);
        }
    }
}

void Game::NotifyOnBoardUpdate()
{
    for (auto& weakPtr : m_listeners) 
    {
        if (auto sp = weakPtr.lock()) 
        {
            sp->OnBoardUpdate();
        }
    }
}

void Game::NotifyOnGameOver()
{
    for (auto& weakPtr : m_listeners) 
    {
        if (auto sp = weakPtr.lock()) 
        {
            sp->OnGameOver();
        }
    }
}