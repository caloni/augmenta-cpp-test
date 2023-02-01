#include <iostream>
#include <cassert>
#include "OrderCache.h"

int main()
{
  // Test 1
  OrderCache test1_cache;
  test1_cache.addOrder(Order{"OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"});
  test1_cache.addOrder(Order{"OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB"});
  test1_cache.addOrder(Order{"OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"});
  test1_cache.addOrder(Order{"OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC"});
  test1_cache.addOrder(Order{"OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB"});
  test1_cache.addOrder(Order{"OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD"});
  test1_cache.addOrder(Order{"OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE"});
  test1_cache.addOrder(Order{"OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE"});
  std::cout << "TEST 1" << std::endl;
  std::cout << "SecId1: " << test1_cache.getMatchingSizeForSecurity("SecId1") << std::endl; // SecId1: 0
  std::cout << "SecId2: " << test1_cache.getMatchingSizeForSecurity("SecId2") << std::endl; // SecId2: 2700
  std::cout << "SecId3: " << test1_cache.getMatchingSizeForSecurity("SecId3") << std::endl; // SecId3: 0
  assert(test1_cache.getMatchingSizeForSecurity("SecId1") == 0);
  assert(test1_cache.getMatchingSizeForSecurity("SecId2") == 2700);
  assert(test1_cache.getMatchingSizeForSecurity("SecId3") == 0);

  // Test 2
  OrderCache test2_cache;
  test2_cache.addOrder(Order{"OrdId1", "SecId1", "Sell", 100, "User10", "Company2"});
  test2_cache.addOrder(Order{"OrdId2", "SecId3", "Sell", 200, "User8", "Company2"});
  test2_cache.addOrder(Order{"OrdId3", "SecId1", "Buy", 300, "User13", "Company2"});
  test2_cache.addOrder(Order{"OrdId4", "SecId2", "Sell", 400, "User12", "Company2"});
  test2_cache.addOrder(Order{"OrdId5", "SecId3", "Sell", 500, "User7", "Company2"});
  test2_cache.addOrder(Order{"OrdId6", "SecId3", "Buy", 600, "User3", "Company1"});
  test2_cache.addOrder(Order{"OrdId7", "SecId1", "Sell", 700, "User10", "Company2"});
  test2_cache.addOrder(Order{"OrdId8", "SecId1", "Sell", 800, "User2", "Company1"});
  test2_cache.addOrder(Order{"OrdId9", "SecId2", "Buy", 900, "User6", "Company2"});
  test2_cache.addOrder(Order{"OrdId10", "SecId2", "Sell", 1000, "User5", "Company1"});
  test2_cache.addOrder(Order{"OrdId11", "SecId1", "Sell", 1100, "User13", "Company2"});
  test2_cache.addOrder(Order{"OrdId12", "SecId2", "Buy", 1200, "User9", "Company2"});
  test2_cache.addOrder(Order{"OrdId13", "SecId1", "Sell", 1300, "User1", "Company"});
  std::cout << "TEST 2" << std::endl;
  std::cout << "SecId1: " << test2_cache.getMatchingSizeForSecurity("SecId1") << std::endl; // SecId1: 300
  std::cout << "SecId2: " << test2_cache.getMatchingSizeForSecurity("SecId2") << std::endl; // SecId2: 1000
  std::cout << "SecId3: " << test2_cache.getMatchingSizeForSecurity("SecId3") << std::endl; // SecId3: 600
  assert(test2_cache.getMatchingSizeForSecurity("SecId1") == 300);
  assert(test2_cache.getMatchingSizeForSecurity("SecId2") == 1000);
  assert(test2_cache.getMatchingSizeForSecurity("SecId3") == 600);

  // Test 3
  OrderCache test3_cache;
  test3_cache.addOrder(Order{"OrdId1", "SecId3", "Sell", 100, "User1", "Company1"});
  test3_cache.addOrder(Order{"OrdId2", "SecId3", "Sell", 200, "User3", "Company2"});
  test3_cache.addOrder(Order{"OrdId3", "SecId1", "Buy", 300, "User2", "Company1"});
  test3_cache.addOrder(Order{"OrdId4", "SecId3", "Sell", 400, "User5", "Company2"});
  test3_cache.addOrder(Order{"OrdId5", "SecId2", "Sell", 500, "User2", "Company1"});
  test3_cache.addOrder(Order{"OrdId6", "SecId2", "Buy", 600, "User3", "Company2"});
  test3_cache.addOrder(Order{"OrdId7", "SecId2", "Sell", 700, "User1", "Company1"});
  test3_cache.addOrder(Order{"OrdId8", "SecId1", "Sell", 800, "User2", "Company1"});
  test3_cache.addOrder(Order{"OrdId9", "SecId1", "Buy", 900, "User5", "Company2"});
  test3_cache.addOrder(Order{"OrdId10", "SecId1", "Sell", 1000, "User1", "Company1"});
  test3_cache.addOrder(Order{"OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"});
  std::cout << "TEST 3" << std::endl;
  std::cout << "SecId1: " << test3_cache.getMatchingSizeForSecurity("SecId1") << std::endl; // SecId1: 900
  std::cout << "SecId2: " << test3_cache.getMatchingSizeForSecurity("SecId2") << std::endl; // SecId2: 600
  std::cout << "SecId3: " << test3_cache.getMatchingSizeForSecurity("SecId3") << std::endl; // SecId3: 0
  assert(test3_cache.getMatchingSizeForSecurity("SecId1") == 900);
  assert(test3_cache.getMatchingSizeForSecurity("SecId2") == 600);
  assert(test3_cache.getMatchingSizeForSecurity("SecId3") == 0);

  return 0;
}
