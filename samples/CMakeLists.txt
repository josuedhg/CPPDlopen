set(triangle_src triangle.cc)
add_library(triangle SHARED ${triangle_src})
set_target_properties(triangle PROPERTIES PREFIX "")

include_directories(${CMAKE_SOURCE_DIR}/lib)
set(sample_src sample.cc)
add_executable(sample ${sample_src})
target_include_directories(sample PRIVATE ${CMAKE_SOURCE_DIR}/samples)
target_link_libraries(sample LINK_PUBLIC cppdlopen)
