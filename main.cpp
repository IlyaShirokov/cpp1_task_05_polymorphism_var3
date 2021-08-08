#include <iostream>
#include "textdocument.h"

using namespace std;

int main()
{

    Paragraph paragraph("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc.txt", 30);
    paragraph.readFile();
    cout << paragraph << endl;
    cout << paragraph.wordCounter() << endl;

    std::cout << "-----------" << std::endl;

    ASCII_Art ascii_art("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc.txt", 30);
    ascii_art.readFile();
    cout << ascii_art << endl;
    cout << ascii_art.wordCounter() << endl;

    std::cout << "-----------" << std::endl;

    Table table("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc.txt", 150, 5, 4);
    table.setArtAndParagraph(&ascii_art, &paragraph);
    table.readFile();
//    cout << table << endl;
//    cout << table.wordCounter() << endl;

    return 0;
}
