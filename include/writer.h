#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <string>

#include "writer_I.h"
#include "memory.h"

using namespace std;

class Writer : public Writer_I<Memory>
{
public:
    Writer(string filename);

    ~Writer();

    void write(vector<Memory> &);

private:
    ofstream *fFile;
    bool fIsOpen;
};

#endif