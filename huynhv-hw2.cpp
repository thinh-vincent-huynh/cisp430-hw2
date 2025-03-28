#include <iostream>
using namespace std;

// array to be populated
const int SIZE = 10;
int ARRAY[SIZE] = {7, 3, 8, 11, 6, 10, 10, 3, 9, 11};

// node struct is enough for linked list implementation
struct node{
    int value;
    node* prev;
    node* next;
    node(int _value, node* _prev, node* _next){
        value = _value;
        prev  = _prev;
        next  = _next;
    }
};

//split a linked list into 2 evenly sub linked lists
void split(node* head,node*&a,node*&b){
    a = head;   // start at head; a stays at head
    b = head;   // start at head and end at middle
    int count = 1;      // head counts as 1 node
    while (b->next){
        b = b->next;    // move b to the end
        count++;        // count num of nodes in list
    }
    for (int i = 1; i < count / 2; i++){
        b = b->prev;    // move b to the middle
    }
    // disconnect 2 evenly sub linked lists
    if (b->prev){   // if NOT only 1 node in list
        b->prev->next = nullptr;
        b->prev = nullptr;
    }
} // 17 lines

node* merge(node* a, node* b){
    if (!a){ return b; }    // merge with b itself
    if (!b){ return a; }    // merge with a itself
    node* c = nullptr;
    if (a->value < b->value){   // merge and sort
        c = a;
        c->next = merge(a->next, b);
        if (c->next){ c->next->prev = c; }
    }else{
        c = b;
        c->next = merge(a, b->next);
        if (c->next){ c->next->prev = c; }
    }
    return c;   // the whole list consisted of a and b
} // 15 lines

node* mergeSort(node* head){
    if (head==nullptr){    // split into nothing
        return nullptr;
    }
    if (head->next==nullptr){  // split into itself
        return head;
    }
    // actually start here
    node *a = nullptr, *b = nullptr;
    split(head, a, b);  // split into 2 halves
    a = mergeSort(a);   // continue to split itself
    b = mergeSort(b);   // continue to split itself
    return merge(a, b); // sorted partition/whole list
} // 14 lines

int main(){
    // populate linked list through array
    // and display the unsorted linked list
    node* head = new node(ARRAY[0], nullptr, nullptr);
    cout << "Unsorted:" << endl << head->value;
    node* curr = head;
    for (int i = 1; i < SIZE; i++){
        cout << " -> ";
        curr->next = new node(ARRAY[i], curr, nullptr);
        cout << curr->next->value;
        curr = curr->next;
    }

    // sort the linked list using mergeSort()
    head = mergeSort(head);

    // display the sorted version of the linked list
    cout << endl << "Sorted:" << endl << head->value;
    curr = head->next;
    while (curr){
        cout << " -> ";
        cout << curr->value;
        curr = curr->next;
    }
    cout << endl;
}
