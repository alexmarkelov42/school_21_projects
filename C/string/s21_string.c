#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = s21_NULL;
  const unsigned char *p = str;
  while (n--)
    if (*p++ == c) {
      result = (void *)(p - 1);
      break;
    }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  unsigned const char *p1 = str1, *p2 = str2;
  while (n--) {
    if (*p1++ != *p2++) {
      result = *--p1 - *--p2;
      break;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *p1 = dest;
  const unsigned char *p2 = src;
  while (n--)
    *p1++ = *p2++;
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *p1 = dest;
  const unsigned char *p2 = src;
  if (p1 < p2) {
    while (n--)
      *p1++ = *p2++;
  } else {
    p1 = p1 + (n - 1);
    p2 = p2 + (n - 1);
    while (n--)
      *p1-- = *p2--;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = str;
  while (n--)
    *p++ = c;
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  char *p = dest;
  while (*p)
    p++;
  while (*src)
    *p++ = *src++;

  *p = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *p = dest;
  while (*p)
    p++;
  while (*src && n--)
    *p++ = *src++;
  *p++ = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *ch = 0;
  int len = s21_strlen(str) + 1;
  for (int i = 0; i < len; i++) {
    if (str[i] == (char)c) {
      ch = (char *)&str[i];
      break;
    }
  }
  return ch;
}

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  s21_size_t size_str1 = s21_strlen(str1);
  s21_size_t size_str2 = s21_strlen(str2);
  s21_size_t size_max = size_str1 > size_str2 ? size_str1 : size_str2;
  for (size_t i = 0; i < size_max; i++) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
      break;
    }
  }
  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 1;
  if (n == 0 || str1 == s21_NULL || str2 == s21_NULL) {
    result = 0;
  } else {
    while (*str1 == *str2 && 0 < --n) {
      if (*str1++ == '\0') {
        result = 0;
        break;
      }
      str2++;
    }
  }
  return (result == 0 ? 0 : (int)(*str1 - *str2));
}

