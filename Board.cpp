#include <array>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;
#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;
  
 




// מודרניזציה ללוח לאחר כל שינוי בו
void ariel::Board::modernizeBoundery(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int len)  //  עדכון גבולות של הלוח
{ // מקבלת אופקי , אנכי, כיוון ואורך של המילה
     int lenWithHorizontal = 0; 
     int lenWithVertical = 0;
    if(dir == Direction::Horizontal) // אם הכיוון אופקי
    {
    
        lenWithHorizontal=(int)horizontal+1; //  אורך האופקי שווה לאופקי שהכנסנו בפונקציה פלוס  1 של הנוכחי כי הוא מוסיף רק את האות הראשונה 
         lenWithVertical=(int)(len+vertical); // אורך המילה יתווסף למאונך 
    }
    else if(dir == Direction::Vertical) // אחרת אם הכיוון הוא אנכי
    {
        lenWithHorizontal=(int)(horizontal+len);
        lenWithVertical=1+(int)vertical;
    }

       if(this->horizontal_start==INT32_MAX&&this->horizontal_end==-1&&this->vertical_start==INT32_MAX&&this->vertical_end==-1) 
       {
        this->horizontal_start = horizontal;
        this->horizontal_end = lenWithHorizontal;
        this->vertical_start=vertical;
        vertical_end = lenWithVertical;
        board.insert(board.begin(),(unsigned int)horizontal_end-horizontal_start,"_");

     }
     else
     {
        if (lenWithHorizontal > horizontal_end)  // נבדוק האם גודל האופקי הנוכחי גדול מגודל האופקי האחרון של הלוח
        {
             board.insert(board.end(),  ((unsigned int)lenWithHorizontal - (unsigned int)horizontal_end), "_");
            horizontal_end = lenWithHorizontal; // נעדכן את הגודל של הלוח להיות הגודל של האופקי
        }
        if(horizontal<horizontal_start) // אם המיקום האופקי שהכנסנו קטן מנקודת ההתחלה של הלוח
        {
            board.insert(board.begin(), horizontal_start - horizontal, "_");
            this->horizontal_start=horizontal;
        }

        if (vertical < vertical_start) 
        {
            vertical_start = vertical;
        }
        if (lenWithVertical > vertical_end)  // נעשה אותו דבר עם האנכי
        {
            this->vertical_end = lenWithVertical;
        }
    }
    //פונקציה שמעדכנת את הגודל ע"פ מה שקבענו לה, אם גדול תרחיב, אם קטן תקצץ עד אליו. פה זה תמיד יגדיל 
        for (auto ptr = board.begin(); ptr < board.end(); ptr++) // נעבור על כל הלוח עם מצביע כדי לעשות את זה גם לאנכי
        {
            (*ptr).resize((unsigned int)vertical_end-vertical_start,'_'); // נכניס לכל משבצת ריקה קו תחתון כנדרש
        }
}
  // פרסום מודעה מאוזנת
void ariel::Board::horizontalPosterize(unsigned int horizontal, unsigned int vertical, const std::string& message) 
{
    board.at(horizontal-horizontal_start).replace(vertical-vertical_start,message.length(),message);
}
  // פרסום מודעה אנכית
void ariel::Board::verticalPosterize(unsigned int horizontal, unsigned int vertical, std::string message) 
{
    for (unsigned int i = 0; i <message.length() ; ++i) 
    {
        board.at(horizontal-horizontal_start+i).at(vertical-vertical_start)=message[i];
    }
}

