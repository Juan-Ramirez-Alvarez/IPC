//
//  SharedMemory.cpp
//  
//
//  Created by Juan Ramirez on 12/8/20.
//
#include "SharedMemory.hpp"
#include "globals.hpp"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sstream>

#define rw_rw_rw 0666

// public:
SharedMemory::SharedMemory(char* file_path, int project_id, int mem_size, CommType communicator_type):
    m_shared_mem_id(0),
    m_shared_mem_size(mem_size),
    m_type_communicator(communicator_type)
{
    int ret_int = generate_shared_mem_key(file_path, project_id);
    if (ret_int < 0)
        return;

    ret_int = generate_shared_mem_id();
    if (ret_int < 0)
        return;

    m_buffer = attach_shared_mem();
    if (m_buffer == (void*)-1)
        return;
}

SharedMemory::~SharedMemory() {
    detach_shared_mem();
}

int SharedMemory::write_to_shm(std::string message) {
    if (message.size() > m_shared_mem_size) {
        std::cout << "Cannot write message greater than buffer size" << std::endl;
        return -1;
    }

    strcpy(m_buffer, message.c_str());

    return 0;
}

int SharedMemory::read_from_shm() {
    std::cout << "Data in buffer:" << std::endl;
    std::cout << m_buffer << std::endl;

    return 0;
}

// private:
int SharedMemory::generate_shared_mem_key(char* file_path, int project_id) {
    m_key = ftok(file_path, project_id);

    if (m_key < 0) {
        std::cout << "Error generating unique key" << std::endl;
        return -1;
    }

    return 0;
}

int SharedMemory::generate_shared_mem_id() {
    m_shared_mem_id = shmget(m_key, m_shared_mem_size, IPC_CREAT | rw_rw_rw);
    if (m_shared_mem_id < 0) {
        std::cout << "Error getting shared memory id" << std::endl;
        return -1;
    }

    return 0;
}

char* SharedMemory::attach_shared_mem() {
    char* str = (char*) shmat(m_shared_mem_id, (void*) 0, 0);
    if (*str < 0) {
        std::cout << "Error attaching to shared memory" << std::endl;
    }

    return str;
}

int SharedMemory::detach_shared_mem() {
    int ret = 0;
    ret = shmdt(m_buffer);
    if (ret < 0) {
        std::cout << "Error detaching from shared memory" << std::endl;
    }

    // remove IPC identifier if reader is done
    if (m_type_communicator == Reader)
        ret = shmctl(m_shared_mem_id, IPC_RMID, NULL);

    return ret;
}
