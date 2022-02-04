#include "inc/solver/Solver.h"

#include <QSharedPointer>

#include "inc/core/Client.h"
#include "inc/service/ComputingService.h"

#include <QDebug>

namespace vrpspd
{

Solver::Solver(QObject *parent)
    : QObject(parent)
{

}

Solver::~Solver()
{

}

void Solver::addClient(const qint16 id,
    const qint16 XCoordinate,
    const qint16 YCoordinate,
    const qint16 quantityToDelivered,
    const qint16 quantityToPickup)
{
    clientList_.addClient(QSharedPointer<core::Client>::create(core::Client{
        id, {XCoordinate, YCoordinate}, quantityToDelivered, quantityToPickup}));
}

void Solver::addWarehouse(const qint16 XCoordinate, const qint16 YCoordinate)
{
    clientList_.addWarehouse({XCoordinate, YCoordinate});
}

QVector<QString> Solver::findBestRoutes()
{
    const auto computingService = service::ComputingService(clientList_.getClients());
    const auto savingVector = computingService.getSavingVector();

    foreach (const auto save, savingVector)
    {
        routeService_.addClientsToRoute(save.client_i(), save.client_j());
    }

    QVector<QString> routesAsStrings{};
    foreach (const auto route, routeService_.getRoutes())
    {
        routesAsStrings.append(route->toString());
    }

    foreach (const auto& client, clientList_.getClients())
    {
        if (client->visited() == false)
        {
            routesAsStrings.append("WRH -> " + QString::number(client->id()) + " -> WRH");
        }
    }

    return routesAsStrings;
}

void Solver::clear()
{
    clientList_.clearClientList();
    routeService_.clearRoutes();
}

}
