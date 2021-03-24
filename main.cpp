#include <iostream>
#include "list.h"
#include "persona.h"
#include "menu.h"

using namespace std;

int main()
{
    List<Persona> lista;
    Menu menu(lista);
    
    return 0;
}