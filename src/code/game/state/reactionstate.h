/**
 * @file reactionstate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief reaction state definitions file
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _REACTIONSTATE_H
#define _REACTIONSTATE_H

#include "gamestate.h"

class ReactionState : public GameState
{
  public:
    void Enter(Game* game) override;
    void Update(Game* game) override;
    void Exit(Game* game) override;
};

#endif   // _REACTIONSTATE_H
