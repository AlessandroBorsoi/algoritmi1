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
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void upo_insertion_sort(void* base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    char* array = base;
    size_t i, j;
    for (i = 1; i < n - 1; ++i)
    {
        j = i;

        while (j > 0 && cmp(array + ((j - 1) * size), array + (j * size)))
        {
            swap(array + ((j - 1) * size), array + (j * size), size);
            --j;
        }
    }
}

void upo_merge_sort(void* base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_quick_sort(void* base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void swap(void* v1, void* v2, size_t size)
{
    char* pc1 = v1;
    char* pc2 = v2;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        char tmp = pc1[i];
        pc1[i] = pc2[i];
        pc2[i] = tmp;
    }
}
