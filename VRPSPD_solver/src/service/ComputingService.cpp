#include "inc/service/ComputingService.h"

#include <QtMath>

namespace vrpspd::service
{

ComputingService::ComputingService(const QVector<QSharedPointer<core::Client>>& clients)
{
    calculateDistanceMatrix(clients);
    calculateSavingMatrix(clients);
    calculateSavingVector();
}

QVector<QVector<qreal>> ComputingService::getDistanceMatrix() const
{
    return distanceMatrix_;
}

QVector<QVector<core::Saving>> ComputingService::getSavingMatrix() const
{
    return savingMatrix_;
}

QVector<core::Saving> ComputingService::getSavingVector() const
{
    return savingVector_;
}

qreal ComputingService::calculateEuclideanDistance(const QPoint &begin, const QPoint &end) const
{
    return qSqrt(qPow(end.x()-begin.x(), 2) + qPow(end.y()-begin.y(), 2));
}

void vrpspd::service::ComputingService::calculateDistanceMatrix(
    const QVector<QSharedPointer<core::Client>>& clients)
{
    foreach (const auto& begin, clients)
    {
        auto distanceVector = QVector<qreal>{};
        foreach (const auto& end, clients)
        {
            if (begin->coordinates() == end->coordinates())
            {
                distanceVector.append(0);
                continue;
            }
            distanceVector.append(
                calculateEuclideanDistance(begin->coordinates(), end->coordinates()));
        }

        distanceMatrix_.append(distanceVector);
    }
}

void ComputingService::calculateSavingMatrix(const QVector<QSharedPointer<core::Client>>& clients)
{
    for (qint16 i=1; i<distanceMatrix_.length(); ++i)
    {
        auto profitVector = QVector<core::Saving>{};
        for (qint16 j=1; j<distanceMatrix_[i].length(); ++j)
        {
            if (i==j)
            {
                profitVector.append(core::Saving{nullptr, nullptr, 0});
                continue;
            }
            const auto saving = distanceMatrix_[i][0] + distanceMatrix_[0][j] - distanceMatrix_[i][j];
            profitVector.append(core::Saving{clients[i], clients[j], saving});
        }

        savingMatrix_.append(profitVector);
    }
}

void ComputingService::calculateSavingVector()
{
    foreach (const auto& savingVector, savingMatrix_)
    {
        const auto zeroElementPlace = std::find_if(savingVector.begin(), savingVector.end(),
            [](const auto& saving){
                if (saving.saving() == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        );

        if (zeroElementPlace != savingVector.end())
        {
            savingVector_.append(QVector(zeroElementPlace+1, savingVector.end()));
        }
    }

    std::sort(savingVector_.begin(), savingVector_.end(),
        [](const auto& saving1, const auto& saving2){
            return saving1.saving() > saving2.saving();});
}

} // vrpspd::service
