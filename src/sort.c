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
            upo_swap(array + ((j - 1) * size), array + (j * size), size);
            --j;
        }
    }
}

void upo_merge_sort(void* base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    upo_merge_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort(void* base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

static void upo_swap(void* v1, void* v2, size_t size)
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

static void upo_merge_sort_rec(void* base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t mid;
    if (lo >= hi) return;
    mid = (lo + hi) / 2;
    upo_merge_sort_rec(base, lo, mid, size, cmp);
    upo_merge_sort_rec(base, mid + 1, hi, size, cmp);
    upo_merge_sort_merge(base, lo, mid, hi, size, cmp);
}

static void upo_merge_sort_merge(void* base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t i, j, k;
    void* aux;
    i = 0;
    j = mid + 1 - lo;
    aux = malloc(size * (hi - lo));
    upo_copy_array(aux, base, lo, hi, size);
    for (k = lo; k <= hi; ++k)
    {
        if (i > mid - lo || cmp(upo_get_array_element(aux, j, size), upo_get_array_element(aux, i, size)))
        {
            upo_copy_array_element(base, aux, size);
            ++j;
        }
        else
        {
            upo_copy_array_element(base, aux, size);
            ++i;
        }
    }
    free(aux);
}

static void upo_copy_array(void* dest, void* src, size_t lo, size_t hi, size_t size)
{
    size_t i;
    size_t n = hi - lo;
    for (i = 0; i < n; ++i)
    {
        upo_copy_array_element(
            upo_get_array_element(dest, i, size), 
            upo_get_array_element(src, i, size), 
            size);
    }
}

static void upo_copy_array_element(void* dest, void* src, size_t size)
{
    char* pc1 = dest;
    char* pc2 = src;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        pc1[i] = pc2[i];
    }
}

static void* upo_get_array_element(void* array, size_t index, size_t size)
{
    char* ret = array;
    return ret + (index * size);
}