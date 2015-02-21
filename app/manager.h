#ifndef ICAVE_MANAGER_H
#define ICAVE_MANAGER_H

#include <vector>

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
    
    Module* registerModule(Module* module) {
      mModules.push_back(module);
      return module;
    }
    
    template<typename T>
    inline Module* createAndRegisterModule() {
      return registerModule(createModule<T>());
    }
    
    static void printInfo();
    
  private:
    std::vector<Module*> mModules;
  }; // class Manager
}; // namespace iCave

#endif // ICAVE_MANAGER_H


