namespace red
{
template <typename T>
void Configuration::ChangeVar(std::string name, std::string category, T value)
{
    auto it = m_configVariable.find(category + "_" + name);

    if (it == m_configVariable.end())
    {
        return;
    }

    auto casted = static_cast<CVar<T>*>(it->second);

    casted->ChangeValue(value);
}
}  // namespace red