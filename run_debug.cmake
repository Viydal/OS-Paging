# run_debug.cmake

# Path to executable
set(EXECUTABLE "${CMAKE_BINARY_DIR}/memsim")

# Arguments to pass to the program
set(ARGUMENTS "../traces/sampleTraces/trace1 3 rand debug")

# Run the executable
execute_process(
    COMMAND ${EXECUTABLE} ${ARGUMENTS}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE out
    ERROR_VARIABLE err
)

# Print output to console
message(STATUS "Program output:\n${out}")
message(STATUS "Program error output:\n${err}")

if(NOT ${result} EQUAL 0)
    message(FATAL_ERROR "Program failed with exit code ${result}")
endif()
