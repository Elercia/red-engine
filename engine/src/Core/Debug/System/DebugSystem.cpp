#include "RedEngine/Core/Debug/System/DebugSystem.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
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
    m_priority = 10;
}

void DebugSystem::Init()
{
    System::Init();
    auto* debugComp = m_world->CreateWorldEntity("DebugSystemEntity")->AddComponent<DebugComponent>();

    GetRedLogger()->AddOutput([=](const std::string& out) { debugComp->AddLog(out); });
}

void DebugSystem::RenderConsole(DebugComponent* debug)
{
    static bool open = true;
    if (!ImGui::Begin("Console", &open))
    {
        ImGui::End();
        return;
    }

    // Header

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Close"))
            open = false;
        ImGui::EndPopup();
    }

    if (ImGui::SmallButton("Clear"))
    {
        debug->ClearLogs();
    }

    static bool autoScroll = true;
    bool scrollToBottom = false;
    ImGui::Checkbox("Auto-scroll", &autoScroll);
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
        ImVec4 color;
        bool has_color = false;
        if (log.find("error") != std::string::npos)
        {
            color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
            has_color = true;
        }
        else if (log[0] == '>')
        {
            color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
            has_color = true;
        }
        if (has_color)
            ImGui::PushStyleColor(ImGuiCol_Text, color);

        ImGui::TextUnformatted(log.c_str());

        if (ImGui::IsItemClicked(0))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable("Clear"))
                {
                    ImGui::SetClipboardText(log.c_str());
                }
                ImGui::EndPopup();
            }
        }

        if (has_color)
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

    ImGui::End();
}

void DebugSystem::Update()
{
    PROFILER_EVENT_CATEGORY("Debug", ProfilerCategory::Input);

    auto* events = m_world->GetWorldComponent<EventsComponent>();
    auto* debugComp = m_world->GetWorldComponent<DebugComponent>();

    RenderConsole(debugComp);

    if (events->GetKeyDown(KeyCodes::KEY_F1))
    {
        if (debugComp->m_physicsDebugDrawer == nullptr)
        {
            debugComp->m_physicsDebugDrawer = std::make_unique<PhysicsDebugDrawer>(debugComp);
            debugComp->m_physicsDebugDrawer->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit |
                                                      b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
        }
        else
        {
            debugComp->m_physicsDebugDrawer.release();
        }

        m_world->GetPhysicsWorld()->SetDebugDrawer(debugComp->m_physicsDebugDrawer.get());
    }

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

    // TODO add the management of the in-game console
}
}  // namespace red
