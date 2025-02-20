set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/test)

link_libraries(MarketData)
link_libraries(DataWriteFile)

add_executable(CTPConfigTest CTPConfigTest.cc)
add_executable(CTPMarkeDataTest CTPMarketDataTest.cc)
add_executable(DataWriteFileTest DataWriteFileTest.cc)