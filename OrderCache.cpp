#include "OrderCache.h"
#include <algorithm>
#include <iterator>

using namespace std;


void OrderCache::addOrder(Order order)
{
  m_orders.push_back(order);
}


void OrderCache::cancelOrder(const std::string& orderId)
{
  auto fndOrd = find_if(m_orders.begin(), m_orders.end(),
    [&orderId](const Order& ord) { return ord.orderId() == orderId; } );

  if (fndOrd != m_orders.end())
  {
    m_orders.erase(fndOrd);
  }
}


void OrderCache::cancelOrdersForUser(const std::string& user)
{
  auto newEnd = remove_if(m_orders.begin(), m_orders.end(),
    [&user](const Order& ord) { return ord.user() == user; } );
  m_orders.resize(distance(m_orders.begin(), newEnd));
}


void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
  auto newEnd = remove_if(m_orders.begin(), m_orders.end(),
    [&securityId, &minQty](const Order& ord) { return ord.securityId() == securityId && ord.qty() >= minQty; } );
  m_orders.resize(distance(m_orders.begin(), newEnd));
}


unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
  // TODO: implement it
  return 0;
}


std::vector<Order> OrderCache::getAllOrders() const
{
  return m_orders;
}

