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
                        resize (max + 15);
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
            int aux = arr[pos];
            for (int i = n; i > pos; i --){
                arr[i]
            }
        };
        T get(int pos);
        int search(T e);
        bool empty();
        int size();


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
