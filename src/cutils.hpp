#ifndef QJS_CUTILS_HPP
#define QJS_CUTILS_HPP

#include <bit>
#include <cstddef>
#include <cstdint>

/* set if CPU is big endian */
#undef WORDS_BIGENDIAN

// We don't need these macros in C++ 20
// #define likely(x)       __builtin_expect(!!(x), 1)
// [[likely]]
// #define unlikely(x)     __builtin_expect(!!(x), 0)
// [[unlikely]]
// #define __maybe_unused __attribute__((unused))
// [[maybe_unused]]

// #define force_inline inline __attribute__((always_inline))
#ifdef _WIN32
// #define force_inline inline __declspec(alwaysinline) // not supported
#define force_inline inline
#elif defined(__GNUC__)
#define force_inline inline __attribute__((always_inline))
#elif defined(__clang__)
#define force_inline inline __attribute__((always_inline))
#else
#define force_inline inline
#endif

// #define no_inline __attribute__((noinline))
#ifdef _WIN32
#define no_inline __declspec(noinline)
#elif defined(__GNUC__)
#define no_inline __attribute__((noinline))
#elif defined(__clang__)
#define no_inline __attribute__((noinline))
#else
#define no_inline
#endif

#define xglue(a, b) a##b
#define glue(a, b) xglue(a, b)
#define tostring(s) #s
#define stringify(s) tostring(s)

// probably not needed as we will use C++ containers
// TODO(CGQAQ): Remove when we sure we don't need it
#ifndef offsetof
#define offsetof(type, field) ((size_t) & ((type *)0)->field)
#endif
#ifndef countof
#define countof(x) (sizeof(x) / sizeof((x)[0]))
#endif

// https://stackoverflow.com/a/3312896
#if defined(__GNUC__) || defined(__clang__)
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#elif defined(_MSC_VER)
#define PACK(__Declaration__) \
    __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#endif

#define UTF8_CHAR_LEN_MAX 6

namespace qjs::cutils {

// Don't need this, just use bool
// typedef int BOOL;
// #ifndef FALSE
// enum {
//    FALSE = 0,
//    TRUE = 1,
//};
// #endif

// TODO(CGQAQ): refactor or not?
[[maybe_unused]] void pstrcpy(char *buf, int buf_size, const char *str);
char *pstrcat(char *buf, int buf_size, const char *s);
int strstart(const char *str, const char *val, const char **ptr);
int has_suffix(const char *str, const char *suffix);

force_inline constexpr static int max_int(int const a, int const b) {
    if (a > b) {
        return a;
    }
    return b;
}

force_inline constexpr static int min_int(int const a, int const b) {
    if (a < b) {
        return a;
    }
    return b;
}

force_inline constexpr static uint32_t max_uint32(uint32_t const a,
                                                  uint32_t const b) {
    if (a > b) {
        return a;
    }
    return b;
}

force_inline constexpr static uint32_t min_uint32(uint32_t const a,
                                                  uint32_t const b) {
    if (a < b) {
        return a;
    }
    return b;
}

force_inline constexpr static int64_t max_int64(int64_t const a,
                                                int64_t const b) {
    if (a > b) {
        return a;
    }
    return b;
}

force_inline constexpr static int64_t min_int64(int64_t const a,
                                                int64_t const b) {
    if (a < b) {
        return a;
    }
    return b;
}

/* WARNING: undefined if a = 0 */
force_inline static int clz32(unsigned int a) { return std::countl_zero(a); }

/* WARNING: undefined if a = 0 */
force_inline static int clz64(uint64_t a) { return std::countl_zero(a); }

/* WARNING: undefined if a = 0 */
force_inline static int ctz32(unsigned int a) { return std::countr_zero(a); }

/* WARNING: undefined if a = 0 */
force_inline static int ctz64(uint64_t a) { return std::countr_zero(a); }

// __attribute__((packed)) but cross platform
PACK(struct packed_u64 { uint64_t v; });

PACK(struct packed_u32 { uint32_t v; });

PACK(struct packed_u16 { uint16_t v; });

force_inline static uint64_t get_u64(const uint8_t *tab) {
    return (reinterpret_cast<const struct packed_u64 *>(tab))->v;
}

force_inline static int64_t get_i64(const uint8_t *tab) {
    return static_cast<int64_t>(
        (reinterpret_cast<const struct packed_u64 *>(tab))->v);
}

/* NOLINTNEXTLINE */
force_inline static void put_u64(uint8_t *tab, uint64_t val) {
    (reinterpret_cast<struct packed_u64 *>(tab))->v = val;
}

force_inline static uint32_t get_u32(const uint8_t *tab) {
    return (reinterpret_cast<const struct packed_u32 *>(tab))->v;
}

force_inline static int32_t get_i32(const uint8_t *tab) {
    return static_cast<int32_t>(
        (reinterpret_cast<const struct packed_u32 *>(tab))->v);
}

/* NOLINTNEXTLINE */
force_inline static void put_u32(uint8_t *tab, uint32_t val) {
    (reinterpret_cast<struct packed_u32 *>(tab))->v = val;
}

force_inline static uint32_t get_u16(const uint8_t *tab) {
    return (reinterpret_cast<const struct packed_u16 *>(tab))->v;
}

force_inline static int16_t get_i16(const uint8_t *tab) {
    return static_cast<int16_t>(
        (reinterpret_cast<const struct packed_u16 *>(tab))->v);
}

/* NOLINTNEXTLINE */
force_inline static void put_u16(uint8_t *tab, uint16_t val) {
    (reinterpret_cast<struct packed_u16 *>(tab))->v = val;
}

force_inline static uint32_t get_u8(const uint8_t *tab) { return *tab; }

force_inline static int32_t get_i8(const uint8_t *tab) {
    return static_cast<int8_t>(*tab);
}

force_inline static void put_u8(uint8_t *tab, uint8_t val) { *tab = val; }

force_inline constexpr static uint16_t bswap16(uint16_t x) {
    return std::byteswap(x);
}

force_inline constexpr static uint32_t bswap32(uint32_t v) {
    return std::byteswap(v);
}

force_inline constexpr static uint64_t bswap64(uint64_t v) {
    return std::byteswap(v);
}

/// TODO(CGQAQ): alloccator? need more investigate to decide how to refactoring
/// it
using DynBufReallocFunc = void *(void *, void *, size_t);
struct [[maybe_unused]] DynBuf {
    uint8_t *buf;
    size_t size;
    size_t allocated_size;
    bool error; /* true if a memory allocation error occurred */
    DynBufReallocFunc *realloc_func;
    void *opaque; /* for realloc_func */

