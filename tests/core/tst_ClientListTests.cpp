#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QPoint>
#include <QSharedPointer>

#include "inc/core/Client.h"
#include "inc/core/ClientList.h"

using namespace testing;

namespace vrpspd::core
{

TEST(ClientListShould, returnTrueWhenAllClientsHaveBeenServed)
{
    ClientList clientList_;
    for (qint16 i=0; i<5; ++i)
    {
        const auto client = QSharedPointer<vrpspd::core::Client>::create(
            vrpspd::core::Client{i, QPoint{i,i}, i, i, true});
        clientList_.addClient(client);
    }

    EXPECT_TRUE(clientList_.allServed());
}

TEST(ClientListShould, returnFalseWhenOneOfClientsHaveNotBeenServed)
{
    ClientList clientList_;
    for (qint16 i=0; i<5; ++i)
    {
        const auto client = QSharedPointer<vrpspd::core::Client>::create(
            vrpspd::core::Client{i, QPoint{i,i}, i, i, true});
        clientList_.addClient(client);
    }

    const auto noServedClient = QSharedPointer<vrpspd::core::Client>::create(
        vrpspd::core::Client{7, QPoint{7,7}, 7, 7, false});
    clientList_.addClient(noServedClient);

    EXPECT_FALSE(clientList_.allServed());
}

} // vrpspd::core
