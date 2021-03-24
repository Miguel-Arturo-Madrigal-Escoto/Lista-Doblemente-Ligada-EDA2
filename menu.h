#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "list.h"
#include "persona.h"

class Menu{
    private:
        void mainInterface(List<Persona>&);
        void insertInterface(List<Persona>&);
        void deleteInterface(List<Persona>&);
        void findDataInterface(List<Persona>&);
        void prevInterface(List<Persona>&);
        void nextInterface(List<Persona>&);
        bool emptyInterface(List<Persona>&);
        void save(List<Persona>&);
        void load(List<Persona>&);
    public:
        Menu(List<Persona>&);
};

#endif