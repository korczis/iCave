#ifndef ICAVE_MANAGER_H
#define ICAVE_MANAGER_H

#include "module.h"

#include <vector>
#include <map>
#include <cstring>

extern unsigned long last_tick;

namespace iCave {
  class Module;
  
  /**
   * @brief Central brain of teensy application
   *
   * Features:
   * - Module registration
   * - Modules factory (TBD)
   * - High level wrapper of:
   *   - setup()
   *     - Init registered modules
   *   - loop()
   *     - Loop registered modules
   */
  class Manager {
  public:
    /**
     * @brief Print information about ENABLED_* defines
     * NOTE: This is hand crafted
     * TODO: Engage some magic to eliminate hand crafting
     */
    static void printInfo();
  
    /**
     * @brief High-level wrapper of setup() for all registered modules
     */
    void setup();
    
    /**
     * @brief High-level wrapper of loop() for all registered modules
     */
    void loop();

    /**
     * @brief Create module and register and set ownership to 'this' manager
     */
    template<typename T> 
    inline T* createModule() {
      T* res = new T(this);
      return res;
    }
    
    /**
     * @brief Register module to this manager - for setup() and loop()
     */ 
    template<typename T>
    T* registerModule(T* module) {
      mModules.push_back(module);
      return module;
    }
    
    /**
     * @brief Create module, set ownership and register to manager. See createModule() and registerModule()
     */
    template<typename T>
    inline T* createAndRegisterModule() {
      return registerModule<T>(createModule<T>());
    }
        
    /**
     * @brief Get registered module by its name
     * NOTE: This implementation is quite naiive now
     * TODO: Use some kind of caching for lookup - hash map, etc
     */
    template<typename T>
    inline T* getModule(const char* name) {
      for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
        Module* m = (*i);
        if(strcmp(name, m->name()) == 0) {
        }
      }
      return NULL;
    }
    
  private:
    /**
     * @brief Internal container for registered modules
     * TODO: Consider using of linked list
     * TODO: Consider hash map based caching for "module name to module instance" lookups (see iCave::Manager::getModule())
     */
    std::vector<Module*> mModules;
    
  }; // class Manager
}; // namespace iCave

#endif // ICAVE_MANAGER_H


