//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_LABEL_H
#define BACHELOR_THESIS_LABEL_H


class Label {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    int value;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    Label(int value);

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    int getValue() const;

    bool operator==(const Label& label) const;

};


#endif //BACHELOR_THESIS_LABEL_H