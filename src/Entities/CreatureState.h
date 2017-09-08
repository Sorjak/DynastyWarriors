#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

#include <tinyfsm.hpp>

using namespace std;

struct GotHungry    : tinyfsm::Event { };
struct DoneEating   : tinyfsm::Event { };
struct BeginEating  : tinyfsm::Event { };

class CreatureState : public tinyfsm::Fsm<CreatureState> {
    void react(tinyfsm::Event const &) { };

    virtual void react(GotHungry    const &);
    virtual void react(DoneEating   const &);
    virtual void react(BeginEating  const &);

    virtual void entry(void) { };  /* entry actions in some states */
    void         exit(void)  { };  /* no exit actions at all */

};