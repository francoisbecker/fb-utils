#ifndef SHMEM_HPP_INCLUDED
#define SHMEM_HPP_INCLUDED

/**
 @file shmem.hpp
 @author François Becker
 
MIT License

Copyright (c) 2017 François Becker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <sys/mman.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>

struct ShMem
{
    ShMem(const std::string& pName, size_t pSize)
    : mName(pName)
    , mSize(pSize)
    {
    }
    
    void connect()
    {
        openOrCreate();
    }
    
    void* getMem()
    {
        return mMem;
    }
    
    void disconnect(bool pDestroy = false)
    {
        if (mMem != nullptr)
        {
            munmap(mMem, mSize);
            mMem = nullptr;
        }
        if (mFD != -1)
        {
            close(mFD);
            mFD = -1;
            if (pDestroy)
            {
                shm_unlink(mName.c_str());
            }
        }
    }
    
    ~ShMem()
    {
        disconnect();
    }
    
private:
    
    void openOrCreate()
    {
        bool lIsCreator = false;
        mFD = shm_open(mName.c_str(), O_RDWR, S_IRUSR | S_IWUSR/* | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH*/);
        if (mFD < 0)
        {
            mFD = shm_open(mName.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR/* | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH*/);
            lIsCreator = true;
        }
        if (mFD >= 0)
        {
            if (lIsCreator)
            {
                if (ftruncate(mFD, (off_t)mSize) < 0)
                {
                    //std::cerr << strerror(errno) << std::endl;
                    return;
                }
            }
            
            mMem = mmap(0, mSize, PROT_READ | PROT_WRITE, MAP_SHARED, mFD, 0);
            if (mMem == MAP_FAILED)
            {
                mMem = nullptr;
            }
        }
    }
    
    std::string mName;
    size_t      mSize;
    int         mFD = -1;
    void*       mMem = nullptr;
};

#if 0
#include <iostream>
class UnitTest
{
public:
    UnitTest()
    {
        ShMem lSHM1("shmem_ut", 8);
        lSHM1.connect();
        if (! lSHM1.getMem())
        {
            std::cerr << "Could not connect (1)" << std::endl;
            return;
        }
        
        strcpy((char*)lSHM1.getMem(), "test");
        
        {
            ShMem lSHM2("shmem_ut", 8);
            lSHM2.connect();
            if (! lSHM2.getMem())
            {
                std::cerr << "Could not connect (2)" << std::endl;
                return;
            }
            
            std::cout << (char*)lSHM2.getMem() << std::endl;
        }
    }
}
mUnitTest;
#endif

#endif
