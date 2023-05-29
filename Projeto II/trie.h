#define ALPHABET_SIZE 26
#include <iostream>

namespace structures
{
    struct TrieNode
    {
        explicit TrieNode(const char letter_)
        {
            letter = letter_;
            position = 0;
            length = 0;
            is_leaf = false;
            for (int i = 0; i < ALPHABET_SIZE; i++)
                children[i] = nullptr;
        }
        TrieNode()
        {
            letter = '\0';
            position = 0;
            length = 0;
            is_leaf = false;
            for (int i = 0; i < ALPHABET_SIZE; i++)
                children[i] = nullptr;
        }

        ~TrieNode()
        {
            for (int i = 0; i < ALPHABET_SIZE; i++)
                if (children[i] != nullptr)
                    delete children[i];
        }

        char letter;
        struct TrieNode *children[ALPHABET_SIZE];
        unsigned long position;
        unsigned long length;
        bool is_leaf;
    };

    struct search_return
    {
        bool search_result;
        TrieNode *last_letter;
    };
    class Trie
    {
    public:
        Trie()
        {
            root = new TrieNode();
        }
        // destrutor recursivo
        ~Trie()
        {
            delete root;
        }

        TrieNode *root;

        // insere nova palavra
        void insert(std::string key, size_t position, size_t length)
        {
            struct TrieNode *crawler = root; // percursor

            // para todas letras da palavra
            for (std::size_t i = 0; i < key.length(); i++)
            {
                int index = key[i] - 'a';                            // ajuste ascii, consigo pos letra letra
                if (crawler->children[index] == nullptr)             // não existe ainda
                    crawler->children[index] = new TrieNode(key[i]); // salvo a letra
                // a partir do percursor, continua percurso
                crawler = crawler->children[index];
            }
            // crawler agora é a última letra da palavra
            crawler->is_leaf = true;
            crawler->position = position;
            crawler->length = length;
        }

        // true se a palavra pertence a trie, caso não, false
        // caso true, altera last_node para o node da última letra
        search_return search(std::string key)
        {
            struct TrieNode *crawler = root; // percursor
            struct search_return returning;

            for (std::size_t i = 0; i < key.length(); i++)
            {
                int index = key[i] - 'a'; // ajuste ascii, consigo pos letra letra
                if (crawler->children[index] == nullptr)
                { // não existe ainda
                    returning.search_result = false;
                    return returning;
                }
                // a partir do percursor, continua percurso
                crawler = crawler->children[index];
            }
            returning.search_result = crawler->is_leaf;
            returning.last_letter = crawler;
            return returning;
        }

        // conta a quantidade de prefixos da palavra
        int prefix_count(std::string key)
        {
            TrieNode *crawler = root;
            int count = 0;

            for (std::size_t i = 0; i < key.length(); i++)
            {
                int index = key[i] - 'a';
                if (crawler->children[index] == nullptr)
                    return count;
                crawler = crawler->children[index];
            }

            if (crawler->is_leaf)
                count++;
            count += children_count(crawler);

            return count;
        }

        // a partir do node conta quantas palavras tem abaixo (recursiva)
        int
        children_count(TrieNode *crawler)
        {
            int count = 0;
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (crawler->children[i] != nullptr)
                {
                    if (crawler->children[i]->is_leaf)
                    {
                        count++;
                    }
                    count += children_count(crawler->children[i]);
                }
            }
            return count;
        }
    };
} // namespace structures