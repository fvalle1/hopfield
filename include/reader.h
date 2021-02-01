#ifndef READER_H
#define READER_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "reader_I.h"
#include "memory.h"

using namespace std;

class Reader : public Reader_I<Memory>{
public:
    Reader(string filename);

    ~Reader();

    void read(vector<Memory> &, const char sep = ',');

private:

ifstream* fFile;
bool fIsOpen;

};

#endif