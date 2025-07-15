add_executable(AnalyzeLog main.cpp)

target_link_libraries(AnalyzeLog PUBLIC ArgParser FileParser)

target_include_directories(AnalyzeLog PUBLIC ${CMAKE_SOURCE_DIR})
