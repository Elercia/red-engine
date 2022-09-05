
namespace red
{

AABB::AABB(const Vector2& position, const Vector2& size) : m_min(position), m_max(position + size)
{
}

AABB& AABB::Grow(const Vector2& point)
{
    m_min.x = Math::Min(m_min.x, point.x);
    m_min.y = Math::Min(m_min.y, point.y);

    m_max.x = Math::Max(m_max.x, point.x);
    m_max.y = Math::Max(m_max.y, point.y);

    return *this;
}

bool AABB::Intersect(const AABB& other)
{
    return other.m_min.x >= m_min.x && other.m_min.y >= m_min.y && other.m_max.x <= m_max.x && other.m_max.y <= m_max.y;
}

}  // namespace red
