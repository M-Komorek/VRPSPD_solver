#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QPoint>

#include "inc/core/Client.h"
#include "inc/core/ClientList.h"
#include "inc/core/Saving.h"

#include "inc/service/ComputingService.h"

namespace vrpspd::service
{

class ComputingServiceTests : public ::testing::Test
{
public:
    ComputingServiceTests() : computingService_{createClients()}
    {
    }

    QVector<QSharedPointer<core::Client>> createClients() const;

protected:
    service::ComputingService computingService_;
};

QVector<QSharedPointer<core::Client>> ComputingServiceTests::createClients() const
{
    auto clientList = core::ClientList{};
    clientList.addWarehouse(QPoint{39, 39});
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{1, QPoint{21, 21}, 0, 0}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{2, QPoint{25, 25}, 0, 0}));
    clientList.addClient(QSharedPointer<core::Client>::create(core::Client{3, QPoint{20, 44}, 0, 0}));

    return clientList.getClients();
}

TEST_F(ComputingServiceTests, calculateDistanceMatrix)
{
    QVector<QVector<qreal>> expectedDistanceMatrix{
        {0    , 25.46, 19.80, 19.65},
        {25.46,     0,  5.66, 23.02},
        {19.80,  5.66,     0, 19.65},
        {19.65, 23.02, 19.65, 0    }
    };

    const auto distanceMatrix = computingService_.getDistanceMatrix();

    for (int i=0; i<expectedDistanceMatrix.length(); ++i)
    {
        for (int j=0; j<expectedDistanceMatrix[i].length(); ++j)
        {
            EXPECT_NEAR(expectedDistanceMatrix[i][j], distanceMatrix[i][j], 0.01);
        }
    }
}

TEST_F(ComputingServiceTests, calculateSavingMatrix)
{
    QVector<QVector<qreal>> expectedSavingMatrix{
        {0    , 39.60, 22.08},
        {39.60,     0, 19.80},
        {22.08,  19.80,    0}
    };

    const auto savingMatrix = computingService_.getSavingMatrix();

    for (int i=0; i<expectedSavingMatrix.length(); ++i)
    {
        for (int j=0; j<expectedSavingMatrix[i].length(); ++j)
        {
            EXPECT_NEAR(expectedSavingMatrix[i][j], savingMatrix[i][j].saving(), 0.01);
        }
    }
}

TEST_F(ComputingServiceTests, calculateSavingVector)
{
    const auto client1 = QSharedPointer<core::Client>::create(core::Client{1, QPoint{21, 21}, 0, 0});
    const auto client2 = QSharedPointer<core::Client>::create(core::Client{2, QPoint{25, 25}, 0, 0});
    const auto client3 = QSharedPointer<core::Client>::create(core::Client{3, QPoint{20, 44}, 0, 0});
    QVector<core::Saving> expectedSavingVector{
        {client1, client2, 39.6},
        {client1, client3, 22.08},
        {client2, client3, 19.80}
    };

    const auto savingVector = computingService_.getSavingVector();

    for (qint16 i=0; i<savingVector.size(); ++i)
    {
        EXPECT_EQ(expectedSavingVector[i].client_i()->id(), savingVector[i].client_i()->id());
        EXPECT_EQ(expectedSavingVector[i].client_j()->id(), savingVector[i].client_j()->id());

        EXPECT_NEAR(expectedSavingVector[i].saving(), savingVector[i].saving(), 0.01);
    }
}

} // vrpspd::service
