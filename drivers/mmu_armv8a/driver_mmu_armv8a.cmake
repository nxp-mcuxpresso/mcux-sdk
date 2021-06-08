#Description: ARM MMU driver; user_visible: True
include_guard(GLOBAL)
message("driver_mmu_armv8a component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
${CMAKE_CURRENT_LIST_DIR}/arm_mmu.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

include(driver_common)
