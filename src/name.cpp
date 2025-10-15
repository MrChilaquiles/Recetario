#include "name.h"

using namespace std;

Name::Name() {}

Name::Name(const Name& other) : last(other.last), first(other.first) {}

string Name::getLast() const {
    return this->last;
}

string Name::getFirst() const {
    return this->first;
}

string Name::toString() const {
    return this->last + ", " + this->first;
}

void Name::setLast(const string& l) {
    this->last = l;
}

void Name::setFirst(const string& f) {
    this->first = f;
}

Name& Name::operator =(const Name& other) {
    if (this != &other) {
        this->last = other.last;
        this->first = other.first;
    }
    return *this;
}

bool Name::operator ==(const Name& other) const {
    return this->last == other.last && this->first == other.first;
}

bool Name::operator !=(const Name& other) const {
    return !(*this == other);
}

bool Name::operator <(const Name& other) const {
    if (this->last != other.last) {
        return this->last < other.last;
    }
    return this->first < other.first;
}

bool Name::operator <=(const Name& other) const {
    return *this < other || *this == other;
}

bool Name::operator >(const Name& other) const {
    return !(*this <= other);
}

bool Name::operator >=(const Name& other) const {
    return !(*this < other);
}

int Name::compareTo(const Name& other) const {
    int lastComparison = this->last.compare(other.last);
    if (lastComparison != 0) {
        return lastComparison;
    }
    return this->first.compare(other.first);
}

int Name::compare(const Name& a, const Name& b) {
    return a.compareTo(b);
}

ostream& operator <<(ostream& os, const Name& n) {
    os << n.last << endl << n.first;
    return os;
}

istream& operator >>(istream& is, Name& n) {
    getline(is, n.last);
    getline(is, n.first);
    return is;
}
