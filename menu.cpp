#include "menu.h"

using namespace std;

Menu::Menu(List<Persona>& lista){
    mainInterface(lista);
}

void Menu::mainInterface(List<Persona>& lista){
    string myStr;
    char option;

    do{
        system("cls");
        cout << " - - LISTA PERSONAS - - " << endl;

        cout << lista.toString();

        cout << " - - MENU - - " << endl;
        cout << "1. Insertar persona " << endl;
        cout << "2. Eliminar persona " << endl;
        cout << "3. Buscar persona " << endl;
        cout << "4. Obtener anterior " << endl;
        cout << "5. Obtener siguiente " << endl;
        cout << "6. Vacia " << endl;
        cout << "7. Cargar registros" << endl;
        cout << "8. Guardar registros " << endl;
        cout << "0. Salir " << endl;
        cout << "-> Elige una opcion: ";
        cin >> option;

        switch(option)
        {
            case '0':
                system("PAUSE");
                break;

            case '1':
                insertInterface(lista);
                break;

            case '2':
                deleteInterface(lista);
                break;

            case '3':
                findDataInterface(lista);
                break;

            case '4':
                prevInterface(lista);
                break;

            case '5':
                nextInterface(lista);
                break;

            case '6':
                cout << " * ESTADO DE LA LISTA * " << endl;
                myStr = emptyInterface(lista)? "La lista esta vacia\n" : "La lista NO esta vacia\n";
                cout << myStr;
                system("PAUSE");
                break;

            case '7':
                load(lista);
                break;

            case '8':
                save(lista);
                break;

            default:
                cout << "La opcion seleccionada es invalida " << endl;
                system("PAUSE");
                system("cls");
                break;
        }
    }while(option != '0');
}

void Menu::insertInterface(List<Persona>& lista){
    List<Persona>::Position pos;
    Persona persona, aux;
    int id;
    char option;

    cout << " * INSERTANDO PERSONA * " << endl;

    do{
        cin >> persona;

        cout << "1. Insertar al principio" << endl;
        cout << "2. Insertar despues de" << endl;
        cout << "3. Insertar al final" << endl;
        cout << "-> Elige una opcion: ";
        cin >> option;

        cin.sync();

        switch(option)
        {
            case '1':
                pos = nullptr;

                try{
                    lista.insertData(pos, persona);
                }catch(List<Persona>::Exception ex){
                    cout << "\nError al insertar: " << ex.what();
                }

                break;

            case '2':
                cout << "Despues de que persona insertar? (id_persona): ";
                cin >> id; cin.sync();
                aux.setIdPersona(id);

                pos = lista.findData(aux, Persona::compararId);

                try{
                    if(pos != nullptr) {
                        lista.insertData(pos, persona);
                    }else{
                        cout << "Insercion invalida " << endl;
                        cout << "La persona con id " << aux.getIdPersona() << " no esta en la lista" << endl;
                    }
                }catch(List<Persona>::Exception ex){
                    cout << "\nError al insertar: " << ex.what();
                }
                break;

            case '3':
                pos = lista.getLastPos();

                try{
                    lista.insertData(pos, persona);
                }catch(List<Persona>::Exception ex){
                    cout << "\nError al insertar: " << ex.what();
                }

                break;
            
        }

        cout << "Agregar otra persona? (s/n) ";
        cin >> option;

        option = tolower(option);

        cout << endl;

    }while(option != 'n');

    system("PAUSE");
}

void Menu::deleteInterface(List<Persona>& lista){
    List<Persona>::Position pos;
    Persona aux;
    int id;

    cout << " * ELIMINANDO PERSONA * " << endl;
    cout << "Ingresa el id: ";
    cin >> id;
    aux.setIdPersona(id);

    pos = lista.findData(aux, Persona::compararId);

    try{
        lista.deleteData(pos);
        cout << " * Eliminado con exito * " << endl;
    }catch(List<Persona>::Exception ex){
        cout << "Error al eliminar: " << ex.what() << endl;
    }
    system("PAUSE");
}

void Menu::findDataInterface(List<Persona>& lista){
    List<Persona>::Position pos;
    Persona aux;
    int id;

    cout << " * BUSCANDO PERSONA * " << endl;
    cout << "Ingresa el id de la persona: ";
    cin >> id; cin.sync();

    aux.setIdPersona(id);
    pos = lista.findData(aux, Persona::compararId);

    cout << "La persona con id " << aux.getIdPersona() << ": ";

    if(pos == nullptr){
        cout << "NO SE ENCUENTRA EN LA LISTA\n ";
    }
    else{
        cout << "se encuentra en la posicion " << pos << " de la lista" << endl;
        cout << lista.retrieve(pos).toString();
    }

    system("PAUSE");
}

void Menu::prevInterface(List<Persona>& lista){
    List<Persona>::Position pos;
    Persona aux;
    int id;

    cout << " * BUSCANDO PERSONA ANTERIOR * " << endl;
    cout << "Ingresa el id de la persona: ";
    cin >> id; cin.sync();

    aux.setIdPersona(id);
    pos = lista.getPrevPos(lista.findData(aux, Persona::compararId));

    cout << "La persona con id " << aux.getIdPersona() << ": ";

    if(pos == nullptr){
        cout << "NO TIENE UN ANTERIOR\n";
    }
    else{
        cout << "tiene una anterior que se encuentra en la posicion " << pos << " de la lista" << endl;
        cout << lista.retrieve(pos).toString();
    }

    system("PAUSE");
}

void Menu::nextInterface(List<Persona>& lista){
    List<Persona>::Position pos;
    Persona aux;
    int id;

    cout << " * BUSCANDO PERSONA SIGUIENTE * " << endl;
    cout << "Ingresa el id de la persona: ";
    cin >> id; cin.sync();

    aux.setIdPersona(id);
    pos = lista.getNextPos(lista.findData(aux, Persona::compararId));

    cout << "La persona con id " << aux.getIdPersona() << ": ";

    if(pos == nullptr){
        cout << "NO TIENE UN POSTERIOR\n";
    }
    else{
        cout << "tiene una anterior que se encuentra en la posicion " << pos << " de la lista" << endl;
        cout << lista.retrieve(pos).toString();
    }

    system("PAUSE");
}

bool Menu::emptyInterface(List<Persona>& lista){
    return lista.isEmpty();
}

void Menu::save(List<Persona>& lista){
    try{
        lista.saveList();
    }catch(List<Persona>::Exception ex){
        cout << ex.what() << endl;
    }  
    system("PAUSE");
}

void Menu::load(List<Persona>& lista){
    try{
        lista.loadList();
    }catch(List<Persona>::Exception ex){
        cout << ex.what() << endl;
    }
    system("PAUSE");
}

