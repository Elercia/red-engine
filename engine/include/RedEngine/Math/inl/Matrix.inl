#include "RedEngine/Math/Math.hpp"

namespace red
{
template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> MatrixT<T, L, C>::Identity()
{
    MatrixT<T, L, C> id;

    for (uint8 c = 0; c < C; c++)
    {
        for (uint8 r = 0; r < L; r++)
        {
            if (c == r)
                id(c, r) = 1;
            else
                id(c, r) = 0;
        }
    }

    return id;
}

template <typename T, uint8 L, uint8 C>
constexpr T& MatrixT<T, L, C>::operator()(uint8 column, uint8 row)
{
    return m_data[L * column + row];
}

template <typename T, uint8 L, uint8 C>
constexpr const T& MatrixT<T, L, C>::operator()(uint8 column, uint8 row) const
{
    return m_data[L * column + row];
}

/*template <typename T, uint8 L, uint8 C>
T MatrixT<T, L, C>::Determinant() const
{

}

template <typename T, uint8 L, uint8 C>
ThisType MatrixT<T, L, C>::Inverse() const
{

}*/

template <typename T, uint8 L, uint8 C>
constexpr bool MatrixT<T, L, C>::EqualsEpsilon(const ThisType& other, const T& epsilon) const
{
    for (uint8 i = 0; i < C; i++)
    {
        for (uint8 j = 0; j < L; j++)
        {
            if (!Math::EqualsEpsilon(operator()(i, j), other(i, j), epsilon))
            {
                return false;
            }
        }
    }

    return true;
}

template <typename T, uint8 L, uint8 C>
constexpr bool MatrixT<T, L, C>::operator==(const ThisType& other) const
{
    return EqualsEpsilon(other, 0.0f);
}

template <typename T, uint8 L, uint8 C>
constexpr bool MatrixT<T, L, C>::operator!=(const ThisType& other) const
{
    return !(*this == other);
}

template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator+(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < C; i++)
    {
        for (uint8 j = 0; j < L; j++)
        {
            ret(i, j) = l(i, j) + r(i, j);
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator-(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < C; i++)
    {
        for (uint8 j = 0; j < L; j++)
        {
            ret(i, j) = l(i, j) - r(i, j);
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& mat, typename MatrixT<T, L, C>::DataType v)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < C; i++)
    {
        for (uint8 j = 0; j < L; j++)
        {
            ret(i, j) = mat(i, j) * v;
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator*(typename MatrixT<T, L, C>::DataType v, const MatrixT<T, L, C>& mat)
{
    return mat * v;
}

template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            for (uint8 k = 0; k < C; k++)
            {
                ret(j, i) += l(k, i) * r(j, k);
            }
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> MatrixT<T, L, C>::Transpose() const
{
    MatrixT<T, L, C> res;

    for (uint8 i = 0; i < C; i++)
    {
        for (uint8 j = 0; j < L; j++)
        {
            res(j, i) = operator()(i, j);
        }
    }

    return res;
}

template <>
constexpr inline float MatrixT<float, 2, 2>::Det() const
{
    return operator()(0, 0) * operator()(1, 1) - operator()(0, 1) * operator()(1, 0);
}

template <>
constexpr inline MatrixT<float, 2, 2>::ThisType MatrixT<float, 2, 2>::Inverse() const
{
    float det = Det();

    if (det == 0)
        return Identity();

    const float a = operator()(0, 0);
    const float b = operator()(1, 0);
    const float c = operator()(0, 1);
    const float d = operator()(1, 1);

    // clang-format off
    Matrix22 m = {
         d,  -c,
        -b,   a,
    };
    // clang-format on

    return (1.f / det) * m;
}

template <>
constexpr inline float MatrixT<float, 3, 3>::Det() const
{
    const float a = operator()(0, 0);
    const float b = operator()(1, 0);
    const float c = operator()(2, 0);

    const float d = operator()(0, 1);
    const float e = operator()(1, 1);
    const float f = operator()(2, 1);

    const float g = operator()(0, 2);
    const float h = operator()(1, 2);
    const float i = operator()(2, 2);

    // clang-format off
    return      a * e * i 
            +   b * f * g 
            +   c * d * h
            - ( c * e * g
            +   a * f * h  
            +   b * d * i );
    // clang-format on
}

template <>
constexpr inline MatrixT<float, 3, 3>::ThisType MatrixT<float, 3, 3>::Inverse() const
{
    float det = Det();
    if (det == 0)
        return Identity();

    const float a = operator()(0, 0);
    const float b = operator()(1, 0);
    const float c = operator()(2, 0);

    const float d = operator()(0, 1);
    const float e = operator()(1, 1);
    const float f = operator()(2, 1);

    const float g = operator()(0, 2);
    const float h = operator()(1, 2);
    const float i = operator()(2, 2);

    const float A = e * i - f * h;
    const float B = -(d * i - f * g);
    const float C = d * h - e * g;
    const float D = -(b * i - c * h);
    const float E = a * i - c * g;
    const float F = -(a * h - b * g);
    const float G = b * f - c * e;
    const float H = -(a * f - c * d);
    const float I = a * e - b * d;

    // clang-format off
    MatrixT<float, 3, 3> mat = {
        A, B, C,
        D, E, F, 
        G, H, I
    };
    // clang-format on

    return (1 / det) * mat;
}

template <>
constexpr inline float MatrixT<float, 4, 4>::Det() const
{
    const float a = operator()(0, 0);
    const float b = operator()(1, 0);
    const float c = operator()(2, 0);
    const float d = operator()(3, 0);

    const float e = operator()(0, 1);
    const float f = operator()(1, 1);
    const float g = operator()(2, 1);
    const float h = operator()(3, 1);

    const float i = operator()(0, 2);
    const float j = operator()(1, 2);
    const float k = operator()(2, 2);
    const float l = operator()(3, 2);

    const float m = operator()(0, 3);
    const float n = operator()(1, 3);
    const float o = operator()(2, 3);
    const float p = operator()(3, 3);

    // clang-format off
    MatrixT<float, 3, 3> A = {  f, j, n,
                                g, k, o,
                                h, l, p };

    MatrixT<float, 3, 3> B = {  e, i, m, 
                                g, k, o,
                                h, l, p };

    MatrixT<float, 3, 3> C = {  e, i, m, 
                                f, j, n,
                                h, l, p };

    MatrixT<float, 3, 3> D = {  e, i, m, 
                                f, j, n,
                                g, k, o };
    // clang-format on

    return a * A.Det() - b * B.Det() + c * C.Det() - d * D.Det();
}

template <>
constexpr inline MatrixT<float, 4, 4>::ThisType MatrixT<float, 4, 4>::Inverse() const
{
    float det = Det();
    if (det == 0)
        return Identity();

    const float a = operator()(0, 0);
    const float b = operator()(1, 0);
    const float c = operator()(2, 0);
    const float d = operator()(3, 0);

    const float e = operator()(0, 1);
    const float f = operator()(1, 1);
    const float g = operator()(2, 1);
    const float h = operator()(3, 1);

    const float i = operator()(0, 2);
    const float j = operator()(1, 2);
    const float k = operator()(2, 2);
    const float l = operator()(3, 2);

    const float m = operator()(0, 3);
    const float n = operator()(1, 3);
    const float o = operator()(2, 3);
    const float p = operator()(3, 3);

    float a11 = -h * k * n + g * l * n + h * j * o - f * l * o - g * j * p + f * k * p;
    float a12 = d * k * n - c * l * n - d * j * o + b * l * o + c * j * p - b * k * p;
    float a13 = -d * g * n + c * h * n + d * f * o - b * h * o - c * f * p + b * g * p;
    float a14 = d * g * j - c * h * j - d * f * k + b * h * k + c * f * l - b * g * l;
    float a21 = h * k * m - g * l * m - h * i * o + e * l * o + g * i * p - e * k * p;
    float a22 = -d * k * m + c * l * m + d * i * o - a * l * o - c * i * p + a * k * p;
    float a23 = d * g * m - c * h * m - d * e * o + a * h * o + c * e * p - a * g * p;
    float a24 = -d * g * i + c * h * i + d * e * k - a * h * k - c * e * l + a * g * l;
    float a31 = -h * j * m + f * l * m + h * i * n - e * l * n - f * i * p + e * j * p;
    float a32 = d * j * m - b * l * m - d * i * n + a * l * n + b * i * p - a * j * p;
    float a33 = -d * f * m + b * h * m + d * e * n - a * h * n - b * e * p + a * f * p;
    float a34 = d * f * i - b * h * i - d * e * j + a * h * j + b * e * l - a * f * l;
    float a41 = g * j * m - f * k * m - g * i * n + e * k * n + f * i * o - e * j * o;
    float a42 = -c * j * m + b * k * m + c * i * n - a * k * n - b * i * o + a * j * o;
    float a43 = c * f * m - b * g * m - c * e * n + a * g * n + b * e * o - a * f * o;
    float a44 = -c * f * i + b * g * i + c * e * j - a * g * j - b * e * k + a * f * k;

    // clang-format off
    MatrixT<float, 4, 4> adj = {
        a11, a21, a31, a41, 
        a12, a22, a32, a42, 
        a13, a23, a33, a43, 
        a14, a24, a34, a44
    };
    // clang-format on

    return (1.f / det) * adj;
}

constexpr inline Vector4 operator*(const Matrix44& m, const Vector4& v)
{
    Vector4 ret;

    ret.w = m(0, 3) * v.x + m(1, 3) * v.y + m(2, 3) * v.z + m(3, 3) * v.w;
    ret.x = m(0, 0) * v.x + m(1, 0) * v.y + m(2, 0) * v.z + m(3, 0) * v.w;
    ret.y = m(0, 1) * v.x + m(1, 1) * v.y + m(2, 1) * v.z + m(3, 1) * v.w;
    ret.z = m(0, 2) * v.x + m(1, 2) * v.y + m(2, 2) * v.z + m(3, 2) * v.w;

    return ret;
}

}  // namespace red