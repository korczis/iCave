#ifndef ICAVE_MODULE_H
#define ICAVE_MODULE_H

  namespace iCave {
    class Manager;
    
    class Module {
    public:
      Module(Manager* manager) : mManager(manager) {}
      virtual ~Module();
      
      virtual void setup() {};
      virtual void loop() {};
      
    protected:
      Manager* mManager;  
    }; // class Module
  }; // namespace iCave
  
#endif // ICAVE_MODULE_H

