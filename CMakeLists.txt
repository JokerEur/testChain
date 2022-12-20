cmake_minimum_required(VERSION 3.8)

project(testChain)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH vcpkg_installed/x64-linux/share)
set(INCLUDE_DIRS include/*.hpp , GUI/*.hpp , GUI/*.h)
set(OpenGL_GL_PREFERENCE LEGACY)

if(UNIX AND NOT APPLE)
    message(STATUS ">>> Linux")

    set(OPENSSL_ROOT_DIR vcpkg_installed/x64-linux)
    set(CMAKE_PREFIX_PATH vcpkg_installed/x64-linux/share)

    include_directories(${INCLUDE_DIRS},vcpkg_installed/x64-linux/include, include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/lib)

    INCLUDE_DIRECTORIES(${INCLUDE_DIRS},vcpkg_installed/x64-linux/include , include)
    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/lib)
endif()

if(APPLE)
    message(STATUS ">>> MacOS")

    add_definitions(-Wno-deprecated-declarations)

    set(OPENSSL_ROOT_DIR vcpkg_installed/x64-osx)
    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/vcpkg_installed/x64-osx)

    include_directories(${INCLUDE_DIRS},vcpkg_installed/x64-osx/include , include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/lib)

    INCLUDE_DIRECTORIES(${INCLUDE_DIRS},vcpkg_installed/x64-osx/include , include)
    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/lib)

endif()

include(FindOpenSSL)
message(STATUS "OPENSSL_FOUND = ${OPENSSL_FOUND}")
message(STATUS "OPENSSL_INCLUDE_DIR = ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OPENSSL_CRYPTO_LIBRARY = ${OPENSSL_CRYPTO_LIBRARY}")
message(STATUS "OPENSSL_CRYPTO_LIBRARIES = ${OPENSSL_CRYPTO_LIBRARIES}")
message(STATUS "OPENSSL_SSL_LIBRARY = ${OPENSSL_SSL_LIBRARY}")
message(STATUS "OPENSSL_SSL_LIBRARIES = ${OPENSSL_SSL_LIBRARIES}")
message(STATUS "OPENSSL_LIBRARIES = ${OPENSSL_LIBRARIES}")
message(STATUS "OPENSSL_VERSION = ${OPENSSL_VERSION}")


file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp , 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp,
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/*.cpp
)

file(GLOB INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp, 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ,
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/*.hpp,
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/*.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL)
