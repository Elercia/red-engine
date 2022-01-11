
namespace red
{
template <typename T, uint8 L, uint8 C>
constexpr MatrixT<T, L, C> MatrixT<T, L, C>::Identity()
{
    MatrixT<T, L, C> id;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            if (i == j)
                id(i, j) = 1;
            else
                id(i, j) = 0;
        }
    }

    return id;
}

template <typename T, uint8 L, uint8 C>
constexpr T& MatrixT<T, L, C>::operator()(uint8 i, uint8 j)
{
    return m_data[C * i + j];
}

template <typename T, uint8 L, uint8 C>
constexpr const T& MatrixT<T, L, C>::operator()(uint8 i, uint8 j) const
{
    return m_data[C * i + j];
}

Matrix44 operator*(const Matrix44& mat, Matrix44::DataType v)
{
    Matrix44 ret;

    for (uint8 i = 0; i < 4; i++)
    {
        for (uint8 j = 0; j < 4; j++)
        {
            ret(i, j) = mat(i, j) * v;
        }
    }

    return ret;
}

Matrix44 operator*(const Matrix44& l, const Matrix44& r)
{
    Matrix44 ret;

    for (uint8 i = 0; i < 4; i++)
    {
        for (uint8 j = 0; j < 4; j++)
        {
            for (uint8 k = 0; k < 4; k++)
            {
                ret(i, j) += l(i, k) * r(k, j);
            }
        }
    }

    return ret;
}

Matrix44 operator*(const Matrix44& l, const Vector4& r)
{
    Matrix44 ret;

    for (uint8 i = 0; i < 4; i++)
    {
        for (uint8 j = 0; j < 4; j++)
        {
            for (uint8 k = 0; k < 4; k++)
            {
                ret(i, j) += l(i, k) * r[k];
            }
        }
    }

    return ret;
}

}  // namespace red