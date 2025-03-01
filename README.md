<!--
 * @Author: LeiJiulong
 * @Date: 2025-02-20 01:28:02
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-01 14:40:27
 * @Description: 
-->
### 安装说明
#### 环境要求
| 库               | 版本      |
| ---------------- | --------- |
| tbb              | >=22      |
| spdlog           | >= 1.14   |
| c-questdb-client | >= 4.0.2  |
| protobuf         | >=3.21.12 |
| zeroMQ           | >=4.3.4   |
##### 上期动态库
将上期动态库改名如下
```
thostmduserapi_se.so -> libthostmduserapi_se.so
```
```
thosttraderapi_se.so -> libthosttraderapi_se.so
```
#### config配置
#### INI配置

```ini
[questDBConfig]
addr=localhost:9000
username=Future
password=quest
max_pool_size=10;
init_pool_size=3;
[CTP]
ConfigPath=/home/leijiulong/temp/ctp_data/CtpConfig.json
[CSV]
CSVOutPutPath=/home/leijiulong/temp/CTPDataGet/DataStore/CSV/
```
CSV 为csv文件输出路径
##### CTP (CtpConfig.json)
在INI配置文件中ConfigPath为CTP配置地址
```json
{
    "gTradeFrontAddr": "tcp://180.168.146.187:10212",
    "BrokerID": "9999",
    // 用户ID
    "UserID": "****",
    // 用户密码
    "PassWord": "****",
    // 订阅合约
    "InstrumentID": [
        "cu2503",
        "al2504",
        "zn2503",
        "pb2503",
        "au2504",
        "ag2504",
        "rb2505",
        "wr2505",
        "fu2505",
        "ru2505",
        "bu2504",
        "hc2505"
    ]
}
```
### 使用说明
```c++
#include <iostream>
#include "MarketData/CTPConfig.h"
#include "MarketData/CTPMarketData.h"
#include "MarketData/DataWriteFile.h"
#include "MarketData/DataWriterAdapter.h"
#include <functional>

int main(int argc, char* argv[])
{
    char configPath[128]{};
    if(argc>1)
    {
        sprintf(configPath, "%s", argv[1]);
    }
    else
    {
        sprintf(configPath, "%s", "/home/leijiulong/temp/CTPDataGet/config.ini");
    }

    CTPConfig config(configPath);
    CTPMarketDataAdapter cad;
    // 初始化一个适配器对象
    DataWriteFile dw;
    WriterAdapter da(&dw);
    auto iniPtr = config.getIniPtr();
    const char* csvPath = iniPtr->GetValue("CSV", "CSVOutPutPath");
    // 设置文件写入路径
    dw.setFileDirPath(csvPath);
    
    cad.connect(&config);
    // 添加写入回调 处理每次接收到行情，也可以自定义回调，输出到其他位置
    cad.set_callback(std::bind(&WriterAdapter::toWrite, &da, std::placeholders::_1));
    // 订阅标的
    cad.subscribe(config.getInstrumentId());
    
    return 0;
}
```
按照如上代码，编译成文件后（如编译为 CTPMarketDataTest）可进行如下运行/测试

```shell
# 第二个参数为配置文件路径
./CTPMarketDataTest /***/config.ini
```