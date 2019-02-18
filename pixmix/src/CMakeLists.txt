include_directories(${PIXMIX_SOURCE_DIR}/include)

set(SOURCES main.cc dr.cc tracking.cc)

add_executable(PIXMIX ${SOURCES})

# Hard coded link, only for windows.
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(PIXMIX PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(PIXMIX ${OpenCV_LIBS})
endif()

target_link_libraries(PIXMIX ${PIXMIX_RELEASE_LIB} ${PIXMIX_DEBUG_LIB})

