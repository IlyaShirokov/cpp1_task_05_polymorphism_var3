#ifndef ItemOfDocument_H
#define ItemOfDocument_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>


class ItemOfDocument
{
public:
    ItemOfDocument(std::string path, int width);

    virtual int wordCounter() = 0;
    virtual void readFile() = 0;
    void setOutputWidth(int width);

    friend std::ostream& operator<< (std::ostream &out, const ItemOfDocument &ItemOfDocument);

    static int filePosition;    //переменная, хранящая текущее положение указателя в файле

protected:
    std::string content;        //строка, хранящая данный для конкретного класса
    int widthOutput;            //ширина вывода в консоли
    std::ifstream filePath;     //объект файла из которого считываем
    int amountWords = 0;        //количество слов в контенте
};


class Paragraph: public ItemOfDocument
{
public:
    Paragraph(std::string path, int width);
    int wordCounter() override;
    void readFile() override;
};


class ASCII_Art: public ItemOfDocument
{
public:
    ASCII_Art(std::string path, int width);
    int wordCounter() override;
    void readFile() override;
};


class Table: public ItemOfDocument
{
public:
    Table(std::string path, int width, int amountRows, int amountColumns);
    void setTableItems(ASCII_Art *art, Paragraph *paragraph, Table *table = nullptr);
    void createTableToOutput();
    int wordCounter() override;
    void readFile() override;

private:
    int m_amountRows;
    int m_amountColumns;
    std::vector<int> m_widthColumns;

    Table *m_table;
    ASCII_Art *m_art;
    Paragraph *m_paragraph;
};

#endif // ItemOfDocument_H
