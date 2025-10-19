#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__

#include <iostream>
#include <string>

class Ingredient {
private:
    std::string name;
    float amount;
    std::string unit;

public:
    Ingredient();
    Ingredient(const Ingredient&);

    std::string getName() const;
    float getAmount() const;
    std::string getUnit() const;

    void setName(const std::string&);
    void setAmount(const float&);
    void setUnit(const std::string&);

    std::string toString() const;
    std::string toString(const bool&) const;

    Ingredient& operator = (const Ingredient&);

    bool operator == (const Ingredient&) const;
    bool operator != (const Ingredient&) const;
    bool operator < (const Ingredient&) const;
    bool operator <= (const Ingredient&) const;
    bool operator > (const Ingredient&) const;
    bool operator >= (const Ingredient&) const;

    int compareTo(const Ingredient&) const;
    static int compare(const Ingredient&, const Ingredient&);

    static int compareByName(const Ingredient&, const Ingredient&);
    static int compareByAmount(const Ingredient&, const Ingredient&);
    static int compareByUnit(const Ingredient&, const Ingredient&);

    friend std::ostream& operator << (std::ostream&, const Ingredient&);
    friend std::istream& operator >> (std::istream&, Ingredient&);
};

#endif // __INGREDIENT_H__