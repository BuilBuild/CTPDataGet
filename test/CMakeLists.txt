set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/test)

link_libraries(MarketData)
link_libraries(DataWriteFile)
link_libraries(DataWriteQuestDB)
link_libraries(CTPTraderApiExecutor)
link_libraries(CTPLOB)
link_libraries(CTPEMS)
link_libraries(protos)
link_libraries(CTPOMS)
link_libraries(CTPMSGHUB)
link_libraries(zmq)
link_libraries(protos)
link_libraries(ICTPStrategy)


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

# ZMQ
# 测试数据行情发布
add_executable(CTPMarketDataGetRunPub CTPMarketDataGetRunPub.cc)
add_executable(CTPMarketDataGetSub CTPMarketDataGetSub.cc)

# OMS
add_executable(CTPOMSTest CTPOMSTest.cc)

# MSGHUB
add_executable(CTPMsgHubTest CTPMsgHubTest.cc)
add_executable(QuestDBSubscriberWriterTest QuestDBSubscriberWriterTest.cc)

# Strategy
add_executable(MaCTPStrategyTest MaCTPStrategyTest.cc)

