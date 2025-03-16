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

// TODO: Need to enhance for collison avoiding
void ht_insert(ht *ht, const char *key, void *data) {
  unsigned int h = ht_hash(ht, key);
  ht_node *p_new = malloc(sizeof(ht_node));

  p_new->data = data;
  p_new->key = key;

  ht_node *node = ht->nodes[h];

  if (node == NULL) {
    ht->nodes[h] = p_new;
  } else {
    if (node->key == key) {
      node->data = data;
    } else {
      // FIX: need to handle
      printf("Occur collision in the hash table\n");
    }
  }
  return;
}

void *ht_get(ht *ht, const char *key) {
  unsigned int h = ht_hash(ht, key);

  if (ht->nodes[h] == NULL) {
    // FIX: need to handle
    printf("Your key is not assocciated\n");
    return 0;
  } else {
    return ht->nodes[h]->data;
  }
}

void ht_clear(ht *ht) {
  for (unsigned int i = 0; i < ht->size; i++) {
    free(ht->nodes[i]);
  }
  free(ht);
}
