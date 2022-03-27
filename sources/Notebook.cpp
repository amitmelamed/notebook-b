//
// Created by Amit on 20/03/2022.
//
#include <string>
#include "Direction.hpp"
#include <iostream>
#include <vector>
#include <map>
#include "Notebook.hpp"


//Constance instance used in the program:
const int rowLen = 99;
const int maxCharValue=126;
const int mincharValue=32;


/**
* implementation of Notebook class functions from header file.
* The notebook have infinite pages.
* each page have infinite rows.
* each row have 100 letters.
* the Notebook stores in map its letters.
* to access the notebook:
* pagesOfRowsOfStrings[**pages**][**rows**][**columns**]
*/
namespace ariel {
    /**
     * erase function gets where to erase(page,row,col) a direction (Vertical or Horizontal) and amount to erase.
     * the function will write '~' over any letter.
     * after drawing '~' we won't be able to write on the erased place, because we write with pen.
     * @param page-Non-Negative Integer.
     * @param row -Non-Negative Integer.
     * @param col -Non-Negative Integer lower than 100.
     * @param direction -Vertical or Horizontal
     * @param amountToErase if Horizontal-lower than 100.
     */
    void Notebook::erase(int page, int row, int col, ariel::Direction direction,
                         int amountToErase) {
        //basic input tests:
        //checking negative numbers, and out of bounds
        if (page < 0 || row < 0 || col < 0 || amountToErase < 0) {
            throw std::invalid_argument("Cant use negative numbers in the input");
        }
        if (col > rowLen) {
            throw std::invalid_argument("cant erase out of notebook bounds");
        }
        if ((col + amountToErase) > rowLen && direction == Direction::Horizontal) {
            throw std::invalid_argument("cant erase out of notebook bounds_46");
        }
        //case 1:direction is horizontal
        if (direction == Direction::Horizontal) {
            //step 1.1: if the row is empty we create a new 100 chars row.
            if (pagesOfRowsOfStrings[page][row].empty()) {
                for (int i = 0; i < rowLen; i++) {
                    pagesOfRowsOfStrings[page][row].push_back('_');
                }
            }
            //step 1.2-create new string of '~' in the length of amountToErase
            string eraseString;
            for (int i = 0; i < amountToErase; ++i) {
                eraseString.push_back('~');
            }
            pagesOfRowsOfStrings[page][row].replace((unsigned long) col, (unsigned long) amountToErase, eraseString);
        }
        //case 2:Direction is vertical
        else {
            for (int i = 0; i < amountToErase; i++) {
                //for each row we check if the row is empty
                //if the row is empty we create new one-"____...__"
                if (pagesOfRowsOfStrings[page][row + i].empty()) {
                    for (int k = 0; k < rowLen; k++) {
                        pagesOfRowsOfStrings[page][row + i].push_back('_');
                    }
                }
                //and then put '~' in the right place
                pagesOfRowsOfStrings[page][row + i].replace((unsigned long) col, 1, "~");
            }
        }
    }

    /**
     * read function gets where to read(page,row,col), a direction (Vertical or Horizontal) and amount to read.
     * the function will return string represent what is in the book, on the specific location.
     * @param pageNumber-Non-Negative Integer
     * @param row-Non-Negative Integer
     * @param col -Non-Negative Integer-lower than 100.
     * @param direction -Vertical or Horizontal
     * @param amountToRead if Horizontal-lower than 100.
     * @return String represent what is written on the specific place in the book.
     */
    std::string Notebook::read(int pageNumber, int row, int col, ariel::Direction direction, int amountToRead) {
        //basic input tests:
        //checking negative numbers, and out of bounds
        if (pageNumber < 0 || row < 0 || col < 0 || amountToRead < 0) {
            throw std::invalid_argument("Cant use negative numbers in the input");
        }
        if (col > rowLen) {
            throw std::invalid_argument("cant read out of notebook bounds_83");
        }
        if ((col + amountToRead) > rowLen + 1 && direction == Direction::Horizontal) {
            throw std::invalid_argument("cant read out of notebook bounds_86");
        }
        //case 1:read in horizontal direction
        if (Direction::Horizontal == direction) {
            if (!pagesOfRowsOfStrings[pageNumber][row].empty()) {
                if (col == rowLen && amountToRead == 1) {
                    string s;
                    s.push_back(pagesOfRowsOfStrings[pageNumber][row].at((unsigned long) rowLen - 1));
                    return s;
                }

                string str = pagesOfRowsOfStrings[pageNumber][row];
                unsigned long start = (unsigned long) (col);
                unsigned long amountToReadInLong = (unsigned long) (amountToRead);
                string r = str.substr(start, amountToReadInLong);
                return r;
            }

                string str;
                for (int i = 0; i < amountToRead; ++i) {
                    str.push_back('_');
                }
                return str;
        }
        //case 2:read in vertical direction

        string str;
        for (int i = 0; i < amountToRead; ++i) {
            if (pagesOfRowsOfStrings[pageNumber][row + i].empty()) {
                str.push_back('_');
            } else {
                str.push_back(pagesOfRowsOfStrings[pageNumber][row + i].at((unsigned long) col));
            }
        }
        return str;

    }

