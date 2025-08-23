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

// BST Node structure
struct BST_Node {
    int data;
    struct BST_Node* left;
    struct BST_Node* right;
};

// Create new BST node
struct BST_Node* createBSTNode(int data) {
    struct BST_Node* newNode = (struct BST_Node*)malloc(sizeof(struct BST_Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    printf("Debug: Created new BST node with data %d\n", data);
    return newNode;
}

// Insert into BST
struct BST_Node* insertBST(struct BST_Node* root, int data) {
    printf("Debug: Inserting %d into BST\n", data);
    
    // Base case: empty tree or leaf position found
    if (root == NULL) {
        printf("Debug: Found insertion point, creating new node\n");
        return createBSTNode(data);
    }
    
    // Recursive case: traverse left or right
    if (data < root->data) {
        printf("Debug: %d < %d, going left\n", data, root->data);
        root->left = insertBST(root->left, data);
    }
    else if (data > root->data) {
        printf("Debug: %d > %d, going right\n", data, root->data);
        root->right = insertBST(root->right, data);
    }
    else {
        printf("Debug: %d already exists in BST\n", data);
    }
    
    return root;
}

// Search in BST
struct BST_Node* searchBST(struct BST_Node* root, int key) {
    printf("Debug: Searching for %d\n", key);
    
    // Base case: empty tree or key found
    if (root == NULL) {
        printf("Debug: Reached NULL, key %d not found\n", key);
        return NULL;
    }
    
    if (key == root->data) {
        printf("Debug: Found key %d at current node\n", key);
        return root;
    }
    
    // Recursive search
    if (key < root->data) {
        printf("Debug: %d < %d, searching left subtree\n", key, root->data);
        return searchBST(root->left, key);
    } else {
        printf("Debug: %d > %d, searching right subtree\n", key, root->data);
        return searchBST(root->right, key);
    }
}

// Find minimum node (leftmost node)
struct BST_Node* findMinBST(struct BST_Node* root) {
    if (root == NULL) return NULL;
    
    printf("Debug: Finding minimum, current node = %d\n", root->data);
    
    while (root->left != NULL) {
        root = root->left;
        printf("Debug: Moving left to node = %d\n", root->data);
    }
    
    printf("Debug: Minimum found = %d\n", root->data);
    return root;
}

// Delete from BST
struct BST_Node* deleteBST(struct BST_Node* root, int key) {
    printf("Debug: Deleting %d from BST\n", key);
    
    if (root == NULL) {
        printf("Debug: Key %d not found for deletion\n", key);
        return root;
    }
    
    if (key < root->data) {
        printf("Debug: %d < %d, deleting from left subtree\n", key, root->data);
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->data) {
        printf("Debug: %d > %d, deleting from right subtree\n", key, root->data);
        root->right = deleteBST(root->right, key);
    }
    else {
        printf("Debug: Found node to delete: %d\n", key);
        
        // Node with only one child or no child
        if (root->left == NULL) {
            printf("Debug: Node has no left child, replacing with right child\n");
            struct BST_Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            printf("Debug: Node has no right child, replacing with left child\n");
            struct BST_Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: get inorder successor
        printf("Debug: Node has two children, finding inorder successor\n");
        struct BST_Node* temp = findMinBST(root->right);
        
        // Copy successor's data to this node
        printf("Debug: Replacing %d with successor %d\n", root->data, temp->data);
        root->data = temp->data;
        
        // Delete the successor
        root->right = deleteBST(root->right, temp->data);
    }
    
    return root;
}

// Inorder traversal (Left, Root, Right)
void inorderBST(struct BST_Node* root) {
    if (root != NULL) {
        printf("Debug: Visiting left subtree of %d\n", root->data);
        inorderBST(root->left);
        
        printf("%d ", root->data);  // Process current node
        
        printf("Debug: Visiting right subtree of %d\n", root->data);
        inorderBST(root->right);
    }
}

// Preorder traversal (Root, Left, Right)
void preorderBST(struct BST_Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);  // Process current node first
        printf("Debug: Processing node %d, now visiting left\n", root->data);
        preorderBST(root->left);
        
        printf("Debug: Back to %d, now visiting right\n", root->data);
        preorderBST(root->right);
    }
}

// Calculate height of BST
int heightBST(struct BST_Node* root) {
    if (root == NULL) {
        printf("Debug: Reached NULL, height = -1\n");
        return -1;
    }
    
    int leftHeight = heightBST(root->left);
    int rightHeight = heightBST(root->right);
    
    int maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;
    int nodeHeight = 1 + maxHeight;
    
    printf("Debug: Node %d has height %d (left: %d, right: %d)\n", 
           root->data, nodeHeight, leftHeight, rightHeight);
    
    return nodeHeight;
}

// BST Main function
void bst_main() {
    printf("=== BINARY SEARCH TREE OPERATIONS ===\n\n");
    
    struct BST_Node* root = NULL;
    
    // Insert nodes
    printf("--- INSERTION ---\n");
    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 70);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    root = insertBST(root, 60);
    root = insertBST(root, 80);
    
