

if(LOO_PLATFORM_WINDOWS OR LOO_BUILD_TESTS_testframework EQUAL 1 )
    add_subdirectory(testframework)
endif()
if(LOO_PLATFORM_WINDOWS OR LOO_BUILD_TESTS_graphic EQUAL 1)
    add_subdirectory(graphic)
endif()
