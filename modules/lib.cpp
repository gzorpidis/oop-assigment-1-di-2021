#include <iostream>
#include <assert.h>
#include "../includes/lib.hpp"
using namespace std;

const int n_of_selves = 5;

typedef book* Book;

const string shelves[n_of_selves]{
    "top shelf",
    "mid shelf",
    "bottom shelf",
    "cupboard\'s top shelf",
    "cupboard\'s bottom shelf",
};


book::book(std::string title, std::string author, unsigned int isbn):
book_title(title), author(author), isbn(isbn)
{}


bool cupboard::place_book(int position, book* to_be_inserted) {
    
    // In order to remove from the cupboard, we will specify
    // the shelf from which we want to remove from
    // if 1 => from the CUPBOARD's top shelf
    // if 2 => from the CUPBOARD's bottom shelf

    bool result;

    switch (position) {
        case 1:
            result = cup_top.place_book(to_be_inserted);
            break;
        case 2:
            result = cup_bottom.place_book(to_be_inserted);
            break;
    }

    return result;
}

bool library::place_book(int position, book* to_be_inserted) {

    bool result;
    
    if (position >= 1 && position <= 5) {
        cout << "Placing book in:" << shelves[position - 1] << endl;    
    }
    switch(position) {
        case 1:
            result = lib_top_shelf.place_book(to_be_inserted);
            break;
        case 2:
            result = lib_mid_shelf.place_book(to_be_inserted);
            break;
        case 3:
            result = lib_bot_shelf.place_book(to_be_inserted);
            break;
        case 4:
            result = lib_cup.place_book(1, to_be_inserted);
            break;
        case 5:
            result = lib_cup.place_book(2, to_be_inserted);
            break;
        default:
            result = false;
            break;
    }

    if (result) {
        this->total_number_of_books++;  // increase because we placed one
        // cout << "Successfully placed book inside the library! (books: " << total_number_of_books << ")." << endl; 
        return true;    // if we reached this, the insertion was successful
    }
    else {
        return false;
    }
}

shelf::shelf(int max):
max_capacity(max),
book_cases(new Book[max_capacity]),
bosc(0)
{
    // Initialize the positions as NULL to denote that there are no books in given positions 
    for(int i = 0; i < max_capacity; i++)
        book_cases[i] = NULL;
    
    cout << "Creating a shelf!" << endl;
}

shelf::~shelf() {
    cout << "Destroying shelf!" << endl;
    // deallocate the memory of the "Book" array
    delete[] book_cases;    
}

cupboard::cupboard(int max):
cup_top(max), 
cup_bottom(max) {
    cout << "Creating cupboard!" << endl;
}

library::library(int max):
lib_top_shelf(max), 
lib_mid_shelf(max), 
lib_bot_shelf(max), 
lib_cup(max), 
total_number_of_books(0) {
    cout << "Creating library!" << endl;
}

cupboard::~cupboard() {
    cout << "Destroying cupboard!" << endl;
}

library::~library() {
    cout << "Destroying library!" << endl;
}

//  H Bάση της βιβλιοθήκης έχει μόνο δομικό ρόλο για τη βιβλιοθήκη – απλά συμμετέχει στις διαδικασίες αρχικοποίησης και καταστροϕής της βιβλιοθήκης.
base::base() {
    // Κατά την κατασκευή μιας βάσης, εκτυπώνεται ένα μήνυμα ότι μια βάση κατασκευάζεται
    cout << "Created the base of the library!" << endl;
}
base::~base() {
    cout << "Destroying base of library!" << endl;
}

bool shelf::place_book(book* book_to_place) {
    if (bosc == max_capacity) {
        cout << "Shelf is full, cannot place book!" << endl;
        return false;
    }

    for(int i = 0; i < max_capacity; i++) {
        if (book_cases[i] == NULL) {
            book_cases[i] = book_to_place;
            cout << "Inserting book: " << endl;
            cout << "\t\"" << book_cases[i]->get_title() << "\" by " <<  book_cases[i]->get_author() << " and ISBN: " <<  book_cases[i]->get_isbn() << " ."<< endl;
            break;
        }
    }
    bosc++;
    return true;
}

bool shelf::take_book() {
    if (bosc == 0) {
        cout << "Shelf is empty, cannot take book!" << endl;
        return false;
    }

    int rem_pos = rand() % max_capacity;
    while (book_cases[rem_pos] == NULL) {
        rem_pos = rand() % max_capacity;
    }

    assert(rem_pos >= 0 && rem_pos < max_capacity);
    book_cases[rem_pos] = NULL;
    bosc--;
    cout << "After removal from shelf, it contains: " << endl;
    print();
    
    return true;
}

bool cupboard::take_book(int position) {
    bool result;
    switch (position) {
        case 1:
            result = cup_top.take_book();
            break;
        case 2:
            result = cup_bottom.take_book();
            break;
    }
    return result;
}

bool library::take_book(int position) {
    
    bool result;

    if (position >= 1 && position <= 5) {
        cout << "\nRemoving book from:" << shelves[position - 1] << endl;   
    }

    switch(position) {
        case 1:
            result = lib_top_shelf.take_book();
            break;
        case 2:
            result = lib_mid_shelf.take_book();
            break;
        case 3:
            result = lib_bot_shelf.take_book();
            break;
        case 4:
            result = lib_cup.take_book(1);
            break;
        case 5:
            result = lib_cup.take_book(2);
            break;
        default:
            result = false;
            break;
    }

    if (result) {
        this->total_number_of_books--;  // we removed a book
        return true;                    // if we reached here the removal was done
    } else {
        return false;
    }
    
}


// Print functions:
void library::print() {
    lib_top_shelf.print();
    lib_mid_shelf.print();
    lib_bot_shelf.print();
    lib_cup.print();
}

void cupboard::print() {
    cup_top.print();
    cup_bottom.print();
}

void shelf::print() {
    if (bosc == 0) {
        cout << "Empty shelf!" << endl;
    } else {
        cout << "Shelf contains: " << endl;
        int pos = 0;
        for(int i = 0; i < max_capacity; i++)
            if (book_cases[i] != NULL) {
                cout << "\t" << pos++ + 1 << ") \"" << 
                book_cases[i]->get_title() << "\" by " << 
                book_cases[i]->get_author() << " and ISBN: " << 
                book_cases[i]->get_isbn() << " ." <<  endl;
            }
    }
}