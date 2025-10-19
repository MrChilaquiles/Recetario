#ifndef __LIST_H__
#define __LIST_H__

#include <string>
#include <exception>
#include <iostream>
using namespace std;

template <class T, int ARRAYSIZE = 100>
class List {
private:
    T data[ARRAYSIZE];
    int last;

    bool isValidPos(const int&) const;

    void copyAll(const List<T, ARRAYSIZE>&);

    void swapData(T&, T&);

    void sortDataMerge(const int&, const int&);
    void sortDataMerge(const int&, const int&, int(const T&, const T&));
    
    void sortDataQuick(const int&, const int&);
    void sortDataQuick(const int&, const int&, int(const T&, const T&));

public:
    class Exception : public exception {
    private:
        string msg;
    public:
        Exception() noexcept : msg("Error indefinido") {}
        Exception(const Exception& ex) noexcept : msg(ex.msg) {}
        Exception(const string& m) : msg(m) {}
        Exception& operator=(const Exception& ex) noexcept {
            msg = ex.msg;

            return *this;
        }
        virtual ~Exception() {}
        virtual const char* what() const noexcept {
            return msg.c_str();
        }
    };
    
    List();

    List(const List<T, ARRAYSIZE>&);

    bool isEmpty();

    bool isFull() const;

    bool isSorted() const;

    void insertData(const int&, const T&);

    
    void deleteData(const int&);
    
    int getFirstPos() const;
    
    int getLastPos() const;
    
    int getPrevPos(const int&) const;
    
    int getNextPos(const int&) const;
    
    int findDataL(const T&) const;
    
    int findDataB(const T&) const;
    
    T& retrieve(const int&);
    
    void sortDataBubble();
    void sortDataInsert();
    void sortDataSelect();
    void sortDataShell();
    void sortDataMerge();
    void sortDataQuick();
    
    string toString() const;
    string toString(const bool&) const;
    
    void deleteAll();
    
    List<T, ARRAYSIZE>& operator = (const List<T, ARRAYSIZE>&);
    
    template <class X>
    friend ostream& operator << (ostream&, const List<X>&);
    
    template <class X>
    friend istream& operator >> (istream&, List<X>&);
    
    // ****************************************************
    int findDataL(const T&, int(const T&, const T&)) const;
    int findDataB(const T&, int(const T&, const T&)) const;

    void insertSortedData(const T&); // Implicita
    void insertSortedData(const T&, int(const T&, const T&));

    void sortDataBubble(int(const T&, const T&));
    void sortDataInsert(int(const T&, const T&));
    void sortDataSelect(int(const T&, const T&));
    void sortDataShell(int(const T&, const T&));
    void sortDataMerge(int(const T&, const T&));
    void sortDataQuick(int(const T&, const T&));

    bool isSorted(int(const T&, const T&)) const;
};

