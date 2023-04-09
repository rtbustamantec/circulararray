#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(int _capacity = 10);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T& operator[](int);    
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;//empty
}

template <class T>
CircularArray<T>::~CircularArray(){
    if(this->array != nullptr){
        delete[] this->array;
    }
}

template <class T>
void CircularArray<T>::push_front(T data) {
    if (is_full()) {
        throw runtime_error( "Array is full" );
    } else if (is_empty()) {
        this->back = 0;
        this->front = 0;
        this->array[0] = data;
    } else {
        this->front = (this->front - 1 + this->capacity) % this->capacity;
        this->array[this->front] = data;
    }
}

template <class T>
void CircularArray<T>::push_back(T data) {
    if (is_full()) {
        throw runtime_error( "Array is full" );
    } else if (is_empty()) {
        this->back = 0;
        this->front = 0;
        this->array[0] = data;
    } else {
        this->front = (this->front - 1 + this->capacity) % this->capacity;
        this->array[this->front] = data;
    }
}

template <class T>
void CircularArray<T>::insert(T data, int pos) {
}

template <class T>
T CircularArray<T>::pop_front() {
    if (is_empty()) {
        throw runtime_error( "Array is full" );
    }
    int old_front = this->front;
    this->front = (this->front + 1) % this->capacity;
    return this->array[old_front];
}

template <class T>
T CircularArray<T>::pop_back() {
    if (is_empty()) {
        throw runtime_error( "Array is empty" );
    }
    int old_back = this->back;
    this->back = (this->back - 1) % this->capacity;
    return this->array[old_back];
}

template <class T>
bool CircularArray<T>::is_empty() {
    return this->front == -1 && this->back == -1;
}

template <class T>
bool CircularArray<T>::is_full() {
    return std::abs(this->front - this->back) == 1 || std::abs(this->front - this->back) == this->capacity - 1;
}

template <class T>
int CircularArray<T>::size() {
    if (is_empty()) {
        return 0;
    }
    if (this->front > this->back) {
        return this->back + 1 + this->capacity - this->front;
    }
    return this->back + 1 - this->front;
}

template <class T>
void CircularArray<T>::clear(){
    this->front = this->back = -1;
}

template <class T>
T& CircularArray<T>::operator[](int pos){
    if (this->is_empty() || pos >= this->size() || pos < 0) {
        throw out_of_range( "Invalid index" );
    }
    return this->array[pos];
}

template <class T>
void CircularArray<T>::sort() {
    int i, j, temp;
    int _size = this->size();
    for (int i = 0; i < _size; i++) {
        for (int j = i + 1; j < _size; j++) {
            int current = (this->front + i) % _size;
            int next = (this->front + j) % _size;
            if (this->array[current] > this->array[next]) {
                temp = this->array[current];
                this->array[current] = this->array[next];
                this->array[next] = temp;
            }
        }
    }
}

template <class T>
bool CircularArray<T>::is_sorted() {
    int _size = size();
    for (int i = 0; i < _size - 1; i++){
        int current_index = (this->front + i) % _size;
        int next_index = (this->front + i + 1) % _size;
        if (this->array[current_index] > this->array[next_index]) {
            return false;
        }
    }
    return true;
}

template <class T>
void CircularArray<T>::reverse() {
    int i, j, temp;
    int _size = this->size();
    for (i = 0, j = _size - 1; i < j; i++, j--) {
        int current_index = (this->front + i) % _size;
        int reverse_index = (this->front + j) % _size;
        temp = array[current_index];
        this->array[current_index] = this->array[reverse_index];
        this->array[reverse_index] = temp;
    }
}

template <class T>
string CircularArray<T>::to_string(string sep) {
    string string_array;
    for (int i; i <= size(); i++) {
        string_array = std::to_string(this->array[i]) + sep;
    }
    return string_array;
}