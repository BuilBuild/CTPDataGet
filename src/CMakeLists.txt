
set(MarketDataSRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/Config.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/CTPConfig.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/CTPMarketData.cc
)

set(DataWriter 
    ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/DataWriteFile.cc
)

set(DataWriteQuestDBSRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/DataWriteQuestDB.cc
)

set(CTPTraderApiExecutor
    ${CMAKE_CURRENT_SOURCE_DIR}/Trader/EMS/CTPTraderApiExecutor.cc
)

set(CTPLOB 
    ${CMAKE_CURRENT_SOURCE_DIR}/Trader/LOB/CTPLOB.cc
)
set(CTPEMS
    ${CMAKE_CURRENT_SOURCE_DIR}/Trader/EMS/CTPEMS.cc

)

set(CTPOMS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Trader/OMS/CTPOMS.cc
)

set(CTPMSGHUB 
    ${CMAKE_CURRENT_SOURCE_DIR}/Trader/MSGHUB/CTPMSGHUB.cc)

find_package(TBB REQUIRED)

add_library(MarketData ${MarketDataSRC})
add_library(DataWriteFile ${DataWriter})
add_library(DataWriteQuestDB ${DataWriteQuestDBSRC})
add_library(CTPLOB ${CTPLOB})
add_library(CTPEMS ${CTPEMS})
add_library(CTPOMS ${CTPOMS})
add_library(CTPMSGHUB ${CTPMSGHUB})
add_library(CTPTraderApiExecutor ${CTPTraderApiExecutor})


target_link_libraries(MarketData PUBLIC thostmduserapi_se)
target_link_libraries(DataWriteFile PUBLIC TBB::tbb)
target_link_libraries(DataWriteQuestDB PUBLIC questdb_client)
target_link_libraries(CTPTraderApiExecutor PUBLIC thosttraderapi_se)
target_link_libraries(CTPLOB PUBLIC TBB::tbb)
target_link_libraries(CTPMSGHUB PUBLIC CTPLOB)

add_executable(main main.cc)
target_link_libraries(main MarketData DataWriteFile DataWriteQuestDB)