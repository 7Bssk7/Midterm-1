//COMSC-210 | Midterm #1 | Arkhip Finski
// IDE used: Visual Studio
#include <iostream>
using namespace std;

//This code assigns constant values. They represent the range of the generated numbers and the size of the list.
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

//This code defines the DoublyLinkedList class, this class creates and performs various interactions with the list.
class DoublyLinkedList {
private: // This code defines private data members of the class DoublyLinkedList
    struct Node { // This is a Node structure for the Double linked list (DoublyLinkedList class)
        int data;  // This variable stores a provided data in each node(integer )
        Node* prev; // This is a pointer to the previous Node in the list
        Node* next; // This is a pointer to the next Node in the list
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // This is a constructor for the Node , it includes the node data, a pointer to the next node, and the previous node.
            data = val;  // This code sets a Node's stored integer to the provided value 
            prev = p;    // This line of code set previous pointer with the provided pointer p( if pointer is not provided, by default it is set to nullptr)
            next = n;    // This line of code set next pointer with the provided pointer n( if pointer is not provided, by default it is set to nullptr)
        }
    };

    Node* head;
    Node* tail;

public:
    // This line of code is a default constructor of double linked list (DoublyLinkedList), sets head and tail pointer to nullptr.
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    //  Both head and tail pointer of the double linked list are set to nullptr, list is empty.

    //This method inserts a new Node with a provided value at the provided position in the list.
    void insert_after(int value, int position) {
        if (position < 0) {  // This code checks if position is not negative
            cout << "Position must be >= 0." << endl; // If position is negative, outputs and error message 
            return; // This code exits the function without modifying the list 
        }

        Node* newNode = new Node(value);  // allocate a new Node on the heap, set its data inteer ti 'value'
        if (!head) {    // If list is empty, head == nullptr
            head = tail = newNode; // new node becomes both head and tail of the list
            return; // This code exits the function without modifying the list  
        }

        Node* temp = head; // this code sets Node temp == head , in order to start traversal at head
        for (int i = 0; i < position && temp; ++i) // this loop looks for the position and checks if pointer did not exceed the size of the list
            temp = temp->next; // moves to the next node with each iteration

        if (!temp) {  // if temp is nullptr, then the provided position is not on the list 
            cout << "Position exceeds list size. Node not inserted.\n"; // output the error message 
            delete newNode; // free the previously allocated node to avoid a memory leak 
            return; // This code exits the function without modifying the list 
        }

        // now, if no error message was displayed , that means temp points to the node after which we should insert newNode 

        newNode->next = temp->next; // set newNode's next to temp's next 
        newNode->prev = temp; // set newNode's prev to temp's prev
        if (temp->next) // checks if temp has next point to something(not a tail)
            temp->next->prev = newNode;  // updates prev pointer of the node before new inserted node to point at newNode
        else    // if temp was a tail , newNode becomes new tail of the list
            tail = newNode; // newNode is now a tail of the list 
        temp->next = newNode; // changes temp->next to point at the newNode
    }

    // This method deletes node with data == value
    void delete_val(int value) {
        if (!head) return;  // This code exits the function without modifying the list, if the list is empty 

        Node* temp = head; // this code sets Node temp == head , in order to start traversal at head
        
        while (temp && temp->data != value) // this loop search forward for a node containing 'value
            temp = temp->next; // this code move to the next node each iteration if node that contains value was not found

        if (!temp) return; // if such a node was not found, exits the function without modifying the list, nothing to delete

        // now  temp points to the node to delete
        if (temp->prev) // if the node to delete is not the head 
            temp->prev->next = temp->next; // set the previous node's next to the node after temp
        else
            head = temp->next;  // temp was a head - update head to point at the next node

        if (temp->next) // if the node to delete is not the tail 
            temp->next->prev = temp->prev; // sets the next node prev to pint at the node before temp
        else
            tail = temp->prev; // temp was a tail - update tail to the previous node 

        delete temp; // free the memory to avoid a memory leak 
    }

    // delete node located at position pos 
    void delete_pos(int pos) {
        if (!head) {  // empty list 
            cout << "List is empty." << endl; // outpus an error message
            return; // This code exits the function without modifying the list 
        }
    
        if (pos == 1) { // special case dleetes the first node 
            pop_front(); // reuse pop-front which handles head/tail updates and deletion 
            return; // done
        }
    
        Node* temp = head; // this code sets Node temp == head , in order to start traversal at head
    
        for (int i = 1; i < pos; i++){  // iterate from index 1 up to pos-1 to reach the pos-th node
            if (!temp) { // if temp becomes nullptr before we reach pos, position doesn't exist
                cout << "Position doesn't exist." << endl;
                return; // This code exits the function without modifying the list 
            }
            else
                temp = temp->next; // otherwise move one step forward
        }
        if (!temp) { // this code chgecks if temp is nullptr here, pos is invalid
            cout << "Position doesn't exist." << endl;
            return; // This code exits the function without modifying the list 
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp; // This code exits the function without modifying the list 
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void every_other_elemnt(){
        int i = 1;
        Node* current = head;

        if (!current){
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }
        while(current){
            if((i%2) != 0){
                cout <<current->data << " ";
            }
            current = current->next;
            ++i;
        } 
        cout << endl;

    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS << endl;  // dummy statement to avoid compiler warning

    // Test 
    int size = MIN_LS;
    DoublyLinkedList list;

    for(int i = 0; i < size; ++i){
        list.push_back((i+1));
    }

    cout << "Print list: " << endl;
    list.print();

    cout << "Every other element of the list:" << endl;
    list.every_other_elemnt();


    
    return 0;
}