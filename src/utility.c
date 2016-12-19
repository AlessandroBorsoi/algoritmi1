/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
/*
#include <string.h>
#include <stdlib.h>
#include <upo/error.h>
*/
#include <upo/utility.h>


void upo_swap(void* a, void* b, size_t size)
{
/*
    char* tmp = malloc(size);
    if (tmp == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory in swap function");
    }

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
*/
    char* aa = a;
    char* bb = b;
    size_t i;

    assert( a );
    assert( b );

    for (i = 0; i < size; ++i)
    {
        char tmp = *aa;
        *aa = *bb;
        *bb = tmp;
        ++aa;
        ++bb;
    }
}
