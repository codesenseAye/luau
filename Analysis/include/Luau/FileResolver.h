// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
#pragma once

#include <string>
#include <optional>

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#include <iostream>
#endif

namespace Luau
{

class AstExpr;

using ModuleName = std::string;

struct SourceCode
{
    enum Type
    {
        None,
        Module,
        Script,
        Local
    };

    std::string source;
    Type type;
};

struct ModuleInfo
{
    ModuleName name;
    bool optional = false;
};

struct SourceModule;

struct FileResolver
{
    virtual ~FileResolver() {}

    virtual std::optional<SourceCode> readSource(const ModuleName& name) = 0;

    virtual std::optional<ModuleInfo> resolveModule(const ModuleInfo* context, AstExpr* expr, Luau::SourceModule *sourceModule = nullptr)
    {
        return std::nullopt;
    }

    virtual std::string getHumanReadableModuleName(const ModuleName& name) const
    {
        return name;
    }

    virtual std::optional<std::string> getEnvironmentForModule(const ModuleName& name) const
    {
        return std::nullopt;
    }
};

struct NullFileResolver : FileResolver
{
    std::optional<SourceCode> readSource(const ModuleName& name) override
    {
        return std::nullopt;
    }
};

} // namespace Luau
