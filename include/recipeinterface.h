#ifndef __RECIPEINTERFACE_H__
#define __RECIPEINTERFACE_H__

#include<string>
#include<fstream>
#include<iostream>

#include "list.h"
#include "recipe.h"
#include "ingredient.h"
#include "ingredientinterface.h"

class RecipeInterface {
private:
    List<Recipe>* myRecipesListRef;

    void mainMenu();

    void addRecipe();

    void deleteRecipe();

    void searchRecipe();

    void showRecipes();

    void sortRecipes();

    void writeToDisk();

    void readFromDisk();

    void enterToContinue();

public:
    RecipeInterface(List<Recipe>&);

    void start();
};

#endif // __RECIPEINTERFACE_H__
