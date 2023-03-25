#include "RedEngine/Core/Debug/System/DebugSystem.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

#include <SDL2/SDL_clipboard.h>
#include <box2d/b2_draw.h>
#include <box2d/box2d.h>
#include <imgui.h>

namespace red
{
DebugSystem::DebugSystem(World* world) : System(world)
{
}

void ShowImGuiDemo(DebugComponent* /*debug*/)
{
    static bool demoOpen = false;
    ImGui::Checkbox("Show ImGui demo", &demoOpen);

    if(demoOpen)
    {
        ImGui::ShowDemoWindow(&demoOpen);
    }
}

void DebugSystem::Init()
{
    System::Init();
    auto* debugComp = m_world->CreateWorldEntity("DebugSystemEntity")->AddComponent<DebugComponent>();

    GetRedLogger()->AddOutput([=](const Logger::LogOoutputInfo& out) { debugComp->AddLog(out); });

    debugComp->AddDebugDrawer("Console", &DebugSystem::RenderConsole);
    debugComp->AddDebugDrawer("Entities", &DebugSystem::RenderEntityTree);
    debugComp->AddDebugDrawer("Physics", &DebugSystem::RenderDebugPhysicsControls);
    debugComp->AddDebugDrawer("Misc", &ShowImGuiDemo);
}

void DebugSystem::RenderConsole(DebugComponent* debug)
{
    PROFILER_EVENT_CATEGORY("DebugSystem::RenderConsole", ProfilerCategory::Debug)

    if (ImGui::SmallButton("Clear"))
    {
        debug->ClearLogs();
    }
    ImGui::SameLine();

    ImGui::PushItemWidth(100);
    // Set log level combo
    {
        static ImGuiComboFlags flags = 0;
        LogLevel currentLogLevel = GetRedLogger()->GetLogLevel();
        if (ImGui::BeginCombo("Log level", Logger::logLevelAsString[(int)currentLogLevel].c_str(), flags))
        {
            for (int level = 0; level < 7; level++)
            {
                const bool is_selected = LogLevel(level) == currentLogLevel;
                if (ImGui::Selectable(Logger::logLevelAsString[level].c_str(), is_selected))
                    SetLogLevel(LogLevel(level));

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }

    ImGui::SameLine();

    static uint32 selectedLogLevels = (uint32) -1;
    std::string shownLevels;
    int bit = 1;
    for (int level = 0; level < 7; level++)
    {
        const bool isSelected = ((1 << (uint32) level) & selectedLogLevels) != 0;
        if (isSelected)
        {
            if (bit != 1)
            {
                shownLevels += "|";
            }

            shownLevels += Logger::logLevelAsString[level];
        }

        bit++;
    }

    // Log level filter
    {
        static ImGuiComboFlags flags = 0;

        if (ImGui::BeginCombo("Shown log levels", shownLevels.c_str(), flags))
        {
            for (int level = 0; level < 7; level++)
            {
                const bool isSelected = ((1 << (uint32) level) & selectedLogLevels) != 0;
                if (ImGui::Selectable(Logger::logLevelAsString[level].c_str(), isSelected))
                {
                    if (isSelected)
                    {
                        selectedLogLevels &= ~(1 << (uint32) level);
                    }
                    else
                    {
                        selectedLogLevels |= (1 << (uint32) level);
                    }
                }
            }
            ImGui::EndCombo();
        }
    }
    ImGui::PopItemWidth();

    static bool autoScroll = true;
    bool scrollToBottom = false;
    ImGui::Checkbox("Auto-scroll", &autoScroll);
    ImGui::SameLine();
    if (ImGui::Button("Scroll to bottom"))
        scrollToBottom = true;

    ImGui::Separator();

    // Log content

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false,
                      ImGuiWindowFlags_HorizontalScrollbar);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));  // Tighten spacing

