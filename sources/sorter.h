#ifndef SORTER_H
#define SORTER_H

namespace algo {

template<class T>
class Sorter {

public:

  static void sort(T* table,unsigned int ssize,bool direction) {
    size = ssize;
    dir = direction;
    quicksort(table,0,size-1);
  }


private:
  static bool dir;
  static unsigned int size;

  static bool compare(T a,T b) {
    if(dir) {
      return a<b;
    } else {
      return a>b;
    }
  }

  static void quicksort(T* table,int left, int right) {
    int i=left,j=right,x=table[(left+right)/2];

    do {
      while(compare(table[i],x)) ++i;
      while(compare(x,table[j])) --j;

      if(i<=j) {
        T temp = table[i];
        table[i] = table[j];
        table[j] = temp;
        ++i; --j;
      }
    } while(i<=j);
    if(left<j) quicksort(table,left,j);
    if(right>i) quicksort(table,i,right);
  }

};

template<class T> bool Sorter<T>::dir = 0;
template<class T> unsigned int Sorter<T>::size = 0;

}

void scal(int* T,int left,int s,int right) {
  int* temp = new int[right-left+1];
  int i = left,j = s+1,k=0;

  while(i<=s && j<=right) {
    if(T[i]<=T[j]) {
      temp[k] = T[i];
      ++i;
    } else {
      temp[k] = T[j];
      ++j;
    }
    ++k;
  }

  if(i>s) {
    while(j<=right) {
      temp[k] = T[j];
      ++k; ++j;
    }
  } else {
    while(i<=s) {
      temp[k] = T[i];
      ++k; ++i;
    }
  }

  k=0;
  for(int p = left; p<=right; p++) {
    T[p] = temp[k]; ++k;
  }

}

void mergesort(int* T,int left,int right) {
  int piv = (left+right)/2;
  if(left<piv) mergesort(T,left,piv);
  if(right>piv+1) mergesort(T,piv+1,right);
  scal(T,left,piv,right);
}


#endif // SORTER_H ///:~
