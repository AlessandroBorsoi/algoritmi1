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
    size_t i, j;
    for (i = 1; i < n; ++i)
    {
        j = i;
        while (j > 0 && cmp(upo_get_array_element(base, j - 1, size), upo_get_array_element(base, j, size)) > 0)
        {
            upo_swap(
                upo_get_array_element(base, j - 1, size), 
                upo_get_array_element(base, j, size), 
                size);
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
    upo_quick_sort_rec(base, 0, n - 1, size, cmp);
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
    aux = malloc(size * (hi - lo + 1));
    upo_copy_array(aux, base, lo, hi, size);
    for (k = lo; k <= hi; ++k)
    {
        if (i > (mid - lo))
        {
            upo_copy_array_element(
                upo_get_array_element(base, k, size), 
                upo_get_array_element(aux, j, size), 
                size);
            ++j;
        }
        else if (j > (hi - lo))
        {
            upo_copy_array_element(
                upo_get_array_element(base, k, size), 
                upo_get_array_element(aux, i, size), 
                size);
            ++i;
        }
        else if (cmp(upo_get_array_element(aux, j, size), upo_get_array_element(aux, i, size)) < 0)
        {
            upo_copy_array_element(
                upo_get_array_element(base, k, size), 
                upo_get_array_element(aux, j, size), 
                size);
            ++j;
        }
        else
        {
            upo_copy_array_element(
                upo_get_array_element(base, k, size), 
                upo_get_array_element(aux, i, size), 
                size);
            ++i;
        }
    }
    free(aux);
}

static void upo_copy_array(void* dest, void* src, size_t lo, size_t hi, size_t size)
{
    size_t i, j;
    for (i = 0, j = lo; j <= hi; ++i, ++j)
    {
        upo_copy_array_element(
            upo_get_array_element(dest, i, size), 
            upo_get_array_element(src, j, size), 
            size);
    }
}

static void upo_copy_array_element(void* dest, void* src, size_t size)
{
    char* to = dest;
    char* from = src;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        to[i] = from[i];
    }
}

static void* upo_get_array_element(void* array, size_t index, size_t size)
{
    char* ret = array;
    return ret + (index * size);
}

static void upo_quick_sort_rec(void* base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t pivot;
    if (lo >= hi) return;
    pivot = partition(base, lo, hi, size, cmp);
    if (pivot > 0)
        upo_quick_sort_rec(base, lo, pivot - 1, size, cmp);
    upo_quick_sort_rec(base, pivot + 1, hi, size, cmp);
}

static size_t partition(void* base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t p = lo;
    size_t i = lo;
    size_t j = hi + 1;
    while (1)
    {
        do 
        {
            ++i;
        } while (!(i >= hi) && !(cmp(upo_get_array_element(base, i, size), upo_get_array_element(base, p, size)) >= 0));
        do 
        {
            --j;
        } while (!(j <= lo) && !(cmp(upo_get_array_element(base, j, size), upo_get_array_element(base, p, size)) <= 0));
        if (i >= j) break;
        upo_swap(upo_get_array_element(base, i, size), upo_get_array_element(base, j, size), size);
    }
    upo_swap(upo_get_array_element(base, p, size), upo_get_array_element(base, j, size), size);
    return j;
}

void upo_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    size_t i, j, swap;
    for (i = 0; i < n - 1; ++i)
    {
        swap = 0;
        for (j = 1; j < n - i; ++j)
        {
            if (cmp(upo_get_array_element(base, j - 1, size), upo_get_array_element(base, j, size)) > 0)
            {
                upo_swap(upo_get_array_element(base, j - 1, size), upo_get_array_element(base, j, size), size);
                swap = 1;
            }
        }
        if (swap == 0) break;
    }
}
