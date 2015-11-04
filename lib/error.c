#include "../include/siphon/error.h"

#include <stdlib.h>
#include <execinfo.h>

#include "lock.h"

/* Fallback definitions to simplify compiling.
 * These won't ever be used because they aren't defined (and thus not used)
 * in linux. These definitions just allow the x-macro to be much simpler.
 */
#if __linux
# ifndef EAI_BADHINTS
#  define EAI_BADHINTS -34
# endif
# ifndef EAI_PROTOCOL
#  define EAI_PROTOCOL -35
# endif
#else
# ifndef EAI_CANCELED
#  define EAI_CANCELED 33
# endif
#endif


#define SP_SYSTEM_ERRORS(XX) \
	XX(EPERM,              "operation not permitted") \
	XX(ENOENT,             "no such file or directory") \
	XX(ESRCH,              "no such process") \
	XX(EINTR,              "interrupted system call") \
	XX(EIO,                "i/o error") \
	XX(ENXIO,              "no such device or address") \
	XX(E2BIG,              "argument list too long") \
	XX(EBADF,              "bad file descriptor") \
	XX(ENOMEM,             "not enough memory") \
	XX(EACCES,             "permission denied") \
	XX(EFAULT,             "bad address in system call argument") \
	XX(EBUSY,              "resource busy or locked") \
	XX(EEXIST,             "file already exists") \
	XX(EXDEV,              "cross-device link not permitted") \
	XX(ENODEV,             "no such device") \
	XX(ENOTDIR,            "not a directory") \
	XX(EISDIR,             "illegal operation on a directory") \
	XX(EINVAL,             "invalid argument") \
	XX(ENFILE,             "file table overflow") \
	XX(EMFILE,             "too many open files") \
	XX(ETXTBSY,            "text file is busy") \
	XX(EFBIG,              "file too large") \
	XX(ENOSPC,             "no space left on device") \
	XX(ESPIPE,             "invalid seek") \
	XX(EROFS,              "read-only file system") \
	XX(EMLINK,             "too many links") \
	XX(EPIPE,              "broken pipe") \
	XX(ERANGE,             "result too large") \
	XX(EAGAIN,             "resource temporarily unavailable") \
	XX(EALREADY,           "connection already in progress") \
	XX(ENOTSOCK,           "socket operation on non-socket") \
	XX(EDESTADDRREQ,       "destination address required") \
	XX(EMSGSIZE,           "message too long") \
	XX(EPROTOTYPE,         "protocol wrong type for socket") \
	XX(ENOPROTOOPT,        "protocol not available") \
	XX(EPROTONOSUPPORT,    "protocol not supported") \
	XX(ENOTSUP,            "operation not supported on socket") \
	XX(EAFNOSUPPORT,       "address family not supported") \
	XX(EADDRINUSE,         "address already in use") \
	XX(EADDRNOTAVAIL,      "address not available") \
	XX(ENETDOWN,           "network is down") \
	XX(ENETUNREACH,        "network is unreachable") \
	XX(ECONNABORTED,       "software caused connection abort") \
	XX(ECONNRESET,         "connection reset by peer") \
	XX(ENOBUFS,            "no buffer space available") \
	XX(EISCONN,            "socket is already connected") \
	XX(ENOTCONN,           "socket is not connected") \
	XX(ESHUTDOWN,          "cannot send after transport endpoint shutdown") \
	XX(ETIMEDOUT,          "connection timed out") \
	XX(ECONNREFUSED,       "connection refused") \
	XX(ELOOP,              "too many symbolic links encountered") \
	XX(ENAMETOOLONG,       "name too long") \
	XX(EHOSTDOWN,          "host is down") \
	XX(EHOSTUNREACH,       "host is unreachable") \
	XX(ENOTEMPTY,          "directory not empty") \
	XX(ENOSYS,             "function not implemented") \
	XX(ECANCELED,          "operation canceled") \
	XX(EPROTO,             "protocol error") \

#define SP_EAI_ERRORS(XX) \
	XX(EAI_ADDRFAMILY,     "address family not supported") \
	XX(EAI_AGAIN,          "temporary failure") \
	XX(EAI_BADFLAGS,       "bad ai_flags value") \
	XX(EAI_CANCELED,       "request canceled") \
	XX(EAI_FAIL,           "permanent failure") \
	XX(EAI_FAMILY,         "ai_family not supported") \
	XX(EAI_MEMORY,         "out of memory") \
	XX(EAI_NODATA,         "no address") \
	XX(EAI_NONAME,         "unknown node or service") \
	XX(EAI_OVERFLOW,       "argument buffer overflow") \
	XX(EAI_SERVICE,        "service not available for socket type") \
	XX(EAI_SOCKTYPE,       "socket type not supported") \
	XX(EAI_BADHINTS,       "invalid value for hints") \
	XX(EAI_PROTOCOL,       "resolved protocol is unknown") \