char *s21_strcpy(char *dest, const char *src) {
  int i;
  for (i = 0; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t size = s21_strlen(src);
  if (size < n)
    s21_memset(dest + size, '\0', n - size);
  return s21_memcpy(dest, src, n);
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  while (*str1 && !s21_strchr(str2, *str1++)) {
    result++;
  }
  return result;
}

char *s21_strerror(int errnum) {
  static char result[100] = "";
#if defined(__APPLE__) || defined(__MACH__)
  int n = 107;
  const char *str_error[] = {
      "Undefined error: 0",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "Device not configured",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource deadlock avoided",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Resource busy",
      "File exists",
      "Cross-device link",
      "Operation not supported by device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Result too large",
      "Resource temporarily unavailable",
      "Operation now in progress",
      "Operation already in progress",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol family",
      "Address already in use",
      "Can't assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Socket is already connected",
      "Socket is not connected",
      "Can't send after socket shutdown",
      "Too many references: can't splice",
      "Operation timed out",
      "Connection refused",
      "Too many levels of symbolic links",
      "File name too long",
      "Host is down",
      "No route to host",
      "Directory not empty",
      "Too many processes",
      "Too many users",
      "Disc quota exceeded",
      "Stale NFS file handle",
      "Too many levels of remote in path",
      "RPC struct is bad",
      "RPC version wrong",
      "RPC prog. not avail",
      "Program version wrong",
      "Bad procedure for program",
      "No locks available",
      "Function not implemented",
      "Inappropriate file type or format",
      "Authentication error",
      "Need authenticator",
      "Device power is off",
      "Device error",
      "Value too large to be stored in data type",
      "Bad executable (or shared library)",
      "Bad CPU type in executable",
      "Shared library version mismatch",
      "Malformed Mach-o file",
      "Operation canceled",
      "Identifier removed",
      "No message of desired type",
      "Illegal byte sequence",
      "Attribute not found",
      "Bad message",
      "EMULTIHOP (Reserved)",
      "No message available on STREAM",
      "ENOLINK (Reserved)",
      "No STREAM resources",
      "Not a STREAM",
      "Protocol error",
      "STREAM ioctl timeout",
      "Operation not supported on socket",
      "Policy not found",
      "State not recoverable",
      "Previous owner died",
      "Interface output queue is full",
  };

#elif defined(__linux__)
  int n = 134;
  const char *str_error[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error",
  };
#endif
  if (errnum >= n || errnum < 0) {
#if defined(__APPLE__) || defined(__MACH__)
    /* char res[30] = ""; */
    s21_sprintf(result, "Unknown error: %d", errnum);
    /* s21_strcpy(result, res); */
#elif defined(__linux__)
    /* char res[30] = ""; */
    s21_sprintf(result, "Unknown error %d", errnum);
    /* s21_strcpy(result, res); */
#endif
  } else {
    s21_strcpy(result, str_error[errnum]);
  }
  return result;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str != s21_NULL) {
    while (str[len]) {
      len++;
    }
  }
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  s21_size_t size_str1 = s21_strlen(str1);
  s21_size_t size_str2 = s21_strlen(str2);
  for (s21_size_t i = 0; i < size_str1 && result == s21_NULL; i++) {
    for (s21_size_t j = 0; j < size_str2 && result == s21_NULL; j++) {
      if (str1[i] == str2[j]) {
        result = (char *)&str1[i];
      }
    }
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  s21_size_t size = s21_strlen(str) + 1;
  char *result = s21_NULL;
  for (s21_size_t i = 0; i < size; i++) {
    if (str[i] == c) {
      result = (char *)&str[i];
    }
  }
  return result;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  while (*str1 && s21_strchr(str2, *str1++)) {
    result++;
  }
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  const char *p1 = haystack, *p2 = needle;
  int i = 1;
  while (i) {
    if (!*p2) {
      result = (char *)haystack;
      i = 0;
    }
    if (!*p1)
      i = 0;
    if (*p1++ != *p2++) {
      p1 = ++haystack;
      p2 = needle;
    }
  }
  return result;
}

int s21_check_delim(char c, const char *delim) {
  int result = 0;
  while (*delim) {
    if (*delim == c)
      result++;
    delim++;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  char *result = s21_NULL;
  static char *pointer_str;
  if (!str)
    str = pointer_str;
  if (str) {
    int f = 0;
    while (s21_check_delim(*str, delim))
      str++;
    if (*str == '\0')
      f = 1;
    char *in = str;
    while (!f) {
      if (*str == '\0') {
        pointer_str = str;
        result = in;
        f = 1;
      }
      if (s21_check_delim(*str, delim)) {
        *str = '\0';
        pointer_str = str + 1;
        result = in;
        f = 1;
      }
      str++;
    }
  }
  return result;
}

void s21_reverse(char *str, int len) {
  int p1 = 0;
  int p2 = len - 1;
  while (p1 < p2) {
    char temp = *(str + p1);
    *(str + p1) = *(str + p2);
    *(str + p2) = temp;
    p1++;
    p2--;
  }
}

char *s21_itoa(long long n, char *str) {
  int len = 0, i = 0, f = 0;
  if (n < 0) {
    n *= -1;
    f = 1;
  }
  do {
    str[i++] = n % 10 + '0';
    n /= 10;
    len++;
  } while (n);
  if (f) {
    str[i++] = '-';
    len++;
  }
  str[i] = '\0';
  s21_reverse(str, len);
  return str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t size_src = s21_strlen(src);
    s21_size_t size_str = s21_strlen(str);
    s21_size_t size_total = size_src + size_str; // + 1???????
    if (size_src >= start_index) {
      result = (char *)calloc(size_total + 1,
                              sizeof(char)); // added +1 so that \0 fits
      if (result != s21_NULL) {
        for (s21_size_t i = 0; i < size_src; i++) {
          result[i] = src[i];
        }
        for (s21_size_t i = start_index; i < size_total; i++) {
          result[i] = str[i - start_index];
        }
        for (s21_size_t i = start_index + size_str; i < size_total; i++) {
          result[i] = src[i - s21_strlen(str)];
        }
        result[size_total] = '\0';
      }
    }
  }
  return result;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  int len = s21_strlen(str);
  // Address 0x4d78863 is 0 bytes after a block of size 3 alloc'd ;;; use
  // calloc()?
  char *result = calloc(len + 1, sizeof(char));
  if (result == s21_NULL) {
    return s21_NULL;
  }
  s21_strcpy(result, str);
  for (int i = 0; i < len; i++) {
    if (str[i] >= 65 && str[i] <= 90)
      result[i] = str[i] + 32;
    else
      result[i] = str[i];
  }
  result[len] = '\0';
  return result;
}

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  s21_size_t len = s21_strlen(str);
  char *result = calloc(len + 1, sizeof(char)); //  result = "" ? or calloc()?
  if (result == s21_NULL) {
    return s21_NULL;
  }
  s21_strcpy(result, str);
  for (int i = 0; str[i] != '\0'; i++)
    if (str[i] >= 97 && str[i] <= 122)
      result[i] = str[i] - 32;
    else
      result[i] = str[i];
  result[len] = '\0';
  return result;
}

int isthere(char c, const char *trim_chars) {
  int res = 0;
  if ((trim_chars != s21_NULL) && (s21_strlen(trim_chars) > 0)) {
    int len = s21_strlen(trim_chars);
    for (int i = 0; i <= len; i++) {
      if (trim_chars[i] == c) {
        res = 1;
      }
    }
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = s21_NULL;
  if (trim_chars == s21_NULL || *trim_chars == '\0') {
    trim_chars = " \f\n\r\t\v";
  }
  if (src != s21_NULL) {
    int len = s21_strlen(src);
    int last_n = len;
    int i = 0;
    int start_n = -1;
    while (i <= len) {
      if (isthere(src[i], trim_chars) == 1) {
        start_n = i;
        i++;
      } else {
        i = len + 1;
      }
    }
    i = len - 1;
    while (i >= 0) {
      if (isthere(src[i], trim_chars) == 1) {
        last_n = i;
        i--;
      } else {
        i = -1;
      }
    }
    result = (char *)calloc(1, sizeof(char));
    int temp = 0;
    for (int j = start_n + 1; j < last_n; j++) {
      char *tmp = (char *)realloc(result, (temp + 2) * sizeof(char *));
      if (!tmp) {
        return s21_NULL;
      } else {
        result = tmp;
      }
      result[temp] = src[j];
      temp++;
    }
    result[temp] = '\0';
  }
  return result;
}
