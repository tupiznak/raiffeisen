#include "myhashmap.h"
#include <iostream>
using namespace std;

template<typename T, typename I>
void MyHashMap<T,I>::append(const T* newEl){
    I newElHash = hashFunct(newEl);
    if (lastIndexNode >= 0){
        int currIndex =0;
        while (true){
            if (compFunct(&newElHash, &arrNodes[currIndex].hash) == 0) {
                cout << "element exist" << endl;
                return;
            }

            int *childIndex = &arrNodes[currIndex].l;
            if(compFunct(&newElHash, &arrNodes[currIndex].hash) > 0)
                childIndex=&arrNodes[currIndex].r;

            if(*childIndex != -1)
                currIndex = *childIndex;
            else{
                *childIndex = lastIndexNode+1;
                validateSize();
                arrNodes[lastIndexNode+1].p = currIndex;
                arrNodes[lastIndexNode+1].hash = newElHash;
                lastIndexNode++;
                break;
            }
        }
    } else {
        validateSize();
        arrNodes[0].hash = newElHash;
        lastIndexNode++;
    }
    cout<< "element added ";
    cout << arrNodes[lastIndexNode].hash << endl;
}

template<typename T, typename I>
bool MyHashMap<T,I>::find(const T* newEl){
    if (lastIndexNode < 0)
        return false;
    I newElHash = hashFunct(newEl);
    ArrNode *curr = &arrNodes[0];
    while (true) {
        if (compFunct(&newElHash, &curr->hash) == 0)
            return true;

        if(compFunct(&newElHash, &curr->hash) < 0) {
            if (curr->l==-1)
                return false;
            else
                curr = &arrNodes[curr->l];
        } else {
            if (curr->r == -1)
                return false;
            else
                curr = &arrNodes[curr->r];
        }
    }
}

template<typename T, typename I>
void MyHashMap<T,I>::remove(const T* newEl) {
    if (lastIndexNode < 0)
        return;
    I newElHash = hashFunct(newEl);
    int currIndex = 0;
    while (true) {
        if (compFunct(&newElHash, &arrNodes[currIndex].hash) == 0) {
            int lastLeftRight = arrNodes[currIndex].r;
            if (lastLeftRight != -1) {
                while (arrNodes[lastLeftRight].l != -1)
                    lastLeftRight = arrNodes[lastLeftRight].l;
                int left = arrNodes[currIndex].l;
                if (left != -1) {
                    arrNodes[left].p=lastLeftRight;
                    arrNodes[lastLeftRight].l = left;
                }
            }
            if (arrNodes[currIndex].r !=-1 || arrNodes[currIndex].l != -1) {
                int *child = &arrNodes[currIndex].l;
                if (arrNodes[currIndex].r !=-1)
                    child = &arrNodes[currIndex].r;

                int parent = arrNodes[currIndex].p;
                int *currFromParent = &arrNodes[parent].r;
                if (arrNodes[parent].l == currIndex)
                    currFromParent = &arrNodes[parent].l;
                if (arrNodes[currIndex].r == lastIndexNode)
                    *currFromParent = currIndex;
                else
                    *currFromParent = *child;
                arrNodes[*child].p = parent;
            } else {
                int parent = arrNodes[currIndex].p;
                if (arrNodes[parent].l == currIndex)
                    arrNodes[parent].l = -1;
                else
                    arrNodes[parent].r = -1;
            }
            if (arrNodes[currIndex].p != -1) {
                if (currIndex != lastIndexNode) {
                    int parent = arrNodes[lastIndexNode].p;
                    if (arrNodes[parent].l == lastIndexNode)
                        arrNodes[parent].l = currIndex;
                    else
                        arrNodes[parent].r = currIndex;
                    if (arrNodes[lastIndexNode].l != -1)
                        arrNodes[arrNodes[lastIndexNode].l].p = currIndex;
                    if (arrNodes[lastIndexNode].r != -1)
                        arrNodes[arrNodes[lastIndexNode].r].p = currIndex;
                    arrNodes[currIndex] = arrNodes[lastIndexNode];
                }
            } else {
                int *child = nullptr;
                if (arrNodes[currIndex].r != -1)
                    child = &arrNodes[currIndex].r;
                else if (arrNodes[currIndex].l != -1)
                    child = &arrNodes[currIndex].l;
                if (child != nullptr) {
                    int parent = arrNodes[lastIndexNode].p;
                    if (arrNodes[parent].l == lastIndexNode)
                        arrNodes[parent].l = *child;
                    else
                        arrNodes[parent].r = *child;

                    if (arrNodes[lastIndexNode].l != -1)
                        arrNodes[arrNodes[lastIndexNode].l].p = *child;
                    if (arrNodes[lastIndexNode].r != -1)
                        arrNodes[arrNodes[lastIndexNode].r].p = *child;

                    ArrNode tmp = arrNodes[*child];
                    arrNodes[*child] = arrNodes[lastIndexNode];
                    arrNodes[currIndex] = tmp;
                }
                if (arrNodes[currIndex].l != -1)
                    arrNodes[arrNodes[currIndex].l].p = currIndex;
                if (arrNodes[currIndex].r != -1)
                    arrNodes[arrNodes[currIndex].r].p = currIndex;
            }
            arrNodes[lastIndexNode].l = -1;
            arrNodes[lastIndexNode].r = -1;
            arrNodes[lastIndexNode].p = -1;
            lastIndexNode--;
        }
        if(compFunct(&newElHash, &arrNodes[currIndex].hash) < 0) {
            if (arrNodes[currIndex].l==-1)
                return;
            else
                currIndex = arrNodes[currIndex].l;
        } else {
            if (arrNodes[currIndex].r == -1)
                return;
            else
                currIndex = arrNodes[currIndex].r;
        }
    }
}

template<typename T, typename I>
void MyHashMap<T,I>::printAll() {
    for (int i=0;i<=lastIndexNode;i++){
        cout << arrNodes[i].hash<< " " << arrNodes[i].l << " " << arrNodes[i].r << " " << arrNodes[i].p << endl;
    }
}


template<typename T, typename I>
MyHashMap<T,I>::MyHashMap(I (*hashFunct)(const T*), int (*compFunct)(const I*, const I*)){
    this->hashFunct = hashFunct;
    this->compFunct = compFunct;
    cout << "my_hash_map created" << endl;
}
template<typename T, typename I>
MyHashMap<T,I>::~MyHashMap(){
    delete [] arrNodes;
    cout << "my_hash_map deleted" << endl;
}

template<typename T, typename I>
void MyHashMap<T,I>::validateSize(){
    if (availableSize()>0)
        return;
    else {
        ArrNode *newArrNodes = new ArrNode[currArrSize?currArrSize*2:2];
        for (int i=0;i<currArrSize;i++)
            newArrNodes[i] = arrNodes[i];
        delete [] arrNodes;
        arrNodes = newArrNodes;
        currArrSize = currArrSize?currArrSize*2:2;
    }
}

template<typename T, typename I>
int MyHashMap<T,I>::availableSize() {
    return currArrSize-1 - lastIndexNode;
}
