#ifndef VRPSPD_CORE_CLIENTLIST_H
#define VRPSPD_CORE_CLIENTLIST_H

#include <QPoint>
#include <QSharedPointer>
#include <QVector>

#include "inc/core/Client.h"

namespace vrpspd::core
{

class ClientList
{
public:
    ClientList() = default;

    QVector<QSharedPointer<Client>> getClients() const;

    void addWarehouse(const QPoint& coordinates);
    void addClient(const QSharedPointer<Client>& client);
    void clearClientList();
    bool allServed() const;

private:
    QVector<QSharedPointer<Client>> clients_;
};

} // vrpspd::core

#endif // VRPSPD_CORE_CLIENTLIST_H
