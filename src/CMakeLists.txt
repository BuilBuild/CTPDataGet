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

find_package(TBB REQUIRED)

add_library(MarketData ${MarketDataSRC})
add_library(DataWriteFile ${DataWriter})

target_link_libraries(MarketData PUBLIC thostmduserapi_se)
target_link_libraries(DataWriteFile PUBLIC TBB::tbb)