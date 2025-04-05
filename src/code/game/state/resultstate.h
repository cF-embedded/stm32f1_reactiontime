/**
 * @file resultstate.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief result state definition file
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _RESULTSTATE_H
#define _RESULTSTATE_H

#include "gamestate.h"

class ResultState : public GameState
{
  public:
    void Enter(Game* game) override;
    void Update(Game* game) override;
    void Exit(Game* game) override;
};

#endif   // _RESULTSTATE_H