#define SP_UTF8_ERRORS(XX) \
	XX(SP_UTF8_ESIZE,      "size of value exceeded maximum allowed") \
	XX(SP_UTF8_EESCAPE,    "invalid escape sequence") \
	XX(SP_UTF8_ECODEPOINT, "invalid code point") \
	XX(SP_UTF8_EENCODING,  "invalid encoding") \
	XX(SP_UTF8_ESURROGATE, "invalid surrogate pair") \
	XX(SP_UTF8_ETOOSHORT , "sequence is too short") \

#define SP_HTTP_ERRORS(XX) \
	XX(SP_HTTP_ESYNTAX,    "invalid syntax") \
	XX(SP_HTTP_ESIZE,      "size of value exceeded maximum allowed") \
	XX(SP_HTTP_ESTATE,     "parser state is invalid") \
	XX(SP_HTTP_ETOOSHORT,  "input is too short") \

#define SP_JSON_ERRORS(XX) \
	XX(SP_JSON_ESYNTAX,    "invalid syntax") \
	XX(SP_JSON_ESIZE,      "size of value exceeded maximum allowed") \
	XX(SP_JSON_ESTACK,     "stack size exceeded") \
	XX(SP_JSON_ESTATE,     "parser state is invalid") \
	XX(SP_JSON_EESCAPE,    "invalid escape sequence") \
	XX(SP_JSON_EBYTE,      "invalid byte value") \

#define SP_MSGPACK_ERRORS(XX) \
	XX(SP_MSGPACK_ESYNTAX, "invalid syntax") \
	XX(SP_MSGPACK_ESTACK,  "stack size exceeded") \

#define SP_LINE_ERRORS(XX) \
	XX(SP_LINE_ESYNTAX,    "invalid syntax") \
	XX(SP_LINE_ESIZE,      "size of value exceeded maximum allowed") \

#define SP_PATH_ERRORS(XX) \
	XX(SP_PATH_EBUFS,      "not enough buffer space available") \
	XX(SP_PATH_ENOTFOUND,  "executable not found") \

#define SP_URI_ERRORS(XX) \
	XX(SP_URI_ESYNTAX,     "invalid syntax") \
	XX(SP_URI_EBUFS,       "not enough buffer space available") \
	XX(SP_URI_ESEGMENT,    "invalid segment value") \
	XX(SP_URI_ERANGE,      "invalid segment range") \

#define FIX_CODE(n) do { \
	if ((n) > 0) {       \
		(n) = -(n);      \
	}                    \
} while (0)

static const char *nil_msg = "undefined error";

static const SpError **errors = NULL;
static size_t error_len = 0;
static size_t error_cap = 0;

static int
cmp_code (const void *key, const void *val)
{
	return (*(const SpError **)val)->code - *(const int *)key;
}

static int
cmp_err (const void *a, const void *b)
{
	return cmp_code (&(*(const SpError **)a)->code, b);
}

static inline void
sort_errors (void)
{
	qsort (errors, error_len, sizeof errors[0], cmp_err);
}

static const SpError *
create_error (int code, const char *domain, const char *name, const char *msg)
{
	size_t len = strlen (msg);
	SpError *new = calloc (1, sizeof *new + len);
	if (new != NULL) {
		new->code = code;
		strncpy (new->domain, domain, sizeof new->domain - 1);
		strncpy (new->name, name, sizeof new->name - 1);
		memcpy (new->msg, msg, len+1);
	}
	return new;
}

static bool
resize_errors (size_t hint)
{
	if (hint < error_cap) {
		return true;
	}

	hint = sp_power_of_2 (hint);

	const SpError **new = realloc (errors, sizeof *new * hint);
	if (new == NULL) {
		return false;
	}

	errors = new;
	error_cap = hint;

	return true;
}

static const SpError *
push_error (int code, const char *domain, const char *name, const char *msg)
{
	FIX_CODE (code);

	const SpError *err = create_error (code, domain, name, msg);
	if (err == NULL) {
		return NULL;
	}

	if (error_len == error_cap) {
		if (!resize_errors (error_len + 1)) {
			free ((void *)err);
			return false;
		}
	}

	errors[error_len++] = err;
	return err;
}

