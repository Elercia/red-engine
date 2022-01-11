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

    static constexpr ThisType Identity();
};

using Matrix44 = MatrixT<float, 4, 4>;

Matrix44 operator*(const Matrix44& mat, Matrix44::DataType v);
Matrix44 operator*(const Matrix44& l, const Matrix44& r);
Matrix44 operator*(const Matrix44& l, const Vector4& r);

}  // namespace red

#include "inl/Matrix.inl"