    /**
     * Show function get input of specific page and prints out the page
     * @param page-Non-Negative Integer
     */
    void Notebook::show(int page) {
        if (page < 0) {
            throw std::invalid_argument("Invaild input: show page function get Non-Negative page only");
        }
        for (auto const &x: pagesOfRowsOfStrings[page]) {
            std::cout << x.first  // string (key)
                      << ':'
                      << x.second // string's value
                      << std::endl;
        }
    }

    /**
     *  Write function gets where to write(page,row,col), a direction (Vertical or Horizontal) and string (text) to write.
     *  Write can only write on specific place once, since we are writing with non deletable pen.
     *  after we write a letter we can erase it with erase function.
     *  after we write a letter we cannot change it!
     * @param page-Non-Negative integer.
     * @param row-Non-Negative Integer.
     * @param col-Non-Negative Integer- lower than 100.
     * @param direction-Vertical or Horizontal.
     * @param text-if Horizontal-text length should be lower than 100.
     */
    void Notebook::write(int page, int row, int col, ariel::Direction direction, std::string text) {
        //basic input tests:
        //checking negative numbers, and out of bounds



        string invaild = "~\n";
        for (int i = 0; i < text.size(); ++i) {
            if (text.at((unsigned long) i) < mincharValue || text.at((unsigned long) i) > maxCharValue) {
                throw std::invalid_argument("bad letters");
            }
            for (int j = 0; j < 2; ++j) {
                if (text.at((unsigned long) i) == invaild.at((unsigned long) j)) {
                    throw std::invalid_argument("cant use ~ and backslash_n");
                }
            }
        }

        if (page < 0 || row < 0 || col < 0) {
            throw std::invalid_argument("Cant use negative numbers in the input_136");
        }
        if (col > (rowLen + 1) && direction == Direction::Vertical) {
            throw std::invalid_argument("cant write out of notebook bounds_139");
        }


        if (((unsigned long) col + text.length()) > rowLen && direction == Direction::Horizontal) {
            throw std::invalid_argument("cant write out of notebook bounds_143");
        }



        //case 1:Horizontal
        if (Direction::Horizontal == direction) {
            //case 1.1- if the row is empty we create a new 100 chars row.
            if (pagesOfRowsOfStrings[page][row].empty()) {
                for (int i = 0; i < rowLen; i++) {
                    pagesOfRowsOfStrings[page][row].push_back('_');
                }
            }
            //case 1.2- we check where we want to write is empty spaces- only ('_') can be written on
            for (int i = 0; i < text.length(); i++) {
                int i_plus_col = i + col;
                if (pagesOfRowsOfStrings[page][row].at((unsigned long) i_plus_col) != '_') {
                    throw std::invalid_argument("Cant write on written places");
                }
            }
            // case 1.3- write on the ______ allowed spaces
            pagesOfRowsOfStrings[page][row].replace((unsigned long) col, text.length(), text);
        }
            //case 2:vertical
        else {

            //for each letter in the text input
            for (int i = 0; i < text.length(); i++) {
                //first check if the row is empty create new 100*'_' new row
                if (pagesOfRowsOfStrings[page][row + i].empty()) {
                    for (int k = 0; k < rowLen + 1; k++) {
                        pagesOfRowsOfStrings[page][row + i].push_back('_');
                    }
                }
                //if we never wrote on the specific place-it means we have there '_' and we will change it to our letter
                //else we throw error
                if (pagesOfRowsOfStrings[page][row + i].at((unsigned long) col) == '_') {
                    //pagesOfRowsOfStrings[page][row+i].replace((unsigned long) col, (unsigned long) 1, text.at(i));
                    string charInStr;
                    charInStr.push_back(text.at((unsigned long) i));
                    pagesOfRowsOfStrings[page][row + i].replace((unsigned long) col, 1, charInStr);
                } else {
                    throw std::invalid_argument("Cant write on written places");
                }
            }
        }
    }
}





