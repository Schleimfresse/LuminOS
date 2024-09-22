#include <stddef.h>

void *memcpy (void *dest, const void *src, size_t len) {
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}

void *memset (void *dest, int val, size_t len) {
  unsigned char *ptr = dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    char temp;

    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* to_string(size_t value) {
    static char buffer[20]; 
    int index = 0;

    if (value == 0) {
        buffer[index++] = '0';
        buffer[index] = '\0';
        return buffer;
    }

    while (value > 0) {
        buffer[index++] = (value % 10) + '0';
        value /= 10;
    }

    buffer[index] = '\0';
    reverse(buffer, index);
    return buffer;
}