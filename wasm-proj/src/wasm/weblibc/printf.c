
#include "wasm/stdio.h"

#include "wasm/stdlib.h"
#include "wasm/impexp.h"
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

// Copyright (c) 2021 Eumerics Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

WASM_IMPORT int printf_string(char const* begin, char const* end);
WASM_IMPORT int printf_integer(int flags, int width, int precision, char length_char, uint8_t length, char type, int value);
WASM_IMPORT int printf_int32(int flags, int width, int precision, char length_char, uint8_t length, char type, int32_t value);
WASM_IMPORT int printf_int64(int flags, int width, int precision, char length_char, uint8_t length, char type, int64_t value);
WASM_IMPORT int printf_long(int flags, int width, int precision, char length_char, uint8_t length, char type, long value);
WASM_IMPORT int printf_long_long(int flags, int width, int precision, char length_char, uint8_t length, char type, long long value);
WASM_IMPORT int printf_intmax(int flags, int width, int precision, char length_char, uint8_t length, char type, intmax_t value);
WASM_IMPORT int printf_signed_size(int flags, int width, int precision, char length_char, uint8_t length, char type, size_t value);
WASM_IMPORT int printf_ptrdiff(int flags, int width, int precision, char length_char, uint8_t length, char type, ptrdiff_t value);
WASM_IMPORT int printf_unsigned(int flags, int width, int precision, char length_char, uint8_t length, char type, unsigned value);
WASM_IMPORT int printf_uint32(int flags, int width, int precision, char length_char, uint8_t length, char type, uint32_t value);
WASM_IMPORT int printf_uint64(int flags, int width, int precision, char length_char, uint8_t length, char type, uint64_t value);
WASM_IMPORT int printf_unsigned_long(int flags, int width, int precision, char length_char, uint8_t length, char type, unsigned long value);
WASM_IMPORT int printf_unsigned_long_long(int flags, int width, int precision, char length_char, uint8_t length, char type, unsigned long long value);
WASM_IMPORT int printf_uintmax(int flags, int width, int precision, char length_char, uint8_t length, char type, uintmax_t value);
WASM_IMPORT int printf_size(int flags, int width, int precision, char length_char, uint8_t length, char type, size_t value);
WASM_IMPORT int printf_unsigned_ptrdiff(int flags, int width, int precision, char length_char, uint8_t length, char type, ptrdiff_t value);
WASM_IMPORT int printf_double(int flags, int width, int precision, char length_char, uint8_t length, char type, double value);
WASM_IMPORT int printf_cstring(int flags, int width, int precision, char length_char, uint8_t length, char type, char const* value);
WASM_IMPORT int printf_char(int flags, int width, int precision, char length_char, uint8_t length, char type, char value);
WASM_IMPORT int printf_pointer(int flags, int width, int precision, char length_char, uint8_t length, char type, void* value);


