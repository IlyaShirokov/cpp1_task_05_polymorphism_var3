#include "textdocument.h"

int TextDocument::filePosition = 0;

TextDocument::TextDocument(std::string path, int width) : widthOutput(width)
{
    filePath.open(path, std::ios::binary);
}

std::ostream& operator<< (std::ostream &out, const TextDocument &textdocument)
{
    int currentPosition = 1;
    for (std::string::const_iterator it = textdocument.content.begin(); it != textdocument.content.end(); ++it)
    {
        if (*it == '\r')
        {
            out << std::endl;
            currentPosition = 1;
            continue;
        }

        if (currentPosition == textdocument.widthOutput)
        {
            out << std::endl;
            out << *it;
            currentPosition = 1;
        }
        else
        {
            out << *it;
            currentPosition++;
        }
    }

    return out;
}

Paragraph::Paragraph(std::string path, int width) : TextDocument(path, width){}

void Paragraph::setOutputWidth(int width)
{
    widthOutput = width;
}

int Paragraph::wordCounter()
{
    std::list<std::string> parcedWords;
    std::string delimiter = " ";
    std::string tempContent = content;

    size_t pos = 0;
    std::string token;
    while ((pos = tempContent.find(delimiter)) != std::string::npos)
    {
        token = tempContent.substr(0, pos);
        parcedWords.push_back(token);
        tempContent.erase(0, pos + delimiter.length());
    }
    amountWords = parcedWords.size();
    return parcedWords.size();
}

void Paragraph::readFile()
{
    filePath.seekg(TextDocument::filePosition, std::ios::beg);
    std::string buffer;
    while (std::getline(filePath, buffer))
    {
        if (buffer == "\r")
            break;
        else
            content += buffer;
    }
    TextDocument::filePosition = filePath.tellg();
}

ASCII_Art::ASCII_Art(std::string path, int width) : TextDocument(path, width){}

void ASCII_Art::setOutputWidth(int width)
{
    widthOutput = width;
}

int ASCII_Art::wordCounter()
{
    std::list<std::string> parcedWords;
    std::string delimiter = " ";
    std::string tempContent = content;

    size_t pos = 0;
    std::string token;
    while ((pos = tempContent.find(delimiter)) != std::string::npos)
    {
        token = tempContent.substr(0, pos);
        parcedWords.push_back(token);
        tempContent.erase(0, pos + delimiter.length());
    }
    amountWords = parcedWords.size();
    return parcedWords.size();
}

void ASCII_Art::readFile()
{
    filePath.seekg(TextDocument::filePosition, std::ios::beg);
    std::string buffer;
    while (std::getline(filePath, buffer))
    {
        if (buffer == "\r")
            break;
        else
            content += buffer;
    }
    TextDocument::filePosition = filePath.tellg();
}

Table::Table(std::string path, int width, int amountRows, int amountColumns) : TextDocument(path, width),
    m_amountRows(amountRows), m_amountColumns(amountColumns){}

void Table::setOutputWidth(int width)
{
    widthOutput = width;
}

int Table::wordCounter()
{
    std::list<std::string> parcedWords;
    std::string delimiter = " ";
    std::string tempContent = content;

    size_t pos = 0;
    std::string token;
    while ((pos = tempContent.find(delimiter)) != std::string::npos)
    {
        token = tempContent.substr(0, pos);
        parcedWords.push_back(token);
        tempContent.erase(0, pos + delimiter.length());
    }
    amountWords = parcedWords.size();
    return parcedWords.size();
}

void Table::readFile()
{
    filePath.seekg(TextDocument::filePosition, std::ios::beg);
    std::string buffer;

    std::getline(filePath, buffer);
    std::istringstream stringWidthCol(buffer);
    std::string singleWidth;
    while(stringWidthCol >> singleWidth)
       m_widthColumns.push_back(std::stoi(singleWidth));

    while (std::getline(filePath, buffer))
    {
        if (buffer == "\r")
            break;
        else
            content += buffer;
    }
    TextDocument::filePosition = filePath.tellg();

    createTableToOutput();
}

void Table::setArtAndParagraph(ASCII_Art *art, Paragraph *paragraph)
{
    m_art = art;
    m_paragraph = paragraph;
}

void Table::createTableToOutput()
{
    std::replace(content.begin(), content.end(), '\r', ' ');
    content.erase(std::remove(content.begin(), content.end(), ','), content.end());
    content.erase(std::remove(content.begin(), content.end(), ' '), content.end());

    std::ofstream tempOutputFile;
    tempOutputFile.open("tempOutputFile.txt", std::ios::binary);

    makeHorizontalLines(tempOutputFile, 0);
    makeVerticalLines(tempOutputFile, 5);
    makeHorizontalLines(tempOutputFile, 5);
    int currentPos = 0;

    for(size_t i = 0; i < content.size() / m_amountColumns; ++i)
    {
        for (int j = 0; j < m_amountColumns; ++j)
        {
            switch (content.at(i*m_amountColumns + j))
            {
            case 'A':
            {
                m_art->setOutputWidth(m_widthColumns.at((i*m_amountColumns + j) % m_amountColumns) * ((widthOutput - m_amountColumns)/100.0));
                //tempOutputFile << *m_art;
            }
            case 'P':
            {
                m_paragraph->setOutputWidth(m_widthColumns.at((i*m_amountColumns + j) % m_amountColumns) * ((widthOutput - m_amountColumns)/100.0));
                //tempOutputFile << *m_paragraph;
            }
            case 'T':
            {
                //реализую позже после отладки существующей части
            }
            }
        }

        tempOutputFile.seekp(0, std::ios::end);
        currentPos = tempOutputFile.tellp();
        break;
    }
std::cout << currentPos;

    tempOutputFile.close();
    //remove("tempOutputFile.txt");
}

void Table::makeHorizontalLines(std::ofstream &tempOutputFile, int offset)
{
//    tempOutputFile.seekp(0, std::ios::beg);
//    if (offset != 0)
//    {
//        tempOutputFile.seekp(0, std::ios::end);
//        //tempOutputFile << "\n\r";
//        //offset = offset * (widthOutput - m_amountColumns);
//        //tempOutputFile.seekp(offset, std::ios::beg);
//        for(int j = 0; j < widthOutput - m_amountColumns; ++j)
//            tempOutputFile << '=';
//    }
//    else
//    {
//        for(int i = 0; i < widthOutput - m_amountColumns; ++i)
//            tempOutputFile << '=';
//    }
//    tempOutputFile.seekp(0, std::ios::beg);

    tempOutputFile.seekp(0, std::ios::end);
    for(int j = 0; j < widthOutput - m_amountColumns; ++j)
        tempOutputFile << '=';
    tempOutputFile.seekp(0, std::ios::beg);
}

void Table::makeVerticalLines(std::ofstream &tempOutputFile, int offset)
{
    for (int amountStr = 0; amountStr < offset; ++amountStr)
    {
        for(size_t i = 0; i < m_widthColumns.size() - 1; ++i)
        {
            tempOutputFile.seekp(m_widthColumns.at(i) * ((widthOutput - m_amountColumns)/100.0), std::ios::cur);
            tempOutputFile << '|';
        }
        tempOutputFile.seekp(0, std::ios::end);
        tempOutputFile << '\n';
    }
}
