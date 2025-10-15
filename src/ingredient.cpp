#include "ingredient.h"

using namespace std;

Ingredient::Ingredient()
{
    
}

Ingredient::Ingredient(const Ingredient& other) : name(other.name), amount(other.amount), unit(other.unit) { }

std::string Ingredient::getName() const {
    return this->name;
}

float Ingredient::getAmount() const {
    return this->amount;
}

std::string Ingredient::getUnit() const {
    return this->unit;
}

void Ingredient::setName(const std::string& n) {
    this->name = n;
}

void Ingredient::setAmount(const float& a) {
    this->amount = a;
}

void Ingredient::setUnit(const std::string& u) {
    this->unit = u;
}

std::string Ingredient::toString() const {
    string result;

    result = to_string(this->amount);
    result += " | ";
    result += this->unit;
    result += " | ";
    result += this->name;
}

Ingredient& Ingredient::operator = (const Ingredient& other) {
    this->name = other.name;
    this->amount = other.amount;
    this->unit = other.unit;

    return *this;
}

bool Ingredient::operator == (const Ingredient& other) const {
    return this->name == other.name;
}

bool Ingredient::operator != (const Ingredient& other) const {
    return !(*this == other);
}

bool Ingredient::operator < (const Ingredient& other) const {
    return this->name < other.name;
}

bool Ingredient::operator <= (const Ingredient& other) const {
    return *this < other || *this == other;
}

bool Ingredient::operator > (const Ingredient& other) const {
    return !(*this <= other);
}

bool Ingredient::operator >= (const Ingredient& other) const {
    return !(*this < other);
}

int Ingredient::compareTo(const Ingredient& other) const {
    return this->name.compare(other.name);
}

int Ingredient::compare(const Ingredient& a, const Ingredient& b) {
    return a.name.compare(b.name);
}

int Ingredient::compareByName(const Ingredient& a, const Ingredient& b) {
    return a.name.compare(b.name);
}

int Ingredient::compareByAmount(const Ingredient& a, const Ingredient& b) {
    return a.amount * 100 - b.amount * 100;
}

int Ingredient::compareByUnit(const Ingredient& a, const Ingredient& b) {
    return a.unit.compare(b.unit);
}

std::istream& operator >> (std::istream& is, Ingredient& i) {
    string myStr;

    is >> i.name;
    is >> i.amount;
    is >> i.unit;

    return is;
}

std::ostream& operator << (std::ostream& os, Ingredient& i) {
    os << i.name << endl;
    os << i.amount << endl;
    os << i.unit << endl;

    return os;
}