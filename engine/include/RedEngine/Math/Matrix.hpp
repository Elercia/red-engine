#pragma once

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/Types.hpp"

namespace red
{

// Row major matrix
template <typename T, uint8 L, uint8 C>
class MatrixT
{
public:
    using ThisType = MatrixT<T, L, C>;
    using DataType = T;

    // Publicly available data structure
    T m_data[C * L] = {0};

    constexpr T& operator()(uint8 i, uint8 j);
    constexpr const T& operator()(uint8 i, uint8 j) const;

    constexpr bool EqualsEpsilon(const ThisType& other, const T& epsilon) const;

    constexpr bool operator==(const ThisType& other) const;
    constexpr bool operator!=(const ThisType& other) const;

    constexpr T Det() const;
    constexpr ThisType Inverse() const;
    constexpr ThisType Transpose() const;

    static constexpr ThisType Identity();
};

using Matrix22 = MatrixT<float, 2, 2>;
using Matrix33 = MatrixT<float, 3, 3>;
using Matrix44 = MatrixT<float, 4, 4>;

template<typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator+(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r);
template<typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator-(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r);

template<typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& mat, typename MatrixT<T, L, C>::DataType v);
template<typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator*(typename MatrixT<T, L, C>::DataType v, const MatrixT<T, L, C>& mat);
template<typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r);

}  // namespace red

#include "inl/Matrix.inl"