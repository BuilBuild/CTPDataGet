
# 设置proto文件路径和生成路径
set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB PROTO_FILES ${PROTO_SRC_DIR}/*.proto)

# 生成proto文件
protobuf_generate_cpp(
    PROTO_SRCS
    PROTO_HDRS
    # OUTPUT_DIR  ${PROTO_GEN_DIR}
    ${PROTO_FILES}
)
# 添加生成目标
add_library(protos ${PROTO_SRCS} ${PROTO_HDRS})

#  grpc
# file(GLOB RPCSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
# message(${RPCSRC})
# add_library(OrderRequestRPC  ${RPCSRC})