    //    void dbuf_init(DynBuf *s);
    //    void dbuf_init2(DynBuf *s, void *opaque, DynBufReallocFunc
    //    *realloc_func); int dbuf_realloc(DynBuf *s, size_t new_size); int
    //    dbuf_write(DynBuf *s, size_t offset, const uint8_t *data, size_t len);
    //    int dbuf_put(DynBuf *s, const uint8_t *data, size_t len);
    //    int dbuf_put_self(DynBuf *s, size_t offset, size_t len);
    //    int dbuf_putc(DynBuf *s, uint8_t c);
    //    int dbuf_putstr(DynBuf *s, const char *str);
    //    static inline int dbuf_put_u16(DynBuf *s, uint16_t val)
    //    {
    //        return dbuf_put(s, (uint8_t *)&val, 2);
    //    }
    //    static inline int dbuf_put_u32(DynBuf *s, uint32_t val)
    //    {
    //        return dbuf_put(s, (uint8_t *)&val, 4);
    //    }
    //    static inline int dbuf_put_u64(DynBuf *s, uint64_t val)
    //    {
    //        return dbuf_put(s, (uint8_t *)&val, 8);
    //    }
    //    int __attribute__((format(printf, 2, 3))) dbuf_printf(DynBuf *s,
    //                                                          const char *fmt,
    //                                                          ...);
    //    void dbuf_free(DynBuf *s);
    //    static inline BOOL dbuf_error(DynBuf *s) {
    //        return s->error;
    //    }
    //    static inline void dbuf_set_error(DynBuf *s)
    //    {
    //        s->error = TRUE;
    //    }
};

int unicode_to_utf8(uint8_t *buf, unsigned int c);
int unicode_from_utf8(const uint8_t *p, int max_len, const uint8_t **pp);

force_inline constexpr static int from_hex(int const c) {
    int constexpr number_count = 10;

    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + number_count;
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + number_count;
    }
    return -1;
}

// TODO(CGQAQ): need more time to know we could use std::qsort instead
void rqsort(void *base, size_t nmemb, size_t size,
            int (*cmp)(const void *, const void *, void *), void *arg);

}  // namespace qjs::cutils

#endif
