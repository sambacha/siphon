#include "../include/siphon/common.h"
#include "../lib/lock.h"
#include "mu.h"

#include <pthread.h>

static void
test_lock (void)
{
	SpLock m = SP_LOCK_MAKE ();

	mu_fassert (SP_TRY_LOCK (m));
	mu_fassert (!SP_TRY_LOCK (m));
	SP_UNLOCK (m);
	mu_fassert (SP_TRY_LOCK (m));
}

static uint64_t bits = 0;
SpLock bit_lock = SP_LOCK_MAKE ();

static void *
mark_bit (void *val)
{
	uint64_t mask = 1 << (uintptr_t)val;

	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec = 1000000;

	SP_LOCK (bit_lock);

	mu_fassert_uint_eq (bits, 0);
	__sync_fetch_and_or (&bits, mask);
	nanosleep (&delay, NULL);
	__sync_fetch_and_and (&bits, ~mask);

	SP_UNLOCK (bit_lock);

	return NULL;
}

static void
test_lock_threads (void)
{
	pthread_t threads[64];
	for (uintptr_t i = 0; i < sp_len (threads); i++) {
		int rc = pthread_create (&threads[i], NULL, mark_bit, (void *)i);
		mu_fassert_int_eq (rc, 0);
	}

	for (uintptr_t i = 0; i < sp_len (threads); i++) {
		int rc = pthread_join (threads[i], NULL);
		mu_fassert_int_eq (rc, 0);
	}
	mu_assert_int_eq (bits, 0);
}

static void
test_rw_writer (void)
{
	SpRWLock rw = SP_RWLOCK_MAKE ();
	mu_fassert (SP_TRY_WLOCK (rw));
	mu_fassert (!SP_TRY_WLOCK (rw));
	mu_fassert (!SP_TRY_RLOCK (rw));
	SP_WUNLOCK (rw);
	mu_fassert (SP_TRY_WLOCK (rw));
}

static void
test_rw_readers (void)
{
	SpRWLock rw = SP_RWLOCK_MAKE ();

	mu_fassert (SP_TRY_RLOCK (rw));
	mu_fassert (SP_TRY_RLOCK (rw));
	mu_fassert (!SP_TRY_WLOCK (rw));
	SP_RUNLOCK (rw);
	mu_fassert (!SP_TRY_WLOCK (rw));
	SP_RUNLOCK (rw);
	mu_fassert (SP_TRY_WLOCK (rw));
}

#define READER_LOOP 15
#define WRITER_LOOP 10

static SpRWLock rw_lock = SP_RWLOCK_MAKE ();
static int *writer_count = NULL;
static int reader_count = 0;

static void *
writer_thread (void *nr)
{
	(void)nr;
	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec = 1000000;

	for (int n = 0; n < WRITER_LOOP; ++n) {
		SP_WLOCK (rw_lock);
		int *new = malloc (sizeof *new);
		mu_fassert_ptr_ne (new, NULL);
		*new = writer_count ? *writer_count + 1 : 1;
		nanosleep (&delay, NULL);
		free (writer_count);
		writer_count = new;
		SP_WUNLOCK (rw_lock);
	}

	return NULL;
}

static void *
reader_thread (void *nr)
{
	(void)nr;

	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec = 1000000;

	for (int n = 0; n < READER_LOOP; ++n) {
		SP_RLOCK (rw_lock);
		nanosleep (&delay, NULL);
		__sync_fetch_and_add (&reader_count, 1);
		SP_RUNLOCK (rw_lock);
	}

	return NULL;
}

static void
test_rw_threads (void)
{
	pthread_t readers[15];
	pthread_t writers[15];

	for (uintptr_t n = 0; n < sp_len (readers); ++n) {
		int rc = pthread_create (&readers[n], NULL, writer_thread, (void *)n);
		mu_fassert_int_eq (rc, 0);
	}

	for (uintptr_t n = 0; n < sp_len (writers); ++n) {
		int rc = pthread_create (&writers[n], NULL, reader_thread, (void *)n);
		mu_fassert_int_eq (rc, 0);
	}

	for (uintptr_t n = 0; n < sp_len (readers); ++n) {
		int rc = pthread_join (readers[n], NULL);
		mu_fassert_int_eq (rc, 0);
	}

	for (uintptr_t n = 0; n < sp_len (writers); ++n) {
		int rc = pthread_join (writers[n], NULL);
		mu_fassert_int_eq (rc, 0);
	}

	mu_fassert_ptr_ne (writer_count, NULL);
	mu_fassert_int_eq (*writer_count, sp_len (writers) * WRITER_LOOP);
	mu_fassert_int_eq (reader_count, sp_len (readers) * READER_LOOP);
}

int
main (void)
{
	mu_init ("lock");

	test_lock ();
	test_lock_threads ();

	test_rw_writer ();
	test_rw_readers ();
	test_rw_threads ();
}

