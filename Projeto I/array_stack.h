// Copyright [2022] <Samantha Costa de Sousa>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>   // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures
{

    template <typename T>
    //! CLASSE PILHA
    class ArrayStack
    {
    public:
        //! construtor simples
        ArrayStack();
        //! construtor com parametro tamanho
        explicit ArrayStack(std::size_t max);
        //! destrutor
        ~ArrayStack();
        //! metodo empilha
        void push(const T &data);
        //! metodo desempilha
        T pop();
        //! metodo retorna o topo
        T &top();
        //! metodo limpa pilha
        void clear();
        //! metodo retorna tamanho
        std::size_t size();
        //! metodo retorna capacidade maxima
        std::size_t max_size();
        //! verifica se esta vazia
        bool empty();
        //! verifica se esta cheia
        bool full();

    private:
        T *contents;
        int top_;
        std::size_t max_size_;

        static const auto DEFAULT_SIZE = 10u;
    };

} // namespace structures

#endif

template <typename T>
structures::ArrayStack<T>::ArrayStack()
{
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template <typename T> //! construtor com parametro tamanho
structures::ArrayStack<T>::ArrayStack(std::size_t max)
{
    max_size_ = max; // diferença é que eu n uso default e sim param
    contents = new T[max_size_];
    top_ = -1;
}

template <typename T> // destrutor
structures::ArrayStack<T>::~ArrayStack()
{
    delete[] contents;
}

template <typename T> // empilha
void structures::ArrayStack<T>::push(const T &data)
{
    if (full())
    {
        throw std::out_of_range("pilha cheia");
    }
    else
    {
        top_++;                // incrementa a pos do topo
        contents[top_] = data; // naquela pos, coloco o dado
    }
}

template <typename T> // desempilha
T structures::ArrayStack<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("pilha vazia");
    }
    else
    {
        T aux;
        aux = contents[top_]; // salvo o desempilhado
        top_--;               // decremento da pos
        return aux;           // retorno oq tirei da pilha
    }
}

template <typename T> // retorna top
T &structures::ArrayStack<T>::top()
{
    if (empty())
    {
        throw std::out_of_range("pilha vazia");
    }
    else
    {
        return contents[top_];
    }
}

template <typename T> // limpa pilha
void structures::ArrayStack<T>::clear()
{
    top_ = -1; // pos inicial volta a ser 0
}

template <typename T> // retorna tamanho
std::size_t structures::ArrayStack<T>::size()
{
    return top_ + 1; // comeca no -1 ent soma
}

template <typename T>
std::size_t structures::ArrayStack<T>::max_size()
{
    return max_size_;
}

template <typename T> // ta vazia?
bool structures::ArrayStack<T>::empty()
{
    return (top_ == -1);
}

template <typename T> // ta cheia?
bool structures::ArrayStack<T>::full()
{
    int max_size_int;
    max_size_int = static_cast<int>(max_size_);
    return (top_ == max_size_int - 1);
}
