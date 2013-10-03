#include "gtest/gtest.h"
#include <set>
#include "vending_machine.h"

class vending_machine_test : public ::testing::Test, public Bin {

  public:
    void accept(CanType deliveredCan) {
      delivered_can = deliveredCan;
    }

  protected:
    vending_machine_test() : machine(*this), delivered_can(None) {}

    virtual void SetUp() {
      machine.add_choice(Fanta);
      machine.add_choice(Cola);
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


