

cmake_minimum_required(VERSION 3.10 )

project("tmm")

 

add_executable(${PROJECT_NAME}
 examples1/example1.cpp
 include/common.h "include/TMMsolve.h" include/userfunc.h
"src/TMMsolve.cpp" src/userfunc.cpp
) 



find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)


find_package(Armadillo CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE armadillo)

 