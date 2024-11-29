#include "ScoreTracker.h"

void ScoreTracker::AddPlayer(const std::shared_ptr<Player>& player)
{
    m_players.push_back(player);
}

void ScoreTracker::OnBoardUpdate()
{
    std::cout << "ScoreTracker: Board updated.\n";
    DisplayScores();
}

void ScoreTracker::OnGameOver()
{
    std::cout << "ScoreTracker: Game over. Final scores:\n";
    DisplayScores();
}

void ScoreTracker::DisplayScores() const
{
    for (const auto& player : m_players) {
        std::cout << player->GetName() << ": " << player->GetScore() << "\n";
    }
}