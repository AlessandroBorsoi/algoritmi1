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

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t* node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

void* upo_bst_put(upo_bst_t tree, void* key, void* value)
{
    void* valueOld = NULL;
    tree->root = upo_bst_put_impl(tree->root, key, value, valueOld, tree->key_cmp);
    return valueOld;
}

void upo_bst_insert(upo_bst_t tree, void* key, void* value)
{
    tree->root = upo_bst_insert_impl(tree->root, key, value, NULL, tree->key_cmp);
}

void* upo_bst_get(const upo_bst_t tree, const void* key)
{
    upo_bst_node_t* node = upo_bst_get_impl(tree->root, key, tree->key_cmp);
    if (node != NULL)
        return node->value;       
    return NULL;
}

int upo_bst_contains(const upo_bst_t tree, const void* key)
{
    if (upo_bst_get_impl(tree->root, key, tree->key_cmp) != NULL)
        return 1;       
    return 0;
}

void upo_bst_delete(upo_bst_t tree, const void* key, int destroy_data)
{
    tree->root = upo_bst_delete_impl(tree->root, key, destroy_data, tree->key_cmp);
}

size_t upo_bst_size(const upo_bst_t tree)
{
    if (tree == NULL)
        return 0;
    return upo_bst_size_impl(tree->root);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    return upo_bst_height_impl(tree->root);
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void* visit_arg)
{
    upo_bst_traverse_in_order_impl(tree->root, visit, visit_arg);
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    if (tree == NULL || tree->root == NULL)
        return 1;
    return 0;
}

static upo_bst_node_t* upo_bst_put_impl(upo_bst_node_t* root, void* key, void* value, void* valueOld, upo_bst_comparator_t key_cmp)
{
    valueOld = NULL;
    if (root == NULL)
    {
        root = malloc(sizeof(struct upo_bst_node_s));
        if (root == NULL)
        {
            perror("Unable to create a bst node");
            abort();
        }
        root->key = key;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (key_cmp(key, root->key) < 0)
    {
        root->left = upo_bst_put_impl(root->left, key, value, valueOld, key_cmp);
    }
    else if (key_cmp(key, root->key) > 0)
    {
        root->right = upo_bst_put_impl(root->right, key, value, valueOld, key_cmp);
    }
    else
    {
        valueOld = root->value;
        root->value = value;
    }
    return root;
}

static upo_bst_node_t* upo_bst_insert_impl(upo_bst_node_t* root, void* key, void* value, void* valueOld, upo_bst_comparator_t key_cmp)
{
    valueOld = NULL;
    if (root == NULL)
    {
        root = malloc(sizeof(struct upo_bst_node_s));
        if (root == NULL)
        {
            perror("Unable to create a bst node");
            abort();
        }
        root->key = key;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (key_cmp(key, root->key) < 0)
    {
        root->left = upo_bst_insert_impl(root->left, key, value, valueOld, key_cmp);
    }
    else if (key_cmp(key, root->key) > 0)
    {
        root->right = upo_bst_insert_impl(root->right, key, value, valueOld, key_cmp);
    }
    return root;
}

static upo_bst_node_t* upo_bst_get_impl(upo_bst_node_t* root, const void* key, upo_bst_comparator_t key_cmp)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (key_cmp(key, root->key) < 0)
    {
        return upo_bst_get_impl(root->left, key, key_cmp);
    }
    else if (key_cmp(key, root->key) > 0)
    {
        return upo_bst_get_impl(root->right, key, key_cmp);
    }
    else
    {
        return root;
    }
}

static upo_bst_node_t* upo_bst_delete_impl(upo_bst_node_t* root, const void* key, int destroy_data, upo_bst_comparator_t key_cmp)
{
    if (root == NULL)
        return NULL;
    if (key_cmp(key, root->key) < 0) 
    {
        root->left = upo_bst_delete_impl(root->left, key, destroy_data, key_cmp);
    }
    else if (key_cmp(key, root->key) > 0)
    {
        root->right = upo_bst_delete_impl(root->right, key, destroy_data, key_cmp);
    }
    else if (root->left != NULL && root->right != NULL)
    {
        root = upo_bst_delete_2c_impl(root, key, destroy_data, key_cmp);
    }
    else
    {
        root = upo_bst_delete_1c_impl(root, destroy_data);
    }
    return root;
}

static upo_bst_node_t* upo_bst_delete_2c_impl(upo_bst_node_t* root, const void* key, int destroy_data, upo_bst_comparator_t key_cmp)
{
    upo_bst_node_t* m = upo_bst_max_impl(root);
    root->key = m->key;
    root->value = m->value;
    root->left =  upo_bst_delete_impl(root->left, key, destroy_data, key_cmp);
    return root;
}

static upo_bst_node_t* upo_bst_max_impl(upo_bst_node_t* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->right != NULL)
    {
        return upo_bst_max_impl(root->right);
    }
    else
    {
        return root;
    }
}

static upo_bst_node_t* upo_bst_delete_1c_impl(upo_bst_node_t* root, int destroy_data)
{
    upo_bst_node_t* n = root;
    if (root->left != NULL)
    {
        root = root->left;
    } 
    else
    {
        root = root->right;
    }
    if (destroy_data)
        free(n);
    return root;
}

static size_t upo_bst_size_impl(upo_bst_node_t* root)
{
    if (root == NULL)
        return 0;
    return 1 + upo_bst_size_impl(root->left) + upo_bst_size_impl(root->right);
}

static size_t upo_bst_height_impl(upo_bst_node_t* root)
{
    if (root == NULL || upo_bst_is_leaf_impl(root) == 1)
        return 0;
    return 1 + upo_bst_max_size(upo_bst_height_impl(root->left), upo_bst_height_impl(root->right));
}

static int upo_bst_is_leaf_impl(upo_bst_node_t* root)
{
    if (root->left == NULL && root->right == NULL)
        return 1;
    return 0;
}

static size_t upo_bst_max_size(size_t v1, size_t v2)
{
    if (v1 > v2)
        return v1;
    return v2;
}

static void upo_bst_traverse_in_order_impl(upo_bst_node_t* root, upo_bst_visitor_t visit, void* visit_arg)
{
    if (root != NULL)
    {
        upo_bst_traverse_in_order_impl(root->left, visit, visit_arg);
        visit(root->key, root->value, visit_arg);
        upo_bst_traverse_in_order_impl(root->right, visit, visit_arg);
    }
}

/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/


void* upo_bst_min(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_max(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_floor(const upo_bst_t tree, const void* key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

void* upo_bst_ceiling(const upo_bst_t tree, const void* key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void* low_key, const void* high_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}

int upo_bst_is_bst(const upo_bst_t tree, const void* min_key, const void* max_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    fprintf(stderr, "To be implemented!\n");
    abort();
}


/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
