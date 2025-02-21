/*
 * @Author: LeiJiulong
 * @Date: 2025-02-20 03:16:53
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-21 14:17:42
 * @Description: 
 */
#pragma once

#include "DataWriter.h"

class WriterAdapter : public Writer
{
public:
    WriterAdapter() = delete;
    WriterAdapter(WriterAdaptee *writerAdaptee):writerAdaptee_(writerAdaptee){}

    void toWrite(const OrderBook &ob) override 
    {
        writerAdaptee_->specificWrite(ob);
    }
    
private:
    WriterAdaptee* writerAdaptee_;
};
