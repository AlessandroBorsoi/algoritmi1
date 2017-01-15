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
static int int_array_check_equal(int a[], size_t na, int b[], size_t nb);
void visitor(void* key, void* value, void* state);

static void test_create_destroy();
static void test_put_get_delete();
static void test_insert();
static void test_clear();
static void test_empty();
static void test_size();
static void test_height();
static void test_traversal();
static void test_null();
static void test_rank();

int int_compare(const void* a, const void* b)
{
    const int* aa = a;
    const int* bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

int int_array_check_equal(int a[], size_t na, int b[], size_t nb)
{
    size_t i;

    if (na != nb)
    {
        return 0;
    }

    for (i = 0; i < na; ++i)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }

    return 1;
}

void visitor(void* key, void* value, void* state)
{
    visit_state_t* visit_state = state;

    if (visit_state != NULL)
    {
        visit_state->keys[visit_state->count] = *((int*) key);
        visit_state->values[visit_state->count] = *((int*) value);
        visit_state->count += 1;
    }

/*
    fprintf(stderr, "%d\n", *((int*) data));
 */
}


void test_create_destroy()
{
    upo_bst_t bst;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    upo_bst_destroy(bst, 0);
}

void test_put_get_delete()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int values_upd[] = {9,8,7,6,5,4,3,2,1,0};
    size_t n = 0;
    size_t i;
    upo_bst_t bst;

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

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys1[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys1[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys1[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys1[i]);

        assert( value != NULL );
        assert( *value == values_upd[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_bst_delete(bst, &keys1[i], 0);
    }

    upo_bst_destroy(bst, 0);

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

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys2[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys2[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys2[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys2[i]);

        assert( value != NULL );
        assert( *value == values_upd[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_bst_delete(bst, &keys2[i], 0);
    }

    upo_bst_destroy(bst, 0);

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

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys3[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys3[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys3[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys3[i]);

        assert( value != NULL );
        assert( *value == values_upd[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_bst_delete(bst, &keys3[i], 0);
    }

    upo_bst_destroy(bst, 0);
}

void test_insert()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int values_dup[] = {10,11,12,13,14,15,16,17,18,19};
    size_t n = 0;
    size_t i;
    upo_bst_t bst;

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

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
    /* Insertion of duplicates */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys1[i], &values_dup[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys1[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }

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
    /* Insertion of duplicates */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys2[i], &values_dup[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys2[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }

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
    /* Insertion of duplicates */
    for (i = 0; i < n; ++i)
    {
        upo_bst_insert(bst, &keys3[i], &values_dup[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_bst_get(bst, &keys3[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_clear()
{
    int keys[] = {4,3,2,1,0,5,6,7,8,9};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = sizeof keys/sizeof keys[0];
    size_t i;
    upo_bst_t bst;

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

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys[i], &values[i]);
    }

    assert( !upo_bst_is_empty(bst) );

    upo_bst_clear(bst, 0);

    assert( upo_bst_is_empty(bst) );

    upo_bst_destroy(bst, 0);

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

    bst = upo_bst_create(int_compare);

    assert( bst != NULL );

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        int* key = malloc(sizeof(int));
        int* value = malloc(sizeof(int));
        *key = keys[i];
        *value = values[i];

        upo_bst_put(bst, key, value);
    }

    assert( !upo_bst_is_empty(bst) );

    upo_bst_clear(bst, 1);

    assert( upo_bst_is_empty(bst) );

    upo_bst_destroy(bst, 0);
}

void test_empty()
{
    int key = 'a';
    int value = 1;
    upo_bst_t bst;
    int child_key = 'b';
    int child_value = 2;

    /* Test the empty tree */

    bst = upo_bst_create(int_compare);

    assert( upo_bst_is_empty(bst) );

    upo_bst_destroy(bst, 0);

    /* Test a tree with a single node */

    bst = upo_bst_create(int_compare);

    upo_bst_put(bst, &key, &value);

    assert( !upo_bst_is_empty(bst) );

    upo_bst_destroy(bst, 0);

    /* Test a tree with two nodes */

    bst = upo_bst_create(int_compare);

    upo_bst_put(bst, &key, &value);
    upo_bst_put(bst, &child_key, &child_value);

    assert( !upo_bst_is_empty(bst) );

    upo_bst_delete(bst, &child_key, 0);

    assert( !upo_bst_is_empty(bst) );

    upo_bst_destroy(bst, 0);
}

void test_size()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = 0;
    size_t i;
    upo_bst_t bst;

    bst = upo_bst_create(int_compare);

    assert( upo_bst_size(bst) == 0 );

    /*
     * BST: empty tree
     */

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys1[i], &values[i]);
    }

    assert( upo_bst_size(bst) == 10 );

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys2[i], &values[i]);
    }

    assert( upo_bst_size(bst) == 10 );

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys3[i], &values[i]);
    }

    assert( upo_bst_size(bst) == 10 );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_height()
{
    int keys1[] = {4,3,2,1,0,5,6,7,8,9};
    int keys2[] = {0,1,2,3,4,5,6,7,8,9};
    int keys3[] = {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = 0;
    size_t i;
    upo_bst_t bst;

    bst = upo_bst_create(int_compare);

    assert( upo_bst_height(bst) == 0 );

    /*
     * BST: empty tree
     */

    upo_bst_clear(bst, 0);

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys1[i], &values[i]);
    }

    assert( upo_bst_height(bst) == 5 );

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys2[i], &values[i]);
    }

    assert( upo_bst_height(bst) == 9 );

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys3[i], &values[i]);
    }

    assert( upo_bst_height(bst) == 9 );

    upo_bst_clear(bst, 0);

    upo_bst_destroy(bst, 0);
}

void test_traversal()
{
    upo_bst_t tree;
    int keys1[] =  {4,3,2,1,0,5,6,7,8,9};
    int keys2[] =  {0,1,2,3,4,5,6,7,8,9};
    int keys3[] =  {9,8,7,6,5,4,3,2,1,0};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = 0;
    size_t i = 0;
    visit_state_t visit_state = {NULL, NULL, 0};
    int in_order_keys[] = {0,1,2,3,4,5,6,7,8,9};
    int in_order_values1[] = {4,3,2,1,0,5,6,7,8,9};
    int in_order_values2[] = {0,1,2,3,4,5,6,7,8,9};
    int in_order_values3[] = {9,8,7,6,5,4,3,2,1,0};

    tree = upo_bst_create(int_compare);

    assert( tree != NULL );

    /*
     * BST: empty tree
     */

    /* In order traversal */

    visit_state.keys = NULL;
    visit_state.values = NULL;
    visit_state.count = 0;
    upo_bst_traverse_in_order(tree, visitor, &visit_state);
    assert( visit_state.count == 0);
    assert( visit_state.keys == NULL );
    assert( visit_state.values == NULL );

    upo_bst_clear(tree, 0);

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(tree, &keys1[i], &values[i]);
    }

    visit_state.keys = malloc(n*sizeof(int));
    if (visit_state.keys == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for visit state keys");
    }
    visit_state.values = malloc(n*sizeof(int));
    if (visit_state.values == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for visit state values");
    }

    /* In order traversal */

    memset(visit_state.keys, 0, n*sizeof(int));
    memset(visit_state.values, 0, n*sizeof(int));
    visit_state.count = 0;
    upo_bst_traverse_in_order(tree, visitor, &visit_state);
    assert( visit_state.count == n);
    assert( int_array_check_equal(visit_state.keys, n, in_order_keys, n) );
    assert( int_array_check_equal(visit_state.values, n, in_order_values1, n) );

    free(visit_state.values);
    free(visit_state.keys);

    upo_bst_clear(tree, 0);

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(tree, &keys2[i], &values[i]);
    }

    visit_state.keys = malloc(n*sizeof(int));
    if (visit_state.keys == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for visit state keys");
    }
    visit_state.values = malloc(n*sizeof(int));
    if (visit_state.values == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for visit state values");
    }

    /* In order traversal */

    memset(visit_state.keys, 0, n*sizeof(int));
    memset(visit_state.values, 0, n*sizeof(int));
    visit_state.count = 0;
    upo_bst_traverse_in_order(tree, visitor, &visit_state);
    assert( visit_state.count == n);
    assert( int_array_check_equal(visit_state.keys, n, in_order_keys, n) );
    assert( int_array_check_equal(visit_state.values, n, in_order_values2, n) );

    free(visit_state.values);
    free(visit_state.keys);

    upo_bst_clear(tree, 0);

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
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(tree, &keys3[i], &values[i]);
    }

    visit_state.keys = malloc(n*sizeof(int));
    if (visit_state.keys == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for visit state keys");
    }
    visit_state.values = malloc(n*sizeof(int));
    if (visit_state.values == NULL)
    {
        upo_throw_sys_error("Unable to allocate memory for visit state values");
    }

    /* In order traversal */

    memset(visit_state.keys, 0, n*sizeof(int));
    memset(visit_state.values, 0, n*sizeof(int));
    visit_state.count = 0;
    upo_bst_traverse_in_order(tree, visitor, &visit_state);
    assert( visit_state.count == n);
    assert( int_array_check_equal(visit_state.keys, n, in_order_keys, n) );
    assert( int_array_check_equal(visit_state.values, n, in_order_values3, n) );

    free(visit_state.values);
    free(visit_state.keys);

    upo_bst_clear(tree, 0);

    upo_bst_destroy(tree, 0);
}

