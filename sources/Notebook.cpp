//
// Created by Amit on 20/03/2022.
//
#include <string>
#include "Direction.hpp"
#include <iostream>
#include <vector>
#include <map>


#include "Notebook.hpp"
const int rowLen=99;
namespace ariel {
    /**
     * implementation of Notebook class functions from header file.
     */
    //constructor-maybe use later
    Notebook::Notebook() {

    }
    int numOfSubarrays(vector<int>& arr) {
        vector<vector<int>> arrayOfSubArrays;
        int sum=0;
        for (int i = 0; i < arr.size(); ++i) {
            for (int j = i+1; j <arr.size() ; ++j) {
                for (int k = i; k <j ; ++k) {
                    sum=sum+arr[(unsigned long)k];
                }
            }
        }
        return sum;
    }


    void Notebook::erase(int page, int row, int col, ariel::Direction direction,
                         int amountToErase) {
        //basic input tests:
        //checking negative numbers, and out of bounds
        if (page < 0 || row < 0 || col < 0 || amountToErase < 0) {
            throw std::invalid_argument("Cant use negative numbers in the input");
        }
        if (col > rowLen) {
            throw std::invalid_argument("cant write out of notebook bounds_43");
        }
        if ((col + amountToErase) > rowLen && direction == Direction::Horizontal) {
            throw std::invalid_argument("cant write out of notebook bounds_46");
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
            //case 2:Direction=vertical
        else {
            for (int i = 0; i < amountToErase; i++) {
                if (pagesOfRowsOfStrings[page][row + i].empty()) {
                    for (int k = 0; k < rowLen; k++) {
                        pagesOfRowsOfStrings[page][row + i].push_back('_');
                    }
                }
                pagesOfRowsOfStrings[page][row + i].replace((unsigned long) col, 1, "~");
            }
        }
    }

    std::string Notebook::read(int pageNumber, int row, int col, ariel::Direction direction, int amountToRead) {
        //basic input tests:
        //checking negative numbers, and out of bounds
        if (pageNumber < 0 || row < 0 || col < 0 || amountToRead < 0) {
            throw std::invalid_argument("Cant use negative numbers in the input");
        }
        if (col > rowLen) {
            throw std::invalid_argument("cant write out of notebook bounds_83");
        }
        if ((col + amountToRead) > rowLen+1 && direction == Direction::Horizontal) {
            throw std::invalid_argument("cant write out of notebook bounds_86");
        }
        //case 1:read in horizontal direction
        if (Direction::Horizontal == direction) {
            if(!pagesOfRowsOfStrings[pageNumber][row].empty()){
                string str = pagesOfRowsOfStrings[pageNumber][row];
                unsigned long start = (unsigned long) (col);
                unsigned long amountToReadInLong = (unsigned long) (amountToRead);
                string r = str.substr(start, amountToReadInLong);
                return r;
            } else{
                string str;
                for (int i = 0; i < amountToRead; ++i) {
                    str.push_back('_');
                }
                return str;
            }

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

    void Notebook::show(int page) {
        if(page<0){
            throw std::invalid_argument("Invaild input: show page function get positive page only");
        }
        for (auto const &x: pagesOfRowsOfStrings[page]) {
            std::cout << x.first  // string (key)
                      << ':'
                      << x.second // string's value
                      << std::endl;
        }
    }

    //need to add vertical write
    void Notebook::write(int page, int row, int col, ariel::Direction direction, std::string text) {
        //basic input tests:
        //checking negative numbers, and out of bounds


        string invaild="~\n";
        for (int i = 0; i <text.size() ; ++i) {
            for (int j = 0; j < 2; ++j) {
                if(text.at((unsigned long)i)==invaild.at((unsigned long )j)){
                    throw std::invalid_argument("cant use ~ and backslash_n");
                }
            }
        }

        if (page < 0 || row < 0 || col < 0) {
            throw std::invalid_argument("Cant use negative numbers in the input_136");
        }
        if (col > (rowLen+1)&&direction==Direction::Vertical) {
            throw std::invalid_argument("cant write out of notebook bounds_139");
        }


        if (((unsigned long) col+text.length()) > rowLen && direction == Direction::Horizontal) {
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
                int i_plus_col=i+col;
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
                    for (int k = 0; k < rowLen+1; k++) {
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





