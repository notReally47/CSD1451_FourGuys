/* mz_strm_libcomp.h -- Stream for apple compression
   part of the minizip-ng project

   Copyright (C) 2010-2021 Nathan Moinvaziri
      https://github.com/zlib-ng/minizip-ng

   This program is distributed under the terms of the same license as zlib.
   See the accompanying LICENSE file for the full text of the license.
*/

#ifndef MZ_STREAM_LIBCOMP_H
#define MZ_STREAM_LIBCOMP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

int32_t mz_stream_libcomp_open(void *stream, const char *filename, int32_t mode);
int32_t mz_stream_libcomp_is_open(void *stream);
int32_t mz_stream_libcomp_read(void *stream, void *buf, int32_t size);
int32_t mz_stream_libcomp_write(void *stream, const void *buf, int32_t size);
int64_t mz_stream_libcomp_tell(void *stream);
int32_t mz_stream_libcomp_seek(void *stream, int64_t offset, int32_t origin);
int32_t mz_stream_libcomp_close(void *stream);
int32_t mz_stream_libcomp_error(void *stream);

int32_t mz_stream_libcomp_get_prop_int64(void *stream, int32_t prop, int64_t *value);
int32_t mz_stream_libcomp_set_prop_int64(void *stream, int32_t prop, int64_t value);

void*   mz_stream_libcomp_create(void **stream);
void    mz_stream_libcomp_delete(void **stream);

void*   mz_stream_libcomp_get_interface(void);

/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
