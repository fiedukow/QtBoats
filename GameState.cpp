#include "GameState.h"
#include <QGraphicsScene>

GameState::GameState(QObject* parent)
  : QObject(parent),
    currentTurn_(Turn::WAITING_PLAYER_1),
    currentState_(State::WAR)
{
  scene = new QGraphicsScene(parent);
  sceneWaiting = new QGraphicsScene(parent);

  player1Area = new PlayArea(10, 10, 0, 0, 400, 400, 20);
  player2Area = new PlayArea(10, 10, 450, 0, 400, 400, 20);
  scene->addItem(player1Area);
  scene->addItem(player2Area);
  gotoNextTurn();
}

QGraphicsScene* GameState::getScene()
{
  if(currentTurn_ == Turn::WAITING_PLAYER_1
     || currentTurn_ == Turn::WAITING_PLAYER_2)
    return sceneWaiting;
  else
    return scene;
}

GameState::~GameState()
{}


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

void GameState::gotoNextTurn()
{
  switch(currentTurn_)
  {
  case Turn::WAITING_PLAYER_1:
    player1Area->setHittable(false);
    player1Area->setHiddenShips(false);
    player2Area->setHittable(true);
    player2Area->setHiddenShips(true);
    break;
  case Turn::WAITING_PLAYER_2:
    player1Area->setHittable(true);
    player1Area->setHiddenShips(true);
    player2Area->setHittable(false);
    player2Area->setHiddenShips(false);
    break;
  }

  endOfTurn();
  emit sceneChanged();
}



GameState::Turn GameState::nextTurn(Turn currentTurn)
{
  switch(currentTurn)
  {
  case Turn::PLAYER_1:
    return Turn::WAITING_PLAYER_2;
  case Turn::WAITING_PLAYER_1:
    return Turn::PLAYER_1;
  case Turn::PLAYER_2:
    return Turn::WAITING_PLAYER_1;
  case Turn::WAITING_PLAYER_2:
    return Turn::PLAYER_2;
  }
  return Turn::PLAYER_1;
}

//  enum class State { BOATS_PLACING, WAR, END_OF_GAME };
GameState::State GameState::nextState(State currentState)
{
  switch(currentState)
  {
    case State::BOATS_PLACING:
      return State::WAR;
    default:
      return State::END_OF_GAME;
  }
}

