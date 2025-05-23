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

    // Update content size for the input to fit in
    if (ip->length + 1 == ip->size) {
      ip->content = realloc(ip->content, 2 * ip->size * sizeof(wchar_t));
      if (ip->content == NULL) return -1;
      ip->size *= 2;
    }
    ip->content[ip->length++] = ch;
  }
  
  // Set current pointer to the beginning of the input
  ip->current = ip->content;
  return count;
}

Number get_next_number(Input ip) {
  /*  Check that current char is either a digit or a 
      negative sign followed by a digit. */
  if (!iswdigit(*ip->current) && 
      (!(*ip->current == '-') ||!iswdigit(*(ip->current + 1)))) return NAN;

  Number n;
  swscanf(ip->current, L"%lf", &n);

  // Advance current pointer until the character following the number
  bool point_read = false;
  if (n < 0) ip->current++;
  for (;;) {
    wchar_t ch = *ip->current;
    if (iswdigit(ch)) ip->current++;
    else if (ch == '.' && !point_read) {
      // Allow one '.' in number
      ip->current++;
      point_read = true;
    } else break;
  }
  return n;
}

wint_t get_next_char(Input ip) {
  if (end_of_input(ip)) return WEOF;
  return *ip->current++;
}

wint_t hint_next_char(Input ip) {
  if (end_of_input(ip)) return WEOF;
  return *ip->current;
}

void reset(Input ip) {
  ip->current = ip->content;
}

bool end_of_input(Input ip) {
  return *ip->current == '\0';
}
