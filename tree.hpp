#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <exception>

template <class T>
class Tree {
private:
    class Node {
    private:
        T* dataPtr;
        Node* left;
        Node* right;
    public:
        class Exception : public std::exception {
        private:
            std::string msg;

        public:
            Exception() noexcept : msg("Error indefinido") {}
            Exception(const Exception& ex) noexcept : msg(ex.msg) {}
            Exception(const std::string& m) : msg(m) {}
            Exception& operator = (const Exception& ex) noexcept {
                msg = ex.msg;
                return *this;
                }
            virtual ~Exception() {}
            virtual const char* what() const noexcept {
                return msg.c_str();
                }
            };

        Node();
        Node(const T&);
        ~Node();

        T* getDataPtr();
        T &getData() const;
        Node* &getLeft();
        Node* &getRight();

        void setDataPtr(T*);
        void setData(const T&);
        void setLeft(Node*&);
        void setRight(Node*&);

        };
public:
    typedef Node* Position;
private:
    Position root;

    void copyAll(Position&, Position&);

    bool isValidPos(Position) const;

    void insertData(Position&, const T&);

    void deleteData(Position&, const T&);

    int getHeight(const Position&) const;

    Position& findData(Position&, const T&);

    void deleteAll(Position&);

    void parsePreOrder(const Position&);
    void parseInOrder(const Position&);
    void parsePostOrder(const Position&);
    Position& getLowest(Position&);
    Position& getHighest(Position&);

public:
    class Exception : public std::exception {
        private:
            std::string msg;

        public:
            Exception() noexcept : msg("Error indefinido") {}
            Exception(const Exception& ex) noexcept : msg(ex.msg) {}
            Exception(const std::string& m) : msg(m) {}
            Exception& operator = (const Exception& ex) noexcept {
                msg = ex.msg;
                return *this;
                }
            virtual ~Exception() {}
            virtual const char* what() const noexcept {
                return msg.c_str();
                }
        };

    Tree();
    Tree(const Tree&);
    ~Tree();

    bool isEmpty() const;

    void insertData(const T&);

    void deleteData(const T&);

    bool isLeaf(const Position&) const;

    Position& getLowest();
    Position& getHighest();

    int getHeight() const;
    int getLeftHeight()const;
    int getRightHeight()const;

    T& retrieve(const Position);

    Position& findData(const T&);

    void deleteAll();

    std::string toString();

    Tree& operator = (const Tree&);

    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();

};


using namespace std;

//------- Node ------------
template<class T>
Tree<T>::Node::Node() : dataPtr(nullptr), left(nullptr) , right(nullptr) {}

template<class T>
Tree<T>::Node::Node(const T& e) : dataPtr(new T(e)), left(nullptr), right(nullptr) {
    if (dataPtr == nullptr){
        throw Exception("Memoria no disponible, constructor");
        }
    }

template<class T>
T *Tree<T>::Node::getDataPtr() {
    return dataPtr;
    }

template<class T>
T& Tree<T>::Node::getData() const {
    return *dataPtr;
    }

template<class T>
typename Tree<T>::Node*& Tree<T>::Node::getLeft() {
    return left;
    }

template<class T>
typename Tree<T>::Node*& Tree<T>::Node::getRight() {
    return right;
    }

template <class T>
Tree<T>::Node::~Node(){
    delete dataPtr;
    }

template<class T>
void Tree<T>::Node::setDataPtr(T* p) {
    dataPtr = p;
    }

template<class T>
void Tree<T>::Node::setData(const T& e) {
    if (dataPtr == nullptr){
        if ((dataPtr = new T(e)) == nullptr){
            throw Exception("Falta de memoria");
            }
        } 
    else {
        *dataPtr = e;
        }
    }

template<class T>
void Tree<T>::Node::setLeft(Node*& p) {
    left = p;
    }

template<class T>
void Tree<T>::Node::setRight(Node*& p) {
    right = p;
    }

// ------------------  Tree ------------------------

template<class T>
Tree<T>::Tree() : root(nullptr) {}

template<class T>
Tree<T>::Tree(const Tree& t) : root(nullptr) {
    copyAll(t.root, root); //this->root segundo parametro
    }

template<class T>
Tree<T>::~Tree() {
    deleteAll();
    root = nullptr;
    }

template<class T>
void Tree<T>::parsePreOrder(const Position& r) {
    if (r == nullptr) {
        return; //"Arbol vacio";
        }
    cout <<  r->getData() << " ";

    parsePreOrder(r->getLeft());
    parsePreOrder(r->getRight());
    }

template<class T>
void Tree<T>::parsePreOrder() {
    parsePreOrder(root);
    }

template<class T>
void Tree<T>::parseInOrder() {
    parseInOrder(root);
    }

template<class T>
void Tree<T>::parseInOrder(const Position& r) {
    if (r == nullptr) {
        return; //"Arbol vacio";
        }

    parseInOrder(r->getLeft());
    std::cout << r->getData() << " ";
    parseInOrder(r->getRight());

    }

