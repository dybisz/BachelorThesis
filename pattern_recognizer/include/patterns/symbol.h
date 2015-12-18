//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_SYMBOL_H
#define BACHELOR_THESIS_SYMBOL_H

class Symbol {
public:
    Symbol(int val);
    Symbol(const Symbol& s);

    int getVal() const;

    bool operator == (const Symbol &b) const;
private:
    int _val;

};
#endif //BACHELOR_THESIS_SYMBOL_H
