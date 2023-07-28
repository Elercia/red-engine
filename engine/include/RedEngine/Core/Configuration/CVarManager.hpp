#pragma once

#include "RedEngine/Core/Configuration/CVarUtils.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
class ICVar;
template <typename Type>
class CVar;
template <typename Type>
class CVarValue;

class CVarManager : public Uncopyable, public Unmovable
{
public:
    static CVarManager& GetInstance();

    template <typename T>
    static CVarValue<T>* NewConsoleVariableDeclaration(const String& name, const String& category,
                                                       const T& defaultValue);

    static void LoadConfigFile(const Path& path);

    template <typename T>
    CVar<T> GetFromName(const String& fullName);

public:
    CVarManager();
    ~CVarManager();

private:
    void LoadConfigFileInternal(const Path& path);

    template <typename T>
    CVarValue<T>* NewConsoleVariableDeclarationInternal(const String& name, const String& category,
                                                        const T& defaultValue);

    ICVar* FindCVar(const String& fullName);

    Map<String, ICVar*> m_configVariable;
};

}  // namespace red

#include "inl/CVarManager.inl"