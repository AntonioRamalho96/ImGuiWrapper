link_libraries(${PROJECT_NAME})

add_executable(main main.cpp)
add_executable(string_reverse string_reverse.cpp)
add_executable(heavy_task_launch heavy_task_launch.cpp)
target_link_libraries(heavy_task_launch pthread)