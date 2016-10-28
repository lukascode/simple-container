#ifndef MYLIST_H
#define MYLIST_H


namespace algo {

template <class T>
class Node {
public:
  T data;
  Node* prev;
  Node* next;

  Node() {
    prev = 0;
    next = 0;
  }

  Node(const T& ddata,Node* prev,Node* next) : data(ddata) {
    this->prev = prev;
    this->next = next;
  }

  ~Node() {

  }


};

template <class T>
class MyList {

public:

  MyList() {
    head = 0;
    tail = 0;
    size = 0;
  }

  MyList(const T& arg,unsigned int ssize) {
    head = 0; tail = 0; size = 0;
    for(unsigned int i = 0; i<ssize; ++i) {
      push_front(arg);
    }
  }

  MyList(MyList<T> const& ml) {
    head = 0; tail = 0; size = 0;
    for(unsigned int i = 0; i<ml.getSize(); ++i) {
       push_back(ml[i]);
    }
  }

  ~MyList() {
    clear();
  }

  void push_back(const T& arg) {
    if(!head) {
      head = new Node<T>(arg,0,0);
      tail = head;
    } else {
      tail->next = new Node<T>(arg,tail,0);
      tail = tail->next;
    }
    ++size;
  }

  void push_front(const T& arg) {
    Node<T>* tmp = new Node<T>(arg,0,head);
    if(head)
      head->prev = tmp;
      else tail = tmp;


    head = tmp;
    ++size;
  }

  void pop_front() {
    if(head) {
      if(head == tail) tail = 0;
      Node<T>* tmp = head->next;
      if(tmp)
      tmp->prev = 0;
      delete head;
      head = tmp;
      --size;
    }
  }

  void pop_back() {
    if(tail) {
      if(head == tail) head = 0;
      Node<T>* tmp = tail->prev;
      if(tmp)
      tmp->next = 0;
      delete tail;
      tail = tmp;
      --size;
      }
  }

  void remove_from(unsigned int i) {
      Node<T>* tmp = find(i);
      if(!tmp) return;
      Node<T>* next = tmp->next;
      Node<T>* prev = tmp->prev;

      if(next && prev) {
        delete next->prev;
        prev->next = next;
        next->prev = prev;
      } else if(!next) {
        pop_back();
      } else {
        pop_front();
      }
      --size;
  }

  void insert_into(const T& arg,unsigned int i) {
    Node<T>* tmp = find(i);
    if(!tmp) return;
    Node<T>* next = tmp->next;
    tmp->next = new Node<T>(arg,tmp,next);
    if(next) next->prev = tmp->next;
    else tail = tmp->next;
    ++size;
    }

  void replace(unsigned int i,unsigned int j) {

    Node<T>* tmpi = find(i);
    Node<T>* tmpj = find(j);

    if(!tmpi || !tmpj || (i==j)) return;

    Node<T>* nexti = tmpi->next;
    Node<T>* previ = tmpi->prev;

    Node<T>* nextj = tmpj->next;
    Node<T>* prevj = tmpj->prev;

    if(nexti == tmpj) {
      replace_congruent(tmpi,tmpj);
    } else if(nextj == tmpi) {
      replace_congruent(tmpj,tmpi);
    } else {
      if(!nexti && !prevj) {
        tail = tmpj;
        head = tmpi;

        tmpj->next = nexti;
        tmpj->prev = previ;
        previ->next = tmpj;

        tmpi->prev = prevj;
        tmpi->next = nextj;
        nextj->prev = tmpi;

      } else if(!nextj && !previ) {
        tail = tmpi;
        head = tmpj;

        tmpj->next = nexti;
        tmpj->prev = previ;
        nexti->prev = tmpj;

        tmpi->next = nextj;
        tmpi->prev = prevj;
        prevj->next = tmpi;

      } else if(!nexti) {
        tail = tmpj;

        tmpj->next = nexti;
        tmpj->prev = previ;
        previ->next = tmpj;

        tmpi->next = nextj;
        tmpi->prev = prevj;
        prevj->next = tmpi;
        nextj->prev = tmpi;

      } else if(!nextj) {

        tail = tmpi;

        tmpi->next = nextj;
        tmpi->prev = prevj;
        prevj->next = tmpi;

        tmpj->next = nexti;
        tmpj->prev = previ;
        previ->next = tmpj;
        nexti->prev = tmpj;

      } else if(!previ) {

        head = tmpj;

        tmpj->prev = previ;
        tmpj->next = nexti;
        nexti->prev = tmpj;

        tmpi->prev = prevj;
        tmpi->next = nextj;
        prevj->next = tmpi;
        nextj->prev = tmpi;

      } else if(!prevj) {
        head = tmpi;

        tmpi->prev = prevj;
        tmpi->next = nextj;
        nextj->prev = tmpi;

        tmpj->prev = previ;
        tmpj->next = nexti;
        previ->next = tmpj;
        nexti->prev = tmpj;

      } else {

        tmpi->next = nextj;
        tmpi->prev = prevj;
        nextj->prev = tmpi;
        prevj->next = tmpi;

        tmpj->next = nexti;
        tmpj->prev = previ;
        nexti->prev = tmpj;
        previ->next = tmpj;

      }
    }

  }


  void clear() {

    while(head) {
      pop_front();
    }
    size = 0;
  }

  unsigned int getSize() const { return size; }

    T& operator[](unsigned int i) const {
        return find(i)->data;
    }

