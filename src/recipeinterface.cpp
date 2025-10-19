#include "recipeinterface.h"

using namespace std;

void RecipeInterface::mainMenu() {
    char op;
    do {
        system("clear");

        cout << "=== RECETARIO ===" << endl << endl;

        cout << "[A]gregar receta" << endl;
        cout << "[E]liminar receta" << endl;
        cout << "[B]uscar receta" << endl;
        cout << "[M]ostrar recetas" << endl;
        cout << "[O]rdenar recetas" << endl;
        cout << "[G]uardar al disco" << endl;
        cout << "[L]eer del disco" << endl;
        cout << "[S]alir" << endl << endl;

        cout << "Elija una opcion: ";
        cin >> op;
        cin.ignore();

        op = toupper(op);

        switch(op) {
        case 'A':
            this->addRecipe();
            break;
        
        case 'E':
            this->deleteRecipe();
            break;
        
        case 'B':
            this->searchRecipe();
            break;
        
        case 'M':
            this->showRecipes();
            break;
        
        case 'O':
            this->sortRecipes();
            break;
        
        case 'G':
            this->writeToDisk();
            break;

        case 'L':
            this->readFromDisk();
            break;
        
        case 'S':
            cout << endl << "Adios..." << endl;
            this->enterToContinue();
            break;

        default:
            cout << endl << "Opcion invalida, trata de nuevo..." << endl;
            this->enterToContinue();
            break;
        }
    }
    while(op != 'S');
}

void RecipeInterface::addRecipe() {
    Recipe myRecipe;
    Name myAuthor;
    string myCadena;
    char op;

    system("clear");

    cout << "=== AGREGAR RECETA ===" << endl << endl;

    cout << "Nombre de la receta: ";
    getline(cin, myCadena);
    myRecipe.setName(myCadena);

    cout << "Categoria (Desayuno/Comida/Cena/Navidenio): ";
    getline(cin, myCadena);
    myRecipe.setCategory(myCadena);

    cout << "Apellido(s) del autor: ";
    getline(cin, myCadena);
    myAuthor.setLast(myCadena);

    cout << "Nombre(s) del autor: ";
    getline(cin, myCadena);
    myAuthor.setFirst(myCadena);

    myRecipe.setAuthor(myAuthor);

    cout << "Tiempo de preparacion: ";
    getline(cin, myCadena);
    myRecipe.setPreparationTime(myCadena);

    cout << "Procedimiento: ";
    getline(cin, myCadena);
    myRecipe.setInstructions(myCadena);

    this->myRecipesListRef->insertData(myRecipesListRef->getLastPos(), myRecipe);

    cout << endl;

    do {
        cout << "Desea agregar ingredientes? (S/N): ";
        cin >> op;
        cin.ignore();

        op = toupper(op);
    } while(op != 'S' && op != 'N');

    if(op == 'S') {
        Recipe& addedRecipe = this->myRecipesListRef->retrieve(myRecipesListRef->getLastPos());
        IngredientInterface ingredientMenu(addedRecipe.getIngredients());
        ingredientMenu.start();
    }

    cout << endl << "Receta agregada exitosamente" << endl;
    this->enterToContinue();
}

void RecipeInterface::deleteRecipe() {
    string myCadena;
    Recipe myRecipe;
    int pos;
    char confirm;

    system("clear");

    cout << "=== ELIMINAR RECETA ===" << endl << endl;

    if(this->myRecipesListRef->isEmpty()) {
        cout << "No hay recetas en el recetario" << endl;
        this->enterToContinue();
        return;
    }

    cout << "Nombre de la receta a eliminar: ";
    getline(cin, myCadena);
    myRecipe.setName(myCadena);

    pos = this->myRecipesListRef->findDataL(myRecipe, Recipe::compareByName);

    if(pos != -1) {
        Recipe foundRecipe = this->myRecipesListRef->retrieve(pos);
        
        cout << endl << "Receta encontrada: " << foundRecipe.getName() << endl;
        cout << "Esta seguro de eliminarla? (S/N): ";
        cin >> confirm;
        cin.ignore();

        confirm = toupper(confirm);

        if(confirm == 'S') {
            this->myRecipesListRef->deleteData(pos);
            cout << endl << "Receta eliminada exitosamente" << endl;
        }
        else {
            cout << endl << "Operacion cancelada" << endl;
        }
    }
    else {
        cout << endl << "Receta no encontrada" << endl;
    }

    this->enterToContinue();
}

