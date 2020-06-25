#include <algorithm>
#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "No file given as an argument." << std::endl;
        return 0;
    }

    QFile file(argv[1]);
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cout << "Couldn't open " << argv[1] << " for reading." << std::endl;
        return 0;
    }
    QTextStream stream(&file);

    std::vector<unsigned int> offsetVector;
    unsigned int lastOffset;

    QStringList curLine;
    while (!stream.atEnd())
    {
        curLine = stream.readLine().split(' ');
        if (!curLine.empty() && !curLine.first().startsWith("//")) // If not a comment or empty line
        {
            lastOffset = curLine.last().toUInt(nullptr, 16);
            curLine = stream.readLine().split(' ');
            offsetVector.push_back(curLine.last().toUInt(nullptr, 16) - lastOffset);
        }

    }
    std::sort(offsetVector.begin(), offsetVector.end());
    std::cout << "Here we go." << std::endl;
    std::cout << std::hex;
    for (unsigned int offset : offsetVector)
        std::cout << offset << std::endl;
    std::cout << std::dec << "Done." << std::endl;
}