    bool exist(const T& arg) {
        Node<T>* tmp = head;
        while(tmp) {
          if(tmp->data == arg) return true; //In complex type T operator == must be added to class by programmer
          tmp = tmp->next;
        }
        return false;
      }

private:
  Node<T>* head;
  Node<T>* tail;
  unsigned int size;


  Node<T>* find(unsigned int i) const {
    if(i > (size-1)) return 0;
    Node<T>* tmp = head;
    while(i>0) {
      tmp = tmp->next;
      --i;
    }
    return tmp;
  }

  void replace_congruent(Node<T>* left,Node<T>* right) {
        if(!left->prev && !right->next) {
          head = right;
          tail = left;
          left->next = right->next;
          left->prev = right;
          right->next = left;
          right->prev = 0;
        } else if(!left->prev) {
          head = right;
          left->next = right->next;
          right->next->prev = left;
          right->next = left;
          left->prev = right;
          right->prev = 0;
        } else if(!right->next) {
          tail = left;
          right->prev = left->prev;
          left->prev->next = right;
          right->next = left;
          left->prev = right;
          left->next = 0;
        } else {
          left->prev->next = right;
          right->next->prev = left;
          right->prev = left->prev;
          left->next = right->next;
          right->next = left;
          left->prev = right;
        }
    }


};
//////////////////////////////////////////

template<class T>
class Stack : private MyList<T> {
  public:
  Stack() {}
  Stack(Stack<T> const& s) : MyList<T>::MyList(s) {}


  void push(const T& arg) {
    MyList<T>::push_front(arg);
  }

  void pop() {
    MyList<T>::pop_front();
  }

  bool empty() {
    if(MyList<T>::getSize() == 0) return true;
    return false;
  }

  const T& top() {
    return MyList<T>::operator[](0);
  }

  unsigned int Size() { return MyList<T>::getSize(); }

  void clear() {
    MyList<T>::clear();
  }

protected:
  void push_back(const T& arg) {
    MyList<T>::push_back(arg);
  }

};

template<class T>
class Queue : public Stack<T> {
  public:

    Queue() {}
    Queue(Queue<T> const& q) : Stack<T>::Stack(q) {}

    void push(const T& arg) {
      Stack<T>::push_back(arg);
    }

    void clear() {
      Stack<T>::clear();
    }
};



template<class T>
using Compare = bool (*)( T const& arg1,T const& arg2);

template<class T>
class priorQueue : private MyList<T> {
  public:
    priorQueue() {}
    priorQueue(priorQueue<T> const& pq) : MyList<T>::MyList(pq) {}

    priorQueue(Compare<T> cmpr,bool dirr) {
        cmp = cmpr;
        dir = dirr;
    }
    void push(T const & arg) {
      unsigned int k=0;
      if(dir) {
        while( (Size()-k != 0) && cmp( MyList<T>::operator[](k),arg) ) ++k;
      } else {
        while( (Size()-k != 0) && cmp(arg,MyList<T>::operator[](k)) ) ++k;
      }
      if(k==0) { MyList<T>::push_front(arg); }
      else MyList<T>::insert_into(arg,k-1);
      }

    void pop() {
      MyList<T>::pop_front();
    }

    bool empty() {
      if(MyList<T>::getSize() == 0) return true;
      return false;
    }

    const T& top() {
      return MyList<T>::operator[](0);
    }

    unsigned int Size() { return MyList<T>::getSize(); }

    void clear() {
      MyList<T>::clear();
    }

  private:
    static Compare<T> cmp;
    static bool dir;

};


template<class T> Compare<T> priorQueue<T>::cmp = 0;
template<class T> bool priorQueue<T>::dir = 0;


/////////////////////////////////////////

//-----



template<class T>
class Qsort {

public:
  static void sort(MyList<T>& mylist,Compare<T> cc,bool dd) {
    dir = dd;
    cmp = cc;

    //choice_sort(mylist);
      quicksort(mylist,0,mylist.getSize()-1);
  }


private:
  static bool dir; //1-asc,0-desc
  static bool (*cmp)(T const& arg1,T const& arg2); //it has to return true when arg1 < arg2 and false otherwise

   static void choice_sort(MyList<T>& mylist) {
     unsigned int min_max;
     for(unsigned int i=0; i<mylist.getSize()-1; ++i) {
       min_max = i;
       for(unsigned int j=i+1; j<mylist.getSize(); ++j) {
         if(dir) {
           if(cmp(mylist[j],mylist[min_max])) min_max = j;
         } else {
           if(cmp(mylist[min_max],mylist[j])) min_max = j;
         }
       }
       mylist.replace(i,min_max);
      }
    }

    //for 5000 point structures it return result over ~2000ms (choice sort ~400 000 ms)
    static void quicksort(MyList<T>& mylist,int left,int right) {
      int i = left;
      int j = right;
      const T& v = mylist[(left+right)/2];

      do {
          if(dir) {

            while( cmp(mylist[i],v) ) ++i;
            while( cmp(v,mylist[j]) ) --j;

          } else {

            while( cmp(v,mylist[i]) ) ++i;
            while( cmp(mylist[j],v) ) --j;

          }

          if(i<=j) {
          mylist.replace(i,j);
          ++i; --j;
        }

      } while(i<=j);
      if(left<j) quicksort(mylist,left,j);
      if(right>i) quicksort(mylist,i,right);

    }

};


template<class T> bool Qsort<T>::dir = 0;
template<class T> Compare<T> Qsort<T>::cmp = 0;



}


#endif // MYLIST_H ///:~