int printf(char const* format, ...)
{
   int print_length = 0;
   int const flag_left_align = 0x01;
   int const flag_plus_sign = 0x02;
   int const flag_plus_space = 0x04;
   int const flag_zero_pad = 0x08;
   int const flag_thousands_separator = 0x10;
   int const flag_hash_modifier = 0x20;
   va_list arg_pointer;
   va_start(arg_pointer, format);
   char const* p = format;
   char c = *format;
   int errored = 0;
   while(c != 0) {
      int flags = 0;
      int width = -1;
      int precision = -1;
      char length_char = 0;
      int length_bytes = 0;
      if(c != '%') {
         char const* begin = p;
         while(c != '%' && c != 0) c = *++p;
         print_length += printf_string(begin, p);
         if(c == 0) break;
      }
      c = *++p;
      if(c == 0){ errored = 1; break; }
      // check for flags
      int has_flag = 1;
      do {
         switch(c) {
            case '-': flags |= flag_left_align; break;
            case '+': flags |= flag_plus_sign; break;
            case ' ': flags |= flag_plus_space; break;
            case '0': flags |= flag_zero_pad; break;
            case '\'': flags |= flag_thousands_separator; break;
            case '#': flags |= flag_hash_modifier; break;
            default: has_flag = 0; break;
         }
         if(!has_flag) break;
         c = *++p;
      } while(has_flag && c != 0);
      if(flags & flag_left_align) flags &= ~flag_zero_pad;
      if(c == 0){ errored = 1; break; }
      // check for width field
      if(c == '*') {
         c = *++p; width = va_arg(arg_pointer, int);
         if(width < 0) { width = -width; flags |= flag_left_align; }
      } else {
         while(c >= '0' && c <= '9') {
            if(width == -1) width = 0;
            width = width * 10 + (c - '0');
            c = *++p;
            if(c == 0) break;
         }
      }
      if(c == 0){ errored = 1; break; }
      // check for precision field
      if(c == '.') {
         c = *++p;
         if(c == '*') { c = *++p; precision = va_arg(arg_pointer, int); }
         else {
            precision = 0;
            while(c >= '0' && c <= '9') {
               precision = precision * 10 + (c - '0');
               c = *++p;
               if(c == 0) break;
            }
         }
      }
      if(c == 0){ errored = 1; break; }
      // check for length field
      if(c == 'L' || c == 'z' || c == 'j' || c == 't') {
         length_char = c; c = *++p;
      } else if(c == 'l' || c == 'h') {
         length_char = c;
         c = *++p;
         if(c == 'l') {
            length_char = 1; c = *++p; // we will use a pseudo char 1
         } else if(c == 'h') {
            length_char = 2; c = *++p; // we will use a pseudo char 2
         }
      } else if(c == 'I') {
         int length_bits = 0;
         length_char = c; c = *++p;
         if(c >= '1' && c <= '9'){
            length_bits = c - '0'; c = *++p;
            if(c < '0' || c > '9'){ errored = 1; break; }
            length_bits = length_bits * 10 + (c - '0'); c = *++p;
            if(length_bits != 32 && length_bits != 64){ errored = 1; break; }
            length_bytes = length_bits / 8;
         }
      }
      if(c == 0){ errored = 1; break; }
      // check for type field
      switch(c)
      {
         case '%': print_length += printf_char(flags, width, precision, length_char, sizeof(char), c, c); break;
         case 'd': case 'i': {
            switch(length_char) {
               case 'l': {
                  long value = va_arg(arg_pointer, long);
                  print_length += printf_long(flags, width, precision, length_char, sizeof(long), c, value);
                  break;
               }
               case 1: {
                  long long value = va_arg(arg_pointer, long long);
                  print_length += printf_long_long(flags, width, precision, length_char, sizeof(long long), c, value);
                  break;
               }
               case 'j': {
                  intmax_t value = va_arg(arg_pointer, intmax_t);
                  print_length += printf_intmax(flags, width, precision, length_char, sizeof(intmax_t), c, value);
                  break;
               }
               case 'z': {
                  size_t value = va_arg(arg_pointer, size_t);
                  print_length += printf_signed_size(flags, width, precision, length_char, sizeof(size_t), c, value);
                  break;
               }
               case 't': {
                  ptrdiff_t value = va_arg(arg_pointer, ptrdiff_t);
                  print_length += printf_ptrdiff(flags, width, precision, length_char, sizeof(ptrdiff_t), c, value);
                  break;
               }
               case 'I': {
                  if(length_bytes == 0) {
                     ptrdiff_t value = va_arg(arg_pointer, ptrdiff_t);
                     print_length += printf_ptrdiff(flags, width, precision, length_char, sizeof(ptrdiff_t), c, value);
                     break;
                  } else if(length_bytes == 4) {
                     int32_t value = va_arg(arg_pointer, int32_t);
                     print_length += printf_int32(flags, width, precision, length_char, length_bytes, c, value);
                     break;
                  } else {
                     int64_t value = va_arg(arg_pointer, int64_t);
                     print_length += printf_int64(flags, width, precision, length_char, length_bytes, c, value);
                     break;
                  }
               }
               default: {
                  int value = va_arg(arg_pointer, int);
                  uint8_t length = (
                     length_char == 'h' ? sizeof(short) :
                     length_char == 2 ? sizeof(char) : sizeof(int)
                  );
                  print_length += printf_integer(flags, width, precision, length_char, length, c, value);
                  break;
               }
            }
            break;
         }
         case 'u': case 'x': case 'X': case 'o': {
            switch(length_char) {
               case 'l': {
                  unsigned long value = va_arg(arg_pointer, unsigned long);
                  print_length += printf_unsigned_long(flags, width, precision, length_char, sizeof(unsigned long), c, value);
                  break;
               }
               case 1: {
                  unsigned long long value = va_arg(arg_pointer, unsigned long long);
                  print_length += printf_unsigned_long_long(flags, width, precision, length_char, sizeof(unsigned long long), c, value);
                  break;
               }
               case 'j': {
                  uintmax_t value = va_arg(arg_pointer, uintmax_t);
                  print_length += printf_uintmax(flags, width, precision, length_char, sizeof(uintmax_t), c, value);
                  break;
               }
               case 'z': {
                  size_t value = va_arg(arg_pointer, size_t);
                  print_length += printf_size(flags, width, precision, length_char, sizeof(size_t), c, value);
                  break;
               }
               case 't': {
                  ptrdiff_t value = va_arg(arg_pointer, ptrdiff_t);
                  print_length += printf_unsigned_ptrdiff(flags, width, precision, length_char, sizeof(ptrdiff_t), c, value);
                  break;
               }
               case 'I': {
                  if(length_bytes == 0) {
                     size_t value = va_arg(arg_pointer, size_t);
                     print_length += printf_size(flags, width, precision, length_char, sizeof(size_t), c, value);
                     break;
                  } else if(length_bytes == 4) {
                     uint32_t value = va_arg(arg_pointer, uint32_t);
                     print_length += printf_uint32(flags, width, precision, length_char, length_bytes, c, value);
                     break;
                  } else {
                     uint64_t value = va_arg(arg_pointer, uint64_t);
                     print_length += printf_uint64(flags, width, precision, length_char, length_bytes, c, value);
                     break;
                  }
               }
               default: {
                  unsigned value = va_arg(arg_pointer, unsigned);
                  uint8_t length = (
                     length_char == 'h' ? sizeof(unsigned short) :
                     length_char == 2 ? sizeof(unsigned char) : sizeof(unsigned int)
                  );
                  print_length += printf_unsigned(flags, width, precision, length_char, length, c, value);
                  break;
               }
            }
            break;
         }
         case 'f': case 'F': case 'e': case 'E':
         case 'g': case 'G': case 'a': case 'A': {
            switch(length_char) {
               case 'L': {
                  va_arg(arg_pointer, long double);
                  print_length += printf_double(flags, width, precision, length_char, sizeof(long double), c, 0);
                  break;
               }
               default: {
                  double value = va_arg(arg_pointer, double);
                  print_length += printf_double(flags, width, precision, length_char, sizeof(double), c, value);
                  break;
               }
            }
            break;
         }
         case 's': {
            char* value = va_arg(arg_pointer, char*);
            print_length += printf_cstring(flags, width, precision, length_char, (length_char == 'L' ? 2 : 1), c, value);
            break;
         }
         case 'c': {
            char value = va_arg(arg_pointer, int);
            print_length += printf_char(flags, width, precision, length_char, sizeof(char), c, value);
            break;
         }
         case 'p': {
            void* value = va_arg(arg_pointer, void*);
            print_length += printf_pointer(flags, width, precision, length_char, sizeof(void*), c, value);
            break;
         }
         case 'n': {
            switch(length_char) {
               case 2: {
                  char* count = va_arg(arg_pointer, char*);
                  *count = print_length;
                  break;
               }
               case 'h': {
                  short* count = va_arg(arg_pointer, short*);
                  *count = print_length;
                  break;
               }
               case 'l': {
                  long* count = va_arg(arg_pointer, long*);
                  *count = print_length;
                  break;
               }
               case 1: {
                  long long* count = va_arg(arg_pointer, long long*);
                  *count = print_length;
                  break;
               }
               case 'j': {
                  uintmax_t* count = va_arg(arg_pointer, uintmax_t*);
                  *count = print_length;
                  break;
               }
               case 'z': {
                  size_t* count = va_arg(arg_pointer, size_t*);
                  *count = print_length;
                  break;
               }
               case 't': {
                  ptrdiff_t* count = va_arg(arg_pointer, ptrdiff_t*);
                  *count = print_length;
                  break;
               }
               default: {
                  int* count = va_arg(arg_pointer, int*);
                  *count = print_length;
                  break;
               }
            }
            break;
         }
         default: errored = 1; break;
      }
      c = *++p;
   }
   va_end(arg_pointer);
   return (errored ? -1 : print_length);
}