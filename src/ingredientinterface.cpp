#include "ingredientinterface.h"

using namespace std;


void IngredientInterface::mainMenu() {
    char op;
    do {
        system("clear");

        cout << "*** ** * Menu de ingredientes * ** ***" << endl;

        cout << "[A]nadir ingrediente" << endl;
        cout << "[E]liminar ingrediente" << endl;
        cout << "[C]ambiar ingrediente" << endl;
        cout << "[M]ostrar ingredientes" << endl;
        cout << "[S]alir" << endl << endl;

        cout << "Elija una opcion (A,E,C,M,S): ";
        cin >> op;
        cin.ignore();

        op = toupper(op);

        switch(op) {
        case 'A':
            this->addIngredient();
            break;
        
        case 'E':
            this->deleteIngredient();
            break;
        
        case 'C':
            this->editIngredient();
            break;
        
        case 'M':
            this->showList();
            break;
        
        case 'S':
            cout << "Adios..." << endl;
            this->enterToContinue();
            break;

        default:
            cout << "Opcion invalida, trata de nuevo..." << endl;
            this->enterToContinue();
            break;
        }
    }

    while(op != 'S');
}

void IngredientInterface::addIngredient() {
    Ingredient myIngredient;
    string myCadena;
    float myReal;

    system("clear");

    cout << "Aniadiendo un ingrediente" << endl << endl;

    cout << "Nombre: ";
    getline(cin, myCadena);
    myIngredient.setName(myCadena);

    cout << "Cantidad: ";
    cin >> myReal;
    myIngredient.setAmount(myReal);
    cin.ignore();

    cout << "Unidad: ";
    getline(cin, myCadena);
    myIngredient.setUnit(myCadena);

    this->myIngredientsListRef->insertData(myIngredientsListRef->getLastPos(), myIngredient);

    cout << endl << endl;

    cout << "Ingrediente aniadido a la lista" << endl;
    this->enterToContinue();
}

void IngredientInterface::deleteIngredient() {
    string myCadena;
    Ingredient myIngredient;
    int pos;

    system("clear");

    cout << "Eliminando un ingrediente" << endl << endl;

    cout << "Nombre del ingrediente a eliminar: ";
    getline(cin, myCadena);
    myIngredient.setName(myCadena);

    pos = this->myIngredientsListRef->findDataL(myIngredient);

    if(pos != -1) {
        this->myIngredientsListRef->deleteData(pos);
        cout << endl << "Ingrediente eliminado de la lista" << endl;
    }
    else {
        cout << endl << "Ingrediente no encontrado en la lista" << endl;
    }

    this->enterToContinue();
}

void IngredientInterface::editIngredient() {
    string myCadena;
    float myReal;
    Ingredient myIngredient;
    int pos;

    system("clear");

    cout << "Modificando un ingrediente" << endl << endl;

    cout << "Nombre del ingrediente a modificar: ";
    getline(cin, myCadena);
    myIngredient.setName(myCadena);

    pos = this->myIngredientsListRef->findDataL(myIngredient);

    if(pos != -1) {
        myIngredient = this->myIngredientsListRef->retrieve(pos);

        cout << endl << "Datos actuales:" << endl;
        cout << "Nombre: " << myIngredient.getName() << endl;
        cout << "Cantidad: " << myIngredient.getAmount() << endl;
        cout << "Unidad: " << myIngredient.getUnit() << endl << endl;

        cout << "Nuevos datos:" << endl;

        cout << "Nombre: ";
        getline(cin, myCadena);
        myIngredient.setName(myCadena);

        cout << "Cantidad: ";
        cin >> myReal;
        myIngredient.setAmount(myReal);
        cin.ignore();

        cout << "Unidad: ";
        getline(cin, myCadena);
        myIngredient.setUnit(myCadena);

        this->myIngredientsListRef->retrieve(pos) = myIngredient;

        cout << endl << "Ingrediente modificado" << endl;
    }
    else {
        cout << endl << "Ingrediente no encontrado en la lista" << endl;
    }

    this->enterToContinue();
}

void IngredientInterface::showList() {
    system("clear");

    cout << "Contenido de la lista de ingredientes" << endl << endl;

    cout << myIngredientsListRef->toString() << endl << endl;

    this->enterToContinue();
}

void IngredientInterface::writeToDisk() {
    string myStr;
    ofstream myArchivo;

    system("clear");

    cout << "Guardar ingredientes al disco" << endl << endl;

    cout << "Nombre del archivo para escribir: ";
    getline(cin, myStr);

    myArchivo.open(myStr, ios_base::trunc);

    if(myArchivo.is_open()) {
        myArchivo << *myIngredientsListRef;

        myArchivo.close();

        cout << "Archivo creado exitosamente" << endl;
    }
    else {
        cout << "Lamentablemente no se pudo abrir el archivo para escritura" << endl;
    }

    this->enterToContinue();
}

void IngredientInterface::readFromDisk() {
    string myStr;
    ifstream myArchivo;

    system("clear");

    cout << "Recuperacion de ingredientes desde un archivo" << endl << endl;

    cout << "Nombre del archivo: ";
    getline(cin, myStr);

    myArchivo.open(myStr);

    if(myArchivo.is_open()) {
        myIngredientsListRef->deleteAll();

        myArchivo >> *myIngredientsListRef;
        
        cout << "Lista de ingredientes efectivamente recuperada" << endl;

        myArchivo.close();
    }
    else {
        cout << "No se pudo abrir el archivo para lectura" << endl;
    }

    cout << endl;

    this->enterToContinue();
}

void IngredientInterface::sortData() {
    system("clear");

    cout << "Ordenando lista..." << endl << endl;

    this->myIngredientsListRef->sortDataMerge();

    cout << "Lista ordenada" << endl << endl;

    cout << this->myIngredientsListRef->toString() << endl << endl;

    this->enterToContinue();
}

void IngredientInterface::enterToContinue() {
    cout << "[ENTER] para continuar....";
    getchar();
}

IngredientInterface::IngredientInterface(List<Ingredient>& listRef) {
    myIngredientsListRef = &listRef;
}

void IngredientInterface::start() {
    this->mainMenu();
}
