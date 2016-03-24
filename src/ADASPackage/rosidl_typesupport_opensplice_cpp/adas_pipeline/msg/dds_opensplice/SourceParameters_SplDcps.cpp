#include "SourceParameters_SplDcps.h"
#include "ccpp_SourceParameters_.h"
#include "dds_type_aliases.h"

const char *
__adas_pipeline_msg_dds__SourceParameters___name(void)
{
    return (const char*)"adas_pipeline::msg::dds_::SourceParameters_";
}

const char *
__adas_pipeline_msg_dds__SourceParameters___keys(void)
{
    return (const char*)"";
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

c_bool
__adas_pipeline_msg_dds__SourceParameters___copyIn(
    c_base base,
    struct ::adas_pipeline::msg::dds_::SourceParameters_ *from,
    struct _adas_pipeline_msg_dds__SourceParameters_ *to)
{
    c_bool result = OS_C_TRUE;
    (void) base;

    to->inputmode_ = (c_long)from->inputmode_;
    to->device_ = (c_long)from->device_;
#ifdef OSPL_BOUNDS_CHECK
    if(from->dir_){
        to->dir_ = c_stringNew(base, from->dir_);
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'adas_pipeline::msg::dds_::SourceParameters_.dir_' of type 'c_string' is NULL.");
        result = OS_C_FALSE;
    }
#else
    to->dir_ = c_stringNew(base, from->dir_);
#endif
    to->fps_ = (c_float)from->fps_;
    to->paused_ = (c_bool)from->paused_;
    return result;
}

void
__adas_pipeline_msg_dds__SourceParameters___copyOut(
    void *_from,
    void *_to)
{
    struct _adas_pipeline_msg_dds__SourceParameters_ *from = (struct _adas_pipeline_msg_dds__SourceParameters_ *)_from;
    struct ::adas_pipeline::msg::dds_::SourceParameters_ *to = (struct ::adas_pipeline::msg::dds_::SourceParameters_ *)_to;
    to->inputmode_ = (::DDS::Long)from->inputmode_;
    to->device_ = (::DDS::Long)from->device_;
    to->dir_ = DDS::string_dup(from->dir_ ? from->dir_ : "");
    to->fps_ = (::DDS::Float)from->fps_;
    to->paused_ = (::DDS::Boolean)(from->paused_ != 0);
}

