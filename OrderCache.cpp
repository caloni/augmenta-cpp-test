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
  int msize = 0;
  vector<Order> orders;
  copy_if(m_orders.begin(), m_orders.end(), back_inserter(orders),
    [&securityId](const Order& ord) { return ord.securityId() == securityId; });

  for (auto ordOp1 = orders.begin(); ordOp1 != orders.end(); ++ordOp1)
  {
    for (auto ordOp2 = ordOp1 + 1; ordOp2 != orders.end(); ++ordOp2)
    {
      if (ordOp1->qty() && ordOp2->qty()
        && ordOp1->side() != ordOp2->side()
        && ordOp1->company() != ordOp2->company())
      {
        int m = min(ordOp1->qty(), ordOp2->qty());
        ordOp1->qty(ordOp1->qty() - m);
        ordOp2->qty(ordOp2->qty() - m);
        msize += m;
      }
    }
  }

  return msize;
}


std::vector<Order> OrderCache::getAllOrders() const
{
  return m_orders;
}

