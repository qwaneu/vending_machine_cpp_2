#include "gtest/gtest.h"
#include <set>

enum CanType { None, Cola, Fanta };

CanType delivered_can = None;
std::set<CanType> choices;

void add_choice(CanType canType) {
  choices.insert(canType);
}

void deliver(CanType choice) {
  std::set<CanType>::iterator result = choices.find(choice);
  if (result != choices.end()) 
    delivered_can = *result;
  else 
    delivered_can = None;
}

class vending_machine_test : public ::testing::Test {
  protected:
    void deliver(CanType choice) {
      ::deliver(choice);
    }
};

TEST_F(vending_machine_test, choiceless_machine_deliver_nothing)
{
  deliver(Cola);
  ASSERT_EQ(None,delivered_can);
}

TEST_F(vending_machine_test, machine_with_cola_delivers_cola_when_asked_for)
{
  add_choice(Cola);
  deliver(Cola);
  ASSERT_EQ(Cola, delivered_can);
}

TEST_F(vending_machine_test, machine_with_fanta_delivers_fanta_when_asked_for)
{
  add_choice(Fanta);
  add_choice(Cola);
  deliver(Fanta);
  ASSERT_EQ(Fanta, delivered_can);
}


