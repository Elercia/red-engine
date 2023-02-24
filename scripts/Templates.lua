function TemplateProject(Name)
	print("Template Project : " .. Name)
	
	group("Template")
	project(Name)
	kind("ConsoleApp")

	RedDefaultProjectOptions()

	local templatePath = rootPath .. "/templates/"..Name

	files
	{
		templatePath .. "/src/**.hpp",
		templatePath .. "/src/**.inl",
		templatePath .. "/src/**.cpp",
	}

	includedirs
	{
		templatePath .. "/include/",
		enginePath .. "/include/",
		ExternalIncludeDirs,
	}

	libdirs
	{
		ExternalLibDirs
	}

	links
	{
		"RedEngineLib",
		libsToLink
	}

	postbuildcommands { '{COPY} "%{cfg.buildtarget.abspath}" "' .. rootPath .. 'templates/%{prj.name}"' }

	print("Copying engine resources for template " .. Name)
	CopyFile(rootPath.."templates/ENGINE_RESOURCES/", rootPath.."templates/"..Name.."/RESOURCES/ENGINE_RESOURCES/")
end

TemplateProject("Pong")
TemplateProject("Perf")