// post מפרסמת מודעה חדשה ודורסת אחרת אם קיימת כבר כזו
void ariel::Board::post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message)
{ // לכן תקבל מיקום אופקי ומיקום אנכי, כיוון ואת ההודעה שנשלחת כרפנרס קבוע בכדי שלא תשתנה ונשלח רפרנס כדי שזו תהיה ההודעה ולא הכתובת
    switch (dir) // נבדוק את הכיוון קודם 
    {
        case Direction::Horizontal: //  אם זה אופקי
            modernizeBoundery(horizontal,vertical,dir,message.length()); // נעדכן את גבולות הלוח במקרה הצורך
            horizontalPosterize(horizontal,vertical,message); // נחליף את הכתוב בלוח במיקום המבוקש שהכנסנו ולכן נביא לו כמות תווים והמודעה עצמה 
            break;
        case Direction::Vertical:  //  אם זה אנכי
            modernizeBoundery(horizontal,vertical,dir,message.length());
                       verticalPosterize(horizontal,vertical,message);
            break;
        default: // אם לא קיבלנו את אחד משני הכיוונים האפשריים כקלט
            throw out_of_range("please enter one of the two options: Horizontal or Vertical");
    }
}




 // פונקציה זו קוראת את ההודעה הכתובה בצורה אופקית ומחזירה אותה כפלט
string ariel::Board::HorizontalReader(unsigned int horizontal, unsigned int vertical, unsigned int lengthOfWord) 
{
vector<string> str_from_board(1,"_");
    str_from_board.at(0).resize(lengthOfWord,'_');
    if(horizontal+1>horizontal_end||horizontal<horizontal_start)
    {
        return str_from_board.at(0);
    }
    for (unsigned int i=0; i < lengthOfWord; ++i) 
    {
        try
        {
            str_from_board.at(0).at(i)=board.at(horizontal-horizontal_start).at(vertical-vertical_start+i);
        } catch (const std::exception& e) 
        {
        }
    }
    return str_from_board.at(0);
}


  // פונקציה זו קוראת את ההודעה הכתובה בצורה אנכית ומחזירה אותה כפלט

string ariel::Board::VerticalReader(unsigned int horizontal, unsigned int vertical, unsigned int lengthOfWord) 
{
   vector<string> str_from_board(1,"_");
    str_from_board.at(0).resize(lengthOfWord,'_');
    if(vertical+1>(int)vertical_end||vertical<vertical_start){return str_from_board.at(0);
    }
    for (unsigned int i=0; i < lengthOfWord && horizontal+i<horizontal_end; ++i) 
    {
        try 
        {
            str_from_board.at(0).at(i) = board.at(horizontal-horizontal_start + i).at(vertical-vertical_start);
        } catch (const std::exception& e) 
        {

        }
    }
    return str_from_board.at(0);
}

/**
 פונקציה זו תקרא לאחת מפונקציות העזר ותחזיר את הפלט שלהן, תלוי באיזה כיוון מדובר
 לכן נעביר להן את המיקום האנכי והאופקי, ואת אורך המודעה
 * return the text found in the coordination's, direction and length inputted by the user
 */
string ariel::Board::read(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int lengthOfWord) 
{
    switch (dir) 
    {
        case Direction::Horizontal:
            return HorizontalReader(horizontal,vertical,lengthOfWord);
        case Direction::Vertical:
            return VerticalReader(horizontal,vertical,lengthOfWord);
        default:
            throw out_of_range("please enter one of the two options: Horizontal or Vertical");
    }
}

void ariel::Board::show()  // צפייה בלוח המודעות
{
      for (auto & item : board) // נעבור בלולאה על כל השורות ובתוכן עם פוינטר אוטומטי
      {
           cout << string(item) << endl; // בכל אחד מהם נדפיס שורת מודעות בלוח לפי הסדר 
      }
}
        // מתוכן נדפיס מתוך כל וקטור אנכי את שורת המודעות הנוכחית ע"י שימוש  בפונקציית הסטרינג שתקבל מיקום איטרטור התחלתי ומיקום סופי 
      
        /*
            i= horizontal_start בהתחלה
           new apartment in Haifa! נראה את שורת המודעות הראשונה

           ואז באיטרציה השנייה של 
           new apartment in Haifa! 
           want to learn spanish in one month? call us +972524535
        */
    

