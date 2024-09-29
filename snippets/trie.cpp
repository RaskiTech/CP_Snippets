#include <string>
#include <array>
using namespace std;
class Trie {
public:
    array<Trie*, 26> childs = {};
    bool isEnd = false;

    Trie() {
        for (int i = 0; i < childs.size(); i++)
            childs[i] = nullptr;
    }
    
    void insert(string word) { _insert(word, 0); }
    void _insert(string& word, int i)
    {
        if (i == word.size())
        {
            isEnd = true;
            return;
        }


        if (childs[word[i] - 'a'] == nullptr)
        {
            childs[word[i] - 'a'] = new Trie();
        }
        
        childs[word[i] - 'a']->_insert(word, i+1);
    }
    
    bool search(string word) { return _search(word, 0); }
    bool _search(string& word, int i)
    {
        if (i == word.size())
            return isEnd;
        if (childs[word[i] - 'a'] == nullptr)
            return false;
        return childs[word[i] - 'a']->_search(word, i+1);
    }
    
    bool startsWith(string prefix) { return _startsWith(prefix, 0); }
    bool _startsWith(string& word, int i)
    {
        if (i == word.size())
            return true;

        if (childs[word[i] - 'a'] == nullptr)
            return false;
            
        return childs[word[i] - 'a']->_startsWith(word, i+1);
    }
};
/*
 * Usage:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
*/