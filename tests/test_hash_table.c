#include "../src/hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_hash() {
  ht *p_ht = ht_create(4);

  assert(ht_hash(p_ht, "Bob") == 3);
  assert(ht_hash(p_ht, "Boy") == 3);
  assert(ht_hash(p_ht, "Bon") == 1);

  ht_clear(p_ht);
  printf("Test test_hash() success...\n");
}

void test_add() {
  ht *p_ht1 = ht_create(4);

  ht_insert(p_ht1, "Bob", "Name: Bob");
  assert(strcmp((char *)ht_get(p_ht1, "Bob"), "Name: Bob") == 0);

  ht_insert(p_ht1, "Boy", "Name: Boy");
  assert(strcmp((char *)ht_get(p_ht1, "Boy"), "Name: Boy") == 0);

  ht_insert(p_ht1, "Bon", "Name: Bon");
  assert(strcmp((char *)ht_get(p_ht1, "Bon"), "Name: Bon") == 0);

  ht_insert(p_ht1, "Bob", 0);
  assert(ht_get(p_ht1, "Bob") == 0);

  ht_clear(p_ht1);
  printf("Test test_add() success...\n");
}

int main() {
  test_hash();
  test_add();
  return 0;
}
