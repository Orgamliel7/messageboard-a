
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;
#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;


 // עדכון המימד של הלוח
 
 Direction dir; //  הצהרה על משתנה מסוג כיוון 




void ariel::Board::modernizeBoundery(unsigned int horizontal, unsigned int vertical, Direction dir, unsigned int len)  //  עדכון גבולות של הלוח
{ // מקבלת אופקי , אנכי, כיוון ואורך של המילה
    unsigned int lenWithHorizontal; // אפס דיפולטיבית
    unsigned int lenWithVertical;
    if(dir == Direction::Horizontal) // אם הכיוון אופקי
    {
        lenWithHorizontal=horizontal+1; //  אורך האופקי שווה לאופקי שהכנסנו בפונקציה פלוס  1 של הנוכחי כי הוא מוסיף רק את האות הראשונה 
        lenWithVertical=len+vertical; // אורך המילה יתווסף למאונך 
    }
    else if(dir == Direction::Vertical) // אחרת אם הכיוון הוא אנכי
    {
        lenWithHorizontal=horizontal+len;
        lenWithVertical=1+vertical;
    }
    if (lenWithHorizontal > horizontal_end) // נבדוק האם גודל האופקי הנוכחי גדול מגודל האופקי האחרון של הלוח
    {
        horizontal_end = lenWithHorizontal; // נעדכן את הגודל של הלוח להיות הגודל של האופקי
    }
    if (horizontal < horizontal_start) // אם המיקום האופקי שהכנסנו קטן מנקודת ההתחלה של הלוח
    {
        horizontal_start = horizontal; // נקודת ההתחלה של הלוח תהיה המיקום האופקי
    }
    if (lenWithVertical > vertical_end)  // נעשה אותו דבר עם האנכי
    {
        vertical_end = lenWithVertical;
    }
    if (vertical < vertical_start) 
    {
        vertical_start = vertical;
    }
    board.resize(horizontal_end,"_"); //פונקציה שמעדכנת את הגודל ע"פ מה שקבענו לה, אם גדול תרחיב, אם קטן תקצץ עד אליו. פה זה תמיד יגדיל

    for (auto ptr = board.begin(); ptr < board.end(); ptr++) // נעבור על כל הלוח עם מצביע כדי לעשות את זה גם לאנכי
    {
        (*ptr).resize(vertical_end,'_'); // נכניס לכל משבצת ריקה קו תחתון כנדרש
    }

}



// post מפרסמת מודעה חדשה ודורסת אחרת אם קיימת כבר כזו
void ariel::Board::post(unsigned int horizontal, unsigned int vertical, Direction dir, const string &message)
{ // לכן תקבל מיקום אופקי ומיקום אנכי, כיוון ואת ההודעה שנשלחת כרפנרס קבוע בכדי שלא תשתנה ונשלח רפרנס כדי שזו תהיה ההודעה ולא הכתובת
    switch (dir) // נבדוק את הכיוון קודם 
    {
        case Direction::Horizontal: //  אם זה אופקי
            modernizeBoundery(horizontal,vertical,dir,message.length()); // נעדכן את גבולות הלוח במקרה הצורך
            board.at(horizontal).replace(vertical,message.length(),message); // נחליף את הכתוב בלוח במיקום המבוקש שהכנסנו ולכן נביא לו כמות תווים והמודעה עצמה 
            break;
        case Direction::Vertical:  //  אם זה אנכי
            modernizeBoundery(horizontal,vertical,dir,message.length());
            for (int i = 0; i < message.length() ; ++i) // נעבור על אורך המודעה 
             {
                board.at(horizontal+i).at(vertical)=message[i]; // כל פעם נחליף תו במיקום המבוקש בתו הרצוי של המחרוזת
             }
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
    if(horizontal+1>(int)horizontal_end)
    {
        return str_from_board.at(0);
    }
    for (unsigned int i=0; i < lengthOfWord && i+vertical<vertical_end; ++i) 
    {
        str_from_board.at(0).at(i)=board.at(horizontal).at(vertical+i);
    }
    return str_from_board.at(0);
}

  // פונקציה זו קוראת את ההודעה הכתובה בצורה אנכית ומחזירה אותה כפלט

string ariel::Board::VerticalReader(unsigned int horizontal, unsigned int vertical, unsigned int lengthOfWord) 
{
    vector<string> str_from_board(1,"_");
    str_from_board.at(0).resize(lengthOfWord,'_');
    if(vertical+1>(int)vertical_end)
    {
        return str_from_board.at(0);
    }
    for (unsigned int i=0; i < lengthOfWord && i+horizontal<horizontal_end; ++i) 
    {
        str_from_board.at(0).at(i)=board.at(horizontal+i).at(vertical);
    }
    return str_from_board.at(0);
}
/**
 פונקציה זו תקרא לאחת מפונקציות העזר ותחזיר את הפלט שלהן, תלוי באיזה כיוון מדובר
 לכן נעביר להן את המיקום האנכי והאופקי, ואת אורך המודעה
 * return the text found in the coordination's, direction and length inputted by the user
 */
string ariel::Board::read(unsigned int horizontal, unsigned int vertical, Direction d, unsigned int lengthOfWord) 
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
    // נעבור בלולאה על כל השורות ובתוכן 
    for (unsigned int i = horizontal_start; i < horizontal_end; ++i) 
    {
        // מתוכן נדפיס מתוך כל וקטור אנכי את שורת המודעות הנוכחית ע"י שימוש  בפונקציית הסטרינג שתקבל מיקום איטרטור התחלתי ומיקום סופי 
        cout << string(board.at(i).substr(vertical_start,vertical_end-vertical_start)) << endl;
        /*
            i= horizontal_start בהתחלה
           new apartment in Haifa! נראה את שורת המודעות הראשונה

           ואז באיטרציה השנייה של 
           new apartment in Haifa! 
           want to learn spanish in one month? call us +972524535
        */
    }
}
