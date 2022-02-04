#ifndef VRPSPD_SERVICE_COMPUTINGSERVICE_H
#define VRPSPD_SERVICE_COMPUTINGSERVICE_H

#include <QSharedPointer>
#include <QVector>

#include "inc/core/Client.h"
#include "inc/core/Saving.h"

namespace vrpspd::service
{

class ComputingService
{
public:
    ComputingService(const QVector<QSharedPointer<core::Client>>& clients);

    QVector<QVector<qreal>> getDistanceMatrix() const;
    QVector<QVector<core::Saving>> getSavingMatrix() const;
    QVector<core::Saving> getSavingVector() const;

private:
    qreal calculateEuclideanDistance(const QPoint& begin, const QPoint& end) const;

    void calculateDistanceMatrix(const QVector<QSharedPointer<core::Client>>& clients);
    void calculateSavingMatrix(const QVector<QSharedPointer<core::Client>>& clients);
    void calculateSavingVector();

    QVector<QVector<qreal>> distanceMatrix_;
    QVector<QVector<core::Saving>> savingMatrix_;
    QVector<core::Saving> savingVector_;
};

} // vrpspd::service

#endif // VRPSPD_SERVICE_COMPUTINGSERVICE_H
