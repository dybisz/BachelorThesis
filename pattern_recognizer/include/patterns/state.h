//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_STATE_H
#define BACHELOR_THESIS_STATE_H

#include <string>

using namespace std;

/*
 * Class created to preserve level of abstraction i.e. to prevent
 * using raw integers as symbols. In addition, it provides various
 * methods to manipulate value it contains.
 */
class State {
public:
    // State can be created in various ways:
    // 1) By explicit value declaration.
    // 2) From another state.
    State(int val);
    State(const State &s);

    // Auxiliary methods, which definition is selfexplanatory regarding
    // their names.
    int getVal() const;
    string toString() const;

    // Overloaded operators and their purpose:
    // 1) ==    Compares values of two states and if the are the
    //          same returns true, otherwise false is returned.
    //          For user convenience, beside State-to-State
    //          comparison, there is possibility to State-to-Integer check.
    bool operator==(const State &b) const;
    bool operator==(const int &b) const;

private:
    int _val;
};

#endif //BACHELOR_THESIS_STATE_H
