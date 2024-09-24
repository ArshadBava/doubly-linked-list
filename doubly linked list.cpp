#include <iostream>
using namespace std;

struct Node {
    int data; 
    Node* next; 
    Node* prev; 

    Node(int data) : data(data), next(NULL), prev(NULL) {}
};

void forwardTraversal(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

void backwardTraversal(Node* tail) {
    Node* curr = tail;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << endl;
}

int findLength(Node* head) {
    int count = 0;
    for (Node* cur = head; cur != NULL; cur = cur->next)
        count++;
    return count;
}

Node* insertBegin(Node* head, int data) {
    Node* new_node = new Node(data);
    new_node->next = head;
    if (head != NULL)
        head->prev = new_node;
    return new_node;
}

Node* insertEnd(Node* head, Node*& tail, int new_data) {
    Node* new_node = new Node(new_data);
    if (head == NULL) {
        tail = new_node;  // Update tail if the list is empty
        return new_node;
    } else {
        Node* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
        new_node->prev = curr;
        tail = new_node;  // Update tail to the new node
    }
    return head;
}

Node* insertAtPosition(Node* head, Node*& tail, int pos, int new_data) {
    Node* new_node = new Node(new_data);
    if (pos == 1) {
        new_node->next = head;
        if (head != NULL)
            head->prev = new_node;
        return new_node;
    }
    Node* curr = head;
    for (int i = 1; i < pos - 1 && curr != NULL; ++i) {
        curr = curr->next;
    }
    if (curr == NULL) {
        delete new_node;
        cout << "Position is out of bounds." << endl;
        return head;
    }
    new_node->prev = curr;
    new_node->next = curr->next;
    curr->next = new_node;
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
    if (new_node->next == NULL) // Update tail if new node is the last node
        tail = new_node;
    return head;
}

Node* delHead(Node* head) {
    if (head == NULL)
        return NULL;
    Node* temp = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    delete temp;
    return head;
}

Node* delLast(Node* head, Node*& tail) {
    if (head == NULL)
        return NULL;
    if (head->next == NULL) {
        delete head;
        tail = NULL; // Update tail to NULL when the list is empty
        return NULL;
    }
    Node* curr = tail;
    curr->prev->next = NULL;
    tail = curr->prev; // Update tail to the previous node
    delete curr; 
    return head;
}

Node* delPos(Node* head, Node*& tail, int pos) {
    if (!head)
        return head;
    Node* curr = head;
    for (int i = 1; curr && i < pos; ++i) {
        curr = curr->next;
    }
    if (!curr)
        return head;
    if (curr->prev)
        curr->prev->next = curr->next;
    if (curr->next)
        curr->next->prev = curr->prev;
    if (head == curr)
        head = curr->next;
    if (tail == curr) // Update tail if we're deleting the last node
        tail = curr->prev;
    delete curr;
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    Node* head = NULL;
    Node* tail = NULL; // Pointer for the tail
    int choice, data, pos;

    while (true) {
        cout << "1. Insert at beginning\n"
             << "2. Insert at end\n"
             << "3. Insert at position\n"
             << "4. Delete head\n"
             << "5. Delete last\n"
             << "6. Delete at position\n"
             << "7. Forward traversal\n"
             << "8. Backward traversal\n"
             << "9. Find length\n"
             << "10. Print list\n"
             << "11. Exit\n"
             << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data: ";
                cin >> data;
                head = insertBegin(head, data);
                if (tail == NULL) tail = head; // Update tail if the list was empty
                break;
            case 2:
                cout << "Enter data: ";
                cin >> data;
                head = insertEnd(head, tail, data);
                break;
            case 3:
                cout << "Enter position and data: ";
                cin >> pos >> data;
                head = insertAtPosition(head, tail, pos, data);
                break;
            case 4:
                head = delHead(head);
                if (head == NULL) tail = NULL; // Update tail if the list is empty
                break;
            case 5:
                head = delLast(head, tail);
                break;
            case 6:
                cout << "Enter position: ";
                cin >> pos;
                head = delPos(head, tail, pos);
                break;
            case 7:
                cout << "Forward Traversal: ";
                forwardTraversal(head);
                break;
            case 8:
                cout << "Backward Traversal: ";
                backwardTraversal(tail); // Use tail for backward traversal
                break;
            case 9:
                cout << "Length: " << findLength(head) << endl;
                break;
            case 10:
                cout << "List: ";
                printList(head);
                break;
            case 11:
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }
}

