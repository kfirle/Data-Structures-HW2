//
// Created by kfir2 on 06/05/2020.
//

#ifndef AVLTREE_LIST_H
#define AVLTREE_LIST_H

#include <iostream>
using std::exception;
using std::cout;
using std::endl;

class NotFound : public exception{};
class BadParameters : public exception{};


/*template<class T>
struct node {

    node<T>* next;
    T data;
};
*/

template <class Key, class Data>
class List {

    public:

    class ListNode {

        Key key;       //will be used for num_of_plays
        Data data;     //will be used for artists tree
        ListNode *next;
        ListNode *previous;

        public:

        explicit ListNode()= default;  // = delete;

        ListNode(Key &key, Data &data, ListNode* next, ListNode *previous):
                key (key), data(data), next(next), previous(previous){}

        ~ListNode() = default;

        const Key& getKey() const{
            return key;
        }

        Data& getData(){
            return data;
        }

        ListNode* getNext() {
            return next;
        }

        ListNode* getPrevious() {
            return previous;
        }

        friend bool operator<(ListNode &node1, ListNode &node2) {
            return node1.key < node2.key;
        }

        friend bool operator==(ListNode &node1, ListNode &node2) {
            return node1.key == node2.key;
        }

        friend class List;
    };

    private:

    ListNode *first;
    ListNode *last;

    public:

    List() : first(nullptr), last(nullptr) {};

    ~List() {
        ListNode *i = first;
        ListNode *next;
        while (i != nullptr) {
            next = i->next;
            delete i;
            i = next;
        }
    }

    ListNode *getFirst() {
        return this->first;
    }

    ListNode *getLast() {
        return this->last;
    }

    ListNode *insertFirst(Key &key, Data &data) {
        /*
        if (key == NULL || data == NULL) {
            throw BadParameters();
        }
        */
        ListNode *new_element = new ListNode(key, data, first, nullptr);
        if (this->first == NULL) {                    // The list is empty
            first = new_element;
            last = first;
        } else {
            if (last == first) {               // The list has one element
                last->previous = new_element;
            } else {                        // The list has more than one element
                //ListNode *tmp = first;
                first->previous = new_element;
            }
            first = new_element;
        }
        return new_element;
    }

    ListNode *insertAfterNode(Key &key, Data &data, ListNode* element) {
        /*
        if (key == NULL || data == NULL || element == nullptr) {
            throw BadParameters();
        }
        */
        ListNode *temp = element->next;
        ListNode *new_element = new ListNode(key, data, temp, element);
        element->next = new_element;
        if (element == last) {
            last = new_element;
        } else {
            temp->previous = new_element;
        }
        return new_element;
    }

    ListNode *findByKey(Key &key) {
        /*
        if (key == NULL) {
            throw BadParameters();
        }
        */
        ListNode *i = first;
        while (i != nullptr) {
            if (i->key == key) {
                return i;
            }
            i = i->next;
        }
        throw NotFound();
    }

    void erase(ListNode* element) {
        /*
        if (element == NULL) {
            throw BadParameters();
        }
        */
        if(element == first && element == last){        // The list has one element
            first= nullptr;
            last = nullptr;
            delete element;
            return;
        }
        if(element == first){
            first = element->next;
            first->previous = nullptr;
            delete element;
            return;
        }
        if(element == last){
            last = element->previous;
            last->next = nullptr;
            delete element;
            return;
        }
        element->previous->next = element->next;
        element->next->previous = element->previous;;
        delete element;
    }

    void printList(){
        cout << "song plays printing:" << endl;
        ListNode *i = first;
        if(i == nullptr){
            cout << "List is empty" << endl;
            return;
        }
        while (i != last) {
            cout << i->key << ", ";
            i = i->next;
        }
        cout << i->key << endl;
    }

};


#endif //AVLTREE_LIST_H
