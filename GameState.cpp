#include "GameState.h"
#include "QtBoats.h"
#include <QGraphicsScene>
#include <QImage>

#include <cassert>

GameState::GameState(QObject* parent)
  : QObject(parent),
    currentTurn_(Turn::WAITING_PLAYER_1),
    currentState_(State::BOATS_PLACING),
    currentMasts(0)
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

  giveBoatsToPlayers();

  gotoNextTurn();
}

GameState::~GameState()
{}

void GameState::giveBoatsToPlayers()
{
  player1Boats.push_back(4);
  /*player1Boats.push_back(3);
  player1Boats.push_back(3);
  player1Boats.push_back(2);
  player1Boats.push_back(2);
  player1Boats.push_back(1);
  player1Boats.push_back(1);
*/
  player2Boats.push_back(4);
  /*player2Boats.push_back(3);
  player2Boats.push_back(3);
  player2Boats.push_back(2);
  player2Boats.push_back(2);
  player2Boats.push_back(1);
  player2Boats.push_back(1);*/
}

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

void GameState::chooseField(int x, int y, PlayArea* area)
{
  switch(currentState_)
  {
  case State::BOATS_PLACING:
    area->placeBoat(x, y);
  break;
  case State::WAR:
    area->hitField(x, y);
  break;
  default:
  break;
  }
}

std::list<uint>* GameState::currentBoatsList()
{
  switch(currentTurn_)
  {
  case Turn::PLAYER_1:
  case Turn::WAITING_PLAYER_1:
    return &player1Boats;
    break;
  case Turn::PLAYER_2:
  case Turn::WAITING_PLAYER_2:
    return &player2Boats;
    break;
  default:
    assert(false);
  }
}

bool GameState::consumeMast(PlayArea* area)
{
  assert(currentState_ == State::BOATS_PLACING);
  std::list<uint>* currentList = currentBoatsList();

  if(currentMasts <= 0)
    return false;

  --currentMasts;

  if(currentMasts != 0)
    return true;

  area->resetBoat();
  if(currentList->size() <= 0)
    return true;

  currentMasts = currentList->front();
  currentList->pop_front();
  return true;
}

bool GameState::isCurrentPlacingFinished()
{
  assert(currentState_ == State::BOATS_PLACING);
  std::list<uint>* currentList = currentBoatsList();
  return (currentList->empty() && currentMasts == 0);
}

bool GameState::isAnyHittable()
{
  assert(currentState_ == State::WAR);
  return (player1Area->isHittable() || player2Area->isHittable());
}

void GameState::currentPlayerWon()
{
  assert(currentState_ == State::WAR);
  switch(currentTurn_)
  {
  case Turn::PLAYER_1:
    showUserMessage("PLAYER 1 WON!");
    break;
  case Turn::PLAYER_2:
    showUserMessage("PLAYER 2 WON!");
    break;
  default:
    assert(false);
  }
  currentState_ = nextState(currentState_);
  player1Area->setAsAlly();
  player2Area->setAsAlly();
}

void GameState::endOfTurn()
{
    switch(currentState_)
    {
    case State::BOATS_PLACING:
      if(!isCurrentPlacingFinished() &&
         (currentTurn_ == Turn::PLAYER_1 || currentTurn_ == Turn::PLAYER_2))
      {
        showUserMessage("Placing boats is not finished yet.");
        return;
      }
      switch(currentTurn_)
      {
      case Turn::PLAYER_2:
        player1Area->setHittable(false);
        currentState_ = nextState(currentState_);
        endOfTurn();
        return;
      case Turn::WAITING_PLAYER_1:
      case Turn::WAITING_PLAYER_2:
        currentMasts = currentBoatsList()->front();
        currentBoatsList()->pop_front();
      default:
        break;
      }
      currentTurn_ = nextTurn(currentTurn_);
    break;
    case State::WAR:
      if(isAnyHittable() &&
         (currentTurn_ == Turn::PLAYER_1 || currentTurn_ == Turn::PLAYER_2))
      {
        showUserMessage("You can still make a shot.");
        return;
      }
      currentTurn_ = nextTurn(currentTurn_);
      break;
    default:
      currentTurn_ = nextTurn(currentTurn_);
      break;
    }
}

void GameState::gotoNextTurn()
{
  if(currentState_ == State::END_OF_GAME)
    return;

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

