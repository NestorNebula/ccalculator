#include <stdlib.h>
#include <math.h>
#include "input.h"

#define MIN_LEN 2

struct input_type {
  wchar_t *content;
  unsigned int length;
  unsigned int size;
  wchar_t *current;
};

Input new_input(void) {
  Input ip = malloc(sizeof(struct input_type));
  if (ip == NULL) return ip;
  ip->content = malloc(MIN_LEN * sizeof(wchar_t));
  if (ip->content == NULL) {
    free(ip);
    return NULL;
  }
  ip->length = 0;
  ip->size = MIN_LEN;
  *ip->content = '\0';
  ip->current = ip->content;
  return ip;
}

void delete_input(Input ip) {
  free(ip->content);
  free(ip);
}

int read_input(Input ip, FILE * stream) {
  int count = 0;
  for (wint_t ch; (ch = getwc(stream)) != '\n' && ch != WEOF; count++) {
    if (ip->length + 1 == ip->size) {
      ip->content = realloc(ip->content, 2 * ip->size * sizeof(wchar_t));
      if (ip->content == NULL) return -1;
      ip->size *= 2;
    }
    ip->content[ip->length++] = ch;
  }
  ip->current = ip->content;
  return count;
}

Number get_next_number(Input ip) {
  if (!iswdigit(*ip->current)) return NAN;
  Number n;
  swscanf(ip->current, L"%lf", &n);
  while (iswdigit(*ip->current)) ip->current++;
  return n;
}

wint_t get_next_char(Input ip) {
  if (end_of_input(ip)) return WEOF;
  wchar_t ch = *ip->current++;
  return ch;
}

bool end_of_input(Input ip) {
  return *ip->current == '\0';
}
