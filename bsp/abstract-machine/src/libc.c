#include <klib.h>
#include <rtthread.h>

char *strchr(const char *s, int c) {
  char *res = NULL;
  for (int i = 0; s[i]; i++) {
    if (s[i] == c) {
      res = (char *)(s + i);
      return res;
    }
  }
  return res;
}

char *strrchr(const char *s, int c) {
  char *res = NULL;
  for (int i = 0; s[i]; i++) {
    if (s[i] == c) {
      res = (char *)(s + i);
    }
  }
  return res;
  // assert(0);
}

char *strstr(const char *haystack, const char *needle) {
  return rt_strstr(haystack, needle);
}

bool isdigit(char x) {
  return x >= '0' && x <= '9';
}

long strtol(const char *restrict nptr, char **restrict endptr, int base) {
  long result = 0;
  int sign = 1;
  int i = 0;

  // 跳过前导空白字符
  while ((unsigned char)nptr[i] == ' ') i++;

  // 检查符号
  if (nptr[i] == '-' || nptr[i] == '+') {
    sign = (nptr[i] == '-') ? -1 : 1;
    i++;
  }

  // 转换数字直到非数字字符或字符串结束
  while (isdigit((unsigned char)nptr[i]) && nptr[i] != '\0') {
    result = result * base + (nptr[i] - '0');
    i++;
  }

  // 设置 endptr 指向下一个字符
  if (endptr != NULL) {
    *endptr = (char *)(nptr + i);
  }

  return result * sign;
}

char *strncat(char *restrict dst, const char *restrict src, size_t sz) {
  int i, j;
  for (i = 0; dst[i]; i++);
  for (j = 0; j < sz && src[j] != '\0'; j++) {
    dst[i+j] = src[j];
  }
  dst[i+j] = '\0';
  return dst;
}
