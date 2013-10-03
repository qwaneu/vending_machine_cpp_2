#include "gtest/gtest.h"
#include <set>

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

class vending_machine_test : public ::testing::Test, public Bin {

  public:
    void accept(CanType deliveredCan) {
      delivered_can = deliveredCan;
    }

  protected:
    vending_machine_test() : machine(*this), delivered_can(None) {}

    virtual void SetUp() {
      add_choice(Fanta);
      add_choice(Cola);
    }

    void add_choice(CanType canType) {
      machine.add_choice(canType);
    }
    CanType deliver(CanType choice) {
      machine.deliver(choice);
      return delivered_can;
    }

    VendingMachine machine;
    CanType delivered_can;
};

TEST_F(vending_machine_test, illegal_choice_delivers_nothing)
{
  ASSERT_EQ(None,deliver(Beer));
}

TEST_F(vending_machine_test, machine_delivers_can_of_choice)
{
  ASSERT_EQ(Cola, deliver(Cola));
  ASSERT_EQ(Fanta, deliver(Fanta));
}


