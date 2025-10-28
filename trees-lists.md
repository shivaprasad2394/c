# Capgemini Trees and List Problems - Complete Solutions

```c
#define C_BST_CODE 1
#define CPP_BST_CODE 0
#define C_LIST_CODE 1
#define CPP_LIST_CODE 0
#define C_QUEUE_CODE 1
#define CPP_QUEUE_CODE 0

// ============================================================================
// BINARY SEARCH TREE OPERATIONS
// ============================================================================

/*
BST Properties:
1. Left subtree contains only nodes with keys lesser than node's key
2. Right subtree contains only nodes with keys greater than node's key
3. Both left and right subtrees are also BSTs

Common Operations:
- Insert: O(log n) average, O(n) worst case
- Search: O(log n) average, O(n) worst case  
- Delete: O(log n) average, O(n) worst case
- Traversal: O(n) for all nodes
*/

#if C_BST_CODE
#include <stdio.h>
#include <stdlib.h>

// Node structure for BST
typedef struct Node {
    int id;              // Data member 'id'
    struct Node* left;   // Pointer to left child
    struct Node* right;  // Pointer to right child
} Node;

/* createNode:
 * step1: allocate new memory using malloc and assign to newNode pointer
 * step2: store 'id' in newNode's data member
 * step3: initialize left and right pointers to NULL
 * step4: return pointer to the new node
 */
Node* createNode(int id) {
    Node* newNode = (Node*) malloc(sizeof(Node));  // step1
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->id = id;       // step2
    newNode->left = NULL;   // step3
    newNode->right = NULL;  // step3
    return newNode;         // step4
}

/* insertNode:
 * Insert 'id' in correct place in BST
 * step1: If root is NULL, create and return new node
 * step2: If 'id' is less than root's id, insert in left subtree
 * step3: If 'id' is greater than root's id, insert in right subtree
 * step4: Return the root pointer unchanged if id equals root->id (no duplicates)
 */
Node* insertNode(Node* root, int id) {
    if (root == NULL) {                // step1
        return createNode(id);
    }
    if (id < root->id) {              // step2
        root->left = insertNode(root->left, id);
    } else if (id > root->id) {       // step3
        root->right = insertNode(root->right, id);
    }
    // step4: equal id, do nothing for duplicates
    return root;
}

/* searchNode:
 * Search for key in BST
 * step1: If root NULL or root->id == key, return root found/not found
 * step2: If key < root->id, recurse to left subtree
 * step3: Else recurse to right subtree
 */
Node* searchNode(Node* root, int key) {
    if (root == NULL || root->id == key) {   // step1
        return root;
    }
    if (key < root->id) {                     // step2
        return searchNode(root->left, key);
    } else {                                  // step3
        return searchNode(root->right, key);
    }
}

/* inorderTraversal:
 * Inorder traversal => left, root, right
 * step1: Recursively traverse left subtree if exists
 * step2: Print current node's id
 * step3: Recursively traverse right subtree if exists
 */
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);   // step1
        printf("%d ", root->id);        // step2
        inorderTraversal(root->right);  // step3
    }
}

/* freeTree:
 * Postorder traversal to free nodes: left, right, root
 */
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* Main function to demonstrate */
int main() {
    Node* root = NULL;

    // Insert nodes
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Search for a node
    int key = 60;
    Node* found = searchNode(root, key);
    if (found != NULL)
        printf("%d found in BST\n", key);
    else
        printf("%d not found in BST\n", key);

    // Free all allocated memory
    freeTree(root);
    return 0;
}

#endif

#if CPP_BST_CODE
#endif

// ============================================================================
// LINKED LIST OPERATIONS
// ============================================================================

/*
Linked List Properties:
1. Dynamic data structure with nodes containing data and pointer to next node
2. No random access - must traverse from head
3. Efficient insertion/deletion at any position

Common Operations:
- Insert: O(1) at head, O(n) at arbitrary position
- Delete: O(1) if node given, O(n) to find and delete
- Search: O(n) linear search
- Traversal: O(n)
*/

#if C_LIST_CODE
#include <stdio.h>
#include <stdlib.h>

// Node structure representing each linked list element
typedef struct Node {
    int id;            // Data member 'id'
    struct Node* next; // Pointer to next node
} Node;

/* createNode:
 * Step1: Allocate new memory using malloc and assign to newNode pointer
 * Step2: Store 'id' in newNode's data member
 * Step3: Initialize 'next' pointer of newNode to NULL
 * Step4: Return pointer to newNode
 */
Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Step1
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->id = id;       // Step2
    newNode->next = NULL;   // Step3
    return newNode;         // Step4
}

/* insertAtEnd:
 * Inserts a node with given 'id' at the end of the linked list
 * Step1: Create new node
 * Step2: If list is empty (head == NULL), new node becomes the head
 * Step3: Else traverse to last node and link new node there
 */
void insertAtEnd(Node** head, int id) {
    Node* newNode = createNode(id); // Step1
    if (*head == NULL) {             // Step2
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {     // Step3
        temp = temp->next;
    }
    temp->next = newNode;
}

/* deleteNode:
 * Deletes the first node with given 'key' from list
 * Step1: If list empty, do nothing
 * Step2: If head node has key, remove head
 * Step3: Else traverse to find node with key, link around it and free
 */
void deleteNode(Node** head, int key) {
    if (*head == NULL) return;            // Step1

    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && temp->id == key) { // Step2
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != key) { // Step3
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;  // key not found

    prev->next = temp->next;
    free(temp);
}

/* printList:
 * Prints all node ids in the list
 */
void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->id);
        head = head->next;
    }
    printf("NULL\n");
}

/* freeList:
 * Frees the whole list memory
 */
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Main function to test the linked list operations
int main() {
    Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printf("Linked List: ");
    printList(head);

    deleteNode(&head, 20);
    printf("After deleting 20: ");
    printList(head);

    freeList(head);
    return 0;
}

#endif

#if CPP_LIST_CODE
#endif

// ============================================================================
// QUEUE OPERATIONS
// ============================================================================

/*
Queue Properties:
1. FIFO (First In First Out) data structure
2. Elements added at rear, removed from front
3. Two main operations: Enqueue (add) and Dequeue (remove)

Implementation Methods:
1. Array-based: Fixed size, simple implementation
2. Linked List-based: Dynamic size, more complex

Time Complexity:
- Enqueue: O(1)
- Dequeue: O(1)
- Peek/Front: O(1)
*/

#if C_QUEUE_CODE
#include <stdio.h>
#include <stdlib.h>

// Node structure (each node is a memory block with data and forward link)
typedef struct Node {
    int id;              // Data member 'id'
    struct Node* next;   // Forward link pointer
} Node;

// Queue structure to keep track of front and rear
typedef struct {
    Node* front;  // Points to the first node in queue
    Node* rear;   // Points to the last node in queue
} Queue;

// Create and initialize a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

/* Enqueue function:
 * step1: create a new memory block using malloc and point to new address returned by malloc
 * step2: 
 *       + if it is the first node to be created then 
 *           - point new block as both front and rear start references.
 *           - store "NULL" in the forward link of new block and "data" in 'id'.
 *       + if the queue already has nodes then
 *           - store NULL in forward link of new block.
 *           - link the current rear block's forward link to new block.
 *           - store data in new block's 'id'.
 *           - update rear pointer to new block.
 * step3: no return required.
 */
void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Step 1
    newNode->id = data;
    newNode->next = NULL;

    if (q->rear == NULL) {  // Step 2: first node to be created
        q->front = q->rear = newNode;
    } else {                // Step 2: queue has existing nodes
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

/* Dequeue function:
 * step1: check if queue is empty (front == NULL),
 *         if yes, print empty message and return -1.
 * step2: create a temp pointer to front node.
 * step3: move front pointer to next node.
 * step4: if after moving, front becomes NULL, set rear to NULL.
 * step5: store data from temp node, free temp memory.
 * step6: return stored data.
 */
int dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;   // indicate underflow
    }
    Node* temp = q->front;  // Step 2
    int data = temp->id;    // Step 5
    q->front = q->front->next;  // Step 3

    if (q->front == NULL) {   // Step 4
        q->rear = NULL;
    }
    free(temp);             // Step 5
    return data;            // Step 6
}

/* Peek function:
 * step1: Check if queue is empty (front == NULL).
 *         If yes, print message and return -1.
 * step2: Return the 'id' of the front node without removing.
 */
int peek(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->front->id;
}

// Test the queue with sample code
int main() {
    Queue* q = createQueue();

    enqueue(q, 100);
    enqueue(q, 200);
    enqueue(q, 300);

    printf("Peek front element: %d\n", peek(q));  // Should print 100
    printf("Dequeued: %d\n", dequeue(q));         // Removes 100
    printf("Peek front element: %d\n", peek(q));  // Now 200
    printf("Dequeued: %d\n", dequeue(q));         // Removes 200
    printf("Dequeued: %d\n", dequeue(q));         // Removes 300
    printf("Dequeued from empty queue: %d\n", dequeue(q)); // -1 with message

    return 0;
}

#endif

#if CPP_QUEUE_CODE
#include <iostream>
#include <vector>
using namespace std;

// Array-based Queue Class
class ArrayQueue {
private:
    vector<int> data;
    int front;
    int rear;
    int maxSize;
    int currentSize;

public:
    ArrayQueue(int size = 100) : maxSize(size), front(0), rear(-1), currentSize(0) {
        data.resize(maxSize);
        cout << "Debug: Array queue initialized with size " << maxSize << endl;
    }
    
    bool isEmpty() {
        bool empty = (currentSize == 0);
        cout << "Debug: Queue is " << (empty ? "empty" : "not empty") << endl;
        return empty;
    }
    
    bool isFull() {
        bool full = (currentSize == maxSize);
        cout << "Debug: Queue is " << (full ? "full" : "not full") << endl;
        return full;
    }
    
    void enqueue(int value) {
        cout << "Debug: Enqueuing " << value << endl;
        
        if (isFull()) {
            cout << "Debug: Queue overflow! Cannot enqueue" << endl;
            return;
        }
        
        rear = (rear + 1) % maxSize;
        data[rear] = value;
        currentSize++;
        
        cout << "Debug: Enqueued at position " << rear << ", size now " << currentSize << endl;
    }
    
    int dequeue() {
        cout << "Debug: Dequeuing element" << endl;
        
        if (isEmpty()) {
            cout << "Debug: Queue underflow! Cannot dequeue" << endl;
            return -1;
        }
        
        int value = data[front];
        front = (front + 1) % maxSize;
        currentSize--;
        
        cout << "Debug: Dequeued " << value << ", front now at " << front 
             << ", size = " << currentSize << endl;
        
        return value;
    }
    
    int peek() {
        cout << "Debug: Peeking front element" << endl;
        
        if (isEmpty()) {
            cout << "Debug: Queue is empty, nothing to peek" << endl;
            return -1;
        }
        
        cout << "Debug: Front element is " << data[front] << endl;
        return data[front];
    }
    
    void display() {
        cout << "Array Queue: [";
        
        if (currentSize == 0) {
            cout << "empty]" << endl;
            return;
        }
        
        for (int i = 0; i < currentSize; i++) {
            int index = (front + i) % maxSize;
            cout << data[index];
            if (i < currentSize - 1) cout << ", ";
        }
        
        cout << "] (front=" << front << ", rear=" << rear 
             << ", size=" << currentSize << ")" << endl;
    }
    
    int size() { return currentSize; }
};

// Linked List-based Queue Class
class LinkedQueue {
private:
    struct Node {
        int data;
        Node* next;
        
        Node(int val) : data(val), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    int currentSize;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), currentSize(0) {
        cout << "Debug: Linked queue initialized" << endl;
    }
    
    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    bool isEmpty() {
        bool empty = (front == nullptr);
        cout << "Debug: Linked queue is " << (empty ? "empty" : "not empty") << endl;
        return empty;
    }
    
    void enqueue(int value) {
        cout << "Debug: Enqueuing " << value << " to linked queue" << endl;
        
        Node* newNode = new Node(value);
        
        if (rear == nullptr) {
            cout << "Debug: Queue empty, new node becomes front and rear" << endl;
            front = rear = newNode;
        } else {
            cout << "Debug: Adding to rear" << endl;
            rear->next = newNode;
            rear = newNode;
        }
        
        currentSize++;
        cout << "Debug: Enqueued successfully, size now " << currentSize << endl;
    }
    
    int dequeue() {
        cout << "Debug: Dequeuing from linked queue" << endl;
        
        if (isEmpty()) {
            cout << "Debug: Queue is empty, cannot dequeue" << endl;
            return -1;
        }
        
        Node* temp = front;
        int value = temp->data;
        
        front = front->next;
        
        if (front == nullptr) {
            cout << "Debug: Queue becomes empty" << endl;
            rear = nullptr;
        }
        
        delete temp;
        currentSize--;
        
        cout << "Debug: Dequeued " << value << ", size now " << currentSize << endl;
        return value;
    }
    
    int peek() {
        cout << "Debug: Peeking linked queue front" << endl;
        
        if (isEmpty()) {
            cout << "Debug: Queue is empty" << endl;
            return -1;
        }
        
        cout << "Debug: Front element is " << front->data << endl;
        return front->data;
    }
    
    void display() {
        cout << "Linked Queue: [";
        
        if (front == nullptr) {
            cout << "empty]" << endl;
            return;
        }
        
        Node* current = front;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << ", ";
            current = current->next;
        }
        
        cout << "] (size=" << currentSize << ")" << endl;
    }
    
    int size() { return currentSize; }
};

void queue_cpp_main() {
    cout << "=== QUEUE OPERATIONS (C++) ===" << endl << endl;
    
    // Array-based queue demo
    cout << "--- ARRAY-BASED QUEUE ---" << endl;
    ArrayQueue arrayQueue(5);  // Small size for demo
    
    // Enqueue operations
    arrayQueue.enqueue(10);
    arrayQueue.display();
    
    arrayQueue.enqueue(20);
    arrayQueue.display();
    
    arrayQueue.enqueue(30);
    arrayQueue.display();
    
    // Peek
    cout << "Front element: " << arrayQueue.peek() << endl;
    
    // Dequeue operations
    cout << "Dequeued: " << arrayQueue.dequeue() << endl;
    arrayQueue.display();
    
    // Linked queue demo
    cout << "\n--- LINKED QUEUE ---" << endl;
    LinkedQueue linkedQueue;
    
    linkedQueue.enqueue(100);
    linkedQueue.display();
    
    linkedQueue.enqueue(200);
    linkedQueue.display();
    
    linkedQueue.enqueue(300);
    linkedQueue.display();
    
    cout << "Front element: " << linkedQueue.peek() << endl;
    
    cout << "Dequeued: " << linkedQueue.dequeue() << endl;
    linkedQueue.display();
    
    cout << "Dequeued: " << linkedQueue.dequeue() << endl;
    linkedQueue.display();
}
#endif

// ============================================================================
// MAIN FUNCTION TO RUN ALL DEMOS
// ============================================================================

int main() {
    printf("CAPGEMINI DATA STRUCTURES PREPARATION\n");
    printf("=====================================\n\n");
    
    #if C_BST_CODE
    bst_main();
    printf("\n");
    #endif
    
    #if CPP_BST_CODE
    bst_cpp_main();
    printf("\n");
    #endif
    
    #if C_LIST_CODE
    linkedlist_main();
    printf("\n");
    #endif
    
    #if CPP_LIST_CODE
    linkedlist_cpp_main();
    printf("\n");
    #endif
    
    #if C_QUEUE_CODE
    queue_main();
    printf("\n");
    #endif
    
    #if CPP_QUEUE_CODE
    queue_cpp_main();
    #endif
    
    return 0;
}
```

