/**
 * @file waitingstate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief waiting state definitions files
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _WAITINGSTATE_H
#define _WAITINGSTATE_H

#include "gamestate.h"

class WaitingState : public GameState
{
  public:
    void Enter(Game* game) override;
    void Update(Game* game) override;
    void Exit(Game* game) override;
};

#endif   // _WAITINGSTATE_H