template<class T>
void Tree<T>::parsePostOrder() {
    parsePostOrder(root);
    }


template<class T>
void Tree<T>::parsePostOrder(const Position& r) {
    if (r == nullptr) {
        return; //"Arbol vacio";
        }

    parsePostOrder(r->getLeft());
    parsePostOrder(r->getRight());
    cout << r->getData() << " ";
    }

template<class T>
int Tree<T>::getHeight() const {
    getHeight(root);
    }

template<class T>
int Tree<T>::getLeftHeight() const {
    getHeight(root->getLeft());
    }

template<class T>
int Tree<T>::getRightHeight() const {
    getHeight(root->getRight());
    }

template<class T>
int Tree<T>::getHeight(const Position& r) const {
    if (r == nullptr) {
        return 0;
        }

    int leftHeight(getHeight(r->getLeft()));
    int rightHeight(getHeight(r->getRight()));

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    }

template<class T>
void Tree<T>::copyAll(Position& t, Position& d) {
    if (t == nullptr) {
            d = nullptr;
            return;
        }

        d = new Node(t->getData());
        copyAll(t->getLeft(), d->getLeft());
        copyAll(t->getRight(), d->getRight());
    }

template<class T>
bool Tree<T>::isValidPos(Position) const {
    return false;
    }

template<class T>
bool Tree<T>::isEmpty() const {
    return root == nullptr;
    }

template<class T>
void Tree<T>::insertData(const T& e) {
    insertData(root, e);
    }

template<class T>
void Tree<T>::insertData(Position& r, const T& e) {
    if (r == nullptr) {
        try {
            if ((r = new Node(e)) == nullptr) {
                throw Exception("Memoria no disponible, insertData");
                }
            } catch (const typename Node::Exception& ex) {
            throw Exception(ex.what());
            }

    } 
    else {
        if (e < r->getData()) {
            insertData(r->getLeft(), e);
            } 
        else {
            insertData(r->getRight(), e);
            }
        }
    }

template<class T>
void Tree<T>::deleteData(const T& e) {
    deleteData(root, e);
    }

template<class T>
void Tree<T>::deleteData(Position& r, const T& e) {
    if(r == nullptr){ //caso base
        return;
        }

    if(e < r->getData()){
        deleteData(r->getLeft(), e);
        }
    else if( e > r->getData()){
        deleteData(r->getRight(), e);
        }
    else{
        if(r->getLeft() == nullptr && r->getRight() == nullptr){//Borrar Hoja
            delete r;
            r = nullptr;
            }
        else if(r->getLeft() == nullptr){
            Position aux(r);
            r = r->getRight();
            delete aux;
            }
        else if (r->getRight() == nullptr) {//Nodo con un solo hijo a la izquierda
            
            Position aux = r;
            r = r->getLeft();
            delete aux;
        } 
        else {//Nodo con dos hijos
            Position successor = getLowest(r->getRight());
            r->setData(successor->getData());
            deleteData(r->getRight(), successor->getData());
            } 
        }
    }

template<class T>
bool Tree<T>::isLeaf(const Position& r) const {
    return r != nullptr and r->getLeft() == r->getRight();
    }

template<class T>
typename Tree<T>::Position& Tree<T>::getLowest(){
    return getLowest(root);
    }
template<class T>
typename Tree<T>::Position& Tree<T>::getLowest(Position& r) {
    if (r == nullptr or r->getLeft() == nullptr) {
        return r;
        }

    return getLowest(r->getLeft());
    }

template<class T>
typename Tree<T>::Position& Tree<T>::getHighest(){
    return getHighest(root);
    }

template<class T>
typename Tree<T>::Position& Tree<T>::getHighest(Position& r) {
    if (r == nullptr or r->getRight() == nullptr) {
        return r;
        }
    return getHighest(r->getRight());
    }

template<class T>
T& Tree<T>::retrieve(const Position r) {
    if (r == nullptr) {
        throw Exception ("Posicion invalida, retrieve");
        }

    return r->getData();
    }

template<class T>
typename Tree<T>::Position& Tree<T>::findData(const T& e) {
    return findData(root, e);
    }

template<class T>
typename Tree<T>::Position& Tree<T>::findData(Position& r , const T& e) {
    if (r == nullptr or r->getData() == e) {
        return r;
        }

    if (e < r->getData()) {
        return (findData(r->getLeft(), e));
        }
    return findData(r->getRight(), e);
    }

template<class T>
void Tree<T>::deleteAll() {
    deleteAll(root);
    }

template<class T>
void Tree<T>::deleteAll(Position& r) {
    if(r != nullptr){
        deleteAll(r->getLeft());
        deleteAll(r->getRight());

        delete r;
        r = nullptr;
        }
    }

template<class T>
string Tree<T>::toString() {
    return std::string();
    }

template<class T>
Tree<T>& Tree<T>::operator=(const Tree& t) {
    deleteAll();

    copyAll(t.root, root);

    return *this;
    }


#endif