void RecipeInterface::searchRecipe() {
    char searchType;
    string myCadena;
    int pos = -1;
    Recipe myRecipe;
    char includeIngredients;

    system("clear");

    cout << "=== BUSCAR RECETA ===" << endl << endl;

    if(this->myRecipesListRef->isEmpty()) {
        cout << "No hay recetas en el recetario" << endl;
        this->enterToContinue();
        return;
    }

    do {
        cout << "Buscar por:" << endl;
        cout << "[N]ombre" << endl;
        cout << "[C]ategoria" << endl;
        cout << "Opcion: ";
        cin >> searchType;
        cin.ignore();

        searchType = toupper(searchType);
    } while(searchType != 'N' && searchType != 'C');

    if(searchType == 'N') {
        cout << endl << "Nombre de la receta: ";
        getline(cin, myCadena);
        myRecipe.setName(myCadena);

        pos = this->myRecipesListRef->findDataL(myRecipe, Recipe::compareByName);

        if(pos != -1) {
            Recipe foundRecipe = this->myRecipesListRef->retrieve(pos);

            do {
                cout << endl << "Mostrar ingredientes? (S/N): ";
                cin >> includeIngredients;
                cin.ignore();
                includeIngredients = toupper(includeIngredients);
            } while(includeIngredients != 'S' && includeIngredients != 'N');

            cout << endl << "=== RECETA ENCONTRADA ===" << endl << endl;
            cout << foundRecipe.toString(includeIngredients == 'S') << endl;

            // Opcion para gestionar ingredientes
            char manageIngredients;
            do {
                cout << endl << "Desea gestionar los ingredientes? (S/N): ";
                cin >> manageIngredients;
                cin.ignore();
                manageIngredients = toupper(manageIngredients);
            } while(manageIngredients != 'S' && manageIngredients != 'N');

            if(manageIngredients == 'S') {
                Recipe& recipeRef = this->myRecipesListRef->retrieve(pos);
                IngredientInterface ingredientMenu(recipeRef.getIngredients());
                ingredientMenu.start();
            }
        }
        else {
            cout << endl << "Receta no encontrada" << endl;
        }
    }
    else if(searchType == 'C') {
        cout << endl << "Categoria (Desayuno/Comida/Cena/Navidenio): ";
        getline(cin, myCadena);

        cout << endl << "=== RECETAS EN CATEGORIA: " << myCadena << " ===" << endl << endl;

        bool found = false;
        for(int i = 0; i <= this->myRecipesListRef->getLastPos(); i++) {
            Recipe currentRecipe = this->myRecipesListRef->retrieve(i);
            if(currentRecipe.getCategory() == myCadena) {
                cout << "- " << currentRecipe.getName() 
                     << " (Autor: " << currentRecipe.getAuthor().toString() 
                     << ", Tiempo: " << currentRecipe.getPreparationTime() << ")" << endl;
                found = true;
            }
        }

        if(!found) {
            cout << "No se encontraron recetas en esta categoria" << endl;
        }
    }

    cout << endl;
    this->enterToContinue();
}

