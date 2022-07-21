// MapWithLRUcache_usingListSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "MapWithLRUcache_usingList.h"
//using namespace cache;
int main() {

    const int CAP = 1700;
    const int MAX_THREADS = 40;
    constexpr int MAX_RANGE_RANDOM_NUMBER = 100000;

    if (CAP < 0) {
        std::cout << " CAP must be a positive number." << '\n';
        return 0;

    }
    else if (CAP < 30) {

        std::cout << " Please check your SSO default, recommend cap >=30." << '\n';
        return 0;
    }

    MapWithLRUCacheUsingSTL_List cache(CAP);





    std::thread threadPool[MAX_THREADS];

    std::string rand_key_4_test{};

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<uint64_t> distr(0, UINT64_MAX); // define the range;

    cache.PUT("this string is long  enough to avoid SSO ", "  Kassel University          "); // make the string.length() >15 char to test SSO
    cache.PUT("", ""); // empty string also take 30 mem in cache (15 for key and 15 for value)
    for (int i = 0; i < MAX_THREADS; ++i)
    {


        std::string key = std::to_string(distr(gen));
        rand_key_4_test = key;
        std::string val = std::to_string(distr(gen));
        threadPool[i] = std::thread(&MapWithLRUCacheUsingSTL_List::PUT, &cache, key, val);


    }
    // std::cout << " RANDOM KEY  is " << rand_key_4_test << '\n';
     // test when the keys are the same
    cache.PUT(rand_key_4_test, "Universidad Central De Las Villas"); //  is MRU
    cache.PUT(rand_key_4_test, "Oklahoma State University - OSU"); // now  is MRU

    for (int i = 0; i < MAX_THREADS; ++i)
    {
        threadPool[i].join();
    }


    std::pair<std::string, std::string> test_get = cache.GET(rand_key_4_test);

    std::cout << test_get.first << " " << test_get.second << '\n'; // client ask 1, hence 1 change to MRU
    //std::cout << cache.get("34234") << std::endl; // client ask 1, hence 1 change to MRU

   // cache.show();


    return 0;
}