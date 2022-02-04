#include "inc/core/ClientList.h"

#include <algorithm>

namespace vrpspd::core
{

QVector<QSharedPointer<Client>> ClientList::getClients() const
{
    return clients_;
}

void ClientList::addWarehouse(const QPoint &coordinates)
{
    clients_.prepend(
        QSharedPointer<Client>::create(Client{0, coordinates, 0, 0, true}));
}

void ClientList::addClient(const QSharedPointer<Client>& client)
{
    clients_.append(client);
}

void ClientList::clearClientList()
{
    clients_.clear();
}

bool ClientList::allServed() const
{
    const auto notServedClient = std::any_of(clients_.begin(), clients_.end(),
        [](const auto& client){if (client->visited()) {return false;} return true;});

    if (notServedClient)
    {
        return false;
    }
    else
    {
        return true;
    }
}

} // vrpspd::core