    printf("\n--- TRAVERSALS ---\n");
    printf("Inorder traversal: ");
    inorderBST(root);
    printf("\n");
    
    printf("Preorder traversal: ");
    preorderBST(root);
    printf("\n\n");
    
    // Search operations
    printf("--- SEARCH ---\n");
    struct BST_Node* found = searchBST(root, 40);
    if (found) printf("Found: %d\n", found->data);
    
    found = searchBST(root, 90);
    if (found) printf("Found: %d\n", found->data);
    else printf("90 not found in BST\n");
    
    // Height calculation
    printf("\n--- HEIGHT ---\n");
    int height = heightBST(root);
    printf("BST height: %d\n", height);
    
    // Deletion
    printf("\n--- DELETION ---\n");
    root = deleteBST(root, 20);  // Delete leaf node
    printf("After deleting 20, inorder: ");
    inorderBST(root);
    printf("\n");
    
    root = deleteBST(root, 30);  // Delete node with two children
    printf("After deleting 30, inorder: ");
    inorderBST(root);
    printf("\n");
}
#endif

#if CPP_BST_CODE
#include <iostream>
using namespace std;

class BST {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        
        Node(int val) : data(val), left(nullptr), right(nullptr) {
            cout << "Debug: Created BST node with data " << val << endl;
        }
    };
    
    Node* root;
    
    Node* insert(Node* node, int data) {
        cout << "Debug: Inserting " << data << " into BST" << endl;
        
        if (node == nullptr) {
            cout << "Debug: Found insertion point, creating new node" << endl;
            return new Node(data);
        }
        
        if (data < node->data) {
            cout << "Debug: " << data << " < " << node->data << ", going left" << endl;
            node->left = insert(node->left, data);
        }
        else if (data > node->data) {
            cout << "Debug: " << data << " > " << node->data << ", going right" << endl;
            node->right = insert(node->right, data);
        }
        else {
            cout << "Debug: " << data << " already exists in BST" << endl;
        }
        
        return node;
    }
    
    Node* search(Node* node, int key) {
        cout << "Debug: Searching for " << key << endl;
        
        if (node == nullptr) {
            cout << "Debug: Reached NULL, key " << key << " not found" << endl;
            return nullptr;
        }
        
        if (key == node->data) {
            cout << "Debug: Found key " << key << " at current node" << endl;
            return node;
        }
        
        if (key < node->data) {
            cout << "Debug: " << key << " < " << node->data << ", searching left" << endl;
            return search(node->left, key);
        } else {
            cout << "Debug: " << key << " > " << node->data << ", searching right" << endl;
            return search(node->right, key);
        }
    }
    
    Node* findMin(Node* node) {
        if (node == nullptr) return nullptr;
        
        cout << "Debug: Finding minimum, current node = " << node->data << endl;
        
        while (node->left != nullptr) {
            node = node->left;
            cout << "Debug: Moving left to node = " << node->data << endl;
        }
        
        cout << "Debug: Minimum found = " << node->data << endl;
        return node;
    }
    
    Node* deleteNode(Node* node, int key) {
        cout << "Debug: Deleting " << key << " from BST" << endl;
        
        if (node == nullptr) {
            cout << "Debug: Key " << key << " not found for deletion" << endl;
            return node;
        }
        
        if (key < node->data) {
            cout << "Debug: " << key << " < " << node->data << ", deleting from left" << endl;
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->data) {
            cout << "Debug: " << key << " > " << node->data << ", deleting from right" << endl;
            node->right = deleteNode(node->right, key);
        }
        else {
            cout << "Debug: Found node to delete: " << key << endl;
            
            if (node->left == nullptr) {
                cout << "Debug: Node has no left child" << endl;
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                cout << "Debug: Node has no right child" << endl;
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            cout << "Debug: Node has two children, finding successor" << endl;
            Node* temp = findMin(node->right);
            
            cout << "Debug: Replacing " << node->data << " with " << temp->data << endl;
            node->data = temp->data;
            
            node->right = deleteNode(node->right, temp->data);
        }
        
        return node;
    }
    
    void inorder(Node* node) {
        if (node != nullptr) {
            cout << "Debug: Visiting left subtree of " << node->data << endl;
            inorder(node->left);
            
            cout << node->data << " ";
            
            cout << "Debug: Visiting right subtree of " << node->data << endl;
            inorder(node->right);
        }
    }
    
    int height(Node* node) {
        if (node == nullptr) {
            cout << "Debug: Reached NULL, height = -1" << endl;
            return -1;
        }
        
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        int nodeHeight = 1 + max(leftHeight, rightHeight);
        
        cout << "Debug: Node " << node->data << " has height " << nodeHeight 
             << " (left: " << leftHeight << ", right: " << rightHeight << ")" << endl;
        
        return nodeHeight;
    }

public:
    BST() : root(nullptr) {}
    
    void insert(int data) { root = insert(root, data); }
    bool search(int key) { return search(root, key) != nullptr; }
    void remove(int key) { root = deleteNode(root, key); }
    void displayInorder() { inorder(root); }
    int getHeight() { return height(root); }
};

