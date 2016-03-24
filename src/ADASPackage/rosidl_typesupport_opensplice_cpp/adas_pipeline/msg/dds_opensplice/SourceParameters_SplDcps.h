#ifndef SOURCEPARAMETERS_SPLTYPES_H
#define SOURCEPARAMETERS_SPLTYPES_H

#include "ccpp_SourceParameters_.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __SourceParameters__adas_pipeline__load (c_base base);

extern c_metaObject __SourceParameters__adas_pipeline_msg__load (c_base base);

extern c_metaObject __SourceParameters__adas_pipeline_msg_dds___load (c_base base);

extern c_metaObject __adas_pipeline_msg_dds__SourceParameters___load (c_base base);
extern const char * __adas_pipeline_msg_dds__SourceParameters___keys (void);
extern const char * __adas_pipeline_msg_dds__SourceParameters___name (void);
struct _adas_pipeline_msg_dds__SourceParameters_ ;
extern  c_bool __adas_pipeline_msg_dds__SourceParameters___copyIn(c_base base, struct adas_pipeline::msg::dds_::SourceParameters_ *from, struct _adas_pipeline_msg_dds__SourceParameters_ *to);
extern  void __adas_pipeline_msg_dds__SourceParameters___copyOut(void *_from, void *_to);
struct _adas_pipeline_msg_dds__SourceParameters_ {
    c_long inputmode_;
    c_long device_;
    c_string dir_;
    c_float fps_;
    c_bool paused_;
};

#endif
