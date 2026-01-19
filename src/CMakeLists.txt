cmake_minimum_required(VERSION 4.2)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS
                Core
                Widgets)

set(floyd_SRCS main.cpp window.cpp)

add_executable(floyd ${floyd_SRCS})

target_link_libraries(floyd Qt5::Core Qt5::Widgets)

