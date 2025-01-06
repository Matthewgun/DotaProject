cmake_minimum_required(VERSION 3.5)
project(DotaProject VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(DotaProject main.cpp HeroLoader.cpp Choosing.cpp Restart.cpp)

# Check and copy openal32.dll if it exists in the project directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/openal32.dll")
    add_custom_command(
        TARGET DotaProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "${CMAKE_CURRENT_SOURCE_DIR}/openal32.dll" 
            "$<TARGET_FILE_DIR:DotaProject>/openal32.dll"
        COMMENT "Copying openal32.dll"
    )
else()
    message(WARNING "openal32.dll not found in the specified directory.")
endif()

# Additional commands for copying assets or other libraries can go here

target_link_libraries(DotaProject PRIVATE sfml-graphics sfml-system sfml-window sfml-audio)

install(TARGETS DotaProject)