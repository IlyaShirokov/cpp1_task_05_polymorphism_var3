#include <iostream>
#include "ItemOfDocument.h"

using namespace std;

int main()
{

    Paragraph paragraph("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc2.txt", 30);
    paragraph.readFile();
    cout << paragraph << endl;
    cout << paragraph.wordCounter() << endl;

    std::cout << "-----------" << std::endl;

    ASCII_Art ascii_art("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc2.txt", 40);
    ascii_art.readFile();
    cout << ascii_art << endl;
    cout << ascii_art.wordCounter() << endl;

    std::cout << "-----------" << std::endl;

    Table smallTable("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc2.txt", 50, 2, 2);
    smallTable.setTableItems(&ascii_art, &paragraph);
    smallTable.readFile();

    Table bigTable("C:\\Users\\Ilyaa\\Desktop\\cpp1_task_05_polymorphism_var3\\testDoc2.txt", 150, 5, 4);
    bigTable.setTableItems(&ascii_art, &paragraph, &smallTable);
    bigTable.readFile();
    cout << bigTable << endl;
    cout << bigTable.wordCounter() << endl;

    return 0;
}
