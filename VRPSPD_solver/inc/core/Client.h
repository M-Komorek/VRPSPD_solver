#ifndef VRPSPD_CORE_CLIENT_H
#define VRPSPD_CORE_CLIENT_H

#include <QPoint>
#include <QString>

namespace vrpspd::core
{

struct Client
{
    Client() = delete;
    Client(const qint16 id,
           const QPoint& coordinates,
           const qint16 quantityToDelivered,
           const qint16 quantityToPickup,
           const bool visited = false);

    qint16 id() const;
    QPoint coordinates() const;
    qint16 quantityToDelivered() const;
    qint16 quantityToPickUp() const;
    bool visited() const;
    void setVisited(const bool visited);

private:
    qint16 id_;
    QPoint coordinates_;
    qint16 quantityToDelivered_;
    qint16 quantityToPickUp_;
    bool visited_;
};

} // vrpspd::core

#endif // VRPSPD_CORE_CLIENT_H
