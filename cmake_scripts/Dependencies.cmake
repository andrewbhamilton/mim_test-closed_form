set(DEPENDENCY_NAME_GOOGLETEST GoogleTest)

set(DEPENDENCY_TAG_GOOGLETEST v1.14.0)



include(FetchContent)


# GoogleTest
message(CHECK_START "Fetch dependency: ${DEPENDENCY_NAME_GOOGLETEST}")


FetchContent_Declare(${DEPENDENCY_NAME_GOOGLETEST}
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG ${DEPENDENCY_TAG_GOOGLETEST})
set(BUILD_GMOCK OFF CACHE INTERNAL "")
set(INSTALL_GTEST OFF CACHE INTERNAL "")
set(GTEST_HAS_ABSL OFF CACHE INTERNAL "")
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(${DEPENDENCY_NAME_GOOGLETEST})

set_target_properties(gtest PROPERTIES FOLDER dependencies)
set_target_properties(gtest_main PROPERTIES FOLDER dependencies)


message(CHECK_PASS "Complete")
