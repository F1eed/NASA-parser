add_executable(AnalyzeLog main.cpp)

target_link_libraries(AnalyzeLog PRIVATE ArgParser FileParser Helpers)

target_include_directories(AnalyzeLog PRIVATE ${CMAKE_SOURCE_DIR})
