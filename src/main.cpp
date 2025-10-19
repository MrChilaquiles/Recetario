#include <iostream>
#include "recipeinterface.h"

using namespace std;

int main() {
    List<Recipe> myRecipeList;
    
    RecipeInterface myInterface(myRecipeList);
    
    myInterface.start();
    
    return 0;
}