void bst_cpp_main() {
    cout << "=== BINARY SEARCH TREE OPERATIONS (C++) ===" << endl << endl;
    
    BST bst;
    
    cout << "--- INSERTION ---" << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    
    cout << "\n--- TRAVERSAL ---" << endl;
    cout << "Inorder: ";
    bst.displayInorder();
    cout << endl;
    
    cout << "\n--- SEARCH ---" << endl;
    cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (bst.search(90) ? "Found" : "Not Found") << endl;
    
    cout << "\n--- HEIGHT ---" << endl;
    cout << "BST Height: " << bst.getHeight() << endl;
    
    cout << "\n--- DELETION ---" << endl;
    bst.remove(30);
    cout << "After deleting 30: ";
    bst.displayInorder();
    cout << endl;
}
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

// Linked List Node structure
struct ListNode {
    int data;
    struct ListNode* next;
};

// Create new node
struct ListNode* createListNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    printf("Debug: Created new node with data %d\n", data);
    return newNode;
}

// Insert at beginning
struct ListNode* insertAtBeginning(struct ListNode* head, int data) {
    printf("Debug: Inserting %d at beginning\n", data);
    
    struct ListNode* newNode = createListNode(data);
    newNode->next = head;
    
    printf("Debug: New node points to old head, new node becomes head\n");
    return newNode;  // New head
}

// Insert at end
struct ListNode* insertAtEnd(struct ListNode* head, int data) {
    printf("Debug: Inserting %d at end\n", data);
    
    struct ListNode* newNode = createListNode(data);
    
    if (head == NULL) {
        printf("Debug: List is empty, new node becomes head\n");
        return newNode;
    }
    
    // Traverse to end
    struct ListNode* current = head;
    while (current->next != NULL) {
        printf("Debug: Traversing, current node = %d\n", current->data);
        current = current->next;
    }
    
    printf("Debug: Reached end at node %d, linking new node\n", current->data);
    current->next = newNode;
    
    return head;
}

