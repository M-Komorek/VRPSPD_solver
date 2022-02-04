#ifndef VRPSPD_SERVICE_ROUTESERVICE_H
#define VRPSPD_SERVICE_ROUTESERVICE_H

#include <QList>
#include <QSharedPointer>
#include <QVariant>

#include <optional>

#include "inc/core/Route.h"

namespace vrpspd::service
{

class RouteService
{
public:
    QList<QSharedPointer<core::Route>> getRoutes() const;
    void addClientsToRoute(
        QSharedPointer<core::Client> client_i,
        QSharedPointer<core::Client> client_j);
    void clearRoutes();

private:
    void addClientsIfBothNotVisited(
        QSharedPointer<core::Client> client_i,
        QSharedPointer<core::Client> client_j);
    void addClientsIfOneVisited(
        QSharedPointer<core::Client> visitedClient,
        QSharedPointer<core::Client> notVisitedClient);
    void addClientsIfBothVisited(
        QSharedPointer<core::Client> client_i,
        QSharedPointer<core::Client> client_j);

    QSharedPointer<core::Route> getRouteIncludedClient(
            const QSharedPointer<core::Client>& client);

    QList<QSharedPointer<core::Route>> routeList_;
};

} // vrpspd::service

#endif // VRPSPD_SERVICE_ROUTESERVICE_H