void test_null()
{
    upo_bst_t bst = NULL;

    assert( upo_bst_size(bst) == 0 );

    assert( upo_bst_is_empty(bst) );

    upo_bst_clear(bst, 0);

    assert( upo_bst_size(bst) == 0 );

    assert( upo_bst_rank(bst, NULL, int_compare) == 0 );

    upo_bst_destroy(bst, 1);
}

void test_rank()
{
    int keys[] = {8,3,1,6,4,7,10,14,13};
    size_t n = 0;
    size_t i;
    upo_bst_t bst;
    int zero = 0;
    int five = 5;
    int twelve = 12;
    int hundred = 100;

    bst = upo_bst_create(int_compare);

    n = sizeof keys/sizeof keys[0];
    for (i = 0; i < n; ++i)
    {
        upo_bst_put(bst, &keys[i], &keys[i]);
    }

    assert( upo_bst_rank(bst, &keys[0], int_compare) == 5 );
    assert( upo_bst_rank(bst, &keys[2], int_compare) == 0 );
    assert( upo_bst_rank(bst, &keys[8], int_compare) == 7 );
    assert( upo_bst_rank(bst, &keys[7], int_compare) == 8 );
    assert( upo_bst_rank(bst, &zero, int_compare) == 0 );
    assert( upo_bst_rank(bst, &five, int_compare) == 3 );
    assert( upo_bst_rank(bst, &twelve, int_compare) == 7 );
    assert( upo_bst_rank(bst, &hundred, int_compare) == 9 );

    upo_bst_destroy(bst, 0);
}

int main()
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    printf("Test case 'put/get/delete'... ");
    fflush(stdout);
    test_put_get_delete();
    printf("OK\n");

    printf("Test case 'insert'... ");
    fflush(stdout);
    test_insert();
    printf("OK\n");

    printf("Test case 'clear'... ");
    fflush(stdout);
    test_clear();
    printf("OK\n");

    printf("Test case 'empty'... ");
    fflush(stdout);
    test_empty();
    printf("OK\n");

    printf("Test case 'size'... ");
    fflush(stdout);
    test_size();
    printf("OK\n");

    printf("Test case 'height'... ");
    fflush(stdout);
    test_height();
    printf("OK\n");

    printf("Test case 'traversal'... ");
    fflush(stdout);
    test_traversal();
    printf("OK\n");

    printf("Test case 'null'... ");
    fflush(stdout);
    test_null();
    printf("OK\n");

    printf("Test case 'rank'... ");
    fflush(stdout);
    test_rank();
    printf("OK\n");

    return 0;
}
