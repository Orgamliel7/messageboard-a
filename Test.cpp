
#include "doctest.h"
#include <string>
#include <vector>
#include "Board.hpp"
#include "Direction.hpp"
#include <array>
#include <exception>
#include <math.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <experimental/random>
#include <ctime>
#include <array>


using namespace std;
using namespace ariel;
const string R="R", RACK="RACK";
const int RANDOM_BOUNDERY=100, KOBE=5,WORD_LEN_12=12;


/*
 יש לבדוק את הפונקציות post, read
 post - מקבלת מיקום (שורה וטור), כיוון (אופקי או אנכי), ומחרוזת המייצגת מודעה, ומדביקה את המחרוזת על הלוח במקום המתאים.
read-  מקבלת מיקום (שורה וטור), כיוון (אופקי או אנכי), ומספר תוים, קוראת את מה שכתוב על הלוח במיקום הנתון ובאורך הנתון, ומחזירה מחרוזת. האות הנמצאת בכל משבצת על הלוח היא האות האחרונה שהודבקה שם.
*/

TEST_CASE("Test board") // לוח ריק בלי מודעות אז נצפה לראות קו תחתון באורכים שונים
{
    Board board;
    CHECK(board.read(0, 0, Direction::Horizontal, 0) == string(""));
    CHECK(board.read(1, 1, Direction::Vertical, 0) == string(""));
    CHECK(board.read(2, 2, Direction::Horizontal, 1) == string("_"));
    CHECK(board.read(3, 3, Direction::Vertical, 5) == string("_____"));
}


TEST_CASE("Test Horizontal direction")
{
    Board board;
    board.post(1, 2, Direction::Horizontal, "Check");
    CHECK(board.read(1, 0, Direction::Horizontal, 2) == string("__"));
    CHECK(board.read(1, 0, Direction::Horizontal, 3) == string("__C"));
    CHECK(board.read(1, 2, Direction::Horizontal, 4) == string("Chec"));
    CHECK(board.read(1, 6, Direction::Horizontal, 1) == string("k"));

}

TEST_CASE("Test Vertical direction")
{
    Board board;
    board.post(1, 1, Direction::Vertical, " GTlosdlus");
    //CHECK(board.read(1, 0, Direction::Horizontal, 2) == string("_G"));
   // CHECK(board.read(2, 0, Direction::Horizontal, 3) == string("_T_"));
   // CHECK(board.read(3, 1, Direction::Horizontal, 3) == string("l__"));
  //  CHECK(board.read(4, 0, Direction::Horizontal, 4) == string("_o__"));
    CHECK(board.read(4, 0, Direction::Vertical, 2) == string("__"));
   
}


TEST_CASE("reading")
{
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    CHECK(board.read(row,col,Direction::Horizontal,KOBE)==string("_____"));
    CHECK(board.read(row,col,Direction::Vertical,KOBE)==string("_____"));
}

TEST_CASE("board")
{
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    CHECK(board.read(row,col,Direction::Horizontal,KOBE)==string("_____"));
    CHECK(board.read(row,col,Direction::Vertical,KOBE)==string("_____"));
}

TEST_CASE("reading empty board")
{
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    CHECK(board.read(row,col,Direction::Horizontal,KOBE)==string("_____"));
    CHECK(board.read(row,col,Direction::Vertical,KOBE)==string("_____"));
}

TEST_CASE("reading board")
{
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    CHECK(board.read(row,col,Direction::Horizontal,KOBE)==string("_____"));
    CHECK(board.read(row,col,Direction::Vertical,KOBE)==string("_____"));
}

