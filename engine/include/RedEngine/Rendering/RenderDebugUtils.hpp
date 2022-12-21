#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <GL/gl3w.h>

namespace red
{
static inline void OpenGLMessageCallback(GLenum source, GLenum type, GLuint /*id*/, GLenum severity, GLsizei /*length*/,
                                         const GLchar* message, const void* /*userParam*/)
{
    const char* sourceStr;
    const char* typeStr;
    const char* severityStr;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            sourceStr = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceStr = "WINDOW SYSTEM";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceStr = "SHADER COMPILER";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceStr = "THIRD PARTY";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceStr = "APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceStr = "UNKNOWN";
            break;
        default:
            sourceStr = "UNKNOWN";
            break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "DEPRECATED BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "UDEFINED BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeStr = "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeStr = "OTHER";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeStr = "MARKER";
            break;
        default:
            typeStr = "UNKNOWN";
            break;
    }

    bool log = false;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "HIGH SEVERITY";
            log = true;
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "MEDIUM SEVERITY";
            log = true;
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "LOW SEVERITY";
            log = true;
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "NOTIFICATION";
            // log = true;
            break;
        default:
            severityStr = "UNKNOWN";
            log = true;
            break;
    }

    if (log)
    {
        RED_LOG_ERROR("OpenGL {}::{} raised from {}: {}\n", typeStr, severityStr, sourceStr, message);
    }
}
}  // namespace red