static void __attribute__((constructor))
init (void)
{
#define COUNT(sym, msg) +1
	resize_errors (2 * (0
		SP_SYSTEM_ERRORS(COUNT)
		SP_EAI_ERRORS(COUNT)
		SP_UTF8_ERRORS(COUNT)
		SP_HTTP_ERRORS(COUNT)
		SP_JSON_ERRORS(COUNT)
		SP_MSGPACK_ERRORS(COUNT)
		SP_PATH_ERRORS(COUNT)
		SP_URI_ERRORS(COUNT)
	));
#undef COUNT

#define PUSH_SYS(sym, msg) push_error (sym, "system", #sym, msg);
#define PUSH_EAI(sym, msg) push_error (SP_EAI_CODE(sym), "addrinfo", #sym, msg);
#define PUSH_UTF8(sym, msg) push_error (sym, "utf8", #sym, msg);
#define PUSH_HTTP(sym, msg) push_error (sym, "http", #sym, msg);
#define PUSH_JSON(sym, msg) push_error (sym, "json", #sym, msg);
#define PUSH_MSGPACK(sym, msg) push_error (sym, "msgpack", #sym, msg);
#define PUSH_PATH(sym, msg) push_error (sym, "path", #sym, msg);
#define PUSH_URI(sym, msg) push_error (sym, "uri", #sym, msg);
	SP_SYSTEM_ERRORS(PUSH_SYS)
	SP_EAI_ERRORS(PUSH_EAI)
	SP_UTF8_ERRORS(PUSH_UTF8)
	SP_HTTP_ERRORS(PUSH_HTTP)
	SP_JSON_ERRORS(PUSH_JSON)
	SP_MSGPACK_ERRORS(PUSH_MSGPACK)
	SP_PATH_ERRORS(PUSH_PATH)
	SP_URI_ERRORS(PUSH_URI)
#undef PUSH_SYS
#undef PUSH_EAI
#undef PUSH_UTF8
#undef PUSH_HTTP
#undef PUSH_JSON
#undef PUSH_MSGPACK
#undef PUSH_PATH
#undef PUSH_URI

	sort_errors ();
}

const char *
sp_strerror (int code)
{
	const SpError *err = sp_error (code);
	return err ? err->msg : nil_msg;
}

int
sp_eai_code (int err)
{
	return SP_EAI_CODE (err);
}

void
sp_error_print (int code, FILE *out)
{
	if (out == NULL) {
		out = stderr;
	}
	const SpError *err = sp_error (code);
	if (err == NULL) {
		fprintf (out, "%s (%d)\n", nil_msg, code);
	}
	else {
		fprintf (out, "%s error: %s (%s)\n", err->domain, err->msg, err->name);
	}
}

void
sp_exit (int code, int exitcode)
{
	sp_error_print (code, stderr);
	exit (exitcode);
}

static void __attribute__((always_inline))
stack_abort (char *buf, size_t len, size_t off)
{
	if (off < len - 1) {
		buf[off++] = '\n';
		size_t stack = sp_stack (buf+off, len - off);
		fwrite (buf, 1, off + stack, stderr);
	}
	abort ();
}

void
sp_abort (int code)
{
	char buf[1024];
	int len;

	const SpError *err = sp_error (code);
	if (err == NULL) {
		len = snprintf (buf, sizeof buf, "%s (%d)", nil_msg, code);
	}
	else {
		len = snprintf (buf, sizeof buf, "%s error: %s (%s)", err->domain, err->msg, err->name);
	}

	stack_abort (buf, sizeof buf, len);
}

void
sp_fabort (const char *fmt, ...)
{
	char buf[1024];

	va_list ap;
	int len;

	va_start(ap, fmt);
	len = vsnprintf (buf, sizeof buf, fmt, ap);
	va_end(ap);

	stack_abort (buf, sizeof buf, len);
}

const SpError *
sp_error (int code)
{
	FIX_CODE (code);

	const SpError **err;
	err = bsearch (&code, errors, error_len, sizeof errors[0], cmp_code);
	return err ? *err : NULL;
}

const SpError *
sp_error_next (const SpError *err)
{
	if (errors == NULL) {
		return NULL;
	}

	if (err == NULL) {
		return errors[0];
	}

	const SpError **pos;
	pos = bsearch (&err->code, errors, error_len, sizeof errors[0], cmp_code);

	if (pos && pos < errors+error_len) {
		return pos[1];
	}
	return NULL;
}

const SpError *
sp_error_add (int code, const char *domain, const char *name, const char *msg)
{
	FIX_CODE (code);

	if (code > SP_EUSER_MIN) {
		return NULL;
	}

	static SpLock lock = SP_LOCK_MAKE ();

	const SpError *err = NULL;
	if (sp_error (code) == NULL) {
		SP_LOCK (lock);
		err = push_error (code, domain, name, msg);
		if (err != NULL) {
			sort_errors ();
		}
		SP_UNLOCK (lock);
	}

	return err;
}

size_t __attribute__((always_inline))
sp_stack (char *buf, size_t len)
{
	char **strs = NULL;
	void *stack[32];
	int count = 0, i = 0;
	ssize_t total = 0;

	count = backtrace (stack, 32);
	strs = backtrace_symbols (stack, count);
	if (strs == NULL) {
		return 0;
	}

	for (i = 1; i < count; ++i) {
		size_t slen = strlen (strs[i]);
		if (slen > len - total - 3) {
			break;
		}
		memcpy (buf+total, "\t", 1);
		memcpy (buf+total+1, strs[i], slen);
		memcpy (buf+total+1+slen, "\n", 2);
		total += slen + 2;
	}

	free (strs);
	return total;
}

