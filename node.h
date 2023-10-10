#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template<typename T> class Node {
    public:
        T data;
        Node* next;
        Node* previous;


        Node(T dataIN)
            : data(dataIN) {
                next = nullptr;
                previous = nullptr;
            }
};

template<typename T> class NodeIterator {
    private:
        Node<T>* current;
        
    public:
        NodeIterator(Node<T>* currentIn)
            : current(currentIn) {        
        }

        NodeIterator() {
            current = nullptr;
        }

        T & operator*() {
            return current->data;
        }

        void operator++() {
            current = current->next;
        }

        bool operator==(NodeIterator other) {
            return(current == other.current);
        }

        bool operator!=(NodeIterator other) {
            return(current != other.current);
        }

        Node<T> * getNode() {
            return current;
        }
};

template<typename T> class NodeIteratorConst {
    private:
        const Node<T>* current;

    public:
        NodeIteratorConst(const Node<T>* currentIn) {
            current = currentIn;
        }

        NodeIteratorConst() {
            current = nullptr;
        }

        const T & operator*() {
            return current->data;
        }

        void operator++() {
            current = current->next;
        }        

        bool operator==(const NodeIteratorConst & other) const {
            return(current == other.current);
        }

        bool operator!=(const NodeIteratorConst & other) const {
            return(current != other.current);
        }
        
        Node<T> * getNode() const {
            return current;
        }
};

#endif