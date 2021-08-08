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

    std::stringstream table_stream;
    std::vector<std::vector<std::string>> parsedString;

    for(size_t i = 0; i < content.size(); ++i)
    {
        std::string delimiter = "\n";
        std::string tempContent;
        std::vector<std::string> currentItem;

        switch (content.at(i))
        {
        case 'A':
        {
            std::stringstream tmp_str;
            m_art->setOutputWidth(m_widthColumns.at((i % m_amountColumns)) * ((widthOutput - m_amountColumns)/100.0));
            tmp_str << *m_art;
            tempContent = tmp_str.str();
            break;
        }
        case 'P':
        {
            std::stringstream tmp_str;
            m_paragraph->setOutputWidth(m_widthColumns.at((i % m_amountColumns)) * ((widthOutput - m_amountColumns)/100.0));
            tmp_str << *m_paragraph;
            tempContent = tmp_str.str();
            break;
        }
        case 'T':
        {
            //реализую позже после отладки существующей части
        }
        }

        size_t pos = 0;
        std::string token;
        while ((pos = tempContent.find(delimiter)) != std::string::npos)
        {
            token = tempContent.substr(0, pos);
            currentItem.push_back(token);
            tempContent.erase(0, pos + delimiter.length());
        }
        parsedString.push_back(currentItem);
    }

    for(size_t i = 0; i < content.size() / m_amountColumns; ++i)
    {
        std::vector<std::vector<std::string>> findMaxLength;
        unsigned int maxLength = 0;

        for (int j = 0; j < m_amountColumns; ++j)
        {
            findMaxLength.push_back(parsedString.at(i*m_amountColumns + j));

            if (parsedString.at(i*m_amountColumns + j).size() > maxLength)
                maxLength = parsedString.at(i*m_amountColumns + j).size() + 1;
        }

        for (unsigned int j = 0; j < maxLength; ++j) //количество строк контента в одной строке таблицы
        {
            for (int k = 0; k < m_amountColumns; ++k) //количевто столбцов
            {
                if (j >= parsedString.at(i * m_amountColumns + k).size())
                    table_stream << std::left << std::setfill(' ') << std::setw (m_widthColumns.at(k) + 3) << ' ';
                else
                    table_stream << std::left << std::setfill(' ') << std::setw (m_widthColumns.at(k) + 3) << parsedString.at(i * m_amountColumns + k).at(j);
                table_stream << '|';
            }
            table_stream << std::endl;
        }
        table_stream << "\n========================================================================================\n";
    }

    content = table_stream.str();
    std::cout << content;
}
