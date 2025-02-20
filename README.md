<!--
 * @Author: LeiJiulong
 * @Date: 2025-02-20 01:28:02
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 12:56:28
 * @Description: 
-->
### 安装说明
#### 环境要求
| 库       | 版本                          |
|------------|-----------------------------|
| tbb   | 22    | 
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
