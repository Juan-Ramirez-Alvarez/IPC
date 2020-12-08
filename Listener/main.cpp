//
//  main.cpp
//  Listener
//
//  Created by Juan Ramirez on 12/3/20.
//

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "../globals.hpp"

int main(int argc, const char * argv[]) {
    // 1. Generate unique key
    key_t key = ftok(FILEPATH, PROJ_ID);
    if (key < 0) {
        std::cout << "Error generating unique key" << std::endl;
        return -1;
    }

    // 2. Get shared mem identifier
    int shared_mem_id = shmget(key, SHARED_MEM_SIZE, IPC_CREAT | rw_rw_rw);
    if (shared_mem_id < 0) {
        std::cout << "Error getting shared memory id" << std::endl;
        return -1;
    }

    // 3. Attach to shared memory
    char* str = (char*) shmat(shared_mem_id, (void*) 0, 0);
    if (*str < 0) {
        std::cout << "Error attaching to shared memory" << std::endl;
        return -1;
    }

    std::cout << str << std::endl;

    // 4. Detach from shared memory
    shmdt(str);
    shmctl(shared_mem_id, IPC_RMID, NULL);

    return 0;
}
