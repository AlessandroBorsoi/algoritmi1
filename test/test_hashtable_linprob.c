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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/hashtable.h>
#include <upo/error.h>


#define MAX(x,y) ((x) > (y) ? (x) : (y))


static int str_compare(const void* a, const void* b);
static int int_compare(const void* a, const void* b);
/*
static void int_key_value_print(void* key, void* value, void* info);
*/
static void count_key_visit(void* key, void* value, void* info);

static void test_create_destroy();
static void test_put_get_delete();
static void test_insert();
static void test_clear();
static void test_empty();
static void test_size();
static void test_keys();
static void test_traverse();
static void test_resize();
static void test_hash_funcs();
static void test_null();


int str_compare(const void* a, const void* b)
{
    const char* aa = a;
    const char* bb = b;

    return strcmp(aa, bb);
}

int int_compare(const void* a, const void* b)
{
    const int* aa = a;
    const int* bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

/*
void int_key_value_print(void* key, void* value, void* info)
{
    FILE* stream = info;
    int* ikey = key;
    int* ivalue = value;

    if (ikey != NULL && ivalue != NULL && stream != NULL)
    {
        fprintf(stream, "Key: %d -> Value: %d\n", *ikey, *ivalue);
    }
}
*/

void count_key_visit(void* key, void* value, void* info)
{
    size_t* counter = info;

    assert( info != NULL );

    (void) value;

    if (key != NULL)
    {
        *counter += 1;
    }
}

void test_create_destroy()
{
    upo_ht_linprob_t ht;

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_compare);

    assert( ht != NULL );

    upo_ht_linprob_destroy(ht, 0);

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_compare);

    assert( ht != NULL );

    upo_ht_linprob_destroy(ht, 1);
}

void test_put_get_delete()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int values_upd[] = {9,8,7,6,5,4,3,2,1,0};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i;
    upo_ht_linprob_t ht;

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m+UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys1[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys1[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys1[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys1[i]);

        assert( value != NULL );
        assert( *value == values_upd[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys1[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys2[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys2[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys2[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys2[i]);

        assert( value != NULL );
        assert( *value == values_upd[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys2[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value != NULL );
        assert( *value == values_upd[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix with interleaved put/get/delete (useful to test tombstones) */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = n/4; i <= 3*n/4; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }
    /* Search */
    for (i = 0; i <= n/2; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        if (i >= n/4 && i <= 3*n/4)
        {
            assert( value != NULL );
            assert( *value == values[i] );
        }
        else
        {
            assert( value == NULL );
        }
    }
    /* Removal */
    for (i = n/2; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }
    /* Insertion */
    for (i = n/2; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }
    /* Search */
    for (i = n/4; i <= 3*n/4; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        if (i >= n/4 && i < n)
        {
            assert( value != NULL );
            assert( *value == values[i] );
        }
        else
        {
            assert( value == NULL );
        }
    }
    /* Removal */
    for (i = 0; i <= n/2; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }
    /* Search */
    for (i = 0; i <= n/2; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value == NULL );
    }
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }
    /* Removal */
    for (i = 0; i <= n/2; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }
    /* Search */
    for (i = 0; i <= n/2; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value == NULL );
    }
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);
}

void test_insert()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int values_upd[] = {9,8,7,6,5,4,3,2,1,0};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i;
    upo_ht_linprob_t ht;

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m+UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys1[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update (should be ignored) */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys1[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys1[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys2[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update (should be ignored) */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys2[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys2[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys3[i], &values[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Update (should be ignored) */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys3[i], &values_upd[i]);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }
    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }
    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &keys3[i]);

        assert( value == NULL );
    }

    upo_ht_linprob_destroy(ht, 0);
}

void test_clear()
{
    int keys[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = sizeof keys/sizeof keys[0];
    size_t i;
    upo_ht_linprob_t ht;

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    /* HT: mix (without malloc) */

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys[i], &values[i]);
    }

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_clear(ht, 0);

    /* HT: mix (with malloc) */

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        int* key = malloc(sizeof(int));
        int* value = malloc(sizeof(int));
        *key = keys[i];
        *value = values[i];

        upo_ht_linprob_put(ht, key, value);
    }

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_clear(ht, 1);

    assert( upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_destroy(ht, 1);
}

void test_empty()
{
    int key1 = 'a';
    int value1 = 1;
    upo_ht_linprob_t ht;
    int key2 = 'b';
    int value2 = 2;

    /* Test the empty hash table */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_destroy(ht, 0);

    /* Test a hash table with a single entry */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    upo_ht_linprob_put(ht, &key1, &value1);

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_destroy(ht, 0);

    /* Test a hash table with two entries (put+delete) */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    upo_ht_linprob_put(ht, &key1, &value1);
    upo_ht_linprob_put(ht, &key2, &value2);

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_delete(ht, &key1, 0);

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_destroy(ht, 0);

    /* Test a hash table with two entries (put+clear) */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    upo_ht_linprob_put(ht, &key1, &value1);
    upo_ht_linprob_put(ht, &key2, &value2);

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_destroy(ht, 0);

    /* Test a hash table with two entries (put+delete+clear) */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    upo_ht_linprob_put(ht, &key1, &value1);
    upo_ht_linprob_put(ht, &key2, &value2);

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_delete(ht, &key1, 0);

    assert( !upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_destroy(ht, 0);
}

void test_size()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    int values_upd[] = {9,8,7,6,5,4,3,2,1,0};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i;
    upo_ht_linprob_t ht;

    /* HT: empty hash table */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m+UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values[i]);
    }

    assert( upo_ht_linprob_size(ht) == n );

    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys1[i], &values_upd[i]);
    }

    assert( upo_ht_linprob_size(ht) == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values[i]);
    }

    assert( upo_ht_linprob_size(ht) == n );

    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys2[i], &values_upd[i]);
    }

    assert( upo_ht_linprob_size(ht) == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_LINPROB_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }

    assert( upo_ht_linprob_size(ht) == n );

    /* Update */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values_upd[i]);
    }

    assert( upo_ht_linprob_size(ht) == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_destroy(ht, 0);
}

