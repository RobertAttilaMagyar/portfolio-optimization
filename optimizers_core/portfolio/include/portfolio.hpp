#pragma once
#include "matrix.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

struct Asset
{
    std::string ticker;
    double meanReturn;
    double volatility;

    Asset(const std::string ticker, const double meanReturn,
          const double volatility)
        : ticker(ticker), meanReturn(meanReturn), volatility(volatility) {}

    Asset() : ticker(""), meanReturn(0), volatility(0) {}

    Asset(const Asset &other)
        : ticker(other.ticker), meanReturn(other.meanReturn),
          volatility(other.volatility) {}

    Asset &operator=(const Asset &other);

    Asset &operator=(Asset &&other) noexcept;

    bool operator==(const Asset &other) const;
};

class Portfolio
{
public:
    Portfolio(const size_t numElements, const bool useRandom = false);

    void chooseDecisions();
    bool normalizeWeights();

    double getPortfolioVariance();
    double getExpectedReturn();
    double getSharpe();

public:
    std::vector<Asset> assets;
    std::vector<double> weights;
    std::vector<bool> decisionVariables;
    Matrix<double> assetCovarianceMatrix;

private:
    size_t _numElements;
    size_t _numRequired; // number of assets that should be held by the portfolio.
};