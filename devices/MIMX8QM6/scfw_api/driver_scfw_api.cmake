#Description: SCFW API Driver; user_visible: True
include_guard(GLOBAL)
message("driver_scfw_api component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main/ipc_imx8qm.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/irq/irq_rpc_clnt.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/misc/misc_rpc_clnt.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/pad/pad_rpc_clnt.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/pm/pm_rpc_clnt.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/rm/rm_rpc_clnt.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/seco/seco_rpc_clnt.c
    ${CMAKE_CURRENT_LIST_DIR}/svc/timer/timer_rpc_clnt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/main
    ${CMAKE_CURRENT_LIST_DIR}/svc
    ${CMAKE_CURRENT_LIST_DIR}/svc/irq
    ${CMAKE_CURRENT_LIST_DIR}/svc/misc
    ${CMAKE_CURRENT_LIST_DIR}/svc/pad
    ${CMAKE_CURRENT_LIST_DIR}/svc/pm
    ${CMAKE_CURRENT_LIST_DIR}/svc/rm
    ${CMAKE_CURRENT_LIST_DIR}/svc/seco
    ${CMAKE_CURRENT_LIST_DIR}/svc/timer
)


