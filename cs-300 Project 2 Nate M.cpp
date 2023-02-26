
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//defines how course is held
struct Course {
    string courseId;
    string courseName;
    vector<string> preRequisite;
};

//structure for the binary tree
struct Node {
    Course course;
    Node* left;
    Node* right;
   
    //constructor
    Node() { 
        left = nullptr;
        right = nullptr;
    }
    //initialize course
    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }

};

//defines a class that contains data
//implementing binary search tree
class BinarySearchTree {

private:

    void Destruct(Node* node);

public:
    Node* root;
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(BinarySearchTree* tree, Node* node);
    void Search(string courseId);
    void PrintCourse(Node* node);
};

//constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
};

//destructor
BinarySearchTree::~BinarySearchTree() {
    Destruct(root);
};

//destructs left and right nodes then deletes them
void BinarySearchTree::Destruct(Node* node) {
    if (node != nullptr) {
        Destruct(node->left);
        node->left = nullptr;
        Destruct(node->right);
        node->right = nullptr;
        delete node;
    }
};



//Menu Display
void DisplayMenu() {
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl << endl;
    cout << "What would you like to do?: ";
}




//search for a course
void BinarySearchTree::Search(string courseId) {
    Node* currentNode = root;

    while (currentNode != nullptr) {
        if (currentNode->course.courseId == courseId) {
            //prints the course id and name
            cout << currentNode->course.courseId << ", ";
            cout << currentNode->course.courseName;
            cout << endl;
            cout << "Prerequisites: ";
            //prints any and all pre reqs
            for (string preRequisite : currentNode->course.preRequisite) {
                if (preRequisite == currentNode->course.preRequisite.back()) {

                    cout << preRequisite << endl;
                }
                else {
                    cout << preRequisite << ", ";
                }
            }

            return;
        }
        //searches left 
        else if (courseId < currentNode->course.courseId) {

            if (currentNode->left != nullptr) {
                currentNode = currentNode->left;
            }
        }
        //searches right 
        else {

            currentNode = currentNode->right;
        }
    }
    //if the course is not in the list
    cout << "Course " << courseId << "not found. " << endl;
    return;
}

//inserts course into the course list
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {

    if (tree->root == nullptr) {
        tree->root = node;
    }
    else {
        Node* curr = tree->root;
        while (curr != nullptr) {

            if (node->course.courseId < curr->course.courseId) {
                if (curr->left == nullptr) {
                    curr->left = node;
                    curr = nullptr;
                }
                else {
                    curr = curr->left;
                }
            }
            else {

                if (curr->right == nullptr) {
                    curr->right = node;
                    curr = nullptr;
                }
                else {
                    curr = curr->right;
                }
            }

        }

    }
}
//prints the course list
void BinarySearchTree::PrintCourse(Node* node) {

    //searches and prints the entire tree
    if (node == nullptr) {
        return;
    }

    //looks at left nodes then prints course id, course name
    PrintCourse(node->left);
    cout << node->course.courseId << ", ";
    cout << node->course.courseName << endl;
    PrintCourse(node->right);
};

//loads file and creates course list
void loadCourse(string filename, BinarySearchTree* bst) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "File loaded." << endl;

        int num;
        string line;
        string word;

        while (getline(file, line)) {

            num = 0;
            Node* node = new Node();
            stringstream str(line);

            while (num < 2) {
                getline(str, word, ',');
                if (num == 0) {
                    node->course.courseId = word;
                }
                else {
                    node->course.courseName = word;
                }
                num++;
            }
            while (getline(str, word, ',')) {
                node->course.preRequisite.push_back(word);
            }

            //inserts node into bst
            bst->Insert(bst, node);
        }
    }
    //if file not found
    else {
        cout << "error, please try again. " << endl;
        return;
    }

}

void main() {

    BinarySearchTree* bst = new BinarySearchTree();

    string fileChoice;
    string courseChoice;

    int userInput = 0;

    cout << "Welcome to this course planner." << endl << endl;
    //main while loop to keep program open while choice is not 9
    while (userInput != 9) {
        DisplayMenu();
        cin >> userInput;

        switch (userInput) {
            //loads file that user chooses
        case 1:
            cout << endl;
            cout << "Enter the file you wish to open ";
            cin >> fileChoice;

            loadCourse(fileChoice, bst);
            cout << endl;
            break;

            //prints courses in alphanumeric order
        case 2:
            cout << endl;
            cout << "******************************************" << endl;
            cout << "COURSE ID |     COURSE NAME" << endl;
            cout << "******************************************" << endl;
            //prints course starting at root   	
            bst->PrintCourse(bst->root);
            cout << endl;
            break;

            //prints course that users choice and any prerequisites
        case 3:
            cout << endl;
            cout << "What course do you want to know more about? ";
            cin >> courseChoice;
            cout << endl;

            std::transform(courseChoice.begin(), courseChoice.end(), courseChoice.begin(), ::toupper);
            bst->Search(courseChoice);

            cout << endl;
            break;

            //exits the program
        case 9:
            cout << "Thank you for your time." << endl;
            break;

            //default message if one of the above choices is not valid
        default:
            cout << userInput << " Invalid Choice" << endl << endl;
            break;
        }
    }
}