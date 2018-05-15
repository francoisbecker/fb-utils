#include "fbu/thread_pool.hpp"

#include "tests_common.hpp"

#include <random>

CASE("Thread Pool")
{
    {
        ThreadPool lTP(0);
        EXPECT(lTP.getNumThreads() > 0u);
        EXPECT(lTP.getNumBusyThreads() == 0);
        lTP.waitForCompletion();
        EXPECT(lTP.getNumBusyThreads() == 0);
    }
    
    {
        ThreadPool lTP(1);
        EXPECT(lTP.getNumThreads() == 1u);
        EXPECT(lTP.getNumBusyThreads() == 0);
        lTP.waitForCompletion();
        EXPECT(lTP.getNumBusyThreads() == 0);
    }
    
    {
        ThreadPool lTP(3);
        EXPECT(lTP.getNumThreads() == 3u);
        EXPECT(lTP.getNumBusyThreads() == 0);
        lTP.waitForCompletion();
        EXPECT(lTP.getNumBusyThreads() == 0);
    }
    
    {
        ThreadPool lTP(10);
        std::atomic_int lCounter(0);
        auto lFunction = [&lCounter]() {
            std::mt19937 lRandomGenerator;
            std::uniform_int_distribution<> lDistribution(20, 40);
            int lSleepDuration = lDistribution(lRandomGenerator);
            std::this_thread::sleep_for(std::chrono::milliseconds(lSleepDuration));
            ++lCounter;
        };
        EXPECT(lTP.getNumThreads() == 10u);
        for (int i = 0 ; i != 100 ; ++i)
        {
            lTP.addJob(lFunction);
        }
        EXPECT(lTP.getNumBusyThreads() == 10);
        lTP.waitForCompletion();
        EXPECT(lTP.getNumBusyThreads() == 0);
        EXPECT(lCounter == 100);
    }
}
