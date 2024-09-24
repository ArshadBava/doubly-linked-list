#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int data) : data(data), next(NULL), prev(NULL) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(NULL), tail(NULL) {}

    void insertBegin(int data) {
        Node* new_node = new Node(data);
        new_node->next = head;
        if (head != NULL)
            head->prev = new_node;
        head = new_node;
        if (tail == NULL) // If list was empty
            tail = head;
    }

    void insertEnd(int data) {
        Node* new_node = new Node(data);
        if (head == NULL) {
            head = new_node;
            tail = new_node;
            return;
        }
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }

    void insertAtPosition(int pos, int data) {
        if (pos < 1) {
            cout << "Position must be 1 or greater." << endl;
            return;
        }
        Node* new_node = new Node(data);
        if (pos == 1) {
            insertBegin(data);
            return;
        }
        Node* curr = head;
        for (int i = 1; curr != NULL && i < pos - 1; i++) {
            curr = curr->next;
        }
        if (curr == NULL) {
            cout << "Position is out of bounds." << endl;
            delete new_node;
            return;
        }
        new_node->next = curr->next;
        new_node->prev = curr;
        if (curr->next != NULL)
            curr->next->prev = new_node;
        curr->next = new_node;
        if (new_node->next == NULL) // If inserted at the end, update tail
            tail = new_node;
    }

    void delHead() {
        if (head == NULL) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        else
            tail = NULL; // If list is empty after deletion
        delete temp;
    }

    void delLast() {
        if (tail == NULL) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail != NULL)
            tail->next = NULL;
        else
            head = NULL; // If list is empty after deletion
        delete temp;
    }

    void delPos(int pos) {
        if (head == NULL || pos < 1) {
            cout << "List is empty or invalid position." << endl;
            return;
        }
        Node* curr = head;
        for (int i = 1; curr != NULL && i < pos; i++) {
            curr = curr->next;
        }
        if (curr == NULL) {
            cout << "Position is out of bounds." << endl;
            return;
        }
        if (curr->prev != NULL)
            curr->prev->next = curr->next;
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
        if (curr == head) // Deleting head
            head = curr->next;
        if (curr == tail) // Deleting tail
            tail = curr->prev;
        delete curr;
    }

    void forwardTraversal() {
        Node* curr = head;
        while (curr != NULL) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void backwardTraversal() {
        Node* curr = tail;
        while (curr != NULL) {
            cout << curr->data << " ";
            curr = curr->prev;
        }
        cout << endl;
    }

    int findLength() {
        int count = 0;
        Node* curr = head;
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void printList() {
        Node* curr = head;
        while (curr != NULL) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head != NULL) {
            delHead();
        }
    }
};

int main() {
    DoublyLinkedList list;
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
                list.insertBegin(data);
                break;
            case 2:
                cout << "Enter data: ";
                cin >> data;
                list.insertEnd(data);
                break;
            case 3:
                cout << "Enter position and data: ";
                cin >> pos >> data;
                list.insertAtPosition(pos, data);
                break;
            case 4:
                list.delHead();
                break;
            case 5:
                list.delLast();
                break;
            case 6:
                cout << "Enter position: ";
                cin >> pos;
                list.delPos(pos);
                break;
            case 7:
                cout << "Forward Traversal: ";
                list.forwardTraversal();
                break;
            case 8:
                cout << "Backward Traversal: ";
                list.backwardTraversal();
                break;
            case 9:
                cout << "Length: " << list.findLength() << endl;
                break;
            case 10:
                cout << "List: ";
                list.printList();
                break;
            case 11:
                return 0;
            default:
                cout << "Invalid option.\n";
        }
    }
}
