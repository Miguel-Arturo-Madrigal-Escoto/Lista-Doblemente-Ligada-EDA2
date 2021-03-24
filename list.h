#ifndef LIST_H
#define LIST_H

#include <exception>
#include <string>
#include <sstream>
#include <fstream>

template <class T>
class List final {
    private:
        class Node {
            private:
                T data;
                Node* prev;
                Node* next;

            public:
                Node();
                Node(const T&);

                T getData() const;
                Node* getPrev() const;
                Node* getNext() const;

                void setData(const T&);
                void setPrev(Node*);
                void setNext(Node*);
        };

        Node *anchor;

        bool isValidPos(Node*) const;

    public:
        class Exception : public std::exception {
            private:
                std::string msg;
            public:
                explicit Exception(const char* message) : msg(message) { }

                explicit Exception(const std::string& message) : msg(message) { }

                virtual ~Exception() throw() {}

                virtual const char* what() const throw () {
                    return msg.c_str();
                }
        };

        typedef Node* Position;

        List();
        List(const List<T>&);

        ~List();

        bool isEmpty() const;

        void insertData(Node*, const T&);

        void deleteData(Node*);

        Node* getFirstPos() const;
        Node* getLastPos() const;
        Node* getPrevPos(Node*) const;
        Node* getNextPos(Node*) const;

        Node* findData(const T&, bool (const T&, const T&)) const;

        T retrieve(Node*) const;

        std::string toString() const;

        void deleteAll();

        void saveList();
        void loadList();
    };

/// Node
template <class T>
List<T>::Node::Node() : prev(nullptr), next(nullptr) { }

template <class T>
List<T>::Node::Node(const T& e) : data(e), prev(nullptr), next(nullptr) {}

template <class T>
T List<T>::Node::getData() const {
    return data;
}

template <class T>
typename List<T>::Node* List<T>::Node::getPrev() const {
    return prev;
}

template <class T>
typename List<T>::Node* List<T>::Node::getNext() const {
    return next;
}

template <class T>
void List<T>::Node::setData(const T& e) {
    this->data = e;
}

template <class T>
void List<T>::Node::setPrev(Node* p){
    this->prev = p;
}

template <class T>
void List<T>::Node::setNext(Node* p) {
    this->next = p;
}


template <class T>
bool List<T>::isValidPos(Node* p) const {
    Node* aux(anchor);

    while(aux != nullptr) {
        if(aux == p){
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}
template <class T>
List<T>::List() : anchor(nullptr) { }

template <class T>
List<T>::~List(){
    saveList();
    deleteAll();
}

template <class T>
bool List<T>::isEmpty() const {
    return anchor == nullptr;
}

template <class T>
void List<T>::insertData(Node* p, const T& e){
    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertData");
    }

    Node *aux(new Node(e));

    if(aux == nullptr) {
        throw Exception("Memoria no disponible, insertData");
    }

    /// insertar al principio
    if(p == nullptr){
        aux->setNext(anchor);

        if(anchor != nullptr) {
            anchor->setPrev(aux);
        }

        anchor = aux;
    }

    /// insertar en cualquier otro lugar
    else{
        aux->setPrev(p);
        aux->setNext(p->getNext());

        if(p->getNext() != nullptr) {
            p->getNext()->setPrev(aux);
        }

        p->setNext(aux);
    }
}

template <class T>
void List<T>::deleteData(Node* p){
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    if(p->getPrev() != nullptr) {
        p->getPrev()->setNext(p->getNext());
    }

    if(p->getNext() != nullptr) {
        p->getNext()->setPrev(p->getPrev());
    }

    /// elimina el primero
    if(p == anchor) {
        anchor = anchor->getNext();
    }

    delete p;
}

template <class T>
typename List<T>::Node* List<T>::getFirstPos() const {
    return anchor;
}

template <class T>
typename List<T>::Node* List<T>::getLastPos() const {
    if(isEmpty()){
        return nullptr;
    }

    Node* aux(anchor);

    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename List<T>::Node* List<T>::getPrevPos(Node* p) const {
    return (!isValidPos(p))? nullptr : p->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getNextPos(Node* p) const {
    return (!isValidPos(p))? nullptr : p->getNext();
}

template <class T>
typename List<T>::Node* List<T>::findData(const T& e, bool comp(const T&, const T&)) const {
    Node* aux(anchor);

    while(aux != nullptr and !comp(aux->getData(), e)){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
T List<T>::retrieve(Node* p) const {
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
    }
    return p->getData();
}

template <class T>
std::string List<T>::toString() const {
    Node* aux(anchor);
    std::string result;

    while(aux != nullptr) {
        result += aux->getData().toString();
        aux = aux->getNext();
    }

    return result;
}

template <class T>
void List<T>::deleteAll() {
    Node* aux;

    while(anchor != nullptr) {
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

template <class T>
void List<T>::saveList(){
    if(isEmpty()){
        return;
    }
    
    std::ofstream archivo("file01.txt");
    if(!archivo){
        throw Exception("Error al guardar, saveList");
    }

    Node* aux(anchor);

    while(aux != nullptr) {
        archivo << aux->getData().getIdPersona() << "|";
        archivo << aux->getData().getNombre() << "|";
        archivo << aux->getData().getApellido() << "*";
        aux = aux->getNext();
    }

    archivo.close();
}

template <class T>
void List<T>::loadList(){
    std::ifstream archivo("file01.txt");

    if(!archivo){
        throw Exception("Error al cargar, loadList");
    }

    T persona;
    std::string linea, temp;
    while(getline(archivo, linea, '*')){
        std::stringstream ss(linea);

        getline(ss, temp, '|');
        persona.setIdPersona(stoi(temp));

        getline(ss, temp, '|');
        persona.setNombre(temp);

        getline(ss, temp);
        persona.setApellido(temp);

        insertData(getLastPos(), persona);
    }   
    archivo.close();  
}

#endif