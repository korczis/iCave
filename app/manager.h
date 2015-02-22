#ifndef ICAVE_MANAGER_H
#define ICAVE_MANAGER_H

#include <vector>
#include <map>
#include <string>

extern unsigned long last_tick;

namespace iCave {
  class Module;
  
  class Manager {
  public:
    void setup();
    void loop();

    template<typename T> 
    inline T* createModule() {
      T* res = new T(this);
      return res;
    }
    
    template<typename T>
    T* registerModule(T* module) {
      mModules.push_back(module);
      return module;
    }
    
    template<typename T>
    inline T* createAndRegisterModule() {
      return registerModule<T>(createModule<T>());
    }
    
    static void printInfo();
    
  private:
    std::vector<Module*> mModules;
    
  }; // class Manager
}; // namespace iCave

#endif // ICAVE_MANAGER_H


