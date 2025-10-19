#include "recipe.h"

using namespace std;

Recipe::Recipe() { }

Recipe::Recipe(const Recipe& other) : name(other.name), category(other.category), author(other.author), ingredients(other.ingredients), preparationTime(other.preparationTime), instructions(other.instructions) { }

string Recipe::getName() const {
    return this->name;
}

string Recipe::getCategory() const {
    return this->category;
}

Name Recipe::getAuthor() const {
    return this->author;
}

List<Ingredient>& Recipe::getIngredients() {
    return this->ingredients;
}

string Recipe::getPreparationTime() const {
    return this->preparationTime;
}

string Recipe::getInstructions() const {
    return this->instructions;
}

void Recipe::setName(const string& n) {
    this->name = n;
}

void Recipe::setCategory(const string& c) {
    this->category = c;
}

void Recipe::setAuthor(const Name& a) {
    this->author = a;
}

void Recipe::setIngredients(const List<Ingredient>& l) {
    this->ingredients = l;
}

void Recipe::setPreparationTime(const string& pt) {
    this->preparationTime = pt;
}

void Recipe::setInstructions(const string& i) {
    this->instructions = i;
}

string Recipe::toString() const {
    string result;

    result += this->name;
    result += " | ";
    result += this->category;
    result += " | ";
    result += this->author.toString();
    result += " | ";
    result += this->preparationTime;
    result += " | ";
    result += this->instructions;

    return result;
}

string Recipe::toString(const bool& s) const {
    string result;

    result += this->name;
    result += " | ";
    result += this->category;
    result += " | ";
    result += this->author.toString();
    result += " | ";
    result += this->preparationTime;
    result += " | ";
    result += this->instructions;

    if(s) {
        result += "\n**********************************************************\n";
        result += this->ingredients.toString();
        result += "\n**********************************************************\n";
    }

    return result;
}

Recipe& Recipe::operator = (const Recipe& other) {
    this->name = other.name;
    this->category = other.category;
    this->author = other.author;
    this->ingredients = other.ingredients;
    this->preparationTime = other.preparationTime;
    this->instructions = other.instructions;

    return *this;
}

bool Recipe::operator == (const Recipe& other) const {
    return this->name == other.name;
}

bool Recipe::operator != (const Recipe& other) const {
    return !(*this == other);
}

bool Recipe::operator < (const Recipe& other) const {
    return this->name < other.name;
}

bool Recipe::operator <= (const Recipe& other) const {
    return *this < other || *this == other;
}

bool Recipe::operator > (const Recipe& other) const {
    return !(*this <= other);
}

bool Recipe::operator >= (const Recipe& other) const {
    return !(*this < other);
}

int Recipe::compareTo(const Recipe& other) const {
    return this->name.compare(other.name);
}

int Recipe::compare(const Recipe& a, const Recipe& b) {
    return a.name.compare(b.name);
}

int Recipe::compareByName(const Recipe& a, const Recipe& b) {
    return a.name.compare(b.name);
}

int Recipe::compareByCategory(const Recipe& a, const Recipe& b) {
    return a.category.compare(b.category);
}

int Recipe::compareByAuthor(const Recipe& a, const Recipe& b) {
    return a.author.compareTo(b.author);
}

int Recipe::compareByPreparationTime(const Recipe& a, const Recipe& b) {
    return a.preparationTime.compare(b.preparationTime);
}

int Recipe::compareByInstructions(const Recipe& a, const Recipe& b) {
    return a.instructions.compare(b.instructions);
}

istream& operator >> (istream& is, Recipe& s) {
    string myStr;

    is >> s.name;
    is >> s.category;
    is >> s.author;
    is >> s.ingredients;
    is >> s.preparationTime;
    is >> s.instructions;

    return is;
}

ostream& operator << (ostream& os, const Recipe& s) {
    os << s.name << endl;
    os << s.category << endl;
    os << s.author << endl;
    os << s.ingredients << endl;
    os << s.preparationTime << endl;
    os << s.instructions << endl;

    return os;
}
