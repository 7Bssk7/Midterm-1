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
        if (!temp) { // this code checks if temp is nullptr here, pos is invalid
            cout << "Position doesn't exist." << endl;
            return; // This code exits the function without modifying the list 
        }
    
        if (!temp->next) {  // if temp->next is nullptr, temp is the last node (tail)
            pop_back(); // reuse pop_back to remove tail safely
            return;
        }
    
        Node* tempPrev = temp->prev; // store pointer to previous node (must exist since pos != 1)
        tempPrev->next = temp->next; // bypass temp: prev->next now points to node after temp 
        temp->next->prev = tempPrev; // sets the node after temp back to prev(maintain the prev node)
        delete temp; // deletes temp, frees memory to avoid a memory leak
    }

    // This method adds a value to the end of the list 
    void push_back(int v) {
        Node* newNode = new Node(v); // this code allocates new node with data v 
        if (!tail) // checks if list is empty (tail == nullptr)
            head = tail = newNode; // the new node is now both head and tail 
        else {
            tail->next = newNode; // otherwise sets the currents's next to newNode 
            newNode->prev = tail; // sets newNode's prev to the old tail
            tail = newNode; // update tail pointer to the newNode
        }
    }
    

    // This method adds a value to the front of the l
    void push_front(int v) { 
        Node* newNode = new Node(v); // this code allocates new node with data v 
        if (!head) // checks if list is empty (head == nullptr)
            head = tail = newNode; // the ned node is now both head and tail 
        else {
            newNode->next = head; // otherwise sets newNode's next to point at the old head 
            head->prev = newNode; // old heads prev points to the newNode
            head = newNode; // updates head to the newNode
        }
    }
    
    // this method removes node from the front of the list 
    void pop_front() {

        if (!head) { // checks if list is empty (head == nullptr)
            cout << "List is empty." << endl; // outputs an error message
            return; // This code exits the function without modifying the list 
        }

        Node * temp = head; // this code keep s the pointer to the current head so we can easily delete it 

        if (head->next) { // checks if there is more that one node 
            head = head->next; // changes head to the next node 
            head->prev = nullptr; // new head's prev must be nullptr, because its now a first node in the list
        }
        else
            head = tail = nullptr; // if list had only one node now list is empty 
        delete temp; // deallocates the original head node
    }

    // This method removes node from the end of the list
    void pop_back() {
        if (!tail) { // checks if the list is empty 
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }
        Node * temp = tail;  // this code keeps the pointer to the current tail so we can easily delete it 

        if (tail->prev) { // checks if there is more than one node 
            tail = tail->prev; // changes tail pointer to the previous node 
            tail->next = nullptr; // new tail's next is now nullptr
        }
        else
            head = tail = nullptr; // if list had only one node now list is empty
        delete temp; // deallocates the original tail node
    }

    // destructor, traverses the list from head and deletes every node(to avoid a memory leak)
    ~DoublyLinkedList() {
        while (head) {   // this loop checks if list is not empty yet
            Node* temp = head; // hold current head;
            head = head->next; // advance to next head 
            delete temp; // deletes old head
        }
    }
    // This method prints all items of the list from head to tail
    void print() {
        Node* current = head; // set current node to point at the current head 
        if (!current) { // checks if list is not empty 
            cout << "List is empty." << endl; // outputs the error message 
            return; // This code exits the function without modifying the list 
        }
        while (current) { // // traverse until current becomes nullptr
            cout << current->data << " "; // print the data of the node
            current = current->next; // moves to next node
        }
        cout << endl;
    }

    // This method prints all items of the list from tail to head
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

    // The function prints every other element starting with the first.
    void every_other_elemnt(){
        int i = 1; 
        Node* current = head; // start traversal at head

        if (!current){ 
            cout << "List is empty." << endl;
            return; // This code exits the function without modifying the list 
        }
        while(current){ // iterate while current points to a node
            if((i%2) != 0){    // if i is odd, output the data stored in the node 
                cout <<current->data << " ";
            }
            current = current->next; // moves to the next node 
            ++i; // increment index
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
    list.print(); // this code outputs every elements of the list

    cout << "Every other element of the list:" << endl;
    list.every_other_elemnt(); // this code outputs every-other elements of the list 


    
    return 0;
}