TEST_CASE("Test - general")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "I");
    board.post(1, 1, Direction::Vertical, "t");
    board.post(2, 2, Direction::Horizontal, "'");
    board.post(3, 3, Direction::Vertical, "s");

    board.post(4, 4, Direction::Horizontal, "work");
    board.post(5, 4, Direction::Horizontal, "ing");
    board.post(6,4,Direction::Vertical,"ng");


    CHECK(board.read(0, 0, Direction::Horizontal, 2) == string("I_"));
    CHECK(board.read(1, 0, Direction::Horizontal, 2) == string("_t"));
    CHECK(board.read(0, 2, Direction::Vertical, 3) == string("__'"));
    CHECK(board.read(3, 2, Direction::Horizontal, 3) == string("_s_"));

    CHECK(board.read(4, 3, Direction::Horizontal, 6) == string("_work_"));
    CHECK(board.read(3, 4, Direction::Vertical, 3) == string("_wi"));
    CHECK(board.read(3, 5, Direction::Vertical, 4) == string("_on_"));
    CHECK(board.read(4, 4, Direction::Vertical, 5) == string("wing_"));
}
// TEST_CASE("adding message to empty board horizontal") {
//     Board board;
//     string str = gen_random(WORD_LEN_5);
//     board.post(0, 0, Direction::Horizontal, str);
//             CHECK(board.read(0, 0, Direction::Horizontal, WORD_LEN_5) == str);
// }

// TEST_CASE("adding message to empty board horizontal and reading verticlly") {
//     Board board;
//     string str = gen_random(WORD_LEN_5);
//     board.post(3, 0, Direction::Horizontal, str);
//     string new_str = "__"+str.substr(0,1)+"__";

//     CHECK(board.read(0, 0, Direction::Vertical, WORD_LEN_5) == new_str);
// }

// TEST_CASE("adding message to empty board vertical and reading horizontally"){
//     Board board;
//     string str = gen_random(WORD_LEN_5);
//     board.post(0,3,Direction::Vertical,str);
//     string new_str = "__"+str.substr(0,1)+"__";
//     CHECK(board.read(0,0,Direction::Horizontal,WORD_LEN_5)==new_str);
// }
TEST_CASE("reading message from empty board"){
    Board board;
    unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
    CHECK(board.read(row,col,Direction::Horizontal,KOBE)==string("_____"));
    CHECK(board.read(row,col,Direction::Vertical,KOBE)==string("_____"));
}

