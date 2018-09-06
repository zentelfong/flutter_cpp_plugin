
solution "flutter_cpp_plugin"
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms {"x64", "x32"}
	


project "flutter_cpp_plugin"
	language "C++"
	kind "StaticLib"
	includedirs { "include","thirdparty/zbar/include"}
	files { "include/**.h","src/**.cpp","src/**.cc","plugins/**.cpp" }
	targetdir("build")
	defines { "_CRT_SECURE_NO_WARNINGS" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "ExtraWarnings"}

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize", "ExtraWarnings"}

