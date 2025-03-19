#include "../src/hash_table.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void run_benchmark(int table_size, int num_inserts) {
  struct rusage usage_start, usage_end;
  ht *p_ht1 = ht_create(table_size);
  size_t memory_used = sizeof(ht) + table_size * sizeof(ht_node *);

  // Key-value pairs (expand to 50)
  struct {
    const char *key;
    void *value;
  } pairs[] = {{"Aaron", "Name: Aaron"},
               {"Abigail", "Name: Abigail"},
               {"Adam", "Name: Adam"},
               {"Addison", "Name: Addison"},
               {"Aiden", "Name: Aiden"},
               {"Alexa", "Name: Alexa"},
               {"Alexander", "Name: Alexander"},
               {"Alexis", "Name: Alexis"},
               {"Amelia", "Name: Amelia"},
               {"Andrew", "Name: Andrew"},
               {"Anna", "Name: Anna"},
               {"Anthony", "Name: Anthony"},
               {"Aria", "Name: Aria"},
               {"Ariana", "Name: Ariana"},
               {"Asher", "Name: Asher"},
               {"Ashley", "Name: Ashley"},
               {"Aubrey", "Name: Aubrey"},
               {"Audrey", "Name: Audrey"},
               {"Austin", "Name: Austin"},
               {"Ava", "Name: Ava"},
               {"Avery", "Name: Avery"},
               {"Bailey", "Name: Bailey"},
               {"Benjamin", "Name: Benjamin"},
               {"Blake", "Name: Blake"},
               {"Brandon", "Name: Brandon"},
               {"Brayden", "Name: Brayden"},
               {"Brian", "Name: Brian"},
               {"Brody", "Name: Brody"},
               {"Brooke", "Name: Brooke"},
               {"Brooklyn", "Name: Brooklyn"},
               {"Caleb", "Name: Caleb"},
               {"Cameron", "Name: Cameron"},
               {"Camila", "Name: Camila"},
               {"Carson", "Name: Carson"},
               {"Carter", "Name: Carter"},
               {"Catherine", "Name: Catherine"},
               {"Charlotte", "Name: Charlotte"},
               {"Chase", "Name: Chase"},
               {"Chloe", "Name: Chloe"},
               {"Christian", "Name: Christian"},
               {"Christopher", "Name: Christopher"},
               {"Claire", "Name: Claire"},
               {"Cole", "Name: Cole"},
               {"Colin", "Name: Colin"},
               {"Connor", "Name: Connor"},
               {"Cooper", "Name: Cooper"},
               {"Daniel", "Name: Daniel"},
               {"David", "Name: David"},
               {"Declan", "Name: Declan"},
               {"Delilah", "Name: Delilah"},
               {"Derek", "Name: Derek"},
               {"Dominic", "Name: Dominic"},
               {"Dylan", "Name: Dylan"},
               {"Easton", "Name: Easton"},
               {"Eleanor", "Name: Eleanor"},
               {"Eli", "Name: Eli"},
               {"Elias", "Name: Elias"},
               {"Elijah", "Name: Elijah"},
               {"Elizabeth", "Name: Elizabeth"},
               {"Ella", "Name: Ella"},
               {"Ellie", "Name: Ellie"},
               {"Emery", "Name: Emery"},
               {"Emily", "Name: Emily"},
               {"Emma", "Name: Emma"},
               {"Ethan", "Name: Ethan"},
               {"Evan", "Name: Evan"},
               {"Evelyn", "Name: Evelyn"},
               {"Faith", "Name: Faith"},
               {"Finn", "Name: Finn"},
               {"Gabriel", "Name: Gabriel"},
               {"Gabriella", "Name: Gabriella"},
               {"Gavin", "Name: Gavin"},
               {"Genesis", "Name: Genesis"},
               {"George", "Name: George"},
               {"Gianna", "Name: Gianna"},
               {"Grace", "Name: Grace"},
               {"Grayson", "Name: Grayson"},
               {"Hadley", "Name: Hadley"},
               {"Hailey", "Name: Hailey"},
               {"Hannah", "Name: Hannah"},
               {"Harper", "Name: Harper"},
               {"Harrison", "Name: Harrison"},
               {"Hayden", "Name: Hayden"},
               {"Hazel", "Name: Hazel"},
               {"Henry", "Name: Henry"},
               {"Hudson", "Name: Hudson"},
               {"Hunter", "Name: Hunter"},
               {"Ian", "Name: Ian"},
               {"Isaac", "Name: Isaac"},
               {"Isabella", "Name: Isabella"},
               {"Isaiah", "Name: Isaiah"},
               {"Isla", "Name: Isla"},
               {"Ivy", "Name: Ivy"},
               {"Jackson", "Name: Jackson"},
               {"Jacob", "Name: Jacob"},
               {"Jade", "Name: Jade"},
               {"James", "Name: James"},
               {"Jason", "Name: Jason"},
               {"Jasper", "Name: Jasper"},
               {"Jayden", "Name: Jayden"},
               {"Jennifer", "Name: Jennifer"},
               {"Jeremiah", "Name: Jeremiah"},
               {"Jessica", "Name: Jessica"},
               {"John", "Name: John"},
               {"Jonathan", "Name: Jonathan"},
               {"Jordan", "Name: Jordan"},
               {"Joseph", "Name: Joseph"},
               {"Joshua", "Name: Joshua"},
               {"Josiah", "Name: Josiah"},
               {"Julia", "Name: Julia"},
               {"Julian", "Name: Julian"},
               {"Juliana", "Name: Juliana"},
               {"Justin", "Name: Justin"},
               {"Kaitlyn", "Name: Kaitlyn"},
               {"Kaleb", "Name: Kaleb"},
               {"Katherine", "Name: Katherine"},
               {"Kayden", "Name: Kayden"},
               {"Kayla", "Name: Kayla"},
               {"Kaylee", "Name: Kaylee"},
               {"Kennedy", "Name: Kennedy"},
               {"Kevin", "Name: Kevin"},
               {"Khloe", "Name: Khloe"},
               {"Kylie", "Name: Kylie"},
               {"Landon", "Name: Landon"},
               {"Lauren", "Name: Lauren"},
               {"Layla", "Name: Layla"},
               {"Leah", "Name: Leah"},
               {"Leo", "Name: Leo"},
               {"Levi", "Name: Levi"},
               {"Liam", "Name: Liam"},
               {"Lila", "Name: Lila"},
               {"Lillian", "Name: Lillian"},
               {"Lily", "Name: Lily"},
               {"Lincoln", "Name: Lincoln"},
               {"Logan", "Name: Logan"},
               {"Lucas", "Name: Lucas"},
               {"Lucy", "Name: Lucy"},
               {"Luke", "Name: Luke"},
               {"Lydia", "Name: Lydia"},
               {"Mackenzie", "Name: Mackenzie"},
               {"Madeline", "Name: Madeline"},
               {"Madison", "Name: Madison"},
               {"Makayla", "Name: Makayla"},
               {"Maria", "Name: Maria"},
               {"Mason", "Name: Mason"},
               {"Matthew", "Name: Matthew"},
               {"Maya", "Name: Maya"},
               {"Mia", "Name: Mia"},
               {"Michael", "Name: Michael"},
               {"Mila", "Name: Mila"},
               {"Miles", "Name: Miles"},
               {"Morgan", "Name: Morgan"},
               {"Natalie", "Name: Natalie"},
               {"Nathan", "Name: Nathan"},
               {"Nathaniel", "Name: Nathaniel"},
               {"Nevaeh", "Name: Nevaeh"},
               {"Nicholas", "Name: Nicholas"},
               {"Noah", "Name: Noah"},
               {"Nolan", "Name: Nolan"},
               {"Nora", "Name: Nora"},
               {"Oliver", "Name: Oliver"},
               {"Olivia", "Name: Olivia"},
               {"Owen", "Name: Owen"},
               {"Paige", "Name: Paige"},
               {"Parker", "Name: Parker"},
               {"Peyton", "Name: Peyton"},
               {"Piper", "Name: Piper"},
               {"Quinn", "Name: Quinn"},
               {"Rachel", "Name: Rachel"},
               {"Reagan", "Name: Reagan"},
               {"Rebecca", "Name: Rebecca"},
               {"Riley", "Name: Riley"},
               {"Robert", "Name: Robert"},
               {"Ruby", "Name: Ruby"},
               {"Ryan", "Name: Ryan"},
               {"Ryder", "Name: Ryder"},
               {"Sadie", "Name: Sadie"},
               {"Samantha", "Name: Samantha"},
               {"Samuel", "Name: Samuel"},
               {"Sarah", "Name: Sarah"},
               {"Savannah", "Name: Savannah"},
               {"Scarlett", "Name: Scarlett"},
               {"Sebastian", "Name: Sebastian"},
               {"Serenity", "Name: Serenity"},
               {"Skylar", "Name: Skylar"},
               {"Sofia", "Name: Sofia"},
               {"Sophia", "Name: Sophia"},
               {"Stella", "Name: Stella"},
               {"Steven", "Name: Steven"},
               {"Sydney", "Name: Sydney"},
               {"Taylor", "Name: Taylor"},
               {"Thomas", "Name: Thomas"},
               {"Tristan", "Name: Tristan"},
               {"Tyler", "Name: Tyler"},
               {"Victoria", "Name: Victoria"},
               {"Violet", "Name: Violet"},
               {"William", "Name: William"},
               {"Wyatt", "Name: Wyatt"},
               {"Xavier", "Name: Xavier"},
               {"Zachary", "Name: Zachary"},
               {"Zoe", "Name: Zoe"},
               {"Zoey", "Name: Zoey"}};
  int pair_count = sizeof(pairs) / sizeof(pairs[0]);
  if (num_inserts > pair_count)
    num_inserts = pair_count;

  // Start measurement
  getrusage(RUSAGE_SELF, &usage_start);
  for (int i = 0; i < num_inserts; i++) {
    ht_insert(p_ht1, pairs[i].key, pairs[i].value);
    memory_used += sizeof(ht_node);
  }

  ht_clear(p_ht1);
  getrusage(RUSAGE_SELF, &usage_end);

  // Calculate time
  double user_time =
      (usage_end.ru_utime.tv_sec - usage_start.ru_utime.tv_sec) +
      (usage_end.ru_utime.tv_usec - usage_start.ru_utime.tv_usec) / 1e6;
  double sys_time =
      (usage_end.ru_stime.tv_sec - usage_start.ru_stime.tv_sec) +
      (usage_end.ru_stime.tv_usec - usage_start.ru_stime.tv_usec) / 1e6;

  // Memory (max resident set size in KB)
  long memory_peak = usage_end.ru_maxrss;

  // Results
  printf("Benchmark Results:\n");
  printf("User CPU Time: %.6f seconds\n", user_time);
  printf("System CPU Time: %.6f seconds\n", sys_time);
  printf("Memory Peak: %ld KB\n", memory_peak);
  printf("Memory Estimated: %zu bytes\n", memory_used);
}

int main() {
  run_benchmark(200, 50);
  return 0;
}
