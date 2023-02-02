#include <gmock/gmock.h>
#include "../OrderCache.cpp"


class AugmentaCppTest_Tests : public testing::Test
{
protected:
	void SetUp() override
	{
	}

};


TEST_F(AugmentaCppTest_Tests, AddOrders)
{
  OrderCache testObj;
  testObj.addOrder(Order{"OrdId1", "SecId3", "Sell", 100, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId2", "SecId3", "Sell", 200, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId3", "SecId1", "Buy", 300, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId4", "SecId3", "Sell", 400, "User5", "Company2"});
  auto orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 4);

  testObj.addOrder(Order{"OrdId5", "SecId2", "Sell", 500, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId6", "SecId2", "Buy", 600, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId7", "SecId2", "Sell", 700, "User1", "Company1"});
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 7);

  testObj.addOrder(Order{"OrdId8", "SecId1", "Sell", 800, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId9", "SecId1", "Buy", 900, "User5", "Company2"});
  testObj.addOrder(Order{"OrdId10", "SecId1", "Sell", 1000, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"});
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 11);
}


TEST_F(AugmentaCppTest_Tests, CancelOrders)
{
  OrderCache testObj;
  testObj.addOrder(Order{"OrdId1", "SecId3", "Sell", 100, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId2", "SecId3", "Sell", 200, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId3", "SecId1", "Buy", 300, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId4", "SecId3", "Sell", 400, "User5", "Company2"});
  testObj.cancelOrder("OrdId1");
  auto orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 3);

  testObj.addOrder(Order{"OrdId5", "SecId2", "Sell", 500, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId6", "SecId2", "Buy", 600, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId7", "SecId2", "Sell", 700, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId8", "SecId1", "Sell", 800, "User2", "Company1"});
  testObj.cancelOrder("OrdId7");
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 6);

  testObj.cancelOrder("InvalidOrdId7");
  testObj.cancelOrder("InvalidOrdId8");
  testObj.cancelOrder("InvalidOrdId9");
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 6);
}


TEST_F(AugmentaCppTest_Tests, CancelOrdersForUser)
{
  OrderCache testObj;
  testObj.addOrder(Order{"OrdId1", "SecId3", "Sell", 100, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId2", "SecId3", "Sell", 200, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId3", "SecId1", "Buy", 300, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId4", "SecId3", "Sell", 400, "User5", "Company2"});
  testObj.cancelOrdersForUser("User1");
  auto orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 2);

  testObj.addOrder(Order{"OrdId5", "SecId2", "Sell", 500, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId6", "SecId2", "Buy", 600, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId7", "SecId2", "Sell", 700, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId8", "SecId1", "Sell", 800, "User2", "Company1"});
  testObj.cancelOrdersForUser("User1");
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 5);

  testObj.cancelOrdersForUser("User1");
  testObj.cancelOrdersForUser("User2");
  testObj.cancelOrdersForUser("User3");
  testObj.cancelOrdersForUser("User5");
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.empty());
}


TEST_F(AugmentaCppTest_Tests, CancelOrdersForSecIdMinimumQty)
{
  OrderCache testObj;
  testObj.addOrder(Order{"OrdId1", "SecId3", "Sell", 100, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId2", "SecId3", "Sell", 200, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId3", "SecId1", "Buy", 300, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId4", "SecId3", "Sell", 400, "User5", "Company2"});
  testObj.cancelOrdersForSecIdWithMinimumQty("SecId3", 300);
  auto orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 3);

  testObj.addOrder(Order{"OrdId5", "SecId2", "Sell", 500, "User2", "Company1"});
  testObj.addOrder(Order{"OrdId6", "SecId2", "Buy", 600, "User3", "Company2"});
  testObj.addOrder(Order{"OrdId7", "SecId2", "Sell", 700, "User1", "Company1"});
  testObj.addOrder(Order{"OrdId8", "SecId1", "Sell", 800, "User2", "Company1"});
  testObj.cancelOrdersForSecIdWithMinimumQty("SecId2", 600);
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.size() == 5);

  testObj.cancelOrdersForSecIdWithMinimumQty("SecId1", 0);
  testObj.cancelOrdersForSecIdWithMinimumQty("SecId2", 0);
  testObj.cancelOrdersForSecIdWithMinimumQty("SecId3", 0);
  orders = testObj.getAllOrders();
  ASSERT_TRUE(orders.empty());
}


TEST_F(AugmentaCppTest_Tests, MatchingSizeTest1)
{
  OrderCache test1_cache;
  test1_cache.addOrder(Order{"OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"});
  test1_cache.addOrder(Order{"OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB"});
  test1_cache.addOrder(Order{"OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"});
  test1_cache.addOrder(Order{"OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC"});
  test1_cache.addOrder(Order{"OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB"});
  test1_cache.addOrder(Order{"OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD"});
  test1_cache.addOrder(Order{"OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE"});
  test1_cache.addOrder(Order{"OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE"});
  ASSERT_TRUE(test1_cache.getMatchingSizeForSecurity("SecId1") == 0);
  ASSERT_TRUE(test1_cache.getMatchingSizeForSecurity("SecId2") == 2700);
  ASSERT_TRUE(test1_cache.getMatchingSizeForSecurity("SecId3") == 0);
}


TEST_F(AugmentaCppTest_Tests, MatchingSizeTest2)
{
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
  ASSERT_TRUE(test2_cache.getMatchingSizeForSecurity("SecId1") == 300);
  ASSERT_TRUE(test2_cache.getMatchingSizeForSecurity("SecId2") == 1000);
  ASSERT_TRUE(test2_cache.getMatchingSizeForSecurity("SecId3") == 600);
}


TEST_F(AugmentaCppTest_Tests, MatchingSizeTest3)
{
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
  ASSERT_TRUE(test3_cache.getMatchingSizeForSecurity("SecId1") == 900);
  ASSERT_TRUE(test3_cache.getMatchingSizeForSecurity("SecId2") == 600);
  ASSERT_TRUE(test3_cache.getMatchingSizeForSecurity("SecId3") == 0);
}


int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
