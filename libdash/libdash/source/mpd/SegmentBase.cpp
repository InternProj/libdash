/*
 * SegmentBase.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "SegmentBase.h"

using namespace dash::mpd;

SegmentBase::SegmentBase    ()  :
                initialization(NULL),
                representationIndex(NULL),
                timescale(1),
                presentationTimeOffset(0),
                timeShiftBufferDepth(""),
                indexRange(""),
                indexRangeExact(false),
                availabilityTimeComplete(true)
{
}
SegmentBase::~SegmentBase   ()
{
    delete(this->initialization);
    delete(this->representationIndex);
}

const IURLType*     SegmentBase::GetInitialization           ()  const
{
    return this->initialization;
}
void                SegmentBase::SetInitialization           (URLType *initialization)
{
    this->initialization = initialization;
}
const IURLType*     SegmentBase::GetRepresentationIndex      ()  const
{
    return this->representationIndex;
}
void                SegmentBase::SetRepresentationIndex      (URLType *representationIndex)
{
    this->representationIndex = representationIndex;
}
uint32_t            SegmentBase::GetTimescale                ()  const
{
    return this->timescale;
}
void                SegmentBase::SetTimescale                (uint32_t timescale)
{
    this->timescale = timescale;
}
uint64_t            SegmentBase::GetPresentationTimeOffset   ()  const
{
    return this->presentationTimeOffset;
}
void                SegmentBase::SetPresentationTimeOffset   (uint64_t presentationTimeOffset)
{
    this->presentationTimeOffset = presentationTimeOffset;
}
const std::string&  SegmentBase::GetTimeShiftBufferDepth     ()  const
{
    return this->timeShiftBufferDepth;
}
void                SegmentBase::SetTimeShiftBufferDepth     (const std::string& timeShiftBufferDepth)
{
    this->timeShiftBufferDepth = timeShiftBufferDepth;
}
const std::string&  SegmentBase::GetIndexRange               ()  const
{
    return this->indexRange;
}
void                SegmentBase::SetIndexRange               (const std::string& indexRange)
{
    this->indexRange = indexRange;
}
bool                SegmentBase::HasIndexRangeExact          ()  const
{
    return this->indexRangeExact;
}
void                SegmentBase::SetIndexRangeExact          (bool indexRangeExact)
{
    this->indexRangeExact = indexRangeExact;
}
double              SegmentBase::GetAvailabilityTimeOffset   () const
{
    return this->availabilityTimeOffset;
}
void                SegmentBase::SetAvailabilityTimeOffset   (double availabilityTimeOffset)
{
    this->availabilityTimeOffset = availabilityTimeOffset;
}
bool                SegmentBase::HasAvailabilityTimeComplete ()  const
{
    return this->availabilityTimeComplete;
}
void                SegmentBase::SetAvailabilityTimeComplete (bool availabilityTimeComplete)
{
    this->availabilityTimeComplete = availabilityTimeComplete;
}
