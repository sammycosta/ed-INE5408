// Copyright [2022] <Samantha Costa de Sousa>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>   // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures
{

    template <typename T>
    //! classe ArrayQueue
    class ArrayQueue
    {
    public:
        //! construtor padrao
        ArrayQueue();
        //! construtor com parametro
        explicit ArrayQueue(std::size_t max);
        //! destrutor padrao
        ~ArrayQueue();
        //! metodo enfileirar
        void enqueue(const T &data);
        //! metodo desenfileirar
        T dequeue();
        //! metodo retorna o ultimo
        T &back();
        //! metodo limpa a fila
        void clear();
        //! metodo retorna tamanho atual
        std::size_t size();
        //! metodo retorna tamanho maximo
        std::size_t max_size();
        //! metodo verifica se vazio
        bool empty();
        //! metodo verifica se esta cheio
        bool full();

    private:
        T *contents;
        std::size_t size_;
        std::size_t max_size_;
        int begin_; // indice do inicio (para fila circular)
        int end_;   // indice do fim (para fila circular)
        static const auto DEFAULT_SIZE = 10u;
    };

} // namespace structures

#endif

template <typename T> // construtor padrão
structures::ArrayQueue<T>::ArrayQueue()
{
    max_size_ = DEFAULT_SIZE;
    size_ = 0;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
}

template <typename T> // construtor com param
structures::ArrayQueue<T>::ArrayQueue(std::size_t max)
{
    max_size_ = max;
    size_ = 0;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
}

template <typename T> // destrutor
structures::ArrayQueue<T>::~ArrayQueue()
{
    delete[] contents;
}

template <typename T> // enqueue
void structures::ArrayQueue<T>::enqueue(const T &data)
{
    if (full())
    {
        throw std::out_of_range("fila cheia");
    }
    else
    {
        int max_size_int;
        max_size_int = static_cast<int>(max_size_);
        end_ = (end_ + 1) % max_size_int;
        size_ = size_ + 1; // qantidade atual aumenta
        contents[end_] = data;
    }
}

template <typename T> // dequeue
T structures::ArrayQueue<T>::dequeue()
{
    if (empty())
    {
        throw std::out_of_range("fila vazia");
    }
    else
    {
        T aux;
        aux = contents[begin_]; // salvo quem ta saindo
        int max_size_int;
        max_size_int = static_cast<int>(max_size_);
        begin_ = (begin_ + 1) % max_size_int;
        size_ = size_ - 1;
        return aux;
    }
}

template <typename T> // retorna o ultimo
T &structures::ArrayQueue<T>::back()
{
    if (empty())
    {
        throw std::out_of_range("fila vazia");
    }
    else
    {
        return contents[end_];
    }
}

template <typename T> // limpa fila
void structures::ArrayQueue<T>::clear()
{
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template <typename T> // retorna tamanho
std::size_t structures::ArrayQueue<T>::size()
{
    return size_;
}

template <typename T>
std::size_t structures::ArrayQueue<T>::max_size()
{
    return max_size_;
}

template <typename T> // ta vazia?
bool structures::ArrayQueue<T>::empty()
{
    return (size() == 0);
}

template <typename T> // ta cheia?
bool structures::ArrayQueue<T>::full()
{

    return (size() == max_size());
}