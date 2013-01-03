#include "GameState.h"
#include "QtBoats.h"
#include <QGraphicsScene>
#include <QImage>

#include <cassert>

GameState::GameState(QObject* parent)
  : QObject(parent),
    currentTurn_(Turn::WAITING_PLAYER_1),
    currentState_(State::WAR)
{
  scene = new QGraphicsScene(parent);
  sceneWaiting = new QGraphicsScene(parent);
  scene->setBackgroundBrush(QBrush(QImage("../resources/water.png")));
  sceneWaiting->setBackgroundBrush(QBrush(QImage("../resources/water.png")));

  player1Area = new PlayArea(10, 10, 0, 0, 400, 400, 20, this);
  player2Area = new PlayArea(10, 10, 450, 0, 400, 400, 20, this);
  scene->addItem(player1Area);
  scene->addItem(player2Area);

  waitingMessage = new QGraphicsTextItem(NULL);
  sceneWaiting->addItem(waitingMessage);

  gotoNextTurn();
}

GameState::~GameState()
{}

QGraphicsScene* GameState::getScene()
{
  if(currentTurn_ == Turn::WAITING_PLAYER_1
     || currentTurn_ == Turn::WAITING_PLAYER_2)
    return sceneWaiting;
  else
    return scene;
}

void GameState::showUserMessage(const QString& msg)
{
  QtBoats* gameWindow = dynamic_cast<QtBoats*>(parent());
  assert(gameWindow != NULL);
  gameWindow->setStatusBarMessage(msg);
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

void GameState::gotoNextTurn()
{
  switch(currentTurn_)
  {
  case Turn::WAITING_PLAYER_1:
    player1Area->setAsAlly();
    player2Area->setAsEnemy();
    break;
  case Turn::WAITING_PLAYER_2:
    player1Area->setAsEnemy();
    player2Area->setAsAlly();
    break;
  case Turn::PLAYER_1:
    waitingMessage->setHtml("<strong style=\"font-size: 24px; color: black;\">Waiting for Player 2</strong>");
    break;
  case Turn::PLAYER_2:
    waitingMessage->setHtml("<strong style=\"font-size: 24px; color: black;\">Waiting for Player 1</strong>");
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

