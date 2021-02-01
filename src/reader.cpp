#include "reader.h"

Reader::Reader(string filename)
{
    fFile = new ifstream();
    fFile->open(filename, std::ios::in);
    fIsOpen = fFile->is_open();
}

Reader::~Reader()
{
    fFile->close();
    delete fFile;
}

void Reader::read(vector<Memory> &data, const char sep)
{
    if (!fIsOpen)
    {
        cerr << "File is not correctly open!" << endl;
    }

    string line;
    while (getline(*fFile, line))
    {
        if (line.empty())
            break;

        istringstream iss(line);
        string elem;

        auto new_point = std::vector<int>();

        while (getline(iss, elem, sep))
        {
            new_point.push_back(stoi(elem));
        }
        data.push_back(Memory(new_point));
    }

    return ;
}