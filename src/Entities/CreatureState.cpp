#include "CreatureState.h"


void CreatureState::react(GotHungry const &) {
    cout << "Got Hungry" << endl;
}

void CreatureState::react(BeginEating const &) {
    cout << "Beginning to Eat" << endl;
}

void CreatureState::react(DoneEating const &) {
    cout << "Done Eating" << endl;
}

/* Creature States */

class Idle
: public CreatureState
{
    void entry() override {
        cout << "Entering Idle" << endl;
    }

    void react(GotHungry const & e) override {

    }
    void react(BeginEating const & e) override {}
    void react(DoneEating const & e) override {}
};

class MovingToFood
: public CreatureState
{
    void entry() override {
        cout << "Entering MovingToFood" << endl;
    }

    void react(BeginEating const & e) override {

    }
    void react(GotHungry const & e) override {}
    void react(DoneEating const & e) override {}
};

class Eating
: public CreatureState
{
    void entry() override {
        cout << "Entering Eating" << endl;
    }

    void react(DoneEating const & e) override {

    };
    void react(BeginEating const & e) override {}
    void react(GotHungry const & e) override {}
};

FSM_INITIAL_STATE(CreatureState, Idle);