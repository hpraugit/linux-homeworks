#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define buffer_size 50


int main(int argc, char** argv){

    if(argc < 2){
        std::cerr << "Please write file name\n";
        exit(1);
    }

    char* file_path =  argv[1];

    

    int read_file =  open(file_path, O_RDONLY , S_IRUSR | S_IRGRP | S_IROTH);

    if(read_file < 0){
        std::cerr  << strerror(errno) << "\n";
        exit(errno);
    }


    while(true){
        char buffer[buffer_size];
        ssize_t byte = read(read_file, buffer, buffer_size);
        if(byte < 0){
            std::cerr  << strerror(errno) << "\n";
            exit(errno);
        }
        if(byte > 0){
            for(int i = 0; i < byte;++i)
                std::cout << buffer[i];
        } else
            break;

    }

    return 0;



}