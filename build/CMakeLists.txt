

cmake_minimum_required (VERSION 2.6)

set(PROJECT_NAME  Vidya)
set(ENGINE_NAME  Engine)
project (${PROJECT_NAME})

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -pedantic -g -Wall -Wextra")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../bin)
set(ENGINE_SRC_DIR ${PROJECT_BINARY_DIR}/../src/engine/)
set(GAME_SRC_DIR ${PROJECT_BINARY_DIR}/../src/game/) 
set(TEST_SRC_DIR ${PROJECT_BINARY_DIR}/../src/tests/)
set(TEST_OUTPUT_DIR ${PROJECT_BINARY_DIR}/../testBin/)

#Prepare engine lib
file(GLOB ENGINE_SRC_FILES
    ${ENGINE_SRC_DIR}*.hpp
    ${ENGINE_SRC_DIR}*.cpp
)
add_library(${ENGINE_NAME} STATIC ${ENGINE_SRC_FILES})
target_include_directories (${ENGINE_NAME} PUBLIC ${PROJECT_BINARY_DIR}/../libs)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2 )
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${ENGINE_NAME} dl pthread ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
#target_link_libraries(${ENGINE_NAME} SDL2main SDL2 SDL_ttf)

set_target_properties(${ENGINE_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../lib)


#Prepare vidya binary
file(GLOB GAME_SRC_FILES
    ${GAME_SRC_DIR}*.hpp
    ${GAME_SRC_DIR}*.cpp
)
add_executable(${PROJECT_NAME} ${GAME_SRC_FILES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Engine) 


#Prepare testing
enable_testing()
file(GLOB TEST_SRCS ${TEST_SRC_DIR}*.cpp)
foreach(testSrc ${TEST_SRCS})
        get_filename_component(testName ${testSrc} NAME_WE)

        add_executable(${testName} ${testSrc})

        target_link_libraries(${testName} LINK_PUBLIC Engine)
        set_target_properties(${testName} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${TEST_OUTPUT_DIR})

        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${TEST_OUTPUT_DIR} 
                 COMMAND ${TEST_OUTPUT_DIR}${testName} )
endforeach(testSrc)
    