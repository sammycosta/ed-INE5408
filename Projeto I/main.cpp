// Copyright [2022] <Samantha Costa de Sousa>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "./array_stack.h"
#include <algorithm>
#include "./array_queue.h"
#include <tuple>

using namespace std;
using namespace structures;

/* Deve retornar falso se abertura+fechamento de tags não estiver correto */
bool validate(string file_contents)
{
    size_t size = file_contents.length();
    ArrayStack<string> stack = ArrayStack<string>(size);

    size_t i = 0;
    size_t tag_start;
    size_t tag_end;

    while (i < size)
    { /* Lendo todos os caractéres da string */
        if (file_contents[i] == '<')
        {
            tag_start = i;
        }
        else if (file_contents[i] == '>')
        {
            /* Fechou uma tag */
            tag_end = i;
            string tag = file_contents.substr(tag_start + 1, tag_end - (tag_start + 1));

            if (tag[0] == '/')
            {                    // Tag de Fechamento
                tag.erase(0, 1); // Removo a barrinha
                if (stack.empty())
                    return false; // Fechou sem abrir
                else if (tag == stack.top())
                    stack.pop(); // Tag que fechou é igual a última que abriu: desempilha
                else
                    return false; // Quebra no aninhamento
            }
            else
            {
                stack.push(tag); // Tag de abertura: empilha.
            }
        }

        i++; // continua a percorrer string
    }

    return stack.empty();
}

/* @param start_position a partir de onde começo a buscar no arquivo
    @param tag qual tag estou buscando o conteúdo
    @return o conteúdo da tag */
string get_tag_content(string file_contents, size_t start_position, string tag)
{
    size_t tag_start = file_contents.find(tag, start_position);
    size_t tag_length = tag.length();
    string closing_tag = tag.insert(1, "/");
    size_t tag_closing_start = file_contents.find(closing_tag, tag_start);
    size_t content_length = tag_closing_start - (tag_start + tag_length);
    string content = file_contents.substr((tag_start + tag_length), content_length);

    return content;
}

/* algoritmo explicado no moodle */
int labeling_algorithm(int **matriz_imagem, int height, int width)
{
    /* Crio matriz de zeros do mesmo tamanho da matriz imagem */
    int **matriz_zeros = new int *[height];
    int contador = 0;
    for (int i = 0; i < height; i++)
    {
        matriz_zeros[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            matriz_zeros[i][j] = 0; // converte char p int
            contador++;
        }
    }

    int label = 1;

    size_t queue_size = height * width;
    ArrayQueue<tuple<int, int>> queue = ArrayQueue<tuple<int, int>>(queue_size); // fila pra salvar coordenadas

    /* Percorre matriz */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (matriz_imagem[i][j] == 1 && matriz_zeros[i][j] == 0)
            {
                /* Encontrou pixel de intensidade 1 não visitado*/
                queue.enqueue(make_tuple(i, j)); // insiro na fila
                matriz_zeros[i][j] = label;      // atribuo o rótulo na outra matriz

                while (!queue.empty())
                {
                    tuple<int, int> removed = queue.dequeue();
                    int coord_i = get<0>(removed);
                    int coord_j = get<1>(removed);
                    // Primeiro check: não passar dos extremos
                    // Segundo check: pixel de intensidade 1 NÃO ROTULADO AINDA.

                    if (coord_i - 1 >= 0)
                    { // Vizinho 1
                        if (matriz_imagem[coord_i - 1][coord_j] == 1 && matriz_zeros[coord_i - 1][coord_j] == 0)
                        {
                            queue.enqueue(make_tuple(coord_i - 1, coord_j));
                            matriz_zeros[coord_i - 1][coord_j] = label;
                        }
                    }

                    if (coord_i + 1 < height)
                    { // Vizinho 2
                        if (matriz_imagem[coord_i + 1][coord_j] == 1 && matriz_zeros[coord_i + 1][coord_j] == 0)
                        {
                            queue.enqueue(make_tuple(coord_i + 1, coord_j));
                            matriz_zeros[coord_i + 1][coord_j] = label;
                        }
                    }

                    if (coord_j - 1 >= 0)
                    { // Vizinho 3
                        if (matriz_imagem[coord_i][coord_j - 1] == 1 && matriz_zeros[coord_i][coord_j - 1] == 0)
                        {
                            queue.enqueue(make_tuple(coord_i, coord_j - 1));
                            matriz_zeros[coord_i][coord_j - 1] = label;
                        }
                    }

                    if (coord_j + 1 < width)
                    { // Vizinho 4
                        if (matriz_imagem[coord_i][coord_j + 1] == 1 && matriz_zeros[coord_i][coord_j + 1] == 0)
                        {
                            queue.enqueue(make_tuple(coord_i, coord_j + 1));
                            matriz_zeros[coord_i][coord_j + 1] = label;
                        }
                    }
                } // while not empty
                /* Terminou uma região */
                label++;
            } // if primeira checagem
        }     // for por j
    }         // for por i

    delete matriz_zeros; // isso deleta os array dentro? idk

    return label;
}
int main()
{
    ifstream file; // objeto da classe ifstream (pra ler arquivos)
    char xmlfilename[100];

    cin >> xmlfilename; // entrada

    file.open(xmlfilename);

    if (!file.is_open())
    {
        /* Arquivo não foi aberto */
        cout << "error\n";
        return -1;
    }

    /* Adquiro conteúdo do arquivo e coloco numa string */
    auto ss = ostringstream();
    ss << file.rdbuf();
    string file_contents = ss.str();
    file.close();

    /* PRIMEIRO PROBLEMA */
    if (!validate(file_contents))
    {
        /* Não passou na verificação 01 */
        cout << "error\n";
        return -1;
    }

    /* SEGUNDO PROBLEMA */
    size_t start_position = 0;
    size_t closing_tag = file_contents.find("</dataset>", 0);

    // enquanto start é menor que a pos do ultimo </img> antes de </dataset>
    while (start_position < closing_tag - 7)
    {
        int height = stoi(get_tag_content(file_contents, start_position, "<height>"));
        int width = stoi(get_tag_content(file_contents, start_position, "<width>"));
        string data_content = get_tag_content(file_contents, start_position, "<data>");
        data_content.erase(remove(data_content.begin(), data_content.end(), '\n'), data_content.end());
        string image_name = get_tag_content(file_contents, start_position, "<name>");

        string closing_img_tag = "</img>";
        size_t incremento_pos = file_contents.find(closing_img_tag, start_position) + closing_img_tag.length();

        /* Criando matriz com a imagem */
        int **matriz_data_content = new int *[height];
        int contador = 0;
        for (int i = 0; i < height; i++)
        {
            matriz_data_content[i] = new int[width];
            for (int j = 0; j < width; j++)
            {
                matriz_data_content[i][j] = data_content[contador] - 48; // converte char p int
                contador++;
            }
        }

        int label = labeling_algorithm(matriz_data_content, height, width) - 1;
        cout << image_name << " " << label << "\n";

        delete matriz_data_content;

        start_position = incremento_pos; // proximo loop eu olho o file_contents a partir do fim da ultima img
    }
    return 0;
}
