#include "GameState.h"

GameState::GameState(std::shared_ptr<Board> board)
    : m_board(board)
{
    m_board->AddListener(std::shared_ptr<IGameListener>(this, [](IGameListener*) {}));
    srand(static_cast<unsigned>(time(0)));
}

void GameState::AddPlayer(const std::shared_ptr<Player>& player)
{
    m_players.push_back(player);
}

void GameState::NextPlayer()
{
    m_activePlayerIndex = (m_activePlayerIndex + 1) % m_players.size();
    NotifyOnBoardUpdate();
}

const std::shared_ptr<Player>& GameState::GetActivePlayer() const
{
    return m_players[m_activePlayerIndex];
}

void GameState::OnBoardUpdate()
{
    std::cout << "GameState: Board was updated. Checking game state.\n";
    CheckGameOver();
}

void GameState::OnGameOver()
{
    m_gameActive = false;
    NotifyOnGameOver();
}

bool GameState::IsGameActive() const
{
    return m_gameActive;
}

void GameState::CheckGameOver()
{
    if (m_board->IsFull()) {
        std::cout << "GameState: The board is full. Game over!\n";
        OnGameOver();
    }
}

int GameState::RollDice()
{
    return rand() % 6 + 1;
}
