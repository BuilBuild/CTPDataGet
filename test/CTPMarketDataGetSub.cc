/*
 * @Author: LeiJiulong
 * @Date: 2025-02-27 11:48:11
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 12:37:33
 * @Description:
 */
#include "protos/MarketData.pb.h"

#include <zmq.hpp>

#include <iostream>

int main()
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.connect("tcp://localhost:5556");
    socket.set(zmq::sockopt::subscribe, "MarketData");

    while (true)
    {
        marketdata::MarketData md;
        zmq::message_t message;
        if (auto res = socket.recv(message, zmq::recv_flags::none))
        {
            // res 是 std::optional<size_t>，用 *res 获取字节数
            std::cout << "Received " << *res << " bytes"<< std::endl;
            md.ParseFromArray(message.data(), message.size());
            std::cout << "Received MarketData: " << md.DebugString() << std::endl;
        }
        else
        {
            // 获取错误码的正确方式
            int error_code = zmq_errno();
            std::cerr << "Receive failed (error: " << error_code << ")"
                      << " - " << zmq_strerror(error_code) << std::endl;
        }
       
    }
}
