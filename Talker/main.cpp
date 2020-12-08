//
//  main.cpp
//  IPC
//
//  Created by Juan Ramirez on 12/3/20.
//

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define FILEPATH "/Users/juanramirez/Documents/IPC/shmfile_juan"
#define PROJ_ID 18
#define Orw_Grw_Orw 0666
#define SHARED_MEM_SIZE 1024

int main(int argc, const char * argv[]) {
    // insert code here...
    // ----- shared memory method write -----

    // 1. Generate unique key
    key_t key  = ftok(FILEPATH, PROJ_ID);
    if (key < 0) {
        std::cout << "Error generating unique key" << std::endl;
        return -1;
    }
    
    
    // 2. Get identifier in shmid
    int shared_mem_id = shmget(key, SHARED_MEM_SIZE, IPC_CREAT | Orw_Grw_Orw);
    if (shared_mem_id < 0) {
        std::cout << "Error getting shared memory id" << std::endl;
        return -1;
    }

    // 3. Attach to shared memory
    char* str = (char*) shmat(shared_mem_id, (void*) 0, 0);
    std::cout << str << std::endl;
    if (*str < 0) {
        std::cout << "Error attaching to shared memory" << std::endl;
        return -1;
    }
    
    int input_digits = 0;
    std::cout << "Data to write:" << std::endl;
    std::cin >> input_digits;
    
    // 4. Detach from shared memory
    shmdt(str);
    
    return 0;
}
