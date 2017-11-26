cmake_minimum_required(VERSION 2.8)
project(figure_fitter_2D)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -fpermissive ${CMAKE_CXX_FLAGS} -Wfatal-errors -Wno-write-strings")

find_package(Armadillo REQUIRED)

add_executable(point_fit_example point_fit_example.cpp figures.h fitter.h)
target_link_libraries(point_fit_example ${ARMADILLO_LIBRARIES})

#add_executable(circle_fit_example circle_fit_example.cpp figures.h fitter.h)
#target_link_libraries(circle_fit_example ${ARMADILLO_LIBRARIES})
