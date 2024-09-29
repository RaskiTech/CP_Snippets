
// Class that stores values for keys, and you can increment and decriment the values (by some amount if you like)
// You can also retrieve the biggest & smallest (and possibly second biggest etc.)
// Min value is 1, but that can be changed. Decrementing from 1 will remove it from memory
// All O(1)

/**
 * MinMaxHash* obj = new MinMaxHash();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

#include <unordered_set>
#include <unordered_map>
using namespace std;
class MinMaxHash {
public:
    struct Link {
        int index;
        unordered_set<string> sSet;
        Link* next = nullptr;
        Link* prev = nullptr;
    };

    unordered_map<string, int> strFreq = {};
    unordered_map<int, Link*> byFreq = {};
    const int BIG = INT_MAX;
    
    // byFreq at 0 and at BIG contain dummy items and this are not available
    MinMaxHash() {
        byFreq[0] = new Link();
        byFreq[0]->index = 0;
        byFreq[BIG] = new Link();
        byFreq[BIG]->index = BIG;
        byFreq[0]->next = byFreq[BIG];
        byFreq[BIG]->prev = byFreq[0];
    }
    
    void InsertAfter(Link* insert, Link* after)
    {
        insert->prev = after;
        insert->next = after->next;
        insert->next->prev = insert;
        after->next = insert;
    }
    void PopOut(Link* link)
    {
        link->next->prev = link->prev;
        link->prev->next = link->next;
        link->next = nullptr;
        link->prev = nullptr;
    }

    void inc(string key) {
        if (strFreq.find(key) == strFreq.end())
        {
            // Add this key
            if (byFreq.find(1) == byFreq.end())
            {
                byFreq[1] = new Link();
                byFreq[1]->index = 1;
                InsertAfter(byFreq[1], byFreq[0]);
            }

            byFreq[1]->sSet.insert(key);
        }
        else
        {
            int index = strFreq[key];
            if (byFreq.find(index + 1) == byFreq.end())
            {
                byFreq[index + 1] = new Link();
                byFreq[index + 1]->index = index + 1;
                InsertAfter(byFreq[index + 1], byFreq[index]);
            }
            byFreq[index + 1]->sSet.insert(key);
            byFreq[index]->sSet.erase(key);

            if (byFreq[index]->sSet.size() == 0)
            {
                PopOut(byFreq[index]);
                delete byFreq[index];
                byFreq.erase(index);
            }
        }
        strFreq[key]++;
    }
    
    void dec(string key) {
        int index = strFreq[key];
        if (index == 1)
        {
            strFreq.erase(key);
            byFreq[index]->sSet.erase(key);
            if (byFreq[index]->sSet.size() == 0)
            {
                PopOut(byFreq[index]);
                delete byFreq[index];
                byFreq.erase(index);
            }
            return;
        }

        if (byFreq.find(index - 1) == byFreq.end())
        {
            byFreq[index - 1] = new Link();
            byFreq[index - 1]->index = index - 1;
            InsertAfter(byFreq[index - 1], byFreq[index]->prev);
        }
        byFreq[index - 1]->sSet.insert(key);
        byFreq[index]->sSet.erase(key);
        if (byFreq[index]->sSet.size() == 0)
        {
            PopOut(byFreq[index]);
            delete byFreq[index];
            byFreq.erase(index);
        }

        strFreq[key]--;
    }
    
    string getMaxKey() {
        if (byFreq[BIG]->prev == byFreq[0])
            return "";
        return *byFreq[BIG]->prev->sSet.begin();
    }
    
    string getMinKey() {
        if (byFreq[BIG]->prev == byFreq[0])
            return "";
        return *byFreq[0]->next->sSet.begin();
    }
};