// TEST_CASE("adding message to empty board vertical"){
//     Board board;
//         string str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Vertical,str);
//         CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_5)==str);
//     }
// TEST_CASE("overwriting existing message horizontal"){
//     Board board;
//         string str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,str);
//         str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,str);
//         CHECK(board.read(0,0,Direction::Horizontal,WORD_LEN_5)==str);
//     }
// TEST_CASE("overwriting existing message vertical"){
//     Board board;
//         string str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Vertical,str);
//         str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Vertical,str);
//         CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_5)==str);
//     }
// TEST_CASE("overwriting existing message with longer message vertical"){
//     Board board;
//         string str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Vertical,str);
//         str = gen_random(WORD_LEN_12);
//         board.post(0,0,Direction::Vertical,str);
//         CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_12)==str);
//     }
// TEST_CASE("overwriting existing message with longer message horizontal"){
//     Board board;
//         string str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,str);
//         str = gen_random(WORD_LEN_12);
//         board.post(0,0,Direction::Horizontal,str);
//         CHECK(board.read(0,0,Direction::Horizontal,WORD_LEN_12)==str);
//     }
// TEST_CASE("overwriting existing message with shorter message horizontal"){
//     Board board;
//         string str = gen_random(WORD_LEN_12);
//         board.post(0,0,Direction::Horizontal,str);
//         string str2 = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,str2);
//         str.replace(0,str2.length(),str2);
//         CHECK(board.read(0,0,Direction::Horizontal,WORD_LEN_12)==str);
//     }
// TEST_CASE("overwriting existing message with shorter message vertical"){
//     Board board;
//         string str = gen_random(WORD_LEN_12);
//         board.post(0,0,Direction::Vertical,str);
//         string str2 = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Vertical,str2);
//         str.replace(0,str2.length(),str2);
//         CHECK(board.read(0,0,Direction::Vertical,WORD_LEN_12)==str);
//     }
// TEST_CASE("add 2 messages same direction different length and rows"){
//     Board board;
//         string long_str = gen_random(WORD_LEN_12);
//         string short_str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,short_str);
//         board.post(1,0,Direction::Horizontal,long_str);
//         CHECK(board.read(1,0,Direction::Horizontal,12)==long_str);
//         CHECK(board.read(0,0,Direction::Horizontal,12)==short_str+"_______");
//     }
// TEST_CASE("add 2 messages same direction different length and columns"){
//     Board board;
//         string long_str = gen_random(WORD_LEN_12);
//         string short_str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Vertical,short_str);
//         board.post(0,1,Direction::Vertical,long_str);
//         CHECK(board.read(0,0,Direction::Vertical,12)==long_str);
//         CHECK(board.read(0,1,Direction::Vertical,12)==short_str+"_______");
//     }
// TEST_CASE("add 2 messages different directions"){
//     Board board;
//         string long_str = gen_random(WORD_LEN_12);
//         string short_str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,short_str);
//         board.post(0,0,Direction::Vertical,long_str);
//         CHECK(board.read(0,0,Direction::Vertical,12)==long_str);
//         CHECK(board.read(0,0,Direction::Vertical,5)==long_str.at(0)+short_str.substr(0,4));
//     }
// TEST_CASE("add 2 messages different directions and distanced locations"){
//     Board board;
//         const int row = 90;
//         const int col=9;
//         string long_str = gen_random(WORD_LEN_12);
//         string short_str = gen_random(WORD_LEN_5);
//         board.post(0,0,Direction::Horizontal,short_str);
//         board.post(row,col,Direction::Vertical,long_str);
//         CHECK(board.read(row,col,Direction::Vertical,12)==long_str);
//         CHECK(board.read(0,0,Direction::Horizontal,5)==short_str);
//     }
// TEST_CASE("add messages to random location vertical"){
//     Board board;
//         unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
//         unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
//         string short_str = gen_random(WORD_LEN_5);
//         board.post(row,col,Direction::Vertical,short_str);
//         CHECK(board.read(row,col,Direction::Vertical,WORD_LEN_5)==short_str);
//     }
// TEST_CASE("add messages to random location horizontal"){
//     Board board;
//         unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
//         unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
//         string short_str = gen_random(WORD_LEN_5);
//         short_str = gen_random(WORD_LEN_5);
//         board.post(row,col,Direction::Horizontal,short_str);
//         CHECK(board.read(row,col,Direction::Horizontal,WORD_LEN_5)==short_str);
//     }
// TEST_CASE("after adding mwssage check if empty cells horizontal") {
//     Board board;
//         unsigned int row = (unsigned int) std::experimental::randint(0, RANDOM_BOUNDERY);
//         unsigned int col = (unsigned int) std::experimental::randint(0, RANDOM_BOUNDERY);
//         string short_str = gen_random(WORD_LEN_5);
//         short_str = gen_random(WORD_LEN_5);
//         board.post(row, col, Direction::Horizontal, short_str);
//                 CHECK(board.read(row + WORD_LEN_5, col, Direction::Horizontal, WORD_LEN_5) == "_____");
//                 CHECK(board.read(row, col + WORD_LEN_5, Direction::Horizontal, WORD_LEN_5) == "_____");
//     }
// TEST_CASE("after adding mwssage check if empty cells vertical"){
//     Board board;
//         unsigned int row = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
//         unsigned int col = (unsigned int)std::experimental::randint(0,RANDOM_BOUNDERY);
//         string short_str = gen_random(WORD_LEN_5);
//         board.post(row,col,Direction::Vertical,short_str);
//         CHECK(board.read(row+WORD_LEN_5,col,Direction::Vertical,WORD_LEN_5)=="_____");
//         CHECK(board.read(row,col+WORD_LEN_5,Direction::Vertical,WORD_LEN_5)=="_____");
//     }
// TEST_CASE("read with word length of zero"){
//     Board board;
//     string short_str = gen_random(WORD_LEN_5);
//     board.post(0,0,Direction::Vertical,short_str);
//     unsigned int row = (unsigned int)std::experimental::randint(WORD_LEN_5,RANDOM_BOUNDERY);
//     unsigned int col = (unsigned int)std::experimental::randint(WORD_LEN_5,RANDOM_BOUNDERY);
//     CHECK(board.read(row,col,Direction::Vertical,0)=="");

// }