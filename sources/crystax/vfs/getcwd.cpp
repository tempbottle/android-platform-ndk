/*
 * Copyright (c) 2011-2014 CrystaX .NET.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY CrystaX .NET ''AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL CrystaX .NET OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of CrystaX .NET.
 */

#include "fileio/api.hpp"

namespace crystax
{
namespace fileio
{

extern const char *cpath;
extern size_t cpath_length;
extern pthread_mutex_t cpath_mutex;

CRYSTAX_LOCAL
char *getcwd(char *buf, size_t size)
{
    DBG("***");

    // WARNING!!! 'absolutize' MUST NOT be called from here
    // because 'getcwd' called from 'absolutize'
    scope_lock_t lock(cpath_mutex);

    if (!cpath)
    {
        DBG("cpath were not yet set; use system getcwd");
        return system_getcwd(buf, size);
    }

    if (size < cpath_length + 1)
    {
        ERR("passed size is less than current path length");
        errno = ERANGE;
        return NULL;
    }

    DBG("return cwd=%s", cpath);
    strncpy(buf, cpath, cpath_length);
    buf[cpath_length] = 0;
    return buf;
}

} // namespace fileio
} // namespace crystax

CRYSTAX_GLOBAL
char *getcwd(char *buf, size_t size)
{
    return ::crystax::fileio::getcwd(buf, size);
}
