#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>


class TextDocument
{
public:
    TextDocument(std::string path, int width);

    virtual int wordCounter() = 0;
    virtual void readFile() = 0;
    virtual void setOutputWidth(int width) = 0;

    friend std::ostream& operator<< (std::ostream &out, const TextDocument &textdocument);

    static int filePosition;    //переменная, хранящая текущее положение указателя в файле

protected:
    std::string content;        //строка, хранящая данный для конкретного класса
    int widthOutput;            //ширина вывода в консоли
    std::ifstream filePath;     //объект файла из которого считываем
    int amountWords = 0;        //количество слов в контенте
};


class Paragraph: public TextDocument
{
public:
    Paragraph(std::string path, int width);
    int wordCounter() override;
    void readFile() override;
    void setOutputWidth(int width) override;
};


class ASCII_Art: public TextDocument
{
public:
    ASCII_Art(std::string path, int width);
    int wordCounter() override;
    void readFile() override;
    void setOutputWidth(int width) override;
};


class Table: public TextDocument
{
public:
    Table(std::string path, int width, int amountRows, int amountColumns);
    void setArtAndParagraph(ASCII_Art *art, Paragraph *paragraph);
    void createTableToOutput();
    int wordCounter() override;
    void readFile() override;
    void setOutputWidth(int width) override;
    void makeHorizontalLines(std::ofstream &tempOutputFile, int offset);
    void makeVerticalLines(std::ofstream &tempOutputFile, int offset);

private:
    int m_amountRows;
    int m_amountColumns;
    std::vector<int> m_widthColumns;
    ASCII_Art *m_art;
    Paragraph *m_paragraph;
    std::vector<std::vector<TextDocument*>> outputView;
};

#endif // TEXTDOCUMENT_H
