#include <iostream>
#include <fstream>

#ifndef FILE_H
#define FILE_H

class File {
    public:
        File(char *path);
        ~File();
        void read_string();
        void close();

        char *path;
        std::streampos size;
        std::ifstream stream;
        char *contents = NULL;
};

#endif