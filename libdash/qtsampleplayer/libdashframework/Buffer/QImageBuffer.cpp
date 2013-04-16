/*
 * QImageBuffer.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "QImageBuffer.h"

using namespace libdash::framework::buffer;

QImageBuffer::QImageBuffer    (uint32_t maxcapacity) :
               eos              (false),
               maxcapacity      (maxcapacity)
{
    InitializeConditionVariable (&this->full);
    InitializeConditionVariable (&this->empty);
    InitializeCriticalSection   (&this->monitorMutex);
}
QImageBuffer::~QImageBuffer   ()
{
    this->Clear();

    DeleteConditionVariable (&this->full);
    DeleteConditionVariable (&this->empty);
    DeleteCriticalSection   (&this->monitorMutex);
}

bool            QImageBuffer::PushBack         (QImage *frame)
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->frames.size() >= this->maxcapacity && !this->eos)
        SleepConditionVariableCS(&this->empty, &this->monitorMutex, INFINITE);

    if(this->frames.size() >= this->maxcapacity)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return false;
    }

    this->frames.push_back(frame);

    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);

    return true;
}
QImage*        QImageBuffer::Front            ()
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->frames.size() == 0 && !this->eos)
        SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->frames.size() == 0)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    QImage *frame = this->frames.front();

    LeaveCriticalSection(&this->monitorMutex);

    return frame;
}
QImage*        QImageBuffer::GetFront         ()
{
    EnterCriticalSection(&this->monitorMutex);

    while(this->frames.size() == 0 && !this->eos)
        SleepConditionVariableCS(&this->full, &this->monitorMutex, INFINITE);

    if(this->frames.size() == 0)
    {
        LeaveCriticalSection(&this->monitorMutex);
        return NULL;
    }

    QImage *frame = this->frames.front();
    this->frames.pop_front();

    WakeAllConditionVariable(&this->empty);
    LeaveCriticalSection(&this->monitorMutex);

    return frame;
}
uint32_t        QImageBuffer::Length           ()
{
    EnterCriticalSection(&this->monitorMutex);

    uint32_t ret = this->frames.size();

    LeaveCriticalSection(&this->monitorMutex);

    return ret;
}
void            QImageBuffer::PopFront         ()
{
    EnterCriticalSection(&this->monitorMutex);

    this->frames.pop_front();

    WakeAllConditionVariable(&this->empty);
    LeaveCriticalSection(&this->monitorMutex);
}
void            QImageBuffer::SetEOS           (bool value)
{
    EnterCriticalSection(&this->monitorMutex);

    this->eos = value;

    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
void            QImageBuffer::ClearTail        ()
{
    EnterCriticalSection(&this->monitorMutex);

    int size = this->frames.size() - 1;

    if (size < 1)
        return;

    QImage* frame = this->frames.front();
    this->frames.pop_front();
    for(int i=0; i < size; i++)
    {
        delete this->frames.front();
        this->frames.pop_front();
    }

    this->frames.push_back(frame);
    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
void            QImageBuffer::Clear            ()
{
    EnterCriticalSection(&this->monitorMutex);

    for(size_t i=0; i < this->frames.size(); i++)
    {
        delete this->frames.front();
        this->frames.pop_front();
    }

    WakeAllConditionVariable(&this->empty);
    WakeAllConditionVariable(&this->full);
    LeaveCriticalSection(&this->monitorMutex);
}
uint32_t        QImageBuffer::Capacity         ()
{
    return this->maxcapacity;
}
