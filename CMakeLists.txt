cmake_minimum_required (VERSION 2.8.11)
project(sethosonline)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

file(GLOB sethosonline_SRC "*.c" )

add_executable(sethosonline ${sethosonline_SRC})
target_link_libraries(sethosonline
  ${SDL_LIBRARIES} ${SDL_TTF_LIBRARIES} ${SDL_IMAGE_LIBRARIES}
  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} m SDL)
