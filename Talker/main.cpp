//
//  main.cpp
//  IPC
//
//  Created by Juan Ramirez on 12/3/20.
//

#include "globals.hpp"
#include "SharedMemory.hpp"

int main(int argc, const char * argv[]) {
    SharedMemory shm_writer = SharedMemory(FILEPATH, PROJ_ID, SHARED_MEM_SIZE, Writer);
    shm_writer.write_to_shm("Hello World");

    return 0;
}