// Insert at specific position (0-indexed)
struct ListNode* insertAtPosition(struct ListNode* head, int data, int position) {
    printf("Debug: Inserting %d at position %d\n", data, position);
    
    if (position == 0) {
        return insertAtBeginning(head, data);
    }
    
    struct ListNode* newNode = createListNode(data);
    struct ListNode* current = head;
    
    // Traverse to position-1
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        printf("Debug: Traversing to position, current = %d\n", current->data);
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Debug: Position out of bounds\n");
        free(newNode);
        return head;
    }
    
    printf("Debug: Inserting after node %d\n", current->data);
    newNode->next = current->next;
    current->next = newNode;
    
    return head;
}

// Delete node with specific value
struct ListNode* deleteByValue(struct ListNode* head, int value) {
    printf("Debug: Deleting node with value %d\n", value);
    
    if (head == NULL) {
        printf("Debug: List is empty\n");
        return head;
    }
    
    // If head node contains the value
    if (head->data == value) {
        printf("Debug: Head node contains value, removing head\n");
        struct ListNode* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    
    // Search for node to delete
    struct ListNode* current = head;
    while (current->next != NULL && current->next->data != value) {
        printf("Debug: Searching, current = %d, next = %d\n", 
               current->data, current->next->data);
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("Debug: Value %d not found in list\n", value);
        return head;
    }
    
    printf("Debug: Found node to delete after %d\n", current->data);
    struct ListNode* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    free(nodeToDelete);
    
    return head;
}

// Search for value
struct ListNode* searchList(struct ListNode* head, int value) {
    printf("Debug: Searching for value %d\n", value);
    
    struct ListNode* current = head;
    int position = 0;
    
    while (current != NULL) {
        printf("Debug: Checking position %d, value = %d\n", position, current->data);
        
        if (current->data == value) {
            printf("Debug: Found value %d at position %d\n", value, position);
            return current;
        }
        
        current = current->next;
        position++;
    }
    
    printf("Debug: Value %d not found\n", value);
    return NULL;
}

// Reverse linked list
struct ListNode* reverseList(struct ListNode* head) {
    printf("Debug: Reversing linked list\n");
    
    struct ListNode* prev = NULL;
    struct ListNode* current = head;
    struct ListNode* next = NULL;
    
    while (current != NULL) {
        printf("Debug: Current = %d, reversing link\n", 
               current ? current->data : -1);
        
        next = current->next;    // Store next
        current->next = prev;    // Reverse current link
        prev = current;          // Move pointers one position ahead
        current = next;
    }
    
    printf("Debug: Reversal complete, new head = %d\n", 
           prev ? prev->data : -1);
    return prev;  // New head
}

// Find middle element (slow-fast pointer technique)
struct ListNode* findMiddle(struct ListNode* head) {
    printf("Debug: Finding middle element using slow-fast pointers\n");
    
    if (head == NULL) return NULL;
    
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        printf("Debug: Slow at %d, Fast at %d\n", slow->data, fast->data);
        slow = slow->next;        // Move slow by 1
        fast = fast->next->next;  // Move fast by 2
    }
    
    printf("Debug: Middle element found: %d\n", slow->data);
    return slow;
}

// Detect cycle in linked list
int hasCycle(struct ListNode* head) {
    printf("Debug: Checking for cycle using Floyd's algorithm\n");
    
    if (head == NULL || head->next == NULL) return 0;
    
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        printf("Debug: Slow at %d, Fast at %d\n", slow->data, fast->data);
        
        if (slow == fast) {
            printf("Debug: Cycle detected!\n");
            return 1;
        }
    }
    
    printf("Debug: No cycle found\n");
    return 0;
}

