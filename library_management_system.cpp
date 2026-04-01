#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int id, string title, string author, bool issued = false) : id(id), title(title), author(author), issued(issued) {}
};

class Library {
private:
    vector<Book> books;

public:

    void loadFromFile() {
        ifstream file("library.txt");
        if (!file.is_open()) return;

        int id, issued;
        string title, author;

        while (file >> id) {
            file.ignore();
            getline(file, title);
            getline(file, author);
            file >> issued;
            file.ignore();

            books.push_back(Book(id, title, author, issued));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("library.txt");

        for (auto &b : books) {
            file << b.id << endl;
            file << b.title << endl;
            file << b.author << endl;
            file << b.issued << endl;
        }

        file.close();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        saveToFile();
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books available\n";
            return;
        }

        for (auto &b : books) {
            cout << b.id << " | "
                 << b.title << " | "
                 << b.author << " | "
                 << (b.issued ? "Issued" : "Available") << endl;
        }
    }

    void sortById() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.id < b.id;
        });
    }

    int binarySearch(int id) const {
        if (books.empty()) return -1;

        int left = 0, right = books.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (books[mid].id == id) return mid;
            else if (books[mid].id < id) left = mid + 1;
            else right = mid - 1;
        }

        return -1;
    }

    void searchBook() {
        sortById();

        int id;
        cout << "Enter ID: ";
        cin >> id;

        int index = binarySearch(id);

        if (index != -1)
            cout << "Found: " << books[index].title << endl;
        else
            cout << "Not Found\n";
    }

    void searchByPrefix() {
        string prefix;
        cout << "Enter prefix: ";
        cin.ignore();
        getline(cin, prefix);

        bool found = false;

        for (auto &b : books) {
            if (b.title.find(prefix) == 0) {
                cout << b.title << endl;
                found = true;
            }
        }

        if (!found)
            cout << "No match\n";
    }

    void issueBook() {
        sortById();

        int id;
        cout << "Enter ID: ";
        cin >> id;

        int index = binarySearch(id);

        if (index != -1 && !books[index].issued) {
            books[index].issued = true;
            saveToFile();
            cout << "Issued\n";
        } else {
            cout << "Not Available\n";
        }
    }

    void returnBook() {
        sortById();

        int id;
        cout << "Enter ID: ";
        cin >> id;

        int index = binarySearch(id);

        if (index != -1 && books[index].issued) {
            books[index].issued = false;
            saveToFile();
            cout << "Returned\n";
        } else {
            cout << "Invalid\n";
        }
    }

    void sortByTitle() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.title < b.title;
        });

        cout << "Sorted by title\n";
    }

    void longestTitle() {
        if (books.empty()) return;

        string res = "";
        size_t maxLen = 0;

        for (auto &b : books) {
            if (b.title.size() > maxLen) {
                maxLen = b.title.size();
                res = b.title;
            }
        }

        cout << "Longest Title: " << res << endl;
    }

    void slidingWindow() {
        int k;
        cout << "Enter window size: ";
        cin >> k;

        if (books.size() < k || k <= 0) {
            cout << "Invalid window size\n";
            return;
        }

        size_t sum = 0;

        for (int i = 0; i < k; i++)
            sum += books[i].title.size();

        size_t maxSum = sum, start = 0;

        for (int i = k; i < books.size(); i++) {
            sum += books[i].title.size();
            sum -= books[i - k].title.size();

            if (sum > maxSum) {
                maxSum = sum;
                start = i - k + 1;
            }
        }

        cout << "Best Window:\n";

        for (size_t i = start; i < start + k; i++)
            cout << books[i].title << " ";

        cout << endl;
    }
};

void menu() {
    cout << "\n===== LIBRARY SYSTEM =====\n";
    cout << "1. Add Book\n";
    cout << "2. Display\n";
    cout << "3. Search by ID\n";
    cout << "4. Prefix Search\n";
    cout << "5. Issue Book\n";
    cout << "6. Return Book\n";
    cout << "7. Sort by Title\n";
    cout << "8. Longest Title\n";
    cout << "9. Sliding Window\n";
    cout << "0. Exit\n";
}

int main() {
    Library lib;
    lib.loadFromFile();

    int choice;

    do {
        menu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.searchByPrefix(); break;
            case 5: lib.issueBook(); break;
            case 6: lib.returnBook(); break;
            case 7: lib.sortByTitle(); break;
            case 8: lib.longestTitle(); break;
            case 9: lib.slidingWindow(); break;
        }

    } while (choice != 0);

    return 0;
}