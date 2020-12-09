//
//  SharedMemory.hpp
//  
//
//  Created by Juan Ramirez on 12/8/20.
//

#include <iostream>

#ifndef SharedMemory_hpp
#define SharedMemory_hpp

enum CommType {
    Writer,
    Reader
};

class SharedMemory {
public:
    SharedMemory(char* file_path, int project_id, int mem_size, CommType communicator_type);
    ~SharedMemory();

    int write_to_shm(std::string message);
    int read_from_shm();

private:
    key_t m_key;
    int m_shared_mem_id;
    int m_shared_mem_size;
    CommType m_type_communicator;

    char* m_buffer;

    int generate_shared_mem_key(char* file_path, int project_id);
    int generate_shared_mem_id();
    char* attach_shared_mem();
    int detach_shared_mem();
};

#endif /* SharedMemory_hpp */
