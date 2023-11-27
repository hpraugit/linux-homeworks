#include <iostream>
#include <random>
#include <ctime>
#include <pthread.h>
#include <cstring>
#include <cerrno>



struct thread_data{
    int* arr;
    int start;
    int end;
    long long res= 0;
};


long long sum(int* arr,int start, int end){
    long long summ = 0;
    for(int i = start;i < end;++i){
        summ += arr[i];
    }
    return summ;
}


void* thread_sum(void* data){
    thread_data* _data = static_cast<thread_data*>(data);
    _data->res = sum(_data->arr, _data->start, _data->end);
    return nullptr;
}


int main(int argc, char** argv){
    
    if(argc < 2){
        std::cout << "Please write N and M\n";
        exit(1);
    }
    else if(argc < 3){
        std::cout << "Please write M\n";
        exit(1);
    }

    long long N = std::atoi(argv[1]), M = std::atoi(argv[2]); 

    srand(time(0));
    int* arr = new int[N];
    for(int i = 0;i < N;++i){
        arr[i] = rand()%10;
    }

    clock_t start_without_thread = clock();
    long long sum_without_thread = sum(arr, 0, N);
    clock_t end_without_thread = clock();

    int thread_N = N/M;
    long long sum_with_thread = 0;
    pthread_t* threads = new pthread_t[M];
    thread_data* threads_data = new thread_data[M];

    clock_t start_with_thread = clock();
    for(int i = 0; i < M;++i){
        threads_data[i] = {
            arr,
            i * thread_N,
            (i == M - 1) ? N : (i+1) * thread_N,
            0
        };
        int current_thread = pthread_create(&threads[i], nullptr, thread_sum, &threads_data[i]);
        if(current_thread != 0){
            std::cerr << strerror(errno);
            exit(errno);
        }
    }
    for(int i = 0; i < M;++i){
        pthread_join(threads[i], nullptr);
        sum_with_thread += threads_data[i].res;
    }
    clock_t end_with_thread = clock();

    double without_thread_time = static_cast<double>(end_without_thread - start_without_thread) / CLOCKS_PER_SEC;
    double with_thread_time = static_cast<double>(end_with_thread - start_with_thread) / CLOCKS_PER_SEC;
    
    std::cout << "Time spent without threads: " <<  without_thread_time << " seconds\n";
    std::cout << "Time spent with " << M << " threads: "  << with_thread_time << " seconds\n";
    

    return 0;
}
