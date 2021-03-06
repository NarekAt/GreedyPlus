#pragma once

#include "GreedySDK.h"
#include <vector>
#include <memory>

template <class Params>
class IMatroid
{
public:
    virtual void ReadInputDataFromFile(const std::string& filePath) = 0;

    virtual bool IsIndependentSubset(typename Params::CollectionType& elems) const = 0;

    virtual typename Params::CollectionType& GetGroundElements() const = 0;

    virtual typename Params::SubSetsSet& GetIndependentSubsets() const = 0;

    virtual ~IMatroid() = default;
};


template <class T>
using IMatroidPtr = std::shared_ptr<IMatroid<T>>;