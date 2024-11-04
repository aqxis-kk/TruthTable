/**
 * @brief Extended lib for string manipulation
 */
#pragma once

#if !__GX_INTERNAL__
#  error "Include \"gx.h\" instead."
#endif

#include <stdio.h>

/**
 * @brief Finds \a target in \a n sized string array \a test.
 * @param[in] target The string to find, nonnull.
 * @param[in] test An array of string to inspect, nonnull.
 * @param[in] n The size of array \a test.
 * @return index of array (&isin; [0, \a n)) if found, -1 otherwise.
 */
int
gx_strfind(const char *__restrict target,
           const char **__restrict test,
           const size_t n) __attribute__((pure, nonnull(1, 2)));

/**
 * @brief Finds \a target[0:l] in \a n sized string array \a test.
 * @param[in] target The string to find, nonnull.
 * @param[in] l The length of string to compare.
 * @param[in] test An array of string to inspect, nonnull.
 * @param[in] n The size of array \a test.
 * @return index of array (&isin; [0, \a n)) if found, -1 otherwise.
 */
int
gx_strlfind(const char *__restrict target,
            const size_t l,
            const char **__restrict test,
            const size_t n) __attribute__((pure, __nonnull__(1, 3)));

/**
 * @brief Finds \a target in 2D char array \a test[x][y].
 * @param[in] target The string to find, nonnull.
 * @param[in] test An array of string to inspect, nonnull.
 * @param[in] x The size of array \a test.
 * @param[in] y The size of array \a test[].
 * @return x index of array (&isin; [0, \a x)) if found, -1 otherwise.
 */
int
gx_strfind_2d(const char *__restrict target,
              const size_t x,
              const size_t y,
              const char test[x][y]) __attribute__((pure, nonnull(1, 4)));

/**
 * @brief Finds \a target[0:l] in 2D char array \a test[x][y].
 * @param[in] target The string to find, nonnull.
 * @param[in] l The length of string to compare.
 * @param[in] x The size of array \a test.
 * @param[in] y The size of array \a test[].
 * @param[in] test An array of string to inspect, nonnull.
 * @return x index of array (&isin; [0, \a x)) if found, -1 otherwise.
 */
int
gx_strlfind_2d(const char *__restrict target,
               const size_t l,
               const size_t x,
               const size_t y,
               const char test[x][y]) __attribute__((pure, nonnull(1, 5)));

/**
 * @brief Finds \a target in \a __VA_ARGS__.
 * @param[in] target The string to find, nonnull.
 * @return index of array (&isin; [0, \a n)) if found, -1 otherwise.
 */
#define gxstrfind_v(target, ...)                                               \
  ({                                                                           \
    const char *test[] = {__VA_ARGS__};                                        \
    gx_strfind(target, test, (sizeof(test) / sizeof(test[0])));                \
  })