// Display linked list
void displayList(struct ListNode* head) {
    printf("List: ");
    struct ListNode* current = head;
    
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(" -> ");
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Get list length
int getLength(struct ListNode* head) {
    int length = 0;
    struct ListNode* current = head;
    
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    printf("Debug: List length = %d\n", length);
    return length;
}

// Linked List Main function
void linkedlist_main() {
    printf("=== LINKED LIST OPERATIONS ===\n\n");
    
    struct ListNode* head = NULL;
    
    // Insert operations
    printf("--- INSERTION ---\n");
    head = insertAtBeginning(head, 10);
    displayList(head);
    
    head = insertAtBeginning(head, 5);
    displayList(head);
    
    head = insertAtEnd(head, 20);
    displayList(head);
    
    head = insertAtEnd(head, 30);
    displayList(head);
    
    head = insertAtPosition(head, 15, 2);
    displayList(head);
    
    // Search operations
    printf("\n--- SEARCH ---\n");
    struct ListNode* found = searchList(head, 15);
    if (found) printf("Found: %d\n", found->data);
    
    found = searchList(head, 100);
    
    // Find middle
    printf("\n--- FIND MIDDLE ---\n");
    struct ListNode* middle = findMiddle(head);
    if (middle) printf("Middle element: %d\n", middle->data);
    
    // Length
    printf("\n--- LENGTH ---\n");
    int length = getLength(head);
    printf("Length: %d\n", length);
    
    // Reverse
    printf("\n--- REVERSE ---\n");
    printf("Before reverse: ");
    displayList(head);
    head = reverseList(head);
    printf("After reverse: ");
    displayList(head);
    
    // Delete operations
    printf("\n--- DELETION ---\n");
    head = deleteByValue(head, 15);
    printf("After deleting 15: ");
    displayList(head);
    
    head = deleteByValue(head, 30);  // Delete head
    printf("After deleting 30: ");
    displayList(head);
}
#endif

#if CPP_LIST_CODE
#include <iostream>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        
        Node(int val) : data(val), next(nullptr) {
            cout << "Debug: Created node with data " << val << endl;
        }
    };
    
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    
    void insertAtBeginning(int data) {
        cout << "Debug: Inserting " << data << " at beginning" << endl;
        
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        
        cout << "Debug: New node becomes head" << endl;
    }
    
    void insertAtEnd(int data) {
        cout << "Debug: Inserting " << data << " at end" << endl;
        
        Node* newNode = new Node(data);
        
        if (head == nullptr) {
            cout << "Debug: List empty, new node becomes head" << endl;
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr) {
            cout << "Debug: Traversing, current = " << current->data << endl;
            current = current->next;
        }
        
        cout << "Debug: Reached end, linking new node" << endl;
        current->next = newNode;
    }
    
    void deleteByValue(int value) {
        cout << "Debug: Deleting node with value " << value << endl;
        
        if (head == nullptr) {
            cout << "Debug: List is empty" << endl;
            return;
        }
        
        if (head->data == value) {
            cout << "Debug: Deleting head node" << endl;
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            cout << "Debug: Searching, current = " << current->data << endl;
            current = current->next;
        }
        
        if (current->next == nullptr) {
            cout << "Debug: Value " << value << " not found" << endl;
            return;
        }
        
        cout << "Debug: Found node to delete" << endl;
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
    }
    
    bool search(int value) {
        cout << "Debug: Searching for " << value << endl;
        
        Node* current = head;
        int position = 0;
        
        while (current != nullptr) {
            cout << "Debug: Position " << position << ", value = " << current->data << endl;
            
            if (current->data == value) {
                cout << "Debug: Found at position " << position << endl;
                return true;
            }
            
            current = current->next;
            position++;
        }
        
        cout << "Debug: Value not found" << endl;
        return false;
    }
    
    void reverse() {
        cout << "Debug: Reversing linked list" << endl;
        
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        
        while (current != nullptr) {
            cout << "Debug: Reversing node " << current->data << endl;
            
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
        cout << "Debug: Reversal complete" << endl;
    }
    
    Node* findMiddle() {
        cout << "Debug: Finding middle using slow-fast pointers" << endl;
        
        if (head == nullptr) return nullptr;
        
        Node* slow = head;
        Node* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            cout << "Debug: Slow at " << slow->data << ", Fast at " << fast->data << endl;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout << "Debug: Middle found: " << slow->data << endl;
        return slow;
    }
    
    void display() {
        cout << "List: ";
        Node* current = head;
        
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " -> ";
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }
    
    int getLength() {
        int length = 0;
        Node* current = head;
        
        while (current != nullptr) {
            length++;
            current = current->next;
        }
        
        cout << "Debug: List length = " << length << endl;
        return length;
    }
};

