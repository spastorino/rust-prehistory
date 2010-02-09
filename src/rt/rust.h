#ifndef RUST_H__
#define RUST_H__

/*
 * Rust runtime library.
 * Copyright 2008, 2009 Graydon Hoare <graydon@pobox.com>.
 * Released under MIT license.
 * See file COPYING for details.
 */

/*
 * Include this file after you've defined the ISO C9x stdint
 * types (size, uint8, uintptr, etc.)
 */

#ifdef __i386__
// 'cdecl' ABI only means anything on i386
#ifdef __WIN32__
#define CDECL __cdecl
#else
#define CDECL __attribute__((cdecl))
#endif
#else
#define CDECL
#endif

struct rust_proc;

struct rust_srv {
    size_t live_allocs;

    virtual void log(char const *);
    virtual void fatal(char const *, char const *, size_t);
    virtual void *malloc(size_t);
    virtual void *realloc(void *, size_t);
    virtual void free(void *);
    virtual rust_srv *clone();

    rust_srv();
    virtual ~rust_srv();
};

inline void *operator new(size_t size, rust_srv *srv)
{
    return srv->malloc(size);
}

/*
 * Local Variables:
 * fill-column: 70;
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * buffer-file-coding-system: utf-8-unix
 * compile-command: "make -k -C .. 2>&1 | sed -e 's/\\/x\\//x:\\//g'";
 * End:
 */

#endif /* RUST_H__ */
