
namespace red
{

AABB::AABB() : m_center(), m_min(), m_max()
{
}

AABB& AABB::Grow(const Vector3& /*point*/)
{
    return *this;
}

bool AABB::Intersect(const AABB& /*other*/)
{
    return true;
}

}  // namespace red
