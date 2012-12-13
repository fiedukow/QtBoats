#include "GameState.h"

GameState::GameState()
{
}

void GameState::endOfTurn()
{
    switch(currentState_)
    {
    case State::BOATS_PLACING:
        if(currentTurn_ == Turn::PLAYER_2)
            currentState_ = nextState(currentState_);
        endOfTurn();
    break;
    case State::WAR:
        currentTurn_ = nextTurn(currentTurn_);
        break;
    default:
        break;
    }
}
