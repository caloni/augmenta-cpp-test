#include "OrderCache.h"


void OrderCache::addOrder(Order order)
{
  // TODO: implement it
}


void OrderCache::cancelOrder(const std::string& orderId)
{
  // TODO: implement it
}


void OrderCache::cancelOrdersForUser(const std::string& user)
{
  // TODO: implement it
}


void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
  // TODO: implement it
}


unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
  // TODO: implement it
  return 0;
}


std::vector<Order> OrderCache::getAllOrders() const
{
  // TODO: implement it
  std::vector<Order> ret;
  return ret;
}

