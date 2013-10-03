#ifndef _VENDING_MACHINE_H
#define _VENDING_MACHINE_H

enum CanType { None, Cola, Fanta, Beer };

class Bin {
  public :
    virtual void accept(CanType deliveredCan) = 0;
};

class VendingMachine {
  public:
    VendingMachine(Bin& deliverTo) : bin(deliverTo) {}

    void add_choice(CanType canType) {
      choices.insert(canType);
    }

    void deliver(CanType choice) {
      std::set<CanType>::iterator result = choices.find(choice);
      if (result != choices.end()) 
        bin.accept(*result);
      else 
        bin.accept(None);
    }


  private:
    std::set<CanType> choices;
    Bin& bin;
};


#endif // _VENDING_MACHINE_H
