cmake_minimum_required(VERSION 3.10.2)
project(esc_controller_app C CXX)

file(GLOB esc_controller_app 
    "app/src/*.c"
    "app/src/*.cpp"
    "deps/src/*.c"
    "deps/src/*.cpp"
    "deps/src/*.cc"
    "deps/src/impl/*.cc"
    "deps/src/impl/list_ports/*.cc"
    )

add_executable(${CMAKE_PROJECT_NAME} ${esc_controller_app})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    "app/inc"
    "app/inc/"
    "deps/inc/"
    "deps/inc/"
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} rt pthread)
else()
    target_link_libraries(${PROJECT_NAME} setupapi)
endif()

