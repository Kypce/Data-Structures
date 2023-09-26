/** BINARY TREE INFORMATION
 * Space Complexity: O(n)
 * 
 * Time Complexity . . .
 *      Insert: O(n)
 *      Delete: O(n)
 *      Access: O(n)
 *      Search: O(n)
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Contains information on person's social security number, birth date (YYYYMMDD), first name, last name, and zip code
struct person {
    int ssn, bdate;
    string fname, lname;
    int zip;

    person(int s, int bd, string fn, string ln, int z) {
        ssn = s;
        bdate = bd;
        fname = fn;
        lname = ln;
        zip = z;
    }

    // Generic print function to print raw data of "person"
    void printPerson() {
        cout << ssn << " " << bdate << " " << fname << " " << lname << " " << zip << "\n";
    }

    // Detailed print function that gives labels with the data of the "person"
    void printPersonDetailed() {
        cout << "SSN: " << ssn << "\nBirth Date: " << bdate << "\nFirst Name: " << fname << "\nLast Name: " << lname 
            << "\nZip Code: " << zip << "\n";
    }
};

class Tree {
    protected:
        struct node {
            person *data;
            node *left, *right;

            node(person *p) {
                data = p;
                left = NULL;
                right = NULL;
            }
        };

        node *root;

    public:
        Tree() {
            root = NULL;
        }

        // Adds new node into tree ordered by last name
        void addNode(person *p, node *&T) {
            if(T == NULL)
                T = new node(p);
            else if(p->lname == T->data->lname) {
                if(p->fname < T->data->fname)
                    addNode(p, T->left);
                else
                    addNode(p, T->right);
            } else if(p->lname < T->data->lname)
                addNode(p, T->left);
            else
                addNode(p, T->right);
        }
        void addNode(person *p) {
            addNode(p, root);
        }

        // Finds person by first + last name 
        void findByName(string fname, string lname, node *T) {
            if(T == NULL)
                return;
            else if(lname == T->data->lname) {
                if(fname == T->data->fname)
                    T->data->printPersonDetailed();
                else if(fname < T->data->fname)
                    return findByName(fname, lname, T->left);
                else
                    return findByName(fname, lname, T->right);
            } else if(lname < T->data->lname)
                return findByName(fname, lname, T->left);
            else
                return findByName(fname, lname, T->right);
        }
        void findByName(string fname, string lname) {
            findByName(fname, lname, root);
        }

        // Finds person by zip code
        void findByZip(int zip, node *T) {
            if(T == NULL)
                return;
            else if(zip == T->data->zip)
                T->data->printPersonDetailed();
            else {
                findByZip(zip, T->left);
                findByZip(zip, T->right);
                return;
            }
        }
        void findByZip(int zip) {
            findByZip(zip, root);
        }

        // Finds the oldest person in tree
        node *findOldest(node *T) {
            if(T == NULL)
                return T;
            else {
                node *oldest = T;
                node *oldestL = findOldest(T->left);

                if(oldestL != NULL) {
                        if(oldest->data->bdate > oldestL->data->bdate)
                            oldest = oldestL;
                }

                node *oldestR = findOldest(T->right);
                if(oldestR != NULL) {
                    if(oldest->data->bdate > oldestR->data->bdate)
                        oldest = oldestR;
                }

                return oldest;
            }
        }
        void findOldest() {
            node *tmp = findOldest(root);
            tmp->data->printPersonDetailed();
        }

        // Prints all the nodes in tree
        void printAll(node *T) {
            if(T == NULL)
                return;
            printAll(T->left);
            T->data->printPerson();
            printAll(T->right);
        }
        void printAll() {
            printAll(root);
        }

        //TODO
        // Deletes a given person
        void deletePerson(string fname, string lname, node *T) {

        }
        void deletePerson(string fname, string lname) {
            deletePerson(fname ,lname, root);
        }
};

// Takes an input file and will read and input contents into linked list
void readToTree(string file, Tree &T) {
    ifstream fin;
    string line;
    fin.open(file);

    if(fin.fail()) {
        printf("Error opening file \"%s\"", file);
        exit(1);
    }

    while(!fin.eof()) {
        int tmp_ssn, tmp_bdate;
        string tmp_fname, tmp_lname;
        int tmp_zip;

        if(fin.fail())
            break;

        fin >> tmp_ssn >> tmp_bdate >> tmp_fname >> tmp_lname >> tmp_zip;

        person *p = new person(tmp_ssn, tmp_bdate, tmp_fname, tmp_lname, tmp_zip);

        //p->printPerson();

        T.addNode(p);
    }

    fin.close();
}

int main() {
    Tree BT;
    string fileName = "People.txt";
    
    int choice = -1;
    int numInput;
    char charInput;
    string stringInput;
    string stringInput2;

    int tmp_ssn, tmp_bdate;
    string tmp_fname, tmp_lname;
    int tmp_zip;
    person *tmp;

    readToTree(fileName, BT);

    printf("Welcome to this interactive employee finder service\n\n");

    while(choice != 0) {
        printf("Please type the number value of one of the following commands . . .\n");
        printf("1: Find by name\n");
        printf("2: Find by zip code\n");
        printf("3: Find the oldest\n");
        printf("4: Print all\n");
        printf("5: Add a user\n");
        //printf("6: Delete user\n");
        printf("0: Exit\n");

        cin >> choice;

        switch(choice) {
            // Search by name
            case 1:
                printf("Please enter first name: ");
                cin >> stringInput;

                printf("Please enter last name: ");
                cin >> stringInput2;

                cout << "\nSearching for all people with name \"" << stringInput << " " << stringInput2 << "\". . .\n\n";
                BT.findByName(stringInput, stringInput2);

                cout << "\n";
                
                break;

            // Search by zip code
            case 2:
                printf("Please enter the 5-digit zip code you would like to search for: ");
                cin >> numInput;
                cout << "\nSearching for all people with zip code \"" << numInput << "\". . .\n\n";

                BT.findByZip(numInput);
                printf("\n");

                break;

            // Find the oldest
            case 3:
                cout << "\nFinding the oldest person in the linked list. . .\n\n";

                BT.findOldest();

                cout << "\n";

                break;

            // Print all persons
            case 4:
                BT.printAll();

                break;

            // Adding a person
            case 5:
                printf("Please type the person's 9 digit SSN number: ");
                cin >> tmp_ssn;
                printf("Please type the person's birth date (format = YYYYMMDD): ");
                cin >> tmp_bdate;
                printf("Please type the person's first name: ");
                cin >> tmp_fname;
                printf("Please type the person's last name: ");
                cin >> tmp_lname;
                printf("Please type the person's 5 digit zip code: ");
                cin >> tmp_zip;

                tmp = new person(tmp_ssn, tmp_bdate, tmp_fname, tmp_lname, tmp_zip);
                BT.addNode(tmp);

                printf("\n");
                break;

            /*// Deletes given person
            case 6:
                printf("To delete, please enter the person's first name and last name when prompted. . .\n");
                printf("First Name: ");
                cin >> stringInput;

                printf("Last Name: ");
                cin >> stringInput2;

                cout << "\nAre you sure you want to delete the person \"" << stringInput << " " << stringInput2 << "\"?\n";
                printf("Type Y for yes or N for no\n");
                cin >> charInput;

                if(charInput == 'Y') {
                    cout << "Attempting to delete \"" << stringInput << " " << stringInput2 << "\". . .\n\n";
                    BT.deletePerson(stringInput, stringInput2);
                } else
                    cout << "Action aborted\n";

                break;
            */
            // Exit
            case 0:
                printf("Thank you for using this service :D\n");
                break;
            
            default:
                printf("Invalid entry given, please try again!\n");
                break;
        }
    }

    return 0;
}
