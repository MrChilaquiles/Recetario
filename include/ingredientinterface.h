#ifndef __INGREDIENTINTERFACE_H__
#define __INGREDIENTINTERFACE_H__

#include <string>
#include <fstream>
#include <iostream>

#include "list.h"
#include "ingredient.h"

class IngredientInterface {
private:
    List<Ingredient>* myIngredientsListRef;

    void mainMenu();

    void addIngredient();

    void deleteIngredient();

    void editIngredient();

    void showList();

    void writeToDisk();

    void readFromDisk();

    void sortData();

    void enterToContinue();

public:
    IngredientInterface(List<Ingredient>&);

    void start();
};

#endif // __INGREDIENTINTERFACE_H__