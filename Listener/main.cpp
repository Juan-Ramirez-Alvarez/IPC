//
//  main.cpp
//  Listener
//
//  Created by Juan Ramirez on 12/3/20.
//

#include "globals.hpp"
#include "SharedMemory.hpp"

int main(int argc, const char * argv[]) {
    SharedMemory shm_reader = SharedMemory(FILEPATH, PROJ_ID, SHARED_MEM_SIZE,Reader);
    shm_reader.read_from_shm();

    return 0;
}
