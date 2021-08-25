#include "File.h"
#include <iostream>
#include <fstream>

File::File(char *path) : stream(path, std::ios::in | std::ios::binary | std::ios::ate) {
    if(!stream) printf("Stream is not open %s\n", path);

    this->path = path;
    size = stream.tellg();
    stream.seekg(0);
}

File::~File(){
    close();
}

void File::close(){
    if(stream.is_open()){
        delete contents;
        stream.close();
    }
}

void File::read_string(){
    contents = new char[size+std::streampos{1}];
    stream.read(contents, size);
    contents[size] = 0;
}