#include <ostream>
#include "List.h"

template <typename T> 
class ListArray : public List<T> {

    private:
        // miembros privados
        T* arr;
        int max;
        int n;
        static const int MINSIZE = 2;

        void resize (int new_size){
            T* newArr = new T[new_size];
            for (int i = 0; i < n; i++){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            max = new_size;
        };

    public:
        // miembros públicos, incluidos los heredados de List<T>
        void insert(int pos, T e) override{
            try {
                if (pos > 0 && pos <= n){
                    if (n == max) {
                        resize (max + 20);
                    }
                    for (int i = n; i > pos; --i) { // All elements after pos are right shifted to avoid overwriting.
                        arr[i] = arr[i - 1];
                    }
                    arr[pos] = e;
                    n++;
                } else {
                    throw std::out_of_range("Position out of range");
                } 
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << std::endl;
            }
        };

        void append(T e) override {
            insert(n, e)
        };

        void prepend(T e) override {
            insert(0, e);
        };

        T remove(int pos) override {
            T value;
            try{
                if (pos >= 0 && pos < n){
                    value = arr[pos];
                    for (int i = pos; i < n - 1; i++) { // All elements after pos are left shifted to avoid gaps.
                        arr[i] = arr[i + 1];
                    }
                    n--;
                    if (n < max - 15) {
                        resize(max - 15);
                    }
                } else {
                    throw std::out_of_range("Position out of range");
                }
            }   
            catch (const std::out_of_range& e) {
                std::cout << e.what() << std::endl;
            }
            return value;
        };

        T get(int pos) override {
            try {
                if (pos >= 0 && pos < n) {
                    return arr[pos];
                } else {
                    throw std::out_of_range("Out of range");
                }
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << std::endl;
            }
        };

        int search(T e) override {
            for (int i = 0; i < n; i++) {
                if (arr[i] == e) {
                    return i;
                }
            }
            return -1;
        };

        bool empty() override {
            if (n == 0) {
                return true;
            } else {
                return false;
            }
        };

        int size() override {
            return n;
        };

        ListArray(){
            arr = new T[MINSIZE];
            max = MINSIZE;
            n = 0;
        };

        ~ListArray(){
            delete[] arr;
        };

        T operator[](int pos){
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Out of range");
            } else {
                return arr[pos];
            }
        };

        friend std::ostream & operator << (std::ostream &out, const ListArray<T> &list) {
            out << "[";
            for (int i = 0; i < list.n; i++) {
                out << list.arr[i] << ", ";
            }
            out << "]";
            return out;
        };
};
