//
// Created by dybisz on 26.12.15.
//

#ifndef BACHELOR_THESIS_SETS_DISASSOCIATION_H
#define BACHELOR_THESIS_SETS_DISASSOCIATION_H

#include <language/language.h>
#include <vector>
#include <stdexcept>

using namespace std;

/*
 * Class created for training/testing sets separation.
 */
namespace set_disassociation {

    // Method separates some part of words provided in 'baseSet', and returns it,
    // as parts of new languages. One can specify how many words must be
    // detached from the original set, by providing value, from <0;1> interval
    // for 'testingSetRatio' argument.
    //
    // E.g. we have provided vector of 2 languages, let's say L1 and L2,
    // 100 words each. By calling this method with 'testingSetRatio' equal
    // to 0.3, we will generate two new languages - L1' and L2', 30 words each.
    // These 60 words will be of course stolen from  L1 and L2 equally i.e.
    // 30 taken from each. After operation, 'baseSet' will consists of L1 and L2
    // with 70 words each.
    //
    // WARNING: Returned pointer must be freed.
    vector<Language *> *detachWords(double testingSetRatio,
                                    vector<Language *> *baseSet);
}

#endif //BACHELOR_THESIS_SETS_DISASSOCIATION_H
