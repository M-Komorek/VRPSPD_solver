#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QSharedPointer>

#include "inc/core/Client.h"
#include "inc/core/ClientList.h"
#include "inc/core/Route.h"

using namespace testing;

namespace vrpspd::core
{

TEST(RouteShould, addClientsIfRouteCapacityAlloweIt)
{
    Route route_{};
    for (qint16 i=1; i<9; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, 10, 10, true});
        route_.add(client);
    }

    const auto expectedRouteString = QString{
        "MAG -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> MAG"};
    const auto routeString = route_.toString();

    EXPECT_EQ(expectedRouteString, routeString);
}

TEST(RouteShould, doNotAddClientsIfRouteDeliveredQuantityWillBeExceeded)
{
    Route route_{};
    for (qint16 i=1; i<15; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, 10, 5, true});
        route_.add(client);
    }

    const auto expectedRouteString = QString{
        "MAG -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> MAG"};
    const auto routeString = route_.toString();

    EXPECT_EQ(expectedRouteString, routeString);
}

TEST(RouteShould, doNotAddClientsIfRoutePickedUpQuantityWillBeExceeded)
{
    Route route_{};
    for (qint16 i=1; i<15; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, 5, 10, true});
        route_.add(client);
    }

    const auto expectedRouteString = QString{
        "MAG -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> MAG"};
    const auto routeString = route_.toString();

    EXPECT_EQ(expectedRouteString, routeString);
}

TEST(RouteShould, addAdjacentClientAtTheBeginningIfRouteCapacityAlloweIt)
{
    Route route{};
    auto client1 = QSharedPointer<Client>::create(
        Client{1, QPoint{1,1}, 5, 10, true});
    auto client2 = QSharedPointer<Client>::create(
        Client{2, QPoint{2,2}, 5, 10, true});
    route.add(client1);
    route.add(client2);

    auto client4 = QSharedPointer<Client>::create(
        Client{4, QPoint{4,4}, 5, 10, true});
    route.addAdjacentClient(client4, client1);

    const auto expectedRouteString = QString{"MAG -> 4 -> 1 -> 2 -> MAG"};
    const auto routeString = route.toString();

    EXPECT_EQ(expectedRouteString, routeString);
}

TEST(RouteShould, addAdjacentClientAtTheEndIfRouteCapacityAlloweIt)
{
    Route route{};
    auto client1 = QSharedPointer<Client>::create(
        Client{1, QPoint{1,1}, 5, 10, true});
    auto client2 = QSharedPointer<Client>::create(
        Client{2, QPoint{2,2}, 5, 10, true});
    route.add(client1);
    route.add(client2);

    auto client4 = QSharedPointer<Client>::create(
        Client{4, QPoint{4,4}, 5, 10, true});
    route.addAdjacentClient(client4, client2);

    const auto expectedRouteString = QString{"MAG -> 1 -> 2 -> 4 -> MAG"};
    const auto routeString = route.toString();

    EXPECT_EQ(expectedRouteString, routeString);
}

TEST(RouteShould, returnTrueIfClientIsInRoute)
{
    Route route_{};
    for (qint16 i=1; i<5; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, 5, 10, true});
        route_.add(client);
    }

    const auto client = QSharedPointer<Client>::create(
        Client{3, QPoint{0,0}, 0, 0, false});

    EXPECT_TRUE(route_.isInRoute(client));
}

TEST(RouteShould, returnFalseIfClientIsNotInRoute)
{
    Route route_{};
    for (qint16 i=1; i<5; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, 5, 10, true});
        route_.add(client);
    }

    const auto client = QSharedPointer<Client>::create(
        Client{333, QPoint{0,0}, 0, 0, false});

    EXPECT_FALSE(route_.isInRoute(client));
}

TEST(RouteShould, returnTrueIfIsIternalClientAndFalseIfNot)
{
    Route route{};
    auto client1 = QSharedPointer<Client>::create(
        Client{1, QPoint{1,1}, 5, 10, true});
    auto client2 = QSharedPointer<Client>::create(
        Client{2, QPoint{2,2}, 5, 10, true});
    auto client3 = QSharedPointer<Client>::create(
        Client{3, QPoint{3,3}, 5, 10, true});
    auto client4 = QSharedPointer<Client>::create(
        Client{4, QPoint{4,4}, 5, 10, true});
    route.add(client1);
    route.add(client2);
    route.add(client3);
    route.add(client4);

    EXPECT_FALSE(route.isInternal(client1));
    EXPECT_TRUE (route.isInternal(client2));
    EXPECT_TRUE (route.isInternal(client3));
    EXPECT_FALSE(route.isInternal(client4));
}

TEST(RouteShould, returnFalseIfNotSameClientsInRoute)
{
    auto route_A = QSharedPointer<Route>::create();
    auto route_B = QSharedPointer<Route>::create();

    for (qint16 i=0; i<5; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, i, i, true});
        route_A->add(client);
    }

    EXPECT_FALSE(route_A->isRouteContainsSameClients(route_B));
}

TEST(RouteShould, returnTrueIfSameClientsInRoute)
{
    auto route_A = QSharedPointer<Route>::create();
    auto route_B = QSharedPointer<Route>::create();

    for (qint16 i=0; i<5; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, i, i, true});
        route_A->add(client);
        route_B->add(client);
    }

    EXPECT_TRUE(route_A->isRouteContainsSameClients(route_B));
}

TEST(RouteShould, returnTrueIfMergeRouteIsPossible)
{
    auto route_A = QSharedPointer<Route>::create();
    auto route_B = QSharedPointer<Route>::create();

    for (qint16 i=0; i<5; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, i, i, true});
        route_A->add(client);
        route_B->add(client);
    }

    EXPECT_TRUE(route_A->isMergeRoutePossible(route_B));
}

TEST(RouteShould, returnFalseIfMergeRouteIsNotPossible)
{
    auto route_A = QSharedPointer<Route>::create();
    auto route_B = QSharedPointer<Route>::create();

    for (qint16 i=0; i<5; ++i)
    {
        auto client = QSharedPointer<Client>::create(
            Client{i, QPoint{i,i}, 15, 15, true});
        route_A->add(client);
        route_B->add(client);
    }

    EXPECT_FALSE(route_A->isMergeRoutePossible(route_B));
}

} // vrpspd::core
