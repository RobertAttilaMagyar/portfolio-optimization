#pragma once
#include "portfolio.hpp"
#include <algorithm>
#include <numeric>
#include <random>
#include <ranges>
#include <math.h>

Asset &Asset::operator=(Asset &&other) noexcept
{
  this->ticker = other.ticker;
  this->meanReturn = other.meanReturn;
  this->volatility = other.volatility;

  return *this;
}

bool Asset::operator==(const Asset &other) const
{
  return this->ticker == other.ticker;
}

bool Portfolio::normalizeWeights()
{
  double sumWeights =
      std::accumulate(weights.begin(), weights.end(), 0.0,
                      [i = size_t{0}, this](double acc, double val) mutable
                      {
                        return acc + (this->decisionVariables[i++] ? val : 0.0);
                      });
  if (sumWeights == 0)
    return false;

  std::transform(weights.begin(), weights.end(), weights.begin(),
                 [sumWeights](double x)
                 { return x / sumWeights; });
  return true;
}

Portfolio::Portfolio(const size_t numElements, const bool useRandom = false)
    : _numElements(numElements), assets(std::vector<Asset>(numElements)),
      weights(std::vector<double>(numElements, 1.0)),
      decisionVariables(std::vector<bool>(numElements, true)),
      assetCovarianceMatrix(Matrix<double>(numElements))
{
  if (useRandom)
  {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::transform(decisionVariables.begin(), decisionVariables.end(),
                   decisionVariables.begin(),
                   [&dist, &gen](double w)
                   { return dist(gen); });

    std::transform(decisionVariables.begin(), decisionVariables.end(),
                   decisionVariables.begin(),
                   [&dist, &gen](bool d)
                   { return dist(gen) < .5; });
  }

  chooseDecisions();
  normalizeWeights();
}

void Portfolio::chooseDecisions()
{
  // Currently all elements should be included in the portfolio
  // in future extend this for smart choosing of which assets to
  // include in each round
  decisionVariables = std::vector<bool>(_numElements, true);
}

double Portfolio::calcExpectedReturn()
{
  return std::accumulate(assets.begin(), assets.end(), 0.0,
                         [i = size_t{0}, this](const Asset &a) mutable
                         {
                           double wS = this->decisionVariables.at(i)
                                           ? this->weights.at(i) * a.meanReturn
                                           : 0.0;
                           i++;
                           return wS;
                         });
}

double Portfolio::calcPortfolioVariance()
{
  double aggrVar;
  for (size_t i = 0; i < _numElements; i++)
  {
    for (size_t j = 0; j < _numElements; j++)
    {
      aggrVar += decisionVariables[i] * decisionVariables[j] * weights[i] *
                 weights[j] * assetCovarianceMatrix(i, j);
    }
  }
}

double Portfolio::calcSharpe() { return calcExpectedReturn() / sqrt(calcPortfolioVariance()); }