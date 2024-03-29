#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "PlayArea.h"
#include <QObject>
#include <list>

class QGraphicsTextItem;
class QtBoats;

class GameState : public QObject
{
  Q_OBJECT

private:
  enum class Turn;
  enum class State;

public:
  explicit GameState(QObject* parent = NULL);
  ~GameState();

  void giveBoatsToPlayers();

  QGraphicsScene* getScene();
  QGraphicsRectItem* getPlayground();
  void showUserMessage(const QString& msg);
  QtBoats* getGameWindow();
  void setPerfectSizeOfArea();

  bool isCurrentPlacingFinished();
  bool isAnyHittable();
  bool consumeMast(PlayArea*);

  QString getPlayer1Name();
  QString getPlayer2Name();

public slots:
  void gotoNextTurn();
  void chooseField(int x, int y, PlayArea *area);
  void currentPlayerWon();

signals:
  void sceneChanged();

private:
  void endOfTurn();
  std::list<uint>* currentBoatsList();
  PlayArea* currentArea();

  Turn currentTurn_;
  State currentState_;
  PlayArea* player1Area;
  PlayArea* player2Area;
  std::list<uint> player1Boats;
  std::list<uint> player2Boats;
  QGraphicsScene* scene;
  QGraphicsScene* sceneWaiting;
  QGraphicsTextItem* waitingMessage;
  uint currentMasts;
  QGraphicsRectItem* playground;
  int size;
  int space;

public: //enums
  enum class Turn { PLAYER_1, WAITING_PLAYER_1, PLAYER_2, WAITING_PLAYER_2 };
  enum class State { BOATS_PLACING, WAR, END_OF_GAME };
private: //enums methods
  static Turn nextTurn(Turn currentTurn);
  static State nextState(State currentState);
};

#endif // GAMESTATE_H