using namespace std;

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPos(const int& p) const {
    return p >= 0 and p <= this->last;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::copyAll(const List<T, ARRAYSIZE>& other) {
    this->last = other.last;
    
    int i(0);
    while (i <= this->last) {
        this->data[i] = other.data[i];
        i++;
    }
}


template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::swapData(T& a, T& b) {
    T aux(a);
    a = b;
    b = aux;
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List() : last(-1) {}

template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(const List<T, ARRAYSIZE>& other) {
    this->copyAll(other);
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() {
    return this->last == -1;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() const {
    return this->last == ARRAYSIZE - 1;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isSorted() const {
    int i(0);

    while (i < this->last) {
        if (this->data[i] > this->data[i + 1]) {
            return false;
        }
        
        i++;
    }

    return true;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertData(const int& p, const T& e) {
    if (this->isFull()) {
        throw Exception("Desbrodamiento de datos, insertData");
    }
    
    if (p != -1 and !this->isValidPos(p)) {
        throw Exception("Posicion invalida, insertData");
    }
    
    int i(this->last++);

    while (i > p) {
        this->data[i + 1] = this->data[i];
        i--;
    }
    
    this->data[p + 1] = e;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteData(const int& p) {
    if (!this->isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    int i(p);

    while (i < this->last) {
        this->data[i] = this->data[i + 1];
        i++;
    }

    this->last--;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPos() const {
    return this->isEmpty() ? -1 : 0;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos() const {
    return this->last;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getPrevPos(const int& p) const {
    return (p == 0 or !this->isValidPos(p) ? -1 : (p - 1));
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getNextPos(const int& p) const {
    return (p == this->last or !this->isValidPos(p) ? -1 : (p + 1));
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& e) const {
    int i(0);

    while(i <= this->last) {
        if (e == this->data[i]) {
            return i;
        }
        
        i++;
    }

    return -1;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& e) const {
    int i(0), j(this->last), m;

    while (i <= j) {
        m = (i + j) / 2;

        if (e == this->data[m]) {
            return m;
        }
        
        if (e < this->data[m]) {
            j = m -1;
        } else {
            i = m + 1;
        }
    }

    return -1;
}

template<class T, int ARRAYSIZE>
T& List<T, ARRAYSIZE>::retrieve(const int& p) {
    if (!this->isValidPos(p)) {
        throw Exception("Posicion invalida, retrieve");
    }
    
    return this->data[p];
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble() {
    int i(this->last), j;
    bool flag;

    do {
        flag = false;
        j = 0;

        while (j < i) {
            if (this->data[j] > this->data[j + 1]) {
                this->swapData(this->data[j], this->data[j + 1]);
                flag = true;
            }

            j++;
        }

        i--;
    } while (flag);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert() {
    int i(1), j;
    T aux;

    while (i <= this->last) {
        aux = this->data[i];
        j = i;

        while (j > 0 and aux < this->data[j - 1]) {
            this->data[j] = this->data[j - 1];

            j--;
        }
        
        if (i != j) {
            this->data[j] = aux;
        }
        
        i++;
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataSelect() {
    int i(0), j, m;

    while (i <= this->last) {
        m = i;
        j = i + 1;

        while (j <= this->last) {
            if (this->data[j] < this->data[m]) {
                m = j;
            }
            
            j++;
        }

        if (i != m) {
            this->swapData(this->data[i], this->data[m]);
        }
        
        i++;
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataShell() {
    float fact(1.0 / 2.0);
    int dif((this->last + 1) * fact), i , j;

    while (dif > 0) {
        i = dif;

        while (i <= this->last) {
            j = i;

            while (j >= dif and this->data[j - dif] > this->data[j]) {
                this->swapData(this->data[j - dif], this->data[j]);

                j -= dif;
            }
            
            i++;
        }
        
        dif *= fact;
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge() {
    this->sortDataMerge(0, this->last);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge(int cmp(const T&, const T&)) {
    this->sortDataMerge(0, this->last, cmp);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick() {
    this->sortDataQuick(0, this->last);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(int cmp(const T&, const T&)) {
    this->sortDataQuick(0, this->last, cmp);
}

template<class T, int ARRAYSIZE>
string List<T, ARRAYSIZE>::toString() const {
    string result;
    int i(0);
    
    while (i <= this->last) {
        result+= this->data[i].toString() + "\n";
        i++;
    }
    
    return result;
}

template<class T, int ARRAYSIZE>
string List<T, ARRAYSIZE>::toString(const bool& s) const {
    string result;
    int i(0);
    
    while (i <= this->last) {
        result+= this->data[i].toString(s) + "\n";
        i++;
    }
    
    return result;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteAll(){
    this->last = -1;
}

template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T, ARRAYSIZE>::operator = (const List<T, ARRAYSIZE>& other) {
    this->copyAll(other);
    
    return *this;
}

template<class X>
ostream& operator << (ostream& os, const List<X>& l) {
    int i(0);
    
    while (i <= l.last) {
        os << l.data[i++] << endl;
    }
    
    return os;
}

template<class X>
istream& operator >> (istream& is, List<X>& l) {
    X myObj;
    
    try {
        while (is >> myObj) {
            if (!l.isFull()) {
                l.data[++l.last] = myObj;
            }
        }
    } catch(const invalid_argument ex) {
        // Nada
    }
    
    return is;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& e, int cmp(const T&, const T&)) const {
    int i(0);
    
    while(i <= this->last) {
        if (cmp(e, this->data[i]) == 0) {
            return i;
        }
        
        i++;
    }
    
    return -1;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& e, int cmp(const T&, const T&)) const {
    int i(0), j(this->last), m;

    while (i <= j) {
        m = (i + j) / 2;

        if (cmp(e, this->data[m]) == 0) {
            return m;
        }
        
        if (cmp(e, this->data[m]) < 0) {
            j = m -1;
        } else {
            i = m + 1;
        }
    }
    
    return -1;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertSortedData(const T& e) {
    int i(this->last);
    
    while (i > -1 and e < this->data[i]) {
        i--;
    }
    
    insertData(i, e);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertSortedData(const T& e, int cmp(const T&, const T&)) {
    int i(this->last);
    
    while (i > -1 and cmp(e, this->data[i]) < 0) {
        i--;
    }
    
    insertData(i, e);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble(int cmp(const T&, const T&)) {
    int i(this->last), j;
    bool flag;

    do {
        flag = false;
        j = 0;

        while (j < i) {
            if (cmp(this->data[j], this->data[j + 1]) > 0) {
                this->swapData(this->data[j], this->data[j + 1]);
                flag = true;
            }

            j++;
        }

        i--;
    } while (flag);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert(int cmp(const T&, const T&)) {
    int i(1), j;
    T aux;

    while (i <= this->last) {
        aux = this->data[i];
        j = i;

        while (j > 0 and cmp(aux, this->data[j - 1]) < 0) {
            this->data[j] = this->data[j - 1];

            j--;
        }
        
        if (i != j) {
            this->data[j] = aux;
        }
        
        i++;
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataSelect(int cmp(const T&, const T&)) {
    int i(0), j, m;

    while (i <= this->last) {
        m = i;
        j = i + 1;

        while (j <= this->last) {
            if (cmp(this->data[j], this->data[m]) < 0) {
                m = j;
            }
            
            j++;
        }

        if (i != m) {
            this->swapData(this->data[i], this->data[m]);
        }
        
        i++;
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataShell(int cmp(const T&, const T&)) {
    float fact(1.0 / 2.0);
    int dif((this->last + 1) * fact), i , j;

    while (dif > 0) {
        i = dif;

        while (i <= this->last) {
            j = i;

            while (j >= dif and cmp(this->data[j - dif], this->data[j]) > 0) {
                this->swapData(this->data[j - dif], this->data[j]);

                j -= dif;
            }
            
            i++;
        }
        
        dif *= fact;
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge(const int& leftEdge, const int& rightEdge) {
    if (leftEdge >= rightEdge) {
        return;
    }

    int m = (leftEdge + rightEdge) / 2;
    
    this->sortDataMerge(leftEdge, m);
    this->sortDataMerge(m + 1, rightEdge);

    static T tmp[ARRAYSIZE];

    for (int n(leftEdge); n <= rightEdge; n++) {
        tmp[n] = this->data[n];
    }
    
    int i(leftEdge), j(m + 1), x(leftEdge);

    while (i <= m and j <= rightEdge) {
        while (i <= m and tmp[i] <= tmp[j]) {
            this->data[x++] = tmp[i++];
        }
        
        if (i <= m) {
            while (j <= rightEdge and tmp[j] <= tmp[i]) {
                this->data[x++] = tmp[j++];
            }
        }
    }

    while (i <= m) {
        this->data[x++] = tmp[i++];
    }

    while (j <= rightEdge) {
        this->data[x++] = tmp[j++];
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge(const int& leftEdge, const int& rightEdge, int cmp(const T&, const T&)) {
    if (leftEdge >= rightEdge) {
        return;
    }

    int m = (leftEdge + rightEdge) / 2;
    
    this->sortDataMerge(leftEdge, m, cmp);
    this->sortDataMerge(m + 1, rightEdge, cmp);

    static T tmp[ARRAYSIZE];

    for (int n(leftEdge); n <= rightEdge; n++) {
        tmp[n] = this->data[n];
    }
    
    int i(leftEdge), j(m + 1), x(leftEdge);

    while (i <= m and j <= rightEdge) {
        while (i <= m and cmp(tmp[i], tmp[j]) <= 0) {
            this->data[x++] = tmp[i++];
        }
        
        if (i <= m) {
            while (j <= rightEdge and cmp(tmp[j], tmp[i]) <= 0) {
                this->data[x++] = tmp[j++];
            }
        }
    }

    while (i <= m) {
        this->data[x++] = tmp[i++];
    }

    while (j <= rightEdge) {
        this->data[x++] = tmp[j++];
    }
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const int& leftEdge, const int& rightEdge) {
    if (leftEdge >= rightEdge) {
        return;
    }
    
    int i(leftEdge), j(rightEdge);

    while (i < j) {
        while (i < j and this->data[i] <= this->data[rightEdge]) {
            i++;
        }
        
        while (i < j and this->data[j] >= this->data[rightEdge]) {
            j--;
        }
        
        if (i != j) {
            this->swapData(this->data[i], this->data[j]);
        }
    }

    if (i != rightEdge) {
        this->swapData(this->data[i], this->data[rightEdge]);
    }
    
    this->sortDataQuick(leftEdge, i - 1);
    this->sortDataQuick(i + 1, rightEdge);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const int& leftEdge, const int& rightEdge, int cmp(const T&, const T&)) {
    if (leftEdge >= rightEdge) {
        return;
    }
    
    int i(leftEdge), j(rightEdge);

    while (i < j) {
        while (i < j and cmp(this->data[i], this->data[rightEdge]) <= 0) {
            i++;
        }
        
        while (i < j and cmp(this->data[j], this->data[rightEdge]) >= 0) {
            j--;
        }
        
        if (i != j) {
            this->swapData(this->data[i], this->data[j]);
        }
    }

    if (i != rightEdge) {
        this->swapData(this->data[i], this->data[rightEdge]);
    }
    
    this->sortDataQuick(leftEdge, i - 1, cmp);
    this->sortDataQuick(i + 1, rightEdge, cmp);
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isSorted(int cmp(const T&, const T&)) const {
    int i(0);

    while (i < this->last) {
        if (cmp(this->data[i], this->data[i + 1]) > 0) {
            return false;
        }
        
        i++;
    }

    return true;
}

#endif // __LIST_H__