###
 # @Author: LeiJiulong
 # @Date: 2025-02-28 13:16:46
 # @LastEditors: LeiJiulong && lei15557570906@outlook.com
 # @LastEditTime: 2025-02-28 13:16:48
 # @Description: 
### 

# protoc -I=. \                  # 指定 .proto 文件所在目录
#   --cpp_out=. \                # 生成普通 protobuf 代码（.pb.h, .pb.cc）
#   --grpc_out=. \               # 生成 gRPC 代码（.grpc.pb.h, .grpc.pb.cc）
#   --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \  # 指定 gRPC 插件路径
#   example.proto                # 输入文件
protoc -I=. --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin OrderRequest.proto
