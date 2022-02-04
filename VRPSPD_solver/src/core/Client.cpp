#include "inc/core/Client.h"

namespace vrpspd::core
{

Client::Client(const qint16 id,
    const QPoint& coordinates,
    const qint16 quantityToDelivered,
    const qint16 quantityToPickup,
    const bool visited)
    : id_{id}
    , coordinates_{coordinates}
    , quantityToDelivered_{quantityToDelivered}
    , quantityToPickUp_{quantityToPickup}
    , visited_{visited}
{
}

qint16 Client::id() const
{
    return id_;
}

QPoint Client::coordinates() const
{
    return coordinates_;
}

qint16 Client::quantityToDelivered() const
{
    return quantityToDelivered_;
}

qint16 Client::quantityToPickUp() const
{
    return quantityToPickUp_;
}

bool Client::visited() const
{
    return visited_;
}

void Client::setVisited(const bool visited)
{
    visited_ = visited;
}

} // vrpspd::core
