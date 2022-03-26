
/**
 * Notebook header file
 * classes declared:Notebook
 */
#include <string>
#include "Direction.hpp"
#include <vector>
#include <iterator>
#include <map>
#include <cassert>
#include <string>

using namespace std;
namespace ariel {

    /**
     * The notebook have infinite pages.
     * each page have infinite rows.
     * each row have 100 letters.
     * the Notebook stores in map its letters.
     * to access the notebook:
     * pagesOfRowsOfStrings[**pages**][**rows**][**columns**]
     *
     */
    class Notebook {
        std::map<int, std::map<int, string> > pagesOfRowsOfStrings;
    public:
        Notebook();

        void write(int page, int row, int col, Direction dir, string text);

        string read(int page, int row, int col, Direction dir, int amountToRead);

        void erase(int page, int row, int col, Direction dir, int amountToErase);

        void show(int page);
    };
}