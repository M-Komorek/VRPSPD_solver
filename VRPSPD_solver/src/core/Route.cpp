#include "inc/core/Route.h"

namespace vrpspd::core
{

Route::Route()
    : route_{QList<QSharedPointer<Client>>{}}
    , deliveredQuantity_{0}
    , pickedUpQuantity_{0}
{
}

QList<QSharedPointer<Client>> Route::getClients() const
{
    return route_;
}

void Route::add(QSharedPointer<Client>& client)
{
    if (isAddToRoutePossible(client))
    {
        client->setVisited(true);
        route_.append(client);
        deliveredQuantity_ += client->quantityToDelivered();
        pickedUpQuantity_  += client->quantityToPickUp();
    }
}

void Route::addAdjacentClient(
    QSharedPointer<Client>& clientToAdd, const QSharedPointer<Client>& neighbor)
{
    if (isAddToRoutePossible(clientToAdd))
    {
        clientToAdd->setVisited(true);
        deliveredQuantity_ += clientToAdd->quantityToDelivered();
        pickedUpQuantity_  += clientToAdd->quantityToPickUp();

        if (route_.first()->id() == neighbor->id())
        {
            route_.prepend(clientToAdd);
        }
        else
        {
            route_.append(clientToAdd);
        }
}
}

bool Route::isInRoute(const QSharedPointer<Client>& client) const
{
    return std::any_of(route_.cbegin(), route_.cend(),
        [&client](const auto& clientInRoute){
            if (client->id() == clientInRoute->id())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    );
}

bool Route::isInternal(const QSharedPointer<Client>& client) const
{
    if (route_.first()->id() == client->id() || route_.last()->id() == client->id())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Route::isRouteContainsSameClients(const QSharedPointer<Route>& route)
{
    if ((*route).toString() == this->toString())
    {
        return true;
    }
    else
    {
      return false;
    }
}

bool Route::isMergeRoutePossible(const QSharedPointer<Route>& route)
{
    auto deliveredQuantityAfterMerge = qint16(deliveredQuantity_);
    auto pickedUpQuantityAfterMerge = qint16(pickedUpQuantity_);

    const auto clients = route->getClients();
    foreach (const auto& client, clients)
    {
        deliveredQuantityAfterMerge += client->quantityToDelivered();
        pickedUpQuantityAfterMerge += client->quantityToPickUp();
    }

    if (qBound(qint16(0), deliveredQuantityAfterMerge, qint16(100)) == deliveredQuantityAfterMerge &&
        qBound(qint16(0), pickedUpQuantityAfterMerge,  qint16(100)) == pickedUpQuantityAfterMerge)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString Route::toString() const
{
    QString route{"WRH"};
    for (const auto& client : route_)
    {
        route += " -> " + QString::number(client->id());
    }
    route += " -> WRH";
    return route;
}

bool Route::isAddToRoutePossible(const QSharedPointer<Client>& client) const
{
    const auto deliveredQuantityWithClient = qint16(deliveredQuantity_ + client->quantityToDelivered());
    const auto pickedUpQuantityWithClient = qint16(pickedUpQuantity_ + client->quantityToPickUp());

    if (qBound(qint16(0), deliveredQuantityWithClient, qint16(100)) == deliveredQuantityWithClient &&
        qBound(qint16(0), pickedUpQuantityWithClient,  qint16(100)) == pickedUpQuantityWithClient)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} // vrpspd::core
