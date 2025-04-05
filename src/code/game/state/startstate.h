/**
 * @file startstate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief start state definitions files
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _STARTSTATE_H
#define _STARTSTATE_H

#include "gamestate.h"

class StartState : public GameState
{
  public:
    void Enter(Game* game) override;
    void Update(Game* game) override;
    void Exit(Game* game) override;
};

#endif   // _STARTSTATE_H
