#include "fbu/read_write_mutex.hpp"

#include "tests_common.hpp"

CASE( "fbu::ReadWriteMutex multiple reads" )
{
    EXPECT( true ); // suppresses the compiler warning about unused parameter 'lest_env'
    
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
    }
}


#if __cplusplus >= 201703L
// Equivalent C++17 tests, behaviour must be replicated

#include <shared_mutex>
CASE( "std::shared_mutex multiple reads" )
{
    EXPECT( true ); // suppresses the compiler warning about unused parameter 'lest_env'
    
    std::shared_mutex lRWMutex;
    
    {
        std::shared_lock<std::shared_mutex> lRL1(lRWMutex);
        std::shared_lock<std::shared_mutex> lRL2(lRWMutex);
    }
}

CASE( "std::shared_mutex multiple reads, try read lock" )
{
    std::shared_mutex lRWMutex;
    
    {
        std::shared_lock<std::shared_mutex> lRL1(lRWMutex);
        std::shared_lock<std::shared_mutex> lRL2(lRWMutex);
        EXPECT(lRWMutex.try_lock_shared());
        lRWMutex.unlock_shared();
    }
}

CASE( "std::shared_mutex multiple reads, try write lock" )
{
    std::shared_mutex lRWMutex;
    
    {
        std::shared_lock<std::shared_mutex> lRL1(lRWMutex);
        std::shared_lock<std::shared_mutex> lRL2(lRWMutex);
        EXPECT(! lRWMutex.try_lock());
    }
}
#endif
