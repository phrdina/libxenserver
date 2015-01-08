/*
 * Copyright (c) Citrix Systems, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * 
 *   2) Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef XEN_EVENT_H
#define XEN_EVENT_H

#include <xen/api/xen_common.h>
#include <xen/api/xen_event_decl.h>
#include <xen/api/xen_event_operation.h>
#include <xen/api/xen_string_set.h>
#include <xen/api/xen_task_decl.h>


/*
 * The event class.
 * 
 * Asynchronous event registration and handling.
 */



typedef struct xen_event_record
{
    int64_t id;
    time_t timestamp;
    char *XEN_CLAZZ;
    enum xen_event_operation operation;
    char *ref;
    char *obj_uuid;
} xen_event_record;

/**
 * Allocate a xen_event_record.
 */
extern xen_event_record *
xen_event_record_alloc(void);

/**
 * Free the given xen_event_record, and all referenced values.  The
 * given record must have been allocated by this library.
 */
extern void
xen_event_record_free(xen_event_record *record);


typedef struct xen_event_record_set
{
    size_t size;
    xen_event_record *contents[];
} xen_event_record_set;

/**
 * Allocate a xen_event_record_set of the given size.
 */
extern xen_event_record_set *
xen_event_record_set_alloc(size_t size);

/**
 * Free the given xen_event_record_set, and all referenced values.  The
 * given set must have been allocated by this library.
 */
extern void
xen_event_record_set_free(xen_event_record_set *set);


/**
 * Registers this session with the event system.  Specifying * as the
 * desired class will register for all classes.
 */
extern bool
xen_event_register(xen_session *session, struct xen_string_set *classes);

/**
 * Registers this session with the event system.  Specifying * as the
 * desired class will register for all classes.
 */
extern bool
xen_event_register_async(xen_session *session, xen_task *result, struct xen_string_set *classes);


/**
 * Unregisters this session with the event system.
 */
extern bool
xen_event_unregister(xen_session *session, struct xen_string_set *classes);

/**
 * Unregisters this session with the event system.
 */
extern bool
xen_event_unregister_async(xen_session *session, xen_task *result, struct xen_string_set *classes);


/**
 * Blocking call which returns a (possibly empty) batch of events.
 */
extern bool
xen_event_next(xen_session *session, struct xen_event_record_set **result);


/**
 * Blocking call which returns a (possibly empty) batch of events.
 */
extern bool
xen_event_from(xen_session *session, struct xen_event_record_set **result, struct xen_string_set *classes, char *token, double timeout);


/**
 * Return the ID of the next event to be generated by the system.
 */
extern bool
xen_event_get_current_id(xen_session *session, int64_t *result);


/**
 * Injects an artificial event on the given object and return the
 * corresponding ID.
 */
extern bool
xen_event_inject(xen_session *session, char **result, char *XEN_CLAZZ, char *ref);


#endif
