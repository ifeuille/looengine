

if(LOO_BUILD_TESTS_testframework EQUAL 1)
    add_subdirectory(testframework)
elseif(LOO_BUILD_TESTS_graphic EQUAL 1)
    add_subdirectory(graphic)
endif()
