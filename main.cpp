#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct book {
    int id;
    string name;
    int books_quantity;
    int borrowed_books;
    vector<string> borrowers; // Vector to store names of users who borrowed this book

};

bool cmp_book_by_name(const book &a, const book &b) {
    return a.name < b.name;
}

bool cmp_book_by_id(const book &a, const book &b) {
    return a.id < b.id;
}

book books[MAX_BOOKS];
int booknumbers = 0;

bool addbook() {
    if (booknumbers >= MAX_BOOKS) {
        cout << "Library is full" << endl;
        return false;
    }

    book b;
    cout << "Enter book info: id, name, total quantity" << endl;
    cin >> b.id >> b.name >> b.books_quantity;

    // Initialize borrowed_books to 0 for the newly added book
    b.borrowed_books = 0;

    books[booknumbers++] = b;

    cout << "Book added successfully." << endl;
    return true;
}

bool isprefix(const book &b, const string &prefix) {
    if (prefix.size() > b.name.size()) {
        return false;
    }
    for (int i = 0; i < (int) prefix.size(); ++i) {
        if (prefix[i] != b.name[i]) {
            return false;
        }
    }
    return true;
}

void list_books_by_name() {
    sort(books, books + booknumbers, cmp_book_by_name);
    for (int i = 0; i < booknumbers; ++i) {
        cout << "ID: " << books[i].id << ", Name: " << books[i].name
             << ", Quantity: " << books[i].books_quantity
             << ", Borrowed: " << books[i].borrowed_books << endl;
    }
}

void list_books_by_id() {
    sort(books, books + booknumbers, cmp_book_by_id);
    for (int i = 0; i < booknumbers; ++i) {
        cout << "ID: " << books[i].id << ", Name: " << books[i].name
             << ", Quantity: " << books[i].books_quantity
             << ", Borrowed: " << books[i].borrowed_books << endl;
    }
}

struct user {
    int national_id;
    string name;
};

user users[MAX_USERS];
int usernumbers = 0;

bool add_user() {
    if (usernumbers >= MAX_USERS) {
        cout << "Users list is full" << endl;
        return false;
    }
    user u;
    cout << "Enter user name & national id" << endl;
    cin >> u.name >> u.national_id;

    users[usernumbers++] = u;

    cout << "User added successfully." << endl;
    return true;
}

bool user_borrow_book() {
    string user_name, book_name;
    cout << "Enter user name and book name" << endl;
    cin >> user_name >> book_name;

    for (int i = 0; i < booknumbers; ++i) {
        if (books[i].name == book_name && books[i].borrowed_books < books[i].books_quantity) {
            for (int j = 0; j < usernumbers; ++j) {
                if (users[j].name == user_name) {
                    books[i].borrowed_books++;
                    books[i].borrowers.push_back(user_name); // Record user who borrowed this book
                    cout << "Book '" << book_name << "' borrowed by '" << user_name << "' successfully." << endl;
                    return true;
                }
            }
            cout << "User '" << user_name << "' not found." << endl;
            return false;
        }
    }
    cout << "Book '" << book_name << "' not available or already borrowed to max capacity." << endl;
    return false;
}

bool user_return_book() {
    string user_name, book_name;
    cout << "Enter user name and book name to return" << endl;
    cin >> user_name >> book_name;

    for (int i = 0; i < booknumbers; ++i) {
        if (books[i].name == book_name && books[i].borrowed_books > 0) {
            for (int j = 0; j < usernumbers; ++j) {
                if (users[j].name == user_name) {
                    books[i].borrowed_books--;
                    cout << "Book '" << book_name << "' returned by '" << user_name << "' successfully." << endl;
                    return true;
                }
            }
            cout << "User '" << user_name << "' not found." << endl;
            return false;
        }
    }
    cout << "Book '" << book_name << "' not borrowed or already returned." << endl;
    return false;
}

void list_users_borrowed_book(const string &book_name) {
    bool found = false;
    for (int i = 0; i < booknumbers; ++i) {
        if (books[i].name == book_name) {
            found = true;
            if (books[i].borrowers.empty()) {
                cout << "No users have borrowed the book '" << book_name << "'." << endl;
            } else {
                cout << "Users who borrowed the book '" << book_name << "':" << endl;
                for (const auto &user : books[i].borrowers) {
                    cout << user << endl;
                }
            }
            break;
        }
    }
    if (!found) {
        cout << "Book '" << book_name << "' not found in the library." << endl;
    }
}

void print_users_with_borrowed_books() {
    for (int i = 0; i < usernumbers; ++i) {
        cout << "User " << users[i].name << " " << users[i].national_id << " borrowed book ids: ";
        bool first = true;
        for (int j = 0; j < booknumbers; ++j) {
            if (books[j].borrowed_books > 0) {
                for (const auto &borrower : books[j].borrowers) {
                    if (borrower == users[i].name) {
                        if (!first) {
                            cout << ", ";
                        }
                        cout << books[j].id;
                        first = false;
                    }
                }
            }
        }
        cout << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout<<"Library menu:"<<endl;
        cout << "1. Add a book" << endl;
        cout << "2. List all books by name" << endl;
        cout << "3. List all books by ID" << endl;
        cout << "4. Add a user" << endl;
        cout << "5. Borrow a book" << endl;
        cout << "6. Return a book" << endl;
        cout << "7. List users who borrowed a specific book" << endl;
        cout << "8. Print all users with borrowed books" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addbook();
                break;
            case 2:
                list_books_by_name();
                break;
            case 3:
                list_books_by_id();
                break;
            case 4:
                add_user();
                break;
            case 5:
                user_borrow_book();
                break;
            case 6:
                user_return_book();
                break;
            case 7: {
                string book_name;
                cout << "Enter book name: ";
                cin >> book_name;
                list_users_borrowed_book(book_name);
                break;
            }
            case 8:
                print_users_with_borrowed_books();
                break;
            case 9:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
        }

    }

    return 0;
}
