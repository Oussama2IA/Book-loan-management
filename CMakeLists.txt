project(LoanApp)
cmake_minimum_required(VERSION 3.16)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LINK_DIRS})
add_definitions(${GTK3_CFLAGS_OTHERS})

add_library(
    members
    src/members.c
)

add_library(
    books
    src/books.c
)

add_library(
    loans
    src/loans.c
)

add_executable(LoanApp src/main.c)

target_link_libraries(LoanApp members books loans ${GTK3_LIBRARIES})