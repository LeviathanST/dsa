#include "hash_table.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

ht *ht_create(unsigned int size) {
  ht *p_ht = malloc(sizeof(ht));
  if (p_ht == NULL) {
    printf("Cannot allocate hash table: %s", strerror(errno));
    return NULL;
  }
  p_ht->nodes = calloc(size, sizeof(ht_node *));
  p_ht->size = size;
  return p_ht;
}

unsigned int ht_hash(ht *ht, const char *key) {
  unsigned int h = 0;
  while (*key) {
    h += (unsigned int)*key++ * 31 / 10;
  }
  return h % ht->size;
}

ht_node *ht_create_node(const char *key, void *data) {
  ht_node *p_node = malloc(sizeof(ht_node));
  if (p_node == NULL) {
    printf("Cannot allocate for new node: %s", strerror(errno));
    free(p_node);
    return 0;
  }
  p_node->data = data;
  p_node->key = key;
  p_node->next = 0;
  return p_node;
}

int ht_insert(ht *ht, const char *key, void *data) {
  unsigned int h = ht_hash(ht, key);
  ht_node *p_node = ht->nodes[h];

  if (!p_node) {
    p_node = ht_create_node(key, data);
    ht->nodes[h] = p_node;
  } else {
    if (p_node->key == key) {
      if (data != NULL) {
        p_node->data = data;
      } else {
        ht->nodes[h] = NULL;
      }
    } else {
      ht_node *p_new_node = ht_create_node(key, data);
      // NOTE: Collision handling (Coalesced hashing)
      int cursor = (int)ht->size - 1;
      while (cursor >= 0 && !ht->nodes[cursor]) {
        cursor--;
      }

      if (cursor == -1) {
        printf("Hash table is full!");
        return -1;
      }
      ht->nodes[cursor] = p_new_node;

      while (p_node->next != NULL)
        p_node = p_node->next;

      p_node->next = ht->nodes[cursor];
    }
  }
  return 0;
}

void *ht_get(ht *ht, const char *key) {
  unsigned int h = ht_hash(ht, key);
  ht_node *p_current_node = ht->nodes[h];

  if (p_current_node == NULL) {
    return 0;
  } else {
    if (strcmp(p_current_node->key, key) >= 0) {
      return p_current_node->data;
    }
    while (p_current_node->next != NULL && p_current_node->key != key)
      p_current_node = p_current_node->next;
    return p_current_node; // NULL or void *data
  }
}

void ht_clear(ht *ht) {
  for (unsigned int i = 0; i < ht->size; i++) {
    free(ht->nodes[i]);
  }
  free(ht);
}