## Instructions for Use:

1. **To enable C code for BST**: Set `C_BST_CODE` to `1`
2. **To enable C++ code for BST**: Set `CPP_BST_CODE` to `1`
3. **To enable C code for Linked List**: Set `C_LIST_CODE` to `1`
4. **To enable C++ code for Linked List**: Set `CPP_LIST_CODE` to `1`
5. **To enable C code for Queue**: Set `C_QUEUE_CODE` to `1`
6. **To enable C++ code for Queue**: Set `CPP_QUEUE_CODE` to `1`

## Compilation Instructions:

**For C code:**
```bash
gcc -o program trees_lists.c
./program
```

**For C++ code:**
```bash
g++ -o program trees_lists.cpp
./program
```

## Key Interview Topics Covered:

### **Binary Search Tree:**
- Insert, Search, Delete operations
- Tree traversals (Inorder, Preorder, Postorder)
- Height calculation
- Find minimum/maximum
- BST validation

### **Linked List:**
- Insert at beginning/end/position
- Delete by value/position
- Search operations
- Reverse linked list
- Find middle element (slow-fast pointers)
- Cycle detection (Floyd's algorithm)
- Length calculation

### **Queue:**
- Array-based implementation (circular queue)
- Linked list-based implementation
- Enqueue/Dequeue operations
- Peek/Front operations
- Empty/Full checks
- Display functionality

## Important Concepts for Interview:

1. **Time Complexity Analysis** - Know Big O for each operation
2. **Space Complexity** - Understand memory usage
3. **Edge Cases** - Empty structures, single elements, boundary conditions
4. **Algorithm Variations** - Different approaches for same problem
5. **Memory Management** - Proper allocation/deallocation in C

Each implementation includes extensive debug logging to help you understand the step-by-step execution. **Practice explaining the logic and tracing through the code during mock interviews!** 🚀
