//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_STATECORRESPONDENCE_H
#define BACHELOR_THESIS_STATECORRESPONDENCE_H

#include <automata/state.h>
#include <patterns/label.h>

#include <vector>

/**
 * Used to encapsulate state correspendence to specific pattern recogniztion
 * classes. Each state can corresponde to many classes.
 */
class StateCorrespondence {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    State state;

    std::vector<Label> labels;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    StateCorrespondence(State state);

    StateCorrespondence(State state, std::vector<Label> labels);

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Adds a label to the correspodence
     */
    void addLabel(Label label);

    const State& getState();

    /*
     * Returns all labels
     */
    const std::vector<Label>& getLabels();

    /*
     * Checks whether a label correspondes to this state
     */
    bool isCorresponding(const Label& label);
};


#endif //BACHELOR_THESIS_STATECORRESPONDENCE_H
