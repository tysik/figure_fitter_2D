cmake_minimum_required(VERSION 2.8)
project(figure_fitter_2D)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Headers figure_fitter.h figures/vec.h figures/figure.h figures/point.h
  figures/line.h figures/segment.h figures/circle.h figures/arc.h)

find_package(Armadillo REQUIRED)
include_directories(${Armadillo_INCLUDE_DIRS} /usr/include/python2.7 figures)

add_executable(dummy examples/dummy.cpp ${Headers})
target_link_libraries(dummy ${ARMADILLO_LIBRARIES} libpython2.7.so)

add_executable(point_fit_example examples/point_fit_example.cpp ${Headers})
target_link_libraries(point_fit_example ${ARMADILLO_LIBRARIES} libpython2.7.so)

add_executable(line_fit_example examples/line_fit_example.cpp ${Headers})
target_link_libraries(line_fit_example ${ARMADILLO_LIBRARIES} libpython2.7.so)

add_executable(segment_fit_example examples/segment_fit_example.cpp ${Headers})
target_link_libraries(segment_fit_example ${ARMADILLO_LIBRARIES} libpython2.7.so)

add_executable(circle_fit_example examples/circle_fit_example.cpp ${Headers})
target_link_libraries(circle_fit_example ${ARMADILLO_LIBRARIES} libpython2.7.so)