void linkedlist_cpp_main() {
    cout << "=== LINKED LIST OPERATIONS (C++) ===" << endl << endl;
    
    LinkedList list;
    
    cout << "--- INSERTION ---" << endl;
    list.insertAtBeginning(10);
    list.display();
    
    list.insertAtEnd(20);
    list.display();
    
    list.insertAtBeginning(5);
    list.display();
    
    cout << "\n--- SEARCH ---" << endl;
    cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (list.search(100) ? "Found" : "Not Found") << endl;
    
    cout << "\n--- MIDDLE ELEMENT ---" << endl;
    auto middle = list.findMiddle();
    if (middle) cout << "Middle: " << middle->data << endl;
    
    cout << "\n--- LENGTH ---" << endl;
    cout << "Length: " << list.getLength() << endl;
    
    cout << "\n--- REVERSE ---" << endl;
    cout << "Before: ";
    list.display();
    list.reverse();
    cout << "After: ";
    list.display();
    
    cout << "\n--- DELETION ---" << endl;
    list.deleteByValue(10);
    list.display();
}
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

#define MAX_SIZE 100

// Array-based Queue
struct ArrayQueue {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
};

// Initialize queue
void initArrayQueue(struct ArrayQueue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    printf("Debug: Array queue initialized\n");
}

// Check if queue is empty
int isArrayQueueEmpty(struct ArrayQueue* queue) {
    int empty = (queue->size == 0);
    printf("Debug: Queue is %s\n", empty ? "empty" : "not empty");
    return empty;
}

// Check if queue is full
int isArrayQueueFull(struct ArrayQueue* queue) {
    int full = (queue->size == MAX_SIZE);
    printf("Debug: Queue is %s\n", full ? "full" : "not full");
    return full;
}

// Enqueue (add element)
void enqueueArray(struct ArrayQueue* queue, int data) {
    printf("Debug: Enqueuing %d\n", data);
    
    if (isArrayQueueFull(queue)) {
        printf("Debug: Queue overflow! Cannot enqueue\n");
        return;
    }
    
    queue->rear = (queue->rear + 1) % MAX_SIZE;  // Circular increment
    queue->data[queue->rear] = data;
    queue->size++;
    
    printf("Debug: Enqueued at position %d, size now %d\n", queue->rear, queue->size);
}

// Dequeue (remove element)
int dequeueArray(struct ArrayQueue* queue) {
    printf("Debug: Dequeuing element\n");
    
    if (isArrayQueueEmpty(queue)) {
        printf("Debug: Queue underflow! Cannot dequeue\n");
        return -1;  // Error value
    }
    
    int data = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;  // Circular increment
    queue->size--;
    
    printf("Debug: Dequeued %d, front now at %d, size = %d\n", 
           data, queue->front, queue->size);
    
    return data;
}

// Peek front element
int peekArrayQueue(struct ArrayQueue* queue) {
    printf("Debug: Peeking front element\n");
    
    if (isArrayQueueEmpty(queue)) {
        printf("Debug: Queue is empty, nothing to peek\n");
        return -1;
    }
    
    int frontData = queue->data[queue->front];
    printf("Debug: Front element is %d\n", frontData);
    return frontData;
}

// Display queue
void displayArrayQueue(struct ArrayQueue* queue) {
    printf("Queue: [");
    
    if (queue->size == 0) {
        printf("empty]\n");
        return;
    }
    
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % MAX_SIZE;
        printf("%d", queue->data[index]);
        if (i < queue->size - 1) printf(", ");
    }
    
    printf("] (front=%d, rear=%d, size=%d)\n", 
           queue->front, queue->rear, queue->size);
}

// Linked List-based Queue
struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct LinkedQueue {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
};

// Initialize linked queue
void initLinkedQueue(struct LinkedQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    printf("Debug: Linked queue initialized\n");
}

