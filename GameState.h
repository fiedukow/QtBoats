#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "PlayArea.h"
#include <QObject>

class GameState : public QObject
{
  Q_OBJECT

private:
  enum class Turn;
  enum class State;

public:
  explicit GameState(QObject* parent = NULL);
  ~GameState();

  QGraphicsScene* getScene();

public slots:
  void gotoNextTurn();

signals:
  void sceneChanged();

private:
  void endOfTurn();

  Turn currentTurn_;
  State currentState_;
  PlayArea* player1Area;
  PlayArea* player2Area;
  QGraphicsScene* scene;
  QGraphicsScene* sceneWaiting;

public: //enums
  enum class Turn { PLAYER_1, WAITING_PLAYER_1, PLAYER_2, WAITING_PLAYER_2 };
  enum class State { BOATS_PLACING, WAR, END_OF_GAME };
private: //enums methods
  static Turn nextTurn(Turn currentTurn);
  static State nextState(State currentState);
};

#endif // GAMESTATE_H
