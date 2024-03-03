#include <iostream>
#include <errno.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include <signal.h>

int find_m_th_prime(int m){
    int n = 1;
    while(m){
        ++n;
        bool is_prime = true;
        for(int i = 2;i*i <= n;++i){
            if(n % i == 0){
                is_prime = false;
                break;
            }
        }
        if(is_prime){
            --m;
        }
    }
    return n;
}




int main(){
    std::string n;
    int m;
    int parnet_to_child_pipefd[2], child_to_parent_pipefd[2];

    //Making pipes
    if(pipe(parnet_to_child_pipefd) < 0){
        std::cerr << strerror(errno);
        exit(errno);
    }
    if(pipe(child_to_parent_pipefd) < 0){
        std::cerr << strerror(errno);
        exit(errno);
    }

    int pid = fork();
    if(pid < 0){
        std::cerr << strerror(errno);
        exit(errno);
    }

    //Parent process
    if(pid > 0){

        if(close(parnet_to_child_pipefd[0]) < 0){
            std::cerr << strerror(errno);
            exit(errno);
        }
        if(close(child_to_parent_pipefd[1]) < 0){
            std::cerr << strerror(errno);
            exit(errno);
        }

        while(true){
            std::cout << "[Parent] Please enter the number: ";
            std::cin >> n;
            if(n == "exit"){
                kill(pid, SIGKILL);
                return 0;
            }
            m = std::stoi(n);

            std::cout << "[Parent] Sending " << m << " to the child process...\n" << 
            "[Parent] Waiting for the response from the child process...\n";
            
            ssize_t write_to_child = write(parnet_to_child_pipefd[1], &m, sizeof(int));
            if(write_to_child < 0){
                std::cerr << strerror(errno);
                exit(errno);
            }

            int m_th_prime;
            ssize_t read_from_child = read(child_to_parent_pipefd[0], &m_th_prime, sizeof(int));
            if(read_from_child < 0){
                std::cerr << strerror(errno);
                exit(errno);
            }

            std::cout << "[Parent] Recived calculation result of prime("<< m <<") = " << m_th_prime << "...\n";

        }
    }

    //Child process
    if(pid == 0){

        if(close(parnet_to_child_pipefd[1]) < 0){
            std::cerr << strerror(errno);
            exit(errno);
        }
        if(close(child_to_parent_pipefd[0]) < 0){
            std::cerr << strerror(errno);
            exit(errno);
        }

        while(true){
            ssize_t read_from_parent = read(parnet_to_child_pipefd[0], &m, sizeof(int));
            if(read_from_parent < 0){
                std::cerr << strerror(errno);
                exit(errno);
            }
           
            std::cout << "[Child] Calculating " << m << "th prime number...\n";

            int m_th_prime =  find_m_th_prime(m);

            std::cout << "[Child] Sending calculating result of prime(" << m_th_prime << ")\n";

            ssize_t write_to_parent = write(child_to_parent_pipefd[1], &m_th_prime, sizeof(int));
            if(write_to_parent < 0){
                std::cerr << strerror(errno);
                exit(errno);
            }

        }

    }
    return 0;
}