// Check if linked queue is empty
int isLinkedQueueEmpty(struct LinkedQueue* queue) {
    int empty = (queue->front == NULL);
    printf("Debug: Linked queue is %s\n", empty ? "empty" : "not empty");
    return empty;
}

// Enqueue in linked queue
void enqueueLinked(struct LinkedQueue* queue, int data) {
    printf("Debug: Enqueuing %d to linked queue\n", data);
    
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        printf("Debug: Queue is empty, new node becomes both front and rear\n");
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        printf("Debug: Adding to rear, linking with previous rear\n");
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    
    queue->size++;
    printf("Debug: Enqueued successfully, size now %d\n", queue->size);
}

// Dequeue from linked queue
int dequeueLinked(struct LinkedQueue* queue) {
    printf("Debug: Dequeuing from linked queue\n");
    
    if (isLinkedQueueEmpty(queue)) {
        printf("Debug: Queue is empty, cannot dequeue\n");
        return -1;
    }
    
    struct QueueNode* temp = queue->front;
    int data = temp->data;
    
    queue->front = queue->front->next;
    
    // If queue becomes empty
    if (queue->front == NULL) {
        printf("Debug: Queue becomes empty after dequeue\n");
        queue->rear = NULL;
    }
    
    free(temp);
    queue->size--;
    
    printf("Debug: Dequeued %d, size now %d\n", data, queue->size);
    return data;
}

// Peek front of linked queue
int peekLinkedQueue(struct LinkedQueue* queue) {
    printf("Debug: Peeking linked queue front\n");
    
    if (isLinkedQueueEmpty(queue)) {
        printf("Debug: Queue is empty\n");
        return -1;
    }
    
    printf("Debug: Front element is %d\n", queue->front->data);
    return queue->front->data;
}

// Display linked queue
void displayLinkedQueue(struct LinkedQueue* queue) {
    printf("Linked Queue: [");
    
    if (queue->front == NULL) {
        printf("empty]\n");
        return;
    }
    
    struct QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }
    
    printf("] (size=%d)\n", queue->size);
}

// Queue Main function
void queue_main() {
    printf("=== QUEUE OPERATIONS ===\n\n");
    
    // Array-based queue demo
    printf("--- ARRAY-BASED QUEUE ---\n");
    struct ArrayQueue arrayQueue;
    initArrayQueue(&arrayQueue);
    
    // Enqueue operations
    enqueueArray(&arrayQueue, 10);
    displayArrayQueue(&arrayQueue);
    
    enqueueArray(&arrayQueue, 20);
    displayArrayQueue(&arrayQueue);
    
    enqueueArray(&arrayQueue, 30);
    displayArrayQueue(&arrayQueue);
    
    // Peek operation
    printf("Front element: %d\n", peekArrayQueue(&arrayQueue));
    
    // Dequeue operations
    printf("Dequeued: %d\n", dequeueArray(&arrayQueue));
    displayArrayQueue(&arrayQueue);
    
    printf("Dequeued: %d\n", dequeueArray(&arrayQueue));
    displayArrayQueue(&arrayQueue);
    
    // Linked list-based queue demo
    printf("\n--- LINKED LIST-BASED QUEUE ---\n");
    struct LinkedQueue linkedQueue;
    initLinkedQueue(&linkedQueue);
    
    // Enqueue operations
    enqueueLinked(&linkedQueue, 100);
    displayLinkedQueue(&linkedQueue);
    
    enqueueLinked(&linkedQueue, 200);
    displayLinkedQueue(&linkedQueue);
    
    enqueueLinked(&linkedQueue, 300);
    displayLinkedQueue(&linkedQueue);
    
    // Peek operation
    printf("Front element: %d\n", peekLinkedQueue(&linkedQueue));
    
    // Dequeue operations
    printf("Dequeued: %d\n", dequeueLinked(&linkedQueue));
    displayLinkedQueue(&linkedQueue);
    
    printf("Dequeued: %d\n", dequeueLinked(&linkedQueue));
    displayLinkedQueue(&linkedQueue);
    
    printf("Dequeued: %d\n", dequeueLinked(&linkedQueue));
    displayLinkedQueue(&linkedQueue);
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