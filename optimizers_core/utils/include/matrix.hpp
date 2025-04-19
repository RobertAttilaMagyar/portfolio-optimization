#pragma once
#include <stdexcept>
#include <vector>

template <typename T>
class Matrix
{
public:
    Matrix() : rows_(0), cols_(0), data_({}) {}

    Matrix(size_t n) : rows_(n), cols_(n), data_(n * n) {}

    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows * cols) {}

    Matrix(const std::vector<T> &flat_data, size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(flat_data)
    {
        if (flat_data.size() != rows * cols)
            throw std::invalid_argument(
                "Data size does not match matrix dimensions.");
    }

    T &operator()(size_t row, size_t col) { return data_.at(row * cols_ + col); }

    const T &operator()(size_t row, size_t col) const
    {
        return data_.at(row * cols_ + col);
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    const std::vector<T> &data() const { return data_; }
    std::vector<T> &data() { return data_; }

private:
    size_t rows_, cols_;
    std::vector<T> data_;
};
