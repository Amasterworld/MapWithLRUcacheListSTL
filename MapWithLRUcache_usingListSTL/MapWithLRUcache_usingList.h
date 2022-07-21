#ifndef _MapWithLRUCacheUsingSTL_List_h
#define _MapWithLRUCacheUsingSTL_List_h


#include<iostream>
#include<string>
#include<unordered_map>
#include <fstream>
#include <thread>
#include <mutex> 
#include <random>
#include <chrono>
#include <string_view>

//#include <exception>
//#include <sstream>
//#include <functional>



//namespace cache {

    class MapWithLRUCacheUsingSTL_List {

    private:

        size_t size_of_mp{};
        size_t m_cap{};

        std::mutex mtx;
        std::mutex recur_mtx;

        std::ofstream store_cache_overflow;

        // can be string_view for list?
        std::list<std::pair<std::string, std::string>> d_list;
        std::unordered_map<std::string, std::list<std::pair<std::string,
            std::string>>::iterator> mp;


        //functions
        void SAVE(std::string_view key, std::string_view value);

    public:



        // constructor
        MapWithLRUCacheUsingSTL_List(size_t cap);

        // destructor
        ~MapWithLRUCacheUsingSTL_List();


        //functions


        void DELETE(std::string& string);
        void PUT(const std::string& key, const std::string& value);
        std::pair<std::string, std::string> GET(const std::string& key);


        void LOAD(std::string_view key_need_get);

        //void show();


    };
//} // namespace cache
#endif