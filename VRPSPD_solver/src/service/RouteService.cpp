#include "inc/service/RouteService.h"

namespace vrpspd::service
{

QList<QSharedPointer<core::Route>> RouteService::getRoutes() const
{
    return routeList_;
}

void RouteService::addClientsToRoute(
    QSharedPointer<core::Client> client_i,
    QSharedPointer<core::Client> client_j)
{
    if (client_i->visited() == false && client_j->visited() == false)
    {
        addClientsIfBothNotVisited(client_i, client_j);
        return;
    }

    if ((client_i->visited() == false && client_j->visited() == true) ||
        (client_i->visited() == true && client_j->visited() == false))
    {
        if (client_i->visited() == true)
        {
            addClientsIfOneVisited(client_i, client_j);
            return;
        }
        else
        {
            addClientsIfOneVisited(client_j, client_i);
            return;
        }
    }

    if (client_i->visited() == true && client_j->visited() == true)
    {
        addClientsIfBothVisited(client_i, client_j);
        return;
    }
}

void RouteService::clearRoutes()
{
    routeList_.clear();
}

void RouteService::addClientsIfBothNotVisited(
    QSharedPointer<core::Client> client_i,
    QSharedPointer<core::Client> client_j)
{
    auto route = QSharedPointer<core::Route>::create(core::Route());
    route->add(client_i);
    route->add(client_j);
    routeList_.append(route);
}

void RouteService::addClientsIfOneVisited(
    QSharedPointer<core::Client> visitedClient,
    QSharedPointer<core::Client> notVisitedClient)
{
    auto routeWithVisitedClient = getRouteIncludedClient(visitedClient);
    if (routeWithVisitedClient != nullptr && !routeWithVisitedClient->isInternal(visitedClient))
    {
        routeWithVisitedClient->addAdjacentClient(notVisitedClient, visitedClient);
    }
}

void RouteService::addClientsIfBothVisited(
    QSharedPointer<core::Client> client_i,
    QSharedPointer<core::Client> client_j)
{
    auto route_i = getRouteIncludedClient(client_i);
    auto route_j = getRouteIncludedClient(client_j);

    if (route_i->isInternal(client_i) || route_j->isInternal(client_j))
    {
        return;
    }

    if (!(route_i->isRouteContainsSameClients(route_j)))
    {
        if (route_i->isMergeRoutePossible(route_j))
        {
            foreach (auto client, route_j->getClients())
            {
                route_i->add(client);
            }
            routeList_.removeOne(route_j);
        }
    }
}

QSharedPointer<core::Route> RouteService::getRouteIncludedClient(
        const QSharedPointer<core::Client>& client)
{
    foreach (const auto& route, routeList_)
    {
        if (route->isInRoute(client))
        {
            return route;
        }
    }

    return nullptr;
}


} // vrpspd::service
