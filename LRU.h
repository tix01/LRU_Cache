#pragma once
#include <list>
#include <unordered_map>

using namespace std;

template<typename T_key, typename T_val>
class LRU {
private:
    list< pair<T_key, T_val> > it_l;
    unordered_map<T_key, decltype(it_l.begin()) > it_m;
    size_t cache_size;
private:

public:
    LRU(int cache_size_) :cache_size(cache_size_) {
    };

    void put(const T_key& key, const T_val& val) {
        auto it = it_m.find(key);
        if (it != it_m.end()) {
            it_l.erase(it->second);
            it_m.erase(it);
        }
        it_l.push_front(make_pair(key, val));
        it_m.insert(make_pair(key, it_l.begin()));
        while (it_m.size() > cache_size) {
            auto last_it = it_l.end();
            last_it--;
            it_m.erase(last_it->first);
            it_l.pop_back();
        }
    };
    int get(const T_key& key) {
        auto it = it_m.find(key);
        if (it == it_m.end()) {
            return -1;
        }
        it_l.splice(it_l.begin(), it_l, it->second);
        return it->second->second;
    };

};
