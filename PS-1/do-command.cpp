#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/times.h>



void do_command(char** argv){

    struct tms start_t, end_t;
    clock_t start = times(&start_t), end;

    int pid = fork();

    if(pid < 0){
        std::cerr << strerror(errno) << '\n';
        exit(errno);
    } else if(pid == 0){
        int exe_result = execvp(argv[0], argv);
        if(exe_result < 0){
            std::cerr << strerror(errno) << '\n';
            exit(errno);
        }
    } else{
        int wstatus;

        int wait_result = waitpid(pid, &wstatus, 0);
        end = times(&end_t);
        std::cout << '\n' << '\n' << "Command completed with " << wstatus << " exit code and took " << end - start << " seconds."; 
    }
}


int main(int argc, char** argv){

    if(argc < 2){
        std::cerr << "Please write command and command arguments\n";
        exit(1);
    }


    for(int i = 0; i < argc - 1;++i){
        argv[i] = argv[i+1];
    }
    argv[argc - 1] = nullptr;
    do_command(argv);
    return 0;
}
