// "Copyright [2022] Samantha Costa de SOusa"

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "./trie.h"

// https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus

int main()
{

    using namespace std;
    using namespace structures;
    string filename;
    string word;

    cin >> filename; // entrada

    ifstream file; // objeto da classe ifstream (pra ler arquivos)
    file.open(filename);
    if (!file.is_open())
    {
        /* Arquivo não foi aberto */
        cout << "error\n";
        return -1;
    }

    Trie my_trie = Trie();
    string line;
    size_t i = 0;

    while (getline(file, line))
    {
        size_t end_position = line.find(']') - 1;
        string word = line.substr(1, end_position);
        my_trie.insert(word, i, line.length());
        i += line.length() + 1; // pos da próxima palavra
    }
    file.close();

    while (1)
    { // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0)
        {
            break;
        }

        int prefixes = my_trie.prefix_count(word);

        if (prefixes == 0)
        {
            cout << word << " is not prefix" << endl;
        }
        else
        {
            cout << word << " is prefix of " << prefixes << " words" << endl;
        }

        search_return sr = my_trie.search(word);
        if (sr.search_result)
        {
            TrieNode *ll = sr.last_letter;
            cout << word << " is at (" << ll->position << "," << ll->length << ")" << endl;
        }
    }
    return 0;
}
