#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <cassert>
#include "includes/lib.hpp"


using namespace std;

// A "book" (as an irl-concept) is a Pointer to a book class (here I notate it as Book)
// so it's easier for the user to understand
typedef book* Book;

int nmax;
int l;
int k1, k2;

const  int n_of_book_titles = 5;
const int n_of_book_authors = 5;

const string book_titles[n_of_book_titles] {
    "Vector Calculus",
    "Intro to probability",
    "Intro to OOP",
    "Intro to signals and systems",
    "Discrete Mathematics"
};

const string book_authors[n_of_book_authors] {
    "Tromba",
    "Rosen",
    "Haralabidis",
    "Koulouptsidis",
    "Orsen"
};

int main(int argc, char**argv) {

    srand(time(NULL));  // Initialize the seed of the rand function

    if (argc <= 4 || argc >= 6) 
        cout << "The call requires exactly 4 parameters [Nmax, L, K1, K2]" << endl;
    else {
        nmax = atoi(argv[1]);
        l = atoi(argv[2]);
        k1 = atoi(argv[3]);
        k2 = atoi(argv[4]);

        library my_lib(nmax);   // (a),create the library, with nmax being the max number of books in each shelf
        
        // (b), create L books
        Book* books = new Book[l];
        for(int i = 0; i < l; i++)    books[i] = new book(book_titles[(rand() % 5 + 1) - 1 ], book_authors[(rand() % 5 + 1) -1], (unsigned int) rand());

        // (c), put k1 books into the library
        if (k1 <= l)
            for(int i = 0; i < k1; i++) {
                int position = rand() % 5 + 1;
                my_lib.place_book( position , books[i]);
            }
        my_lib.print();

        cout << "\nRemovals:" << endl;
        if (k2 <= l)
            for(int i = 0; i < k2; i++) {
                int position = rand() % 5 + 1;
                my_lib.take_book(position);
                cout << endl;
            }
        
        cout << "Final Library Printing: \n\n" << endl;
        my_lib.print();


        cout << "\nList of created books::\n";
        for(int i = 0; i < l; i++) cout << "\"" << books[i]->get_title() << "\" by " <<  books[i]->get_author() << " and ISBN: " <<  books[i]->get_isbn() << " ."<< endl;


        for(int i = 0; i < l; i++) delete books[i];
        delete[] books;
    }
    return 0;
} 