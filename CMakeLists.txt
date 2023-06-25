cmake_minimum_required (VERSION 3.23)

project (oop2_project)
set (MY_AUTHORS "Ofek_Gorgi-Bark_Kobi")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (assets)
add_subdirectory (utils)
add_subdirectory (services)
add_subdirectory (models)
add_subdirectory (stateManagement)
add_subdirectory (screens)

# external libraries
if(WIN32)
	set (CURL_USE_SCHANNEL TRUE)
endif()
add_subdirectory (dependencies/curl-8.1.2)
add_subdirectory (dependencies/nlohmann)

include (cmake/Zip.cmake)

if(WIN32)
	set (SFML_LOCATION "C:/SFML/SFML-2.5.1")
	set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
endif()

if(APPLE)
	set (SFML_DIR "/usr/local/Cellar/sfml/2.5.1")
endif()

set(CURL_LIBRARY dependencies/curl-8.1.2)
set(CURL_INCLUDE_DIR dependencies/curl-8.1.2/include)

find_package (SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(CURL REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _USE_MATH_DEFINES NOMINMAX)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CURL_LIBRARIES}/include)
target_link_libraries (${CMAKE_PROJECT_NAME} PRIVATE sfml-main sfml-graphics sfml-audio sfml-network CURL::libcurl nlohmann_json::nlohmann_json)

include (cmake/SFML.cmake)