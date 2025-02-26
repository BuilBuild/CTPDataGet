/*
 * @Author: LeiJiulong
 * @Date: 2025-02-25 23:36:29
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-27 07:49:44
 * @Description:
 */

#include "IOMS.h"

using OMSConfig = ORMSConfig;

class CTPOMS : public IOMS
{
public:
    CTPOMS() = delete;
    CTPOMS(const OMSConfig &config);
    virtual ~CTPOMS();

public:
    //---------- 订单操作接口 ----------
    virtual OrderID createOrder(const OrderRequest &req) override;
    // virtual bool modifyOrder(OrderID id, const OrderModify &mod)override;
    virtual bool cancelOrder(OrderID id) override{ return false;}

    //---------- 状态查询接口 ----------
    virtual OrderStatus getOrderStatus(OrderID id) const override;
    virtual std::vector<Order> getOpenOrders() const override;

    //---------- 连接管理 ----------
    virtual bool connect(const std::string &config) override;
    virtual void disconnect() override;
    virtual bool isConnected() const override;

    // ----------- 行情接收 ----------
    virtual void marketDataReceive() override;

    //---------- 事件订阅 ----------
    virtual void registerCallback(std::function<void(const OrderEvent &)> cb) override;

    //---------- 系统控制 ----------
    virtual void start() override; // 启动OMS
    virtual void stop() override;  // 停止OMS

private:
    //---------- 对外获取数据 ----------
    zmq::context_t context_;
    zmq::socket_t subscriber_;

    std::thread marketDataThread_;

};
