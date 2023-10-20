#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define buffer_size 50


int main(int argc, char** argv){

    if(argc < 3){
        std::cerr << "Please write copy file name\n";
        exit(1);
    } else if(argc < 2){
        std::cerr << "Please write file names\n";
        exit(1);
    }

    char* file_path =  argv[1];
    char* copy_file_path =  argv[2];
    

    int original_file =  open(file_path, O_RDONLY , S_IRUSR | S_IRGRP | S_IROTH);
    int copy_file =  open(copy_file_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    
    
    
    if(original_file < 0 || copy_file < 0){
        std::cerr  << strerror(errno) << "\n";
        exit(errno);
    }

    while(true){
        char buffer[buffer_size];


        ssize_t read_byte = read(original_file, buffer, buffer_size);
        if(read_byte < 0){
            std::cerr  << strerror(errno) << "\n";
            exit(errno);
        }


        ssize_t write_byte = write(copy_file, buffer, read_byte);
        if(write_byte < 0){
            std::cerr  << strerror(errno) << "\n";
            exit(errno);
        }




        if(read_byte == 0)
            break;

    }

    return 0;



}