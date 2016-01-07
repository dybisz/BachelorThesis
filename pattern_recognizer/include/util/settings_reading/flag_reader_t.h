//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_FLAGREADER_H
#define BACHELOR_THESIS_FLAGREADER_H

#include <string>

template<class T>
class FlagReader_T {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // The short flag e.g. '-x'
    std::string shortFlag;
    // The long flag e.g. '--max-iter'
    std::string longFlag;

    // Called when flag has been activated
    void (*activate)(T*, std::string);

    // The optional variable value which is linked with this flag
    T* variableValue;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//


public:
    /*
     * activate is a function that takes no arguments
     * and is called when flag have been provided.
     */
    FlagReader_T(void (*activate)(T*, std::string),
                 std::string shortFlag,
                 std::string longFlag):
            activate(activate),
            shortFlag(shortFlag),
            longFlag(longFlag),
            variableValue(NULL){}

    /*
     * variableValue is the variable which is linked to this flag.
     * activate is a function with 2 arguments:
     *      VarType* variableValue
     *      string argument.
     */
    FlagReader_T(T* variableValue,
                 void (*activate)(T*, std::string),
                 std::string shortFlag,
                 std::string longFlag) :
            FlagReader_T<T>(activate, shortFlag, longFlag){
        this->variableValue = variableValue;
    }

    /*
     * Applies the flag
     */
    void apply(std::string argument){
        activate(variableValue, argument);
    }

};


#endif //BACHELOR_THESIS_FLAGREADER_H
