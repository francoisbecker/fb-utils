#ifndef READ_WRITE_MUTEX_HPP_INCLUDED
#define READ_WRITE_MUTEX_HPP_INCLUDED

/**
 @file read_write_mutex.hpp
 @author François Becker

MIT License

Copyright (c) 2018 François Becker

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

#include "fbu/assert_cpp11.hpp"

#if __cplusplus >= 201703L
#warning "For C++17 and later, use std::shared_mutex instead of fbu::ReadWriteMutex"
#endif

#include <mutex>
#include <atomic>

namespace fbu
{
    /**
     A read/write mutex with a write priority.
     Warning: if too many threads try to writelock this, reader threads might be blocked.
     This tries to follow the SharedMutex concept: http://en.cppreference.com/w/cpp/concept/SharedMutex
     @todo: implement unit tests.
     @todo: check whether "All lock and unlock operations on a single mutex occur in a single total order" is valid.
     */
    class ReadWriteMutex
    {
        std::mutex mMutex;
        std::condition_variable mReadingAllowed;
        std::condition_variable mWritingAllowed;
        std::atomic_uint mReadLocked;
        std::atomic_uint mWriteWaiting; //< when not equal to 0: prevents readers to acquire it as long as there is a waiting write.
        std::atomic_bool mWriteLocked;

    public:
        ReadWriteMutex()
        : mReadLocked(0u)
        , mWriteWaiting(0u)
        , mWriteLocked(false)
        {
        }
        
        /**
         Read lock
        */
        void lock_shared()
        {
            std::unique_lock<std::mutex> lMonitor(mMutex);
            while (mWriteLocked || mWriteWaiting != 0)
            {
                mReadingAllowed.wait(lMonitor);
            }
            ++mReadLocked;
        }
        
        /**
         Try read lock
         @return  true if the read lock has been acquired, false otherwise.
         */
        bool try_lock_shared()
        {
            std::unique_lock<std::mutex> lMonitor(mMutex, std::try_to_lock);
            if (!lMonitor.owns_lock())
            {
                return false;
            }
            if (mWriteLocked || mWriteWaiting != 0)
            {
                return false;
            }
            ++mReadLocked;
            return true;
        }

        /**
         Read unlock
        */
        void unlock_shared()
        {
            std::unique_lock<std::mutex> lMonitor(mMutex);
            --mReadLocked;
            if (mReadLocked == 0)
            {
                mWritingAllowed.notify_one();
            }
        }

        /**
         Write lock
        */
        void lock()
        {
            std::unique_lock<std::mutex> lMonitor(mMutex);
            ++mWriteWaiting;
            while (mWriteLocked || mReadLocked != 0)
            {
                mWritingAllowed.wait(lMonitor);
            }
            mWriteLocked = true;
            --mWriteWaiting;
        }
        
        /**
         Try write lock
         @return  true if the write lock has been acquired, false otherwise.
         */
        bool try_lock()
        {
            std::unique_lock<std::mutex> lMonitor(mMutex, std::try_to_lock);
            if (!lMonitor.owns_lock())
            {
                return false;
            }
            if (mWriteLocked || mReadLocked != 0)
            {
                return false;
            }
            mWriteLocked = true;
            return true;
        }

        /**
         Write unlock
        */
        void unlock()
        {
            std::unique_lock<std::mutex> lMonitor(mMutex);
            mWriteLocked = false;
            if (mWriteWaiting != 0)
            {
                mWritingAllowed.notify_one();
            }
            else
            {
                mReadingAllowed.notify_all();
            }
        }
    };

    /**
     RAII Read Lock
    */
    class ReadLock
    {
        ReadWriteMutex& mRWMutex;
    public:
        ReadLock(ReadWriteMutex& pRWMutex)
        : mRWMutex(pRWMutex)
        {
            mRWMutex.lock_shared();
        }
        ~ReadLock()
        {
            mRWMutex.unlock_shared();
        }
    };

    /**
     RAII Write Lock
    */
    class WriteLock
    {
        ReadWriteMutex& mRWMutex;
    public:
        WriteLock(ReadWriteMutex& pRWMutex)
        : mRWMutex(pRWMutex)
        {
            mRWMutex.lock();
        }
        ~WriteLock()
        {
            mRWMutex.unlock();
        }
    };
}

#endif

