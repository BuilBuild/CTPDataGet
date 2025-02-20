# aux_source_directory(MarketData/ SRC)


# add_library(MarketData ${SRC})
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

find_package(TBB REQUIRED)
# find_package(questdb REQUIRED)
add_library(MarketData ${MarketDataSRC})
add_library(DataWriteFile ${DataWriter})
add_library(DataWriteQuestDB ${DataWriteQuestDBSRC})

target_link_libraries(MarketData PUBLIC thostmduserapi_se)
target_link_libraries(DataWriteFile PUBLIC TBB::tbb)
target_link_libraries(DataWriteQuestDB PUBLIC questdb_client)