#ifndef ICAVE_CORE_H
#define ICAVE_CORE_H
  #include "module.h"
  
  namespace iCave {
    class CoreModule : public Module {
    public:
      CoreModule(Manager* manager) : Module(manager) {} 
      
      virtual const char* name() const { 
        return "core";
      }
      
      /* virtual */ void setup();
    }; // class CoreModule    
  }; // namespace iCave
  
#endif // ICAVE_CORE_H