void RecipeInterface::showRecipes() {
    char filterOption;
    char includeIngredients;
    string categoryFilter;

    system("clear");

    cout << "=== MOSTRAR RECETAS ===" << endl << endl;

    if(this->myRecipesListRef->isEmpty()) {
        cout << "No hay recetas en el recetario" << endl;
        this->enterToContinue();
        return;
    }

    do {
        cout << "Filtrar por categoria? (S/N): ";
        cin >> filterOption;
        cin.ignore();
        filterOption = toupper(filterOption);
    } while(filterOption != 'S' && filterOption != 'N');

    if(filterOption == 'S') {
        cout << endl << "Categoria (Desayuno/Comida/Cena/Navidenio): ";
        getline(cin, categoryFilter);
    }

    do {
        cout << endl << "Incluir ingredientes en el listado? (S/N): ";
        cin >> includeIngredients;
        cin.ignore();
        includeIngredients = toupper(includeIngredients);
    } while(includeIngredients != 'S' && includeIngredients != 'N');

    system("clear");
    cout << "=== LISTADO DE RECETAS ===" << endl << endl;

    bool showIngredients = (includeIngredients == 'S');
    bool found = false;

    if(filterOption == 'S') {
        cout << "Categoria: " << categoryFilter << endl << endl;
        
        for(int i = 0; i <= this->myRecipesListRef->getLastPos(); i++) {
            Recipe currentRecipe = this->myRecipesListRef->retrieve(i);
            if(currentRecipe.getCategory() == categoryFilter) {
                cout << currentRecipe.toString(showIngredients) << endl;
                cout << "----------------------------------------" << endl << endl;
                found = true;
            }
        }

        if(!found) {
            cout << "No se encontraron recetas en esta categoria" << endl;
        }
    }
    else {
        cout << this->myRecipesListRef->toString(showIngredients) << endl;
    }

    this->enterToContinue();
}

void RecipeInterface::sortRecipes() {
    char sortType;

    system("clear");

    cout << "=== ORDENAR RECETAS ===" << endl << endl;

    if(this->myRecipesListRef->isEmpty()) {
        cout << "No hay recetas en el recetario" << endl;
        this->enterToContinue();
        return;
    }

    do {
        cout << "Ordenar por:" << endl;
        cout << "[N]ombre" << endl;
        cout << "[T]iempo de preparacion" << endl;
        cout << "[A]utor" << endl;
        cout << "[C]ategoria" << endl;
        cout << "Opcion: ";
        cin >> sortType;
        cin.ignore();

        sortType = toupper(sortType);
    } while(sortType != 'N' && sortType != 'T' && sortType != 'A' && sortType != 'C');

    system("clear");

    cout << "Ordenando lista..." << endl << endl;

    if(sortType == 'N') {
        this->myRecipesListRef->sortDataMerge(Recipe::compareByName);
        cout << "Lista ordenada por nombre" << endl << endl;
    }
    else if(sortType == 'T') {
        this->myRecipesListRef->sortDataMerge(Recipe::compareByPreparationTime);
        cout << "Lista ordenada por tiempo de preparacion" << endl << endl;
    }
    else if(sortType == 'A') {
        this->myRecipesListRef->sortDataMerge(Recipe::compareByAuthor);
        cout << "Lista ordenada por autor" << endl << endl;
    }
    else if(sortType == 'C') {
        this->myRecipesListRef->sortDataMerge(Recipe::compareByCategory);
        cout << "Lista ordenada por categoria" << endl << endl;
    }

    cout << this->myRecipesListRef->toString(false) << endl << endl;

    this->enterToContinue();
}

void RecipeInterface::writeToDisk() {
    string myStr;
    ofstream myArchivo;

    system("clear");

    cout << "=== GUARDAR RECETARIO ===" << endl << endl;

    if(this->myRecipesListRef->isEmpty()) {
        cout << "No hay recetas para guardar" << endl;
        this->enterToContinue();
        return;
    }

    cout << "Nombre del archivo: ";
    getline(cin, myStr);

    myArchivo.open(myStr, ios_base::trunc);

    if(myArchivo.is_open()) {
        for(int i = 0; i <= this->myRecipesListRef->getLastPos(); i++) {
            Recipe currentRecipe = this->myRecipesListRef->retrieve(i);
            
            myArchivo << "a" << endl;
            
            myArchivo << currentRecipe.getName() << endl;
            myArchivo << currentRecipe.getCategory() << endl;
            myArchivo << currentRecipe.getAuthor().getLast() << endl;
            myArchivo << currentRecipe.getAuthor().getFirst() << endl;
            myArchivo << currentRecipe.getPreparationTime() << endl;
            myArchivo << currentRecipe.getInstructions() << endl;
            
            List<Ingredient>& ingredients = currentRecipe.getIngredients();
            
            if(!ingredients.isEmpty()) {
                myArchivo << "s" << endl;
                
                for(int j = 0; j <= ingredients.getLastPos(); j++) {
                    Ingredient currentIngredient = ingredients.retrieve(j);
                    
                    myArchivo << "a" << endl;
                    myArchivo << currentIngredient.getName() << endl;
                    myArchivo << currentIngredient.getAmount() << endl;
                    myArchivo << currentIngredient.getUnit() << endl;
                    myArchivo << endl;
                }
                
                myArchivo << "s" << endl;
            }
            else {
                myArchivo << "n" << endl;
            }
            
            myArchivo << endl << endl;
        }
        
        myArchivo.close();

        cout << endl << "Recetario guardado exitosamente en: " << myStr << endl;
    }
    else {
        cout << endl << "Error: No se pudo abrir el archivo para escritura" << endl;
    }

    this->enterToContinue();
}

