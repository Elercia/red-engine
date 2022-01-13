
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

/*template <typename T, uint8 L, uint8 C>
T MatrixT<T, L, C>::Determinant() const
{

}

template <typename T, uint8 L, uint8 C>
ThisType MatrixT<T, L, C>::Inverse() const
{

}*/

template <typename T, uint8 L, uint8 C>
MatrixT<T, L, C> operator+(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            ret(i, j) = l(i, j) + r(i, j);
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
MatrixT<T, L, C> operator-(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            ret(i, j) = l(i, j) - r(i, j);
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& mat, typename MatrixT<T, L, C>::DataType v)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            ret(i, j) = mat(i, j) * v;
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& l, const MatrixT<T, L, C>& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            for (uint8 k = 0; k < C; k++)
            {
                ret(i, j) += l(i, k) * r(k, j);
            }
        }
    }

    return ret;
}

template <typename T, uint8 L, uint8 C>
MatrixT<T, L, C> operator*(const MatrixT<T, L, C>& l, const Vector4& r)
{
    MatrixT<T, L, C> ret;

    for (uint8 i = 0; i < L; i++)
    {
        for (uint8 j = 0; j < C; j++)
        {
            for (uint8 k = 0; k < C; k++)
            {
                ret(i, j) += l(i, k) * r[k];
            }
        }
    }

    return ret;
}

template <>
float MatrixT<float, 2, 2>::Det() const
{
    return operator()(0, 0) * operator()(1, 1) - operator()(0, 1) * operator()(1, 0);
}

template <>
MatrixT<float, 2, 2>::ThisType MatrixT<float, 2, 2>::Inverse() const
{
    return ThisType::Identity();
}

template <>
float MatrixT<float, 3, 3>::Det() const
{
    const float& a = operator()(0, 0);
    const float& b = operator()(0, 1);
    const float& c = operator()(0, 2);

    const float& d = operator()(1, 0);
    const float& e = operator()(1, 1);
    const float& f = operator()(1, 2);

    const float& g = operator()(2, 0);
    const float& h = operator()(2, 1);
    const float& i = operator()(2, 2);

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
MatrixT<float, 3, 3>::ThisType MatrixT<float, 3, 3>::Inverse() const
{
    return ThisType::Identity();
}

template <>
float MatrixT<float, 4, 4>::Det() const
{
    const float& a = operator()(0, 0);
    const float& b = operator()(0, 1);
    const float& c = operator()(0, 2);
    const float& d = operator()(0, 3);

    const float& e = operator()(1, 0);
    const float& f = operator()(1, 1);
    const float& g = operator()(1, 2);
    const float& h = operator()(1, 3);

    const float& i = operator()(2, 0);
    const float& j = operator()(2, 1);
    const float& k = operator()(2, 2);
    const float& l = operator()(2, 3);

    const float& m = operator()(3, 0);
    const float& n = operator()(3, 1);
    const float& o = operator()(3, 2);
    const float& p = operator()(3, 3);

    // clang-format off
    MatrixT<float, 3, 3> A = {  f, g, h, 
                                j, k, l,
                                n, o, p };

    MatrixT<float, 3, 3> B = {  e, g, h, 
                                i, k, l,
                                m, o, p };

    MatrixT<float, 3, 3> C = {  e, f, h, 
                                i, j, l,
                                m, n, p };

    MatrixT<float, 3, 3> D = {  e, f, g, 
                                i, j, k,
                                m, n, o };
    // clang-format on

    return a * A.Det() - b * B.Det() + c * C.Det() - d * D.Det();
}

template <>
MatrixT<float, 4, 4>::ThisType MatrixT<float, 4, 4>::Inverse() const
{
    return ThisType::Identity();
}

}  // namespace red