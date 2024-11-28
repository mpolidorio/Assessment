#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Struct with all data requested */
typedef struct {
  float avg;
  size_t max;
  size_t min;
  size_t array_size;
  size_t *array_pointer;
} data_t;

/*
 * This function searches for the maximum and minimum values in an array
 * and updates the respective fields in the data_t struct.
 */
void compute_max_and_min(data_t *results, size_t *array, ssize_t size) {
  size_t i;
  results->max = array[0];
  results->min = array[0];

  for (i = 0; i < size; i++) {
    if (array[i] <= results->min)
      results->min = array[i];
    else if (array[i] > results->max)
      results->max = array[i];
  }
}

/*
 * This function computes the average of the array elements and updates
 * the avg field in the data_t struct. It also handles division by zero.
 */
size_t compute_average(data_t *results, size_t *array, size_t size) {
  size_t i;
  float average = 0;

  if (size <= 0) {
    printf("Error, 0 division!\n");
    return 1;
  }

  for (i = 0; i < size; i++)
    average += array[i];

  results->avg = average / (float)size;
  return 0;
}

/*
 * This function identifies all even numbers in the array, creates a new
 * dynamically allocated array for them, and updates the array_pointer
 * and array_size fields in the data_t struct.
 */
void find_even_array(data_t *results, size_t *array, size_t size) {

  size_t *even_array;
  size_t i, j = 0;

  for (i = 0; i < size; i++) {
    if (array[i] % 2 == 0)
      j++;
  }

  if (j == 0) {
    results->array_size = 0;
    results->array_pointer = NULL;
    return;
  }

  even_array = malloc(j * sizeof(size_t));
  if (even_array == NULL) {
    printf("Could not allocate memory for the final array!\n");
    return;
  }

  j = 0;
  for (i = 0; i < size; i++) {
    if (array[i] % 2 == 0) {
      even_array[j] = array[i];
      j++;
    }
  }

  results->array_size = j;
  results->array_pointer = even_array;
}

/*
 * This function performs all calculations, including computing the
 * average, finding max and min values, and identifying even numbers.
 * It also prints the results.
 */
int calculations(data_t *results, size_t *array, size_t size) {

  if (size == 0) {
    printf("Enter a valid number, please!\n");
    return 1;
  }

  compute_average(results, array, size);
  compute_max_and_min(results, array, size);
  find_even_array(results, array, size);

  printf("Max: %zu\n", results->max);
  printf("Min: %zu\n", results->min);
  printf("Avg: %.2f\n", results->avg);
  printf("Array size: %zu\n", results->array_size);

  printf("Even array values:\n");
  for (size_t i = 0; i < results->array_size; i++)
    printf("%zu\n", results->array_pointer[i]);

  return 0;
}

int main(int argc, char *argv[]) {

  data_t example;
  size_t array[] = {3, 4, 6, 3, 56, 7, 34, 4, 6, 7, 3, 4};

  printf("\a");
  printf("\a");
  printf("\a");
  printf("\a");
  printf("\a");

  printf("%zu\n", sizeof(array) / sizeof(size_t));
  size_t size = sizeof(array) / sizeof(size_t);
  calculations(&example, array, size);

  return 0;
}
