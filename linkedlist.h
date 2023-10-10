#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <utility>
#include <initializer_list>

template<typename T> class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int count;


    public:
        LinkedList() {
            head = nullptr;
            tail = nullptr;
            count = 0;
        }

        LinkedList(initializer_list<T> inputList) {
            head = nullptr;
            tail = nullptr;
            count = 0;
            for(auto & element : inputList) {
                push_back(element);
            }
        }

        void push_front(T item) {
            Node<T> * newHead = new Node<T>(item);
            if (count == 0) {
                head = newHead;
                tail = newHead;
            } else {
                newHead->next = head;
                head->previous = newHead;
                head = newHead;
            }
            head->previous = nullptr;
            count++;
        }

        T & front() {
            return head->data;
        }

        void push_back(T item) {
            Node<T> * newTail = new Node<T>(item);
            if (count == 0) {
                head = newTail;
                tail = newTail;
            } else {
                tail->next = newTail;
                newTail->previous = tail;
                tail = newTail;
            }
            tail->next = nullptr;
            count++;
        }

        T & back() {
            return tail->data;
        }

        int size() {
            return count;
        }

        NodeIterator<T> begin() {
            return NodeIterator<T>(head);
        }

        const NodeIteratorConst<T> begin() const {
            return NodeIteratorConst<T>(head);
        }

        NodeIterator<T> end() {
            return NodeIterator<T>(nullptr);
        }

        const NodeIteratorConst<T> end() const {
            return NodeIteratorConst<T>(nullptr);
        }

        void reverse() {
            Node<T>* newHead = tail;
            Node<T>* newTail = head;

            Node<T>* current = head;
            Node<T>* temp = nullptr;

            while(current != nullptr) {
                // Swap the current node's next and previous nodes
                temp = current->previous;
                current->previous = current->next;
                current->next = temp;

                // Navigate to next node to switch
                current = current->previous;
            }

            head = newHead;
            tail = newTail;
        }

        NodeIterator<T> insert(NodeIterator<T> target, T element) {
            Node<T>* newNode = new Node<T>(element);
            NodeIterator<T> returnItr = NodeIterator<T>(newNode);

            Node<T>* insertNode = target.getNode();

            newNode->previous = insertNode->previous;
            insertNode->previous = newNode;

            newNode->next = insertNode;
            if (newNode->previous == nullptr) {
                head = newNode;
            }
            else {
                newNode->previous->next = newNode;
            }

            return returnItr;
        }

        NodeIterator<T> erase(NodeIterator<T> target) {
            Node<T>* delNode = target.getNode();
            NodeIterator<T> nextNodeItr = NodeIterator<T>(delNode->next);

            if (delNode == head) {
                head = delNode->next;
                head->previous = nullptr;
                delNode->next = nullptr;
            }

            if (delNode->next != nullptr) {
                delNode->next->previous = delNode->previous;
            }

            if (delNode->previous != nullptr) {
                delNode->previous->next = delNode->next;
            }

            delete delNode;

            return nextNodeItr;
        }

        ~LinkedList() {
            if(head != nullptr && tail != nullptr) {
                auto itr = begin();
                ++itr;
                auto itrEnd = end();
                while (itr != itrEnd) {
                    delete itr.getNode()->previous;
                    ++itr;
                }
            }
        }
};

#endif