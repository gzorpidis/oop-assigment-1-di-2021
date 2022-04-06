#pragma once

#include <string.h>
#include <iostream>

////// BOOK class
class book {
    private:
        std::string book_title;
        std::string author;
        unsigned int isbn;
    public:
        book(std::string title, std::string author, unsigned int isbn);
        ~book() {};
        std::string get_author()const { return author; };       // Inline definitions
        std::string get_title() const { return book_title; };
        unsigned int get_isbn() const { return isbn; };
};

///// Base class
class base {
    public:
        base();
        ~base();
};

///// Shelf class     
class shelf {
    private:
        const unsigned int max_capacity;
        unsigned int bosc;
        book** book_cases;
    public:
        shelf(int nmax);
        ~shelf();
        bool place_book(book*);
        bool take_book();
        void print();
};

///// Cupboard class
class cupboard {
    private:
        // Το ντουλάπι εσωτερικά έχει δύο ράϕια.
        shelf cup_top;
        shelf cup_bottom;
    public:
        cupboard(int);
        ~cupboard();
        bool place_book(int,book*);
        bool take_book(int);
        void print();    
};

//// Library class
//// Consists of 3 shelves, one base, one cupboard
class library {
    private:
        base lib_base;
        cupboard lib_cup;
        shelf lib_top_shelf, lib_mid_shelf, lib_bot_shelf;
        unsigned int total_number_of_books;      // when we place a book, we have to increase this

    public:
        library(int nmax);
        ~library();
        bool place_book(int, book* book_to_be_inserted);
        bool take_book(int);
        void print();
};