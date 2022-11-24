find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/common/logger)
include_directories(${PROJECT_SOURCE_DIR}/src/coreapi)

#file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 
#file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

#add_executable(TestSuite ${SOURCES} ${HEADERS})
#target_link_libraries(TestSuite PRIVATE GTest::GTest logger RedisCache)
#set_target_properties(TestSuite PROPERTIES FOLDER "tests")
#add_test(NAME TestSuite COMMAND $<TARGET_FILE:TestSuite> --success)