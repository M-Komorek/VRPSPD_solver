#ifndef VRPSPD_CORE_ROUTE_H
#define VRPSPD_CORE_ROUTE_H

#include <QList>
#include <QSharedPointer>

#include "inc/core/Client.h"

namespace vrpspd::core
{

class Route
{
public:
    Route();

    QList<QSharedPointer<Client>> getClients() const;

    void add(QSharedPointer<Client>& client);
    void addAdjacentClient(
        QSharedPointer<Client>& clientToAdd, const QSharedPointer<Client>& neighbor);

    bool isInRoute(const QSharedPointer<Client>& client) const;
    bool isInternal(const QSharedPointer<Client>& client) const;
    bool isRouteContainsSameClients(const QSharedPointer<Route>& route);
    bool isMergeRoutePossible(const QSharedPointer<Route>& route);

    QString toString() const;

private:
    bool isAddToRoutePossible(const QSharedPointer<Client>& client) const;

    QList<QSharedPointer<Client>> route_;
    qint16 deliveredQuantity_;
    qint16 pickedUpQuantity_;
};

} // vrpspd::core

#endif // VRPSPD_CORE_ROUTE_H
