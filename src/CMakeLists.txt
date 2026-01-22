# Replace the explicit file list with a globbing pattern to include all .cpp files recursively
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})