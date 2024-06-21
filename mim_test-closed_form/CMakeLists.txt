set(TARGET_NAME ${PROJECT_NAME})

file(GLOB SOURCE_FILES *.cpp *.c *.h)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE GTest::gtest_main)


if(BUILD_TESTING)
	include(GoogleTest)

	gtest_discover_tests(${TARGET_NAME})
endif()
