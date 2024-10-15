#pragma once

#include <map>

template <typename Key, typename Value>
class Map
{
   private:
    std::map<Key, Value> map;

   public:
    Map() = default;
    Map(std::map<Key, Value> map) { this->map = map; }

    void Set(Key key, Value value) { map[key] = value; }

    Value& Get(Key key) { return map[key]; }

    bool Contains(Key key) { return map.count(key) > 0; }

    size_t Size() { return map.size(); }

    typename std::map<Key, Value>::iterator begin() { return map.begin(); }
    typename std::map<Key, Value>::iterator end() { return map.end(); }
};