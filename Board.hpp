#pragma once
#include <vector>
#include <string>
#include "Direction.hpp"
namespace ariel
{
    using namespace std;
    class Board // private by default 
    {
            vector<string> board; // הלוח יהיה וקטור של מחרוזות שהן המודעות עצמן
            unsigned int horizontal_start=INT32_MAX;
            unsigned int horizontal_end=0;
            unsigned int vertical_start=INT32_MAX;
            unsigned int vertical_end=0;
            void modernizeBoundery(unsigned int horizontal, unsigned int vertical,Direction dir, unsigned int len);
            string HorizontalReader(unsigned int horizontal, unsigned int vertical, unsigned int len);
            string VerticalReader(unsigned int horizontal, unsigned int vertical, unsigned int len);
    public:
        Board() noexcept: board(0,"_"){};
        void post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message);
        string read(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int length);
        void show();
    };


}
