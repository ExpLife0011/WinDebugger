-- premake5.lua
-- cmd> premake5 --file=premake5.lua vs2015

-- solution
workspace "BuildAll"
    configurations { "Debug", "Release" }
    location "Intermedia"
    language "C++"
    architecture "x86"
    
	-- Catch requires RTTI and exceptions
	exceptionhandling "On"
	rtti "On"


    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        targetsuffix("_d")

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    filter "system:windows"
        defines { "_WIN32" }

    filter {}

    targetdir("../Bin")  
    objdir("Intermedia/Obj/%{prj.name}/%{cfg.longname}")
   
-----------------------------------------------------   
-- Helper function for set  ------------
function setup_include_link_env()
    includedirs {
		"../Src"
	}
	
 --   libdirs {
 --       "../lib"
 --   }
	
 --	filter "configurations:Debug"
 --		links { }
	
 --	filter "configurations:Release"
 --	links { }
		
end

-- project: example access kernel address space
project "Example_AccKernel"
    kind "ConsoleApp"
    setup_include_link_env()
	files {
        "../Src/Examples/AccKernel.cpp"
    }
    
-- project: example write code page
project "Example_WriteCodePage"
    kind "ConsoleApp"
    setup_include_link_env()
	files {
        "../Src/Examples/WriteCodePage.cpp"
    }
	
-- project: example modify data segment  register. 
project "Example_ProtectSegmenet"
    kind "ConsoleApp"
    setup_include_link_env()
	files {
        "../Src/Examples/ProtectSegmenet.cpp"
    }

-- project: example fault exception. 
project "Example_Fault"
    kind "ConsoleApp"
    setup_include_link_env()
	files {
        "../Src/Examples/Fault.cpp"
    }
