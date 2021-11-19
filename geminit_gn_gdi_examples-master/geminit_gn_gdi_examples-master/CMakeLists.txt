cmake_minimum_required(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

PROJECT(example_setpixel)
PROJECT(example_line)
PROJECT(example_ellipse)
PROJECT(example_image)
PROJECT(example_polygon)
PROJECT(example_rectangle)
PROJECT(example_string)
PROJECT(example_triangle)

INCLUDE_DIRECTORIES(include/)

FILE(MAKE_DIRECTORY out)
FILE(MAKE_DIRECTORY out/lib)
FILE(MAKE_DIRECTORY out/fonts)
FILE(MAKE_DIRECTORY out/images)
FILE(COPY script/ DESTINATION out/ )
FILE(COPY lib/ DESTINATION out/lib/ )
FILE(COPY fonts/ DESTINATION out/fonts/ )
FILE(COPY images/ DESTINATION out/images/ )

ADD_EXECUTABLE(example_setpixel src/example_setpixel.cpp)
ADD_EXECUTABLE(example_line src/example_line.cpp)
ADD_EXECUTABLE(example_ellipse src/example_ellipse.cpp)
ADD_EXECUTABLE(example_image src/example_image.cpp)
ADD_EXECUTABLE(example_polygon src/example_polygon.cpp)
ADD_EXECUTABLE(example_rectangle src/example_rectangle.cpp)
ADD_EXECUTABLE(example_string src/example_string.cpp)
ADD_EXECUTABLE(example_triangle src/example_triangle.cpp)

TARGET_LINK_LIBRARIES(example_setpixel -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_line -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_ellipse -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_image -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_polygon -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_rectangle -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_string -Llib geminit-gn-gdi png16 jpeg)
TARGET_LINK_LIBRARIES(example_triangle -Llib geminit-gn-gdi png16 jpeg)

SET_TARGET_PROPERTIES(example_setpixel PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_line PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_ellipse PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_image PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_polygon PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_rectangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_string PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
SET_TARGET_PROPERTIES(example_triangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)

add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)
