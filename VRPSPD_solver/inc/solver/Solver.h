#ifndef VRPSPD_SOLVER_H
#define VRPSPD_SOLVER_H

#include <QObject>

#include "inc/core/ClientList.h"

#include "inc/service/ComputingService.h"
#include "inc/service/RouteService.h"

namespace vrpspd
{

class Solver : public QObject
{
    Q_OBJECT

public:
    Solver(QObject *parent = nullptr);
    ~Solver();

    Q_INVOKABLE void addClient(const qint16 id,
       const qint16 XCoordinate,
       const qint16 YCoordinate,
       const qint16 quantityToDelivered,
       const qint16 quantityToPickup);
    Q_INVOKABLE void addWarehouse(const qint16 XCoordinate, const qint16 YCoordinate);
    Q_INVOKABLE QVector<QString> findBestRoutes();
    Q_INVOKABLE void clear();

private:
    service::RouteService routeService_;
    core::ClientList clientList_;
};

}

#endif // VRPSPD_SOLVER_H
