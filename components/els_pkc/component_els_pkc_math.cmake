#Description: Component els_pkc.math; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_math component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ExactDivide.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ExactDivideOdd.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ExactDivideOdd_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ModExp_SqrMultL2R.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ModInv.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ModInv_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_NDash.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_NDash_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_QDash.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_QDash_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_ReduceModEven.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_SecModExp.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_SecModExp_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/src/mcuxClMath_Utils.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMath/inc/internal
)


include(component_els_pkc_secure_counter)
include(component_els_pkc_pre_processor)
include(component_els_pkc_flow_protection)
include(component_els_pkc_pkc)