    const auto& logs = debug->GetLogBuffer();
    for (const auto& log : logs)
    {
        if ((selectedLogLevels & (1 << (uint32) log.level)) == 0)
        {
            continue;
        }

        ImVec4 color;
        switch (log.level)
        {
            case LogLevel::LEVEL_CUSTOM:
                color = ImVec4(0.8f, 0.6f, 0.f, 1.f);
                break;
            case LogLevel::LEVEL_WARNING:
                color = ImVec4(1.f, 0.8f, 0.f, 1.f);
                break;
            case LogLevel::LEVEL_ERROR:
                color = ImVec4(1.f, 0.2f, 0.f, 1.f);
                break;
            case LogLevel::LEVEL_FATAL:
                color = ImVec4(1.f, 0.4f, 0.f, 1.f);
                break;
            default:
                color = ImGui::GetStyle().Colors[ImGuiCol_Text];
                break;
        }

        ImGui::PushStyleColor(ImGuiCol_Text, color);

        ImGui::TextUnformatted(log.str.c_str());

        if (ImGui::IsItemClicked(0))  // TODO not working
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Copy"))
                {
                    ImGui::SetClipboardText(log.str.c_str());
                }
                ImGui::EndPopup();
            }
        }

        ImGui::PopStyleColor();
    }

    if (scrollToBottom || (autoScroll && ImGui::GetScrollY() < ImGui::GetScrollMaxY()))
        ImGui::SetScrollHereY(1.0f);
    scrollToBottom = false;

    ImGui::PopStyleVar();
    ImGui::EndChild();

    ImGui::Separator();

    // Input zone
    bool reclaimFocus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;

    static char inputBuffer[512] = {0};
    if (ImGui::InputText("Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), input_text_flags))
    {
        debug->HandleCommand(inputBuffer);
        inputBuffer[0] = '\0';
        reclaimFocus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaimFocus)
        ImGui::SetKeyboardFocusHere(-1);  // Auto focus previous widget
}

void DebugSystem::Update()
{
    PROFILER_EVENT_CATEGORY("DebugSystem::Update", ProfilerCategory::Debug);

    auto events = QuerySingletonComponent<1>();
    auto debugComp = QuerySingletonComponent<0>();

    m_world->GetPhysicsWorld()->DrawDebug();

    static bool open = true;
    if (ImGui::Begin("Debug menu", &open))
    {
        const ImGuiTabBarFlags tab_bar_flags =
            ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton;
        if (ImGui::BeginTabBar("MenuDebugTabBar", tab_bar_flags))
        {
            for (auto& drawer : debugComp->m_drawers)
            {
                if (ImGui::BeginTabItem(drawer.name.c_str()))
                {
                    drawer.callback(debugComp.Get());

                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    if (events->GetKeyDown(KeyCodes::KEY_F2))
    {
        CVar<FullScreenMode::Enum> fullscreen{"fullscreen_mode", "window", FullScreenMode::WINDOWED};

        fullscreen.ChangeValue(fullscreen.GetValue() == FullScreenMode::WINDOWED ? FullScreenMode::FULLSCREEN
                                                                                 : FullScreenMode::WINDOWED);
    }

    if (events->GetKeyDown(KeyCodes::KEY_F5))
    {
        Time::SetTimeScale(Time::TimeScale() + 0.1F);
    }

    if (events->GetKeyDown(KeyCodes::KEY_F6))
    {
        Time::SetTimeScale(Time::TimeScale() - 0.1F);
    }

    if (events->GetKey(KeyCodes::KEY_B) && events->GetKey(KeyCodes::KEY_LCTRL))
    {
        m_world->GetCurrentLevel()->Serialize(Path::Resource("serializedLevel.json"));
    }

    if (events->GetKey(KeyCodes::KEY_L) && events->GetKey(KeyCodes::KEY_LCTRL))
    {
        m_world->LoadLevel(Path::Resource("serializedLevel.json"));
    }
}

void ShowEntityList(DebugComponent* debug)
{
    auto* world = debug->GetWorld();
    const auto& entities = world->GetEntities();
    auto& filteredEntities = debug->GetFilteredEntities();

    static char searchStr[512] = {};
    static bool caseInsensitive = true;

    bool textModified = ImGui::InputText("##SearchText", searchStr, 512, ImGuiInputTextFlags_EnterReturnsTrue);
    if (textModified)
        ImGui::SetKeyboardFocusHere(-1);
    textModified = ImGui::IsItemDeactivatedAfterEdit() || textModified;
    ImGui::SameLine();
    textModified = ImGui::Button("Search") || textModified;
    ImGui::SameLine();
    textModified = ImGui::Checkbox("Ignore case", &caseInsensitive) || textModified;

    static bool bFirst = true;
    if (textModified || bFirst)
    {
        bFirst = false;

        filteredEntities.clear();
        if (searchStr[0] == '\0')
        {
            filteredEntities = entities;
        }
        else
        {
            for (auto e : entities)
            {
                if (utils::Find(e->GetName(), searchStr, caseInsensitive) != std::string::npos)
                {
                    filteredEntities.push_back(e);
                }
            }
        }
    }

    ImVec2 size = {0, 300};
    if (ImGui::BeginTable("split", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable,
                          size))
    {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Position", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();

        for (auto* e : filteredEntities)
        {
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(e->GetName().c_str());

            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("%s", e->GetFullName().c_str());
            }

            auto* transform = e->GetComponent<Transform>();
            auto pos = transform->GetLocalPosition();
            auto scale = transform->GetScale();
            auto rot = transform->GetLocalRotationDeg();

            ImGui::TableNextColumn();
            ImGui::Text("%.2f ; %.2f", pos.x, pos.y);

            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Position %.2f ; %.2f\nScale %.2f ; %.2f\nRotation %.2f", pos.x, pos.y, scale.x,
                                  scale.y, rot);
            }
        }
        ImGui::EndTable();
    }
}

void ShowEntityTree(DebugComponent* /*debug*/)
{
}

enum EntityDisplayMode
{
    List,
    Tree,

    Count
};

void DebugSystem::RenderEntityTree(DebugComponent* debug)
{
    const char* sDisplayMode[] = {"List", "Tree"};

    static int currentMode = EntityDisplayMode::List;
    ImGui::Combo("Display mode", &currentMode, sDisplayMode, EntityDisplayMode::Count);

    ImGui::Separator();

    switch (currentMode)
    {
        case EntityDisplayMode::List:
            ShowEntityList(debug);
            break;
        case EntityDisplayMode::Tree:
            ShowEntityTree(debug);
            break;
    }
}

void DebugSystem::RenderDebugPhysicsControls(DebugComponent* debug)
{
    static bool enabled = false;
    bool enabledChanged = ImGui::Checkbox("Enable debug drawer", &enabled);

    ImGui::Separator();

    int flagValue = 0;
    static bool flags[5] = {true, true, true, true, true};
    static const char* flagsStr[5] = {"Shapes", "Joints", "Bounding boxes", "Pairs", "Center of mass"};
    for (int i = 0; i < 5; i++)
    {
        ImGui::Checkbox(flagsStr[i], &flags[i]);

        flagValue |= (int) (flags[i]) << i;
    }

    if (enabledChanged)
    {
        auto* world = debug->GetWorld();

        if (enabled)
        {
            debug->m_physicsDebugDrawer = std::make_unique<PhysicsDebugDrawer>(debug);
        }
        else
        {
            debug->m_physicsDebugDrawer.release();
        }

        world->GetPhysicsWorld()->SetDebugDrawer(debug->m_physicsDebugDrawer.get());
    }

    if (debug->m_physicsDebugDrawer != nullptr)
        debug->m_physicsDebugDrawer->SetFlags(flagValue);
}
}  // namespace red
