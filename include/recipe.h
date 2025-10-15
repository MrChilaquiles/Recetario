#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <iostream>
#include <string>

#include "list.h"
#include "name.h"
#include "ingredient.h"

class Recipe {
private:
    std::string name;
    std::string category;
    Name author;
    List<Ingredient> ingredients;
    std::string preparationTime;
    std::string instructions;

public:
    Recipe();
    Recipe(const Recipe&);

    std::string getName() const;
    std::string getCategory() const;
    Name getAuthor() const;
    List<Ingredient>& getIngredients() const;
    std::string getPreparationTime() const;
    std::string getInstructions() const;

    void setName(const std::string&);
    void setCategory(const std::string&);
    void setAuthor(const Name&);
    void setIngredients(const List<Ingredient>&);
    void setPreparationTime(const std::string&);
    void setInstructions(const std::string&);
    
    std::string toString() const;

    Recipe& operator = (const Recipe&);

    bool operator == (const Recipe&) const;
    bool operator != (const Recipe&) const;
    bool operator < (const Recipe&) const;
    bool operator <= (const Recipe&) const;
    bool operator > (const Recipe&) const;
    bool operator >= (const Recipe&) const;

    int compareTo(const Recipe&) const;
    static int compare(const Recipe&, const Recipe&);

    static int compareByName(const Recipe&, const Recipe&);
    static int compareByCategory(const Recipe&, const Recipe&);
    static int compareByAuthor(const Recipe&, const Recipe&);
    static int compareByPreparationTime(const Recipe&, const Recipe&);
    static int compareByInstructions(const Recipe&, const Recipe&);

    friend std::ostream& operator << (std::ostream&, Recipe&);
    friend std::istream& operator >> (std::istream&, Recipe&);
};

#endif // __RECIPE_H__