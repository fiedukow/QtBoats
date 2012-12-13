#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{


public:
    GameState();
private:
    void endOfTurn();

    Turn currentTurn_;
    State currentState_;

public: //enums
    enum class Turn { PLAYER_1, WAITING_PLAYER_1, PLAYER_2, WAITING_PLAYER_2 };
    enum class State { BOATS_PLACING, WAR, END_OF_GAME };

private: //enums methods
    static Turn nextTurn(Turn currentTurn);
    static State nextState(State currentState);
};

#endif // GAMESTATE_H
