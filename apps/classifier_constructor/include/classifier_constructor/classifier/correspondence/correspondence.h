//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_STATECORRESPONDENCE_H
#define BACHELOR_THESIS_STATECORRESPONDENCE_H

#include <automata/state.h>
#include <patterns/label.h>

#include <vector>

/**
 * Used to encapsulate state correspendence to specific pattern recognition
 * classes.
 * Each class can corresponde to many states.
 * Classes are represented as labels
 */
class Correspondence {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    const int LABEL_NOT_FOUND = -1;

    std::vector<Label> labels;
    // Corresponding states of i-th label are stored in i-th element.
    std::vector<std::vector<State>> correspondingStates;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Returns index of label in the label vector or
     * STATE_NOT_FOUND if label was not found.
     */
    int getLabelIndex(const Label &label) const;

    /*
     * Adds new correspondence.
     */
    void addNewCorrespondence(Label label, State state);

    void addStateToExistingCorrespondence(State state, int labelIndex);


public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    Correspondence();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const std::vector<Label>& getLabels() const;

    /*
     * Returns all corresponding states
     */
    const std::vector<State>& getStates(const Label& label) const;


    /*
     * Checks whether a state correspondes to given label
     */
    bool isCorresponding(const Label& label, const State& state) const;

    /*
     * Adds a label to the correspodence.
     */
    void addCorrespondence(Label label, State state);
};


#endif //BACHELOR_THESIS_STATECORRESPONDENCE_H
