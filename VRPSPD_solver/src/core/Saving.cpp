#include "inc/core/Saving.h"

namespace vrpspd::core
{

Saving::Saving(const QSharedPointer<Client>& client_i,
               const QSharedPointer<Client>& client_j,
               const qreal saving)
    : client_i_{client_i}, client_j_{client_j}, saving_{saving}
{
}

QSharedPointer<Client> Saving::client_i() const
{
    return client_i_;
}

QSharedPointer<Client> Saving::client_j() const
{
    return client_j_;
}

qreal Saving::saving() const
{
    return saving_;
}

} // vrpspd::core