void RecipeInterface::readFromDisk() {
    string myStr;
    ifstream myArchivo;
    char confirm;

    system("clear");

    cout << "=== CARGAR RECETARIO ===" << endl << endl;

    if(!this->myRecipesListRef->isEmpty()) {
        cout << "ATENCION: Hay recetas en memoria." << endl;
        cout << "Cargar desde archivo reemplazara todas las recetas actuales." << endl;
        cout << "Desea continuar? (S/N): ";
        cin >> confirm;
        cin.ignore();

        confirm = toupper(confirm);

        if(confirm != 'S') {
            cout << endl << "Operacion cancelada" << endl;
            this->enterToContinue();
            return;
        }
    }

    cout << endl << "Nombre del archivo: ";
    getline(cin, myStr);

    myArchivo.open(myStr);

    if(myArchivo.is_open()) {
        this->myRecipesListRef->deleteAll();
        
        string line;
        
        while(getline(myArchivo, line)) {
            if(line == "a") {
                Recipe newRecipe;
                Name author;
                string name, category, last, first, time, instructions;
                
                getline(myArchivo, name);
                getline(myArchivo, category);
                getline(myArchivo, last);
                getline(myArchivo, first);
                getline(myArchivo, time);
                getline(myArchivo, instructions);
                
                newRecipe.setName(name);
                newRecipe.setCategory(category);
                author.setLast(last);
                author.setFirst(first);
                newRecipe.setAuthor(author);
                newRecipe.setPreparationTime(time);
                newRecipe.setInstructions(instructions);
                
                string answer;
                getline(myArchivo, answer);
                
                if(answer == "s" || answer == "S") {
                    string command;
                    
                    while(getline(myArchivo, command)) {
                        if(command == "a") {
                            Ingredient newIngredient;
                            string ingredientName, unit, amountStr;
                            double amount;
                            
                            getline(myArchivo, ingredientName);
                            getline(myArchivo, amountStr);
                            getline(myArchivo, unit);
                            
                            amount = stod(amountStr);
                            
                            newIngredient.setName(ingredientName);
                            newIngredient.setAmount(amount);
                            newIngredient.setUnit(unit);
                            
                            List<Ingredient>& ingredients = newRecipe.getIngredients();
                            ingredients.insertData(ingredients.getLastPos(), newIngredient);
                            
                            getline(myArchivo, line);
                        }
                        else if(command == "s" || command == "S") {
                            break;
                        }
                    }
                }
                
                this->myRecipesListRef->insertData(this->myRecipesListRef->getLastPos(), newRecipe);
                
                getline(myArchivo, line);
                getline(myArchivo, line);
            }
        }
        
        cout << endl << "Recetario cargado exitosamente desde: " << myStr << endl;

        myArchivo.close();
    }
    else {
        cout << endl << "Error: No se pudo abrir el archivo para lectura" << endl;
    }

    cout << endl;
    this->enterToContinue();
}

void RecipeInterface::enterToContinue() {
    cout << endl << "[ENTER] para continuar....";
    getchar();
}

RecipeInterface::RecipeInterface(List<Recipe>& listRef) {
    myRecipesListRef = &listRef;
}

void RecipeInterface::start() {
    this->mainMenu();
}