/**
 * @file gamestate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief game states definiots files
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _GAMESTATE_H
#define _GAMESTATE_H

class Game;

/// @brief GameState interface
class GameState
{
  public:
    virtual ~GameState() {}

    /* State methods */
    virtual void Enter(Game* game) = 0;
    virtual void Update(Game* game) = 0;
    virtual void Exit(Game* game) = 0;
};

#endif   // _GAMESTATE_H
