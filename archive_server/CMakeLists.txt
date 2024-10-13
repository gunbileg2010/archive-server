cmake_minimum_required(VERSION 3.10)
project(ArchiveServer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include paths for Crow and OpenSSL
include_directories(/usr/include/crow)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Generate a secure secret during compilation
add_custom_command(
    OUTPUT secrets.hpp
    COMMAND ${CMAKE_COMMAND} -E echo "#ifndef SECRETS_HPP" > ${CMAKE_BINARY_DIR}/secrets.hpp
    COMMAND ${CMAKE_COMMAND} -E echo "#define SECRETS_HPP" >> ${CMAKE_BINARY_DIR}/secrets.hpp
    COMMAND ${CMAKE_COMMAND} -E echo "#include <string>" >> ${CMAKE_BINARY_DIR}/secrets.hpp
    COMMAND ${CMAKE_COMMAND} -E echo "std::string get_secure_secret() { return \"" >> ${CMAKE_BINARY_DIR}/secrets.hpp
    COMMAND ${CMAKE_COMMAND} -E echo "$<SHELL_PATH:openssl rand -base64 32>\"; }" >> ${CMAKE_BINARY_DIR}/secrets.hpp
    COMMAND ${CMAKE_COMMAND} -E echo "#endif" >> ${CMAKE_BINARY_DIR}/secrets.hpp
    DEPENDS ${CMAKE_SOURCE_DIR}/main.cpp
)

# Include generated secrets.hpp
include_directories(${CMAKE_BINARY_DIR})

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Crow REQUIRED)

# Add the executable
add_executable(archive_server main.cpp encryption.cpp)

# Link the necessary libraries
target_link_libraries(archive_server OpenSSL::SSL OpenSSL::Crypto crow)