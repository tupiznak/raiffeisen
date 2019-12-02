#ifndef MYHASHMAP_H
#define MYHASHMAP_H


template<typename T, typename I>
class MyHashMap
{
public:
    void printAll();
    void append(const T* newEl);
    bool find(const T* newEl);
    void remove(const T* newEl);

    MyHashMap(I (*hashFunct)(const T*), int (*compFunct)(const I*, const I*));
    ~MyHashMap();

private:
    I (*hashFunct)(const T*);
    int (*compFunct)(const I*, const I*);
    struct ArrNode{
        int l = -1;
        int r = -1;
        int p = -1;
        I hash;
    };
    ArrNode *arrNodes = nullptr;
    int lastIndexNode = -1;
    int currArrSize = 0;

    void validateSize();
    int availableSize();
};

#endif // MYHASHMAP_H
