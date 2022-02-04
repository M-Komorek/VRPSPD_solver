#ifndef VRPSPD_CORE_SAVING_H
#define VRPSPD_CORE_SAVING_H

#include <QSharedPointer>
#include <QVector>

#include "inc/core/Client.h"

namespace vrpspd::core
{

struct Saving
{
    Saving() = delete;
    Saving(const QSharedPointer<Client>& client_i,
           const QSharedPointer<Client>& client_j,
           const qreal saving);

    QSharedPointer<Client> client_i() const;
    QSharedPointer<Client> client_j() const;
    qreal saving() const;

private:
    QSharedPointer<Client> client_i_;
    QSharedPointer<Client> client_j_;
    qreal saving_;
};

} // vrpspd::core

#endif // VRPSPD_CORE_SAVING_H
