//
// Created by dybisz on 20.12.15.
//
#include <language/interval.h>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Interval::Interval(double a, double b) : _lb(a), _rb(b) { }

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

bool Interval::isInIntervalIE(double c) {
    return (c >= _lb && c < _rb);
}

bool Interval::isInIntervalEI(double c) {
    return (c > _lb && c <= _rb);
}

bool Interval::isInIntervalEE(double c) {
    return (c > _lb && c < _rb);
}

bool Interval::isInIntervalII(double c) {
    return (c >= _lb && c <= _rb);
}

double Interval::getLBound() const{
    return _lb;
}

double Interval::getRBound() const{
    return _rb;
}

string Interval::toString() {
    string out = "|";
    out += to_string(_lb);
    out +=" , ";
    out += to_string(_rb);
    out += "|";
    return out;
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

bool Interval::operator == (const Interval &b) const {
    return (_lb == b.getLBound()) && (_rb == b.getRBound());
}