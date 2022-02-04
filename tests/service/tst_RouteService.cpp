#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QPoint>

#include "inc/core/Client.h"
#include "inc/core/ClientList.h"
#include "inc/core/Saving.h"

#include "inc/service/ComputingService.h"
#include "inc/service/RouteService.h"

#include <QDebug>

namespace vrpspd::service
{

TEST(RouteService, ShouldAddClientsToRouteInCorretWay)
{
    auto clientList = core::ClientList{};
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{1, QPoint{21, 21}, 0, 17, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{2, QPoint{25, 25}, 0, 25, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{3, QPoint{20, 44}, 0, 10, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{4, QPoint{44, 34}, 0, 29, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{5, QPoint{54, 19}, 0, 20, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{6, QPoint{54, 44}, 0, 15, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{7, QPoint{25, 58}, 0, 28, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{8, QPoint{54, 64}, 0, 36, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{9, QPoint{18, 27}, 0, 14, false}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{10, QPoint{38, 50}, 0, 24, false}));
    clientList.addWarehouse(QPoint{39, 39});

    const auto computingService = ComputingService(clientList.getClients());
    const auto savingVector = computingService.getSavingVector();

    auto routeService = RouteService();

    foreach (const auto save, savingVector)
    {
        routeService.addClientsToRoute(save.client_i(), save.client_j());
    }

    const auto expectedRoute1 = "MAG -> 3 -> 7 -> 2 -> 1 -> 9 -> MAG";
    const auto expectedRoute2 = "MAG -> 5 -> 6 -> 8 -> 10 -> MAG";

    EXPECT_EQ(routeService.getRoutes().first()->toString(), expectedRoute1);
    EXPECT_EQ(routeService.getRoutes().last()->toString(),  expectedRoute2);
}

} // vrpspd::service
