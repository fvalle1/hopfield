#include "writer.h"

Writer::Writer(string filename)
{
    fFile = new ofstream();
    fFile->open(filename, std::ios::out);
    fIsOpen = fFile->is_open();
}

Writer::~Writer()
{
    fFile->close();
    delete fFile;
}

void Writer::write(vector<Memory> &data)
{
    if (!fIsOpen)
    {
        cerr << "File is not correctly open!" << endl;
    }

   std::for_each(data.begin(), data.end(), [this](auto&& memory){
       (*(this->fFile))<<memory<<endl;
   });

    return;
}