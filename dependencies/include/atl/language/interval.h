//
// Created by dybisz on 20.12.15.
//

#ifndef BACHELOR_THESIS_INTERVAL_H
#define BACHELOR_THESIS_INTERVAL_H

#include <string>

using namespace std;

// Class represents intervals of types: <a,b), (a,b>, (a,b) and <a,b>,
// where a and b are real numbers.
class Interval {
public:
    Interval(double a, double b);

    // because creating 4 different classes for all combination of
    // exclusive-inclusive parentheses makes no sense, I have decided
    // to provide 4 distinct methods. Signatures translate as follows:
    // IE   Inclusive - Exclusive   < a ; b )
    // EI   Exclusive - Inclusive   ( a ; b >
    // EE   Exclusive - Exclusive   ( a ; b )
    // II   Inclusive - Inclusive   < a ; b >
    bool isInIntervalIE(double c);
    bool isInIntervalEI(double c);
    bool isInIntervalEE(double c);
    bool isInIntervalII(double c);

    double getLBound() const;
    double getRBound() const;
    string toString();

    // Overloaded operators and their purpose:
    // 4) ==    Checks whether lower and upper bounds of two intervals
    //          are the same.
    bool operator == (const Interval &b) const;

private:
    double _lb;
    double _rb;
};

#endif //BACHELOR_THESIS_INTERVAL_H
