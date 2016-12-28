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
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/error.h>


typedef struct {
            int* keys;
            int* values;
            size_t count;
        } visit_state_t;


static int int_compare(const void* a, const void* b);

static void test_min_max();
static void test_delete_min_max();
static void test_floor_ceiling();
static void test_bst_property();


int int_compare(const void* a, const void* b)
{
    const int* aa = a;
    const int* bb = b;

    return (*aa > *bb) - (*aa < *bb);
}


void test_min_max()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int max_key = 9;
    size_t n = 0;
    size_t i;
    upo_bst_t bst;
    int* key = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    key = upo_bst_min(bst);
    assert( key == NULL );
    key = upo_bst_max(bst);
    assert( key == NULL );

    /*
     * BST:
     *         4
     *        / \
     *       3   5
     *      /     \
     *     2       6
     *    /         \
     *   1           7
     *  /             \
     * 0               8
     *                  \
     *                   9
     */

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values[i]);
    }
    /* Search */
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key == max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *   0
     *    \
     *     1
     *      \
     *       2
     *        \
     *         3
     *          \
     *           4
     *            \
     *             5
     *              \
     *               6
     *                \
     *                 7
     *                  \
     *                   8
     *                    \
     *                     9
     */

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values[i]);
    }
    /* Search */
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key == max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *                     9
     *                    /
     *                   8
     *                  /
     *                 7
     *                /
     *               6
     *              /
     *             5
     *            /
     *           4
     *          /
     *         3
     *        /
     *       2
     *      /
     *     1
     *    /
     *   0
     */

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values[i]);
    }
    /* Search */
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key == max_key );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_delete_min_max()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int max_key = 9;
    size_t n = 0;
    size_t i;
    upo_bst_t bst;
    int* key = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key == NULL );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key == NULL );

    /*
     * BST:
     *         4
     *        / \
     *       3   5
     *      /     \
     *     2       6
     *    /         \
     *   1           7
     *  /             \
     * 0               8
     *                  \
     *                   9
     */

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values[i]);
    }
    /* Delete & Search */
    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key != min_key );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key != max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *   0
     *    \
     *     1
     *      \
     *       2
     *        \
     *         3
     *          \
     *           4
     *            \
     *             5
     *              \
     *               6
     *                \
     *                 7
     *                  \
     *                   8
     *                    \
     *                     9
     */

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values[i]);
    }
    /* Delete & Search */
    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key != min_key );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key != max_key );

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *                     9
     *                    /
     *                   8
     *                  /
     *                 7
     *                /
     *               6
     *              /
     *             5
     *            /
     *           4
     *          /
     *         3
     *        /
     *       2
     *      /
     *     1
     *    /
     *   0
     */

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values[i]);
    }
    /* Delete & Search */
    upo_bst_delete_min(bst, 0);
    key = upo_bst_min(bst);
    assert( key != NULL );
    assert( *key != min_key );
    upo_bst_delete_max(bst, 0);
    key = upo_bst_max(bst);
    assert( key != NULL );
    assert( *key != max_key );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_floor_ceiling()
{
    int keys[] = {8,6,4,2,0,10,12,14,16,18};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int mid_key = 8;
    int max_key = 18;
    int ref_key = -1;
    size_t n = 0;
    size_t i;
    upo_bst_t bst = NULL;
    int* key = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    ref_key = min_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    ref_key = mid_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    ref_key = max_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    /*
     * BST:
     *         8
     *        / \
     *       6  10
     *      /     \
     *     4      12
     *    /         \
     *   2          14
     *  /             \
     * 0              16
     *                  \
     *                  18
     */

    n = sizeof keys/sizeof keys[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys[i], &values[i]);
    }

    /* Search */

    ref_key = min_key-1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key == NULL );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );

    ref_key = min_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );

    ref_key = min_key+1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == min_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == (min_key+2) );

    ref_key = mid_key-1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key-2 );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );

    ref_key = mid_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );

    ref_key = mid_key+1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == mid_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == (mid_key+2) );

    ref_key = max_key-1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == (max_key-2) );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );

    ref_key = max_key;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );

    ref_key = max_key+1;
    key = upo_bst_floor(bst, &ref_key);
    assert( key != NULL );
    assert( *key == max_key );
    key = upo_bst_ceiling(bst, &ref_key);
    assert( key == NULL );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_keys_range()
{
    int keys[] = {8,6,4,2,0,10,12,14,16,18};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = 0;
    int mid_key = 8;
    int max_key = 18;
    int ref_lo_key = -1;
    int ref_hi_key = -1;
    size_t n = 0;
    size_t i;
    upo_bst_t bst = NULL;
    upo_bst_key_list_t key_list = NULL;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    ref_lo_key = min_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list == NULL );

    ref_lo_key = min_key;
    ref_hi_key = mid_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list == NULL );

    ref_lo_key = mid_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list == NULL );

    key_list = upo_bst_keys(bst);
    assert( key_list == NULL );

    /*
     * BST:
     *         8
     *        / \
     *       6  10
     *      /     \
     *     4      12
     *    /         \
     *   2          14
     *  /             \
     * 0              16
     *                  \
     *                  18
     */

    n = sizeof keys/sizeof keys[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys[i], &values[i]);
    }

    /* Search */

    ref_lo_key = min_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list != NULL );
    i = 0;
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        int* key = key_list->key;

        /* NOTE: keys are returned in reverse order since insertion happens at the front of the list */
        assert( *key == (max_key-(int)i*2) );

        key_list = key_list->next;
        free(old_list);

        ++i;
    }

    ref_lo_key = min_key;
    ref_hi_key = mid_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list != NULL );
    i = 0;
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        int* key = key_list->key;

        /* NOTE: keys are returned in reverse order since insertion happens at the front of the list */
        assert( *key == (mid_key-(int)i*2) );

        key_list = key_list->next;
        free(old_list);

        ++i;
    }

    ref_lo_key = mid_key;
    ref_hi_key = max_key;
    key_list = upo_bst_keys_range(bst, &ref_lo_key, &ref_hi_key);
    assert( key_list != NULL );
    i = 0;
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        int* key = key_list->key;

        /* NOTE: keys are returned in reverse order since insertion happens at the front of the list */
        assert( *key == (max_key-(int)i*2) );

        key_list = key_list->next;
        free(old_list);

        ++i;
    }

    key_list = upo_bst_keys(bst);
    assert( key_list != NULL );
    i = 0;
    while (key_list != NULL)
    {
        upo_bst_key_list_t old_list = key_list;
        int* key = key_list->key;

        /* NOTE: keys are returned in reverse order since insertion happens at the front of the list */
        assert( *key == (max_key-(int)i*2) );

        key_list = key_list->next;
        free(old_list);

        ++i;
    }

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_bst_property()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int min_key = INT_MIN;
    int max_key = INT_MAX;
    int tmp_key;
    size_t n = 0;
    size_t i;
    upo_bst_t bst;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* BST: empty tree */

    assert( upo_bst_is_bst(bst, &min_key, &max_key) );

    /*
     * BST:
     *         4
     *        / \
     *       3   5
     *      /     \
     *     2       6
     *    /         \
     *   1           7
     *  /             \
     * 0               8
     *                  \
     *                   9
     */

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST & Check */
    tmp_key = keys1[0];
    keys1[0] = min_key;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys1[0] = tmp_key;

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *   0
     *    \
     *     1
     *      \
     *       2
     *        \
     *         3
     *          \
     *           4
     *            \
     *             5
     *              \
     *               6
     *                \
     *                 7
     *                  \
     *                   8
     *                    \
     *                     9
     */

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST & Check */
    tmp_key = keys2[0];
    keys2[0] = max_key,
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys2[0] = tmp_key;

    upo_bst_clear(bst, 0);

    /*
     * BST:
     *                     9
     *                    /
     *                   8
     *                  /
     *                 7
     *                /
     *               6
     *              /
     *             5
     *            /
     *           4
     *          /
     *         3
     *        /
     *       2
     *      /
     *     1
     *    /
     *   0
     */

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values[i]);
    }

    /* Check */
    assert( upo_bst_is_bst(bst, &min_key, &max_key) );
    /* Invalidate the BST & Check */
    tmp_key = keys3[0];
    keys3[0] = min_key;
    assert( !upo_bst_is_bst(bst, &min_key, &max_key) );
    keys3[0] = tmp_key;

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}


int main()
{
    printf("Test case 'min/max'... ");
    fflush(stdout);
    test_min_max();
    printf("OK\n");

    printf("Test case 'delete min/max'... ");
    fflush(stdout);
    test_delete_min_max();
    printf("OK\n");

    printf("Test case 'floor/ceiling'... ");
    fflush(stdout);
    test_floor_ceiling();
    printf("OK\n");

    printf("Test case 'keys range'... ");
    fflush(stdout);
    test_keys_range();
    printf("OK\n");

    printf("Test case 'BST property'... ");
    fflush(stdout);
    test_bst_property();
    printf("OK\n");

    return 0;
}