void test_keys()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i = 0;
    upo_ht_linprob_t ht;
    upo_ht_key_list_t key_list;

    /* HT: empty hash table */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values[i]);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list != NULL );
    /* Check that each key is in the list */
    for (i = 0; i < n; ++i)
    {
        upo_ht_key_list_node_t* node = NULL;

        for (node = key_list;
             node != NULL && int_compare(&keys1[i], node->key) != 0;
             node = node->next)
        {
            ; /* empty */
        }
        assert( node != NULL );
    }
    while (key_list != NULL)
    {
        upo_ht_key_list_t tmp = key_list;
        key_list = key_list->next;
        free(tmp);
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values[i]);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list != NULL );
    /* Check that each key is in the list */
    for (i = 0; i < n; ++i)
    {
        upo_ht_key_list_node_t* node = NULL;

        for (node = key_list;
             node != NULL && int_compare(&keys2[i], node->key) != 0;
             node = node->next)
        {
            ; /* empty */
        }
        assert( node != NULL );
    }
    while (key_list != NULL)
    {
        upo_ht_key_list_t tmp = key_list;
        key_list = key_list->next;
        free(tmp);
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list != NULL );
    /* Check that each key is in the list */
    for (i = 0; i < n; ++i)
    {
        upo_ht_key_list_node_t* node = NULL;

        for (node = key_list;
             node != NULL && int_compare(&keys3[i], node->key) != 0;
             node = node->next)
        {
            ; /* empty */
        }
        assert( node != NULL );
    }
    while (key_list != NULL)
    {
        upo_ht_key_list_t tmp = key_list;
        key_list = key_list->next;
        free(tmp);
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }

    /* Keys */
    key_list = upo_ht_linprob_keys(ht);
    assert( key_list == NULL );

    upo_ht_linprob_destroy(ht, 0);
}

