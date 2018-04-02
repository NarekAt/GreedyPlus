#include "stdafx.h"
#include "MinWireLengthCellPlacementFitness.h"

void
MinWireLengthCellPlacementFitness::Evaluate(Generation& generation)
{
    auto& connMatrix = m_problem->GetIndependentSubsets();

    auto minWire = std::numeric_limits<size_t>::max();

    for (auto chromosome : generation)
    {
        long weightedWireLength = 0;
        // Iterate over all the nets
        for (size_t i = 0; i != connMatrix.size(); ++i)
        {
            for (size_t j = 0; j != connMatrix[j].size(); ++j)
            {
                if (connMatrix[i][j] == std::numeric_limits<size_t>::max())
                    continue;

                weightedWireLength += GetManhattanDistance(chromosome, i, j) * connMatrix[i][j];
            }
        }
        chromosome->SetFitness(weightedWireLength);
    }
}

long
MinWireLengthCellPlacementFitness::GetManhattanDistance(ChromosomePtr ch, size_t i, size_t j)
{
    std::string chromStr = ch->AsString();

    size_t numOfRows = static_cast<size_t>(sqrt(chromStr.size()));

    std::pair<size_t, size_t> c1, c2;

    for (size_t k = 0; k != chromStr.size(); ++k)
    {
        // TODO: refactor code
        auto chromId = chromStr[k] - 'a';
        if (chromId == i)
        {
            c1.first = k / numOfRows;
            c1.second = k % numOfRows;
        }
        else if (chromId = j)
        {
            c2.first = k / numOfRows;
            c2.second = k % numOfRows;
        }
    }

    return abs(long(c1.first - c2.first)) + abs(long(c1.second - c2.second));
}