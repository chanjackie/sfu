#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "point_array.h"

int main() {
  point_array_t test;
  point_array_init(&test);
  for (int i=0;i<100;i++) {
    point_t point;
    point.x=rand()%100;
    point.y=rand()%100;
    point.z=rand()%100;
    point_array_append(&test, &point);
  }
  puts("First print after 100 appends");
  for (int i=0;i<100;i++) {
    printf("%lf %lf %lf\n", test.points[i].x, test.points[i].y, test.points[i].z);
  }
  point_t four;
  four.x=1;
  four.y=2;
  four.z=3;
  point_array_append(&test, &four);
  for (int i=0;i<101;i++) {
    point_array_remove(&test, 0);
  }
  puts("After remove:");
  for (int i=0;i<test.len;i++) {
    printf("%lf %lf %lf\n", test.points[i].x, test.points[i].y, test.points[i].z);
  }
  point_array_reset(&test);
  return 0;
}