void test_traverse()
{
    int keys1[] = {0,1,2,3,4,5,6,7,8,9};
    int keys2[] = {0,10,20,30,40,50,60,70,80,90};
    int keys3[] = {0,1,2,3,4,10,11,12,13,14};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t m = MAX( MAX(sizeof keys1/sizeof keys1[0], sizeof keys1/sizeof keys2[0]), sizeof keys1/sizeof keys3[0] );
    size_t n = 0;
    size_t i;
    upo_ht_linprob_t ht;
    size_t key_counter = 0;

    /* HT: empty hash table */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: no collision */

    ht = upo_ht_linprob_create(2*m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys1/sizeof keys1[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys1[i], &values[i]);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys1[i], 0);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: all collisions */

    ht = upo_ht_linprob_create(m*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys2/sizeof keys2[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_insert(ht, &keys2[i], &values[i]);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys2[i], 0);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);

    /* HT: mix */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof keys3/sizeof keys3[0];
    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys3[i], &values[i]);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == n );

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys3[i], 0);
    }

    key_counter = 0;
    upo_ht_linprob_traverse(ht, count_key_visit, &key_counter);
    assert( key_counter == 0 );

    upo_ht_linprob_destroy(ht, 0);
}

void test_resize()
{
    int keys[] = {0,1,2,3,4,5,6,7,8,9};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = 1;
    size_t i = 0;
    upo_ht_linprob_t ht = NULL;

    ht = upo_ht_linprob_create(m, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &keys[i], &values[i]);

        assert( upo_ht_linprob_size(ht) <= upo_ht_linprob_capacity(ht) );
    }

    /* Removal */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_delete(ht, &keys[i], 0);

        assert( upo_ht_linprob_size(ht) <= upo_ht_linprob_capacity(ht) );
    }

    upo_ht_linprob_destroy(ht, 0);
}

void test_hash_funcs()
{
    int int_keys[] = {0,1,2,3,4,5,6,7,8,9};
    char* str_keys[] = {"alice","bob","charlie","dany","eric","george","john","katy","luke","mark"};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    size_t n = 0;
    size_t i = 0;
    upo_ht_linprob_t ht = NULL;

    /* HT with integer keys and with division method as hash function */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_div, int_compare);

    assert( ht != NULL );

    n = sizeof int_keys/sizeof int_keys[0];

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &int_keys[i], &values[i]);
    }

    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &int_keys[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT with integer keys and with multiplication method as hash function */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_int_mult_knuth, int_compare);

    assert( ht != NULL );

    n = sizeof int_keys/sizeof int_keys[0];

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &int_keys[i], &values[i]);
    }

    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &int_keys[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }

    upo_ht_linprob_destroy(ht, 0);

    /* HT with string keys */

    ht = upo_ht_linprob_create(UPO_HT_SEPCHAIN_DEFAULT_CAPACITY, upo_ht_hash_str_kr2e, str_compare);

    assert( ht != NULL );

    n = sizeof str_keys/sizeof str_keys[0];

    /* Insertion */
    for (i = 0; i < n; ++i)
    {
        upo_ht_linprob_put(ht, &str_keys[i], &values[i]);
    }

    /* Search */
    for (i = 0; i < n; ++i)
    {
        int* value = NULL;

        value = upo_ht_linprob_get(ht, &str_keys[i]);

        assert( value != NULL );
        assert( *value == values[i] );
    }

    upo_ht_linprob_destroy(ht, 0);
}

void test_null()
{
    upo_ht_linprob_t ht = NULL;

    assert( upo_ht_linprob_size(ht) == 0 );

    assert( upo_ht_linprob_is_empty(ht) );

    upo_ht_linprob_clear(ht, 0);

    assert( upo_ht_linprob_size(ht) == 0 );

    upo_ht_linprob_destroy(ht, 0);
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

    printf("Test case 'insert/get/delete'... ");
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

    printf("Test case 'keys... ");
    fflush(stdout);
    test_keys();
    printf("OK\n");

    printf("Test case 'traverse'... ");
    fflush(stdout);
    test_traverse();
    printf("OK\n");

    printf("Test case 'resize'... ");
    fflush(stdout);
    test_resize();
    printf("OK\n");

    printf("Test case 'hash_funcs'... ");
    fflush(stdout);
    test_hash_funcs();
    printf("OK\n");

    printf("Test case 'null'... ");
    fflush(stdout);
    test_null();
    printf("OK\n");


    return 0;
}
