set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/test)

link_libraries(MarketData)
link_libraries(DataWriteFile)
link_libraries(DataWriteQuestDB)
link_libraries(CTPTraderApiExecutor)
link_libraries(CTPLOB)
link_libraries(CTPEMS)

add_executable(CTPConfigTest CTPConfigTest.cc)
add_executable(CTPMarkeDataTest CTPMarketDataTest.cc)
add_executable(DataWriteFileTest DataWriteFileTest.cc)
add_executable(DataWriteQuestDBTest DataWriteQuestDBTest.cc)
add_executable(QuestConnectPoolTest QuestConnectPoolTest.cc)

# EMS
add_executable(CTPTraderApiExecutorTest CTPTraderApiExecutorTest.cc)
add_executable(CTPEMSTest CTPEMSTest.cc)

# LOB
add_executable(OrderBookTest OrderBookTest.cc)
