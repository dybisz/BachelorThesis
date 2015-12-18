//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_SYMBOL_H
#define BACHELOR_THESIS_SYMBOL_H

/*
 * Class created to preserve level of abstraction i.e. to prevent
 * using raw integers as symbols. In addition, it provides various
 * methods to manipulate value it contains.
 */
class Symbol {
public:
    // Symbol can be created in various ways:
    // 1) By explicit value declaration.
    // 2) From another symbol.
    Symbol(int val);
    Symbol(const Symbol& s);

    // Auxiliary methods, which definition is selfexplanatory regarding
    // their names.
    int getVal() const;

    // Overloaded operators and their purpose:
    // 1) ==    Compares values of two symbol and if the are the
    //          same returns true, otherwise false is returned.
    //          For user convenience, beside Symbol-to-Symbol
    //          comparision, there is possibility to Symbol-to-Integer check.
    bool operator == (const Symbol &b) const;
    bool operator == (const int &b) const;
private:
    int _val;

};
#endif //BACHELOR_THESIS_SYMBOL_H
