cmake_minimum_required (VERSION 3.20)

project (oop2_project)

set (MY_AUTHORS "Ofek_Gorgi-Bark_Kobi")

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
	set(CMAKE_CXX_STANDARD 23)
else ()
	set(CMAKE_CXX_STANDARD 20)
endif ()
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
	add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline /analyze)

endif ()


if(APPLE)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

	add_executable (${CMAKE_PROJECT_NAME}  src/main.cpp)

	add_subdirectory (include)
	add_subdirectory (src)
	add_subdirectory (assets)
	add_subdirectory (utils)
	add_subdirectory (services)
	add_subdirectory (models)
	add_subdirectory (stateManagement)
	add_subdirectory (screens)


	# external libraries
	#add_subdirectory (dependencies/curl-8.1.2)
	#add_subdirectory (dependencies/nlohmann)


	set (SFML_STATIC_LIBRARIES FALSE)
	set (SFML_DIR "/usr/local/Cellar/sfml/2.5.1")

	find_package (SFML 2.5 COMPONENTS audio graphics REQUIRED)
	find_package(CURL REQUIRED)

	set_target_properties ( PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

	target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-network ${CURL_LIBRARIES})

endif()

if(WIN32)

	add_executable (${CMAKE_PROJECT_NAME} main.cpp screens/src/AfterGameScreen.cpp screens/include/AfterGameScreen.h screens/src/HelpScreen.cpp screens/include/HelpScreen.h screens/include/ErrorScreen.h src/GameBar.cpp include/GameBar.h utils/src/TimeCounting.cpp utils/include/TimeCounting.h utils/src/TextClass.cpp utils/include/TextClass.h)

	target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

	add_subdirectory (include)
	add_subdirectory (src)
	add_subdirectory (assets)
	add_subdirectory (utils)
	add_subdirectory (services)
	add_subdirectory (models)
	add_subdirectory (stateManagement)
	add_subdirectory (screens)

	set (SFML_STATIC_LIBRARIES TRUE)
	set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

	find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

	set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

	target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-main sfml-audio)

	configure_file (C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)

	include(cmake/zip.cmake)

endif()