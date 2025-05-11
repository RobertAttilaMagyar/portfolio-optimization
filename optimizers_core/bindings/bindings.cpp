#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "portfolio.hpp"
#include "matrix.hpp"

namespace py = pybind11;

PYBIND11_MODULE(portfoliomodule, m)
{
    m.doc() = "Python bindings for Portfolio and Asset using pybind11";

    py::class_<Asset>(m, "Asset")
        .def(py::init<>())
        .def(py::init<const std::string &, double, double>(),
             py::arg("ticker"), py::arg("meanReturn"), py::arg("volatility"))
        .def_readwrite("ticker", &Asset::ticker)
        .def_readwrite("mean_return", &Asset::meanReturn)
        .def_readwrite("volatility", &Asset::volatility)
        .def("__eq__", &Asset::operator==)
        .def("__repr__", [](const Asset &a)
             { return "<Asset ticker='" + a.ticker + "' return=" +
                      std::to_string(a.meanReturn) + " vol=" +
                      std::to_string(a.volatility) + ">"; });

    py::class_<Portfolio>(m, "Portfolio")
        .def(py::init<size_t, bool>(), py::arg("numElements"), py::arg("useRandom") = false)
        .def("choose_decisions", &Portfolio::chooseDecisions)
        .def("normalize_weights", &Portfolio::normalizeWeights)
        .def("get_portfolio_variance", &Portfolio::getPortfolioVariance)
        .def("get_expected_return", &Portfolio::getExpectedReturn)
        .def("get_sharpe", &Portfolio::getSharpe)
        .def_readwrite("assets", &Portfolio::assets)
        .def_readwrite("weights", &Portfolio::weights)
        .def_readwrite("decision_variables", &Portfolio::decisionVariables)
        .def("__repr__", [](const Portfolio &p)
             { return "<Portfolio with " + std::to_string(p.assets.size()) + " assets>"; });

    py::class_<Matrix<double>>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<size_t>(), py::arg("n"))
        .def(py::init<size_t, size_t>(), py::arg("rows"), py::arg("cols"))
        .def(py::init<const std::vector<double> &, size_t, size_t>(),
             py::arg("flat_data"), py::arg("rows"), py::arg("cols"))
        .def("__getitem__", [](const Matrix<double> &m, std::pair<size_t, size_t> idx)
             { return m(idx.first, idx.second); })
        .def("__setitem__", [](Matrix<double> &m, std::pair<size_t, size_t> idx, double val)
             { m(idx.first, idx.second) = val; })
        .def("rows", &Matrix<double>::rows)
        .def("cols", &Matrix<double>::cols)
        .def_property("data", [](Matrix<double> &m)
                      { return m.data(); }, [](Matrix<double> &m, const std::vector<double> &d)
                      { m.data() = d; })
        .def("__repr__", [](const Matrix<double> &m)
             { return "<Matrix " + std::to_string(m.rows()) + "x" + std::to_string(m.cols()) + ">"; });
}
