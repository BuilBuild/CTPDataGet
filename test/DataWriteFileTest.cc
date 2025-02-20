/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 03:56:24
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 08:35:08
 * @Description: 
 */
#include "MarketData/DataWriteFile.h"
#include "MarketData/DataWriterAdapter.h"
#include "MarketData/DataWriter.h"

#include <iostream>
#include <vector>
#include <string>
#include <string.h>


class SelfWrite: public WriterAdaptee
{
    void specificWrite(const OrderBook &b) override 
    {
        std::cout << "hello " << b.Volume << std::endl;
    }
};

int main()
{
    
    std::vector<OrderBook> obvec;
    
    DataWriteFile dataWriteFile;
    dataWriteFile.setFileDirPath("/home/leijiulong/temp/CTPDataGet/DataStore/CSV/");
    SelfWrite sw;
    WriterAdapter w(&dataWriteFile);
    WriterAdapter w2(&sw);
    for(int i = 0; i< 10; ++i)
    {
        OrderBook ob{};
        memcpy(ob.InstrumentID, "aaaaa", 5);
        ob.Volume = i;
        w.toWrite(ob);
        w2.toWrite(ob);
    }

    // Data
    
    // return 0;
}
