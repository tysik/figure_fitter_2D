cmake_minimum_required(VERSION 2.8)
project(figure_fitter_2D)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Armadillo REQUIRED)
include_directories(${Armadillo_INCLUDE_DIRS} figures fitters)

add_executable(point_fit_example examples/point_fit_example.cpp figures/point.h figures/vec.h figures/figure.h fitters/figure_fitter.h)
target_link_libraries(point_fit_example ${ARMADILLO_LIBRARIES})

add_executable(line_fit_example examples/line_fit_example.cpp figures/line.h fitters/figure_fitter.h)
target_link_libraries(line_fit_example ${ARMADILLO_LIBRARIES})

add_executable(segment_fit_example examples/segment_fit_example.cpp figures/segment.h fitters/figure_fitter.h)
target_link_libraries(segment_fit_example ${ARMADILLO_LIBRARIES})

add_executable(circle_fit_example examples/circle_fit_example.cpp figures/circle.h fitters/figure_fitter.h)
target_link_libraries(circle_fit_example ${ARMADILLO_LIBRARIES})
