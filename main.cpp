#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, int value);
void printTree(Node* root, int depth);
void filess(Node*& root, int& size);
Node* remove(Node* root, int value);
Node* getSuccessor(Node* cur); 

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

Node* getSuccessor(Node* cur) {
    cur = cur->right;
    while (cur != nullptr && cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

Node* remove(Node* root, int value) {
    if (root == nullptr){
        return nullptr;
    }
    if (value < root->data) {
        root->left = remove(root->left, value);
    } else if (value > root->data) {
        root->right = remove(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* successor = getSuccessor(root);
            root->data = successor->data;
            root->right = remove(root->right, successor->data);
        }
    }
    return root;
}


void printTree(Node* root, int depth = 0) {
    if (root == nullptr){
       return; 
    } 

    printTree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        cout << "   ";
    }
    cout << root->data << endl;
    printTree(root->left, depth + 1);
}

void filess(Node*& root) {
    ifstream file("numbers.txt");
    int value;
    while (file >> value) {
        if (value >= 1 && value <= 999) {
            root = insert(root, value);
        }
    }
    file.close();
}

int main() {
    Node* root = nullptr;
    int choice;

    cout << "Choose:" << endl;
    cout << "1 for file input" << endl;
    cout << "2 for manual input" << endl;
    cin >> choice;

    if (choice == 1) {
        filess(root);
    } else if (choice == 2) {
        cout << "Enter numbers and type done to finish it" << endl;
        while (true) {
            char input[10];
            cin >> input;
            if (strcmp(input, "done") == 0){
               break; 
            } 
            int value = atoi(input);
            if (value >= 1 && value <= 999) {
                root = insert(root, value);
            }
        }
    }

    while (true) {
        cout << " " << endl;
        printTree(root);
        cout << " " << endl;
        cout << "Type I to insert a number" << endl;
        cout << "Type R to remove a number" << endl;
        cout << "Type S to search for a number" << endl;
        cout << "Type Q to quit" << endl;

        int value;
        char input[10];
            cin >> input;
            
        if (strcmp(input, "I") == 0) {
            cout << "Enter number to insert ";
            cin >> value;
            if (value >= 1 && value <= 999) {
                root = insert(root, value);
            }
        } else if (strcmp(input, "R") == 0) {
            cout << "Enter number to remove: ";
            cin >> value;
            root = remove(root, value);
        } else {
            break;
        }
    }

    return 0;
}
