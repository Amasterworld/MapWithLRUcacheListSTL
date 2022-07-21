#include "pch.h"
#include "Header.h"

//using namespace cache;
// constructor
MapWithLRUCacheUsingSTL_List::MapWithLRUCacheUsingSTL_List(size_t cap = 30) {

    m_cap = cap;
    
    store_cache_overflow.open("cache.txt", std::ofstream::trunc); // trunc overwrite, app -> append


}

// destructor
MapWithLRUCacheUsingSTL_List::~MapWithLRUCacheUsingSTL_List() {

    store_cache_overflow.close();

}



//given the key, delete node from the DLL
void MapWithLRUCacheUsingSTL_List::DELETE(std::string& key) {
    
    d_list.remove(*mp[key]); // delete LRU from d_list
    mp.erase(key); // delete LRU ele from the un map
	    
    size_of_mp -= (key.capacity() + mp[key]->second.capacity());
    
}

std::pair<std::string, std::string> MapWithLRUCacheUsingSTL_List::GET(const std::string& key) {

    std::scoped_lock<std::mutex> lk(mtx);

    //if the key exist in the cache 
    if (mp.count(key)) {
	    //get second the element (value) of pair in the d_list
        // and move the pair to the first position of d_list -> to be MRU
        d_list.splice(d_list.begin(), d_list, mp[key]);
        return make_pair(key, mp[key]->second);
    }
    throw std::range_error("There is no such key in cache");
    return make_pair(key," not found"); 

}


void MapWithLRUCacheUsingSTL_List::PUT(const std::string& key, const std::string& value) {


    std::scoped_lock<std::mutex> lk(mtx);
    /*---- if want to see please ucomment code line below */
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));

    /* if key is available then update itand move it to the top d_list->MRU*/
    if  (mp.count(key)) { // (mp.find(key) != mp.end()) {
		
		/* the key exist in the cache then its capacity does not change, but  the value of the key is updated*/
        
        size_of_mp -= mp[key]->second.capacity();
       
        //update the capacity of the new value
        size_of_mp += value.capacity();
		
        if (size_of_mp < m_cap) {
            /*update the value containing in the second d_list*/
            mp[key]->second = value;
            /*move the pair to be the first element of the list->MRU*/
            d_list.splice(d_list.begin(), d_list, mp[key]);
            return;
        }
        else {
            /* move it to the HDD */
            SAVE(key, value);
            size_of_mp -= value.capacity();
        }
			
       // std::cout << "Key exists. \n";
        return;
    }
    //std::cout << "key = " << key << " inserted and its capa " << key.capacity() << '\n';


    size_of_mp += key.capacity() + value.capacity();

    std::cout << "Total current memory usage: " << size_of_mp << '\n';

    // just for safety condition when the cap of cache is very small and the inputs are very big
    if ((key.capacity() > m_cap || value.capacity() > m_cap) || (size_of_mp > m_cap && mp.size() == 0)) {

        std::cout << "The strings of key and value are(is) very big. Swapped to the HDD ." << '\n';
        SAVE(key, value);
        size_of_mp -= (key.capacity() + value.capacity());
        return;
    }

    //if the size of LRU becomes more than capacity then
    //we need to swap least recently used node
    if (size_of_mp > m_cap) {
        // std::cout << "REACH the limit, MOVED the data to the Hard Disk " << '\n';

        SAVE(d_list.back().first, d_list.back().second); // save LRU ele to the HDD

        mp.erase(d_list.back().first); // delete LRU ele from the un map
        d_list.pop_back(); // delete LRU from d_list

    }
    // if key is not available and the capacity does not reach the limit
    // then add it to the first element of the list ->MRU
    d_list.emplace_front(make_pair(key, value));
        
    // update map
    mp[key] = d_list.begin();

}

/*void MapWithLRUCache::show() {
    std::cout << "----------------\n";
    std::cout << "The members in the cache are:\n";
    std::cout << '\n';
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        std::cout << " Key = " << it->first << " and value = " << it->second->val << '\n';
    }
}*/

void MapWithLRUCacheUsingSTL_List::SAVE(std::string_view key, std::string_view value) {


    std::scoped_lock<std::recursive_mutex> lk(recur_mtx);
    std::cout << "key swapped  to HDD: " << key << " -- value: " << value << '\n';
    if (store_cache_overflow.is_open()) {

        store_cache_overflow << key << " " << value << '\n';
    }

}


size_t MapWithLRUCacheUsingSTL_List::SIZE() const  {
    return mp.size();
}

void MapWithLRUCacheUsingSTL_List::LOAD(std::string_view key_need_get) {

    // I do not implement LOAD method, because its policy was not provided
    // when we want to load we have to find the way to solve the problem:
    // confliction between the key in txt file and the key in the ma or
    // even the confliction between key in txt file(can happend the the same key
    // in the txt file)

}