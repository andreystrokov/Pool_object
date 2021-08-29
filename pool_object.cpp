//#include <C:\Users\ASUS\Desktop\Programming\Profiler.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <deque>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
      if(Liberated.empty()){
          T* ptr = new T;
          Allocated.insert(ptr);
          return ptr;
      } else {
          T* ptr = Liberated.front();
            Allocated.insert(ptr);
            Liberated.pop_front();
          return ptr;
      }
  };
  T* TryAllocate(){
      if(Liberated.empty()){
          return nullptr;
      } else {
          T* ptr = Liberated.front();
          Allocated.insert(ptr);
          Liberated.pop_front();
          return ptr;
      }
  };
  void Deallocate(T* object){

      auto it = Allocated.find(object);
      if(it == Allocated.end()){
          throw invalid_argument("");
      }
      Liberated.push_back(*it);
      Allocated.erase(it);
  };
  ~ObjectPool(){
      for (auto& e : Allocated) {
          delete e;
      }
      Allocated.clear();
      while (!Liberated.empty()) {
          delete Liberated.front();
          Liberated.pop_front();
      }
  };
private:
    set<T*>Allocated;
        deque<T*> Liberated;
};


int main() {
    ObjectPool<string> pool;

        auto p1 = pool.Allocate();
        auto p2 = pool.Allocate();
        auto p3 = pool.Allocate();


        *p1 = "first";
        *p2 = "second";
        *p3 = "third";
        pool.Deallocate(p1);

        auto p4 = pool.Allocate();

    return 0;
}
