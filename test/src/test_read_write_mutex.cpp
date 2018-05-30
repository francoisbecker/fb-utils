#include "fbu/read_write_mutex.hpp"

#include "tests_common.hpp"

CASE( "fbu::ReadWriteMutex multiple reads" )
{
    fbu::ReadWriteMutex lRWMutex;
    
    {
        fbu::ReadLock lRL1(lRWMutex);
        fbu::ReadLock lRL2(lRWMutex);
    }
}

CASE( "fbu::ReadWriteMutex multiple reads, try read lock" )
{
    fbu::ReadWriteMutex lRWMutex;
    
    {
        fbu::ReadLock lRL1(lRWMutex);
        fbu::ReadLock lRL2(lRWMutex);
        EXPECT(lRWMutex.try_lock_shared());
        lRWMutex.unlock_shared();
    }
}
    
CASE( "fbu::ReadWriteMutex multiple reads, try write lock" )
{
    fbu::ReadWriteMutex lRWMutex;
    
    {
        fbu::ReadLock lRL1(lRWMutex);
        fbu::ReadLock lRL2(lRWMutex);
        EXPECT(! lRWMutex.try_lock());
        lRWMutex.unlock();
    }
}
