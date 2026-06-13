/*
 * ============================================================================
 *  SYSTEM PROGRAMMING STUDY FILE - ALL PROGRAMS IN ONE FILE
 *  Covers: Threads | IPC | Synchronization | Scheduling | Atomics | Lock-free
 * ============================================================================
 *
 *  HOW TO COMPILE & RUN:
 *    gcc -Wall -Wextra -pthread -o sysprog sysprog_all.c -lrt
 *    ./sysprog              (runs all demos)
 *    ./sysprog threads      (run only the threads demo)
 *    ./sysprog ipc          (run only the IPC demos)
 *    ./sysprog sync         (synchronization)
 *    ./sysprog sched        (scheduling)
 *    ./sysprog atomic       (atomics & spinlock)
 *    ./sysprog ring         (ring buffer & mailbox)
 *    ./sysprog proc         (processes)
 *    ./sysprog signal       (interrupts & signals)
 *
 *  NOTES:
 *    - Linux/POSIX targeted (works on any modern Linux + glibc)
 *    - -pthread links the POSIX threads library
 *    - -lrt links the realtime library (POSIX message queues, shm_open)
 *    - Each section: Definition -> Key APIs -> Algorithm -> Example -> Code
 *
 *  SECTIONS:
 *    1. THREADS                  (create, join, detach, args, return values)
 *    2. IPC                      (pipe, FIFO, message queue, shared memory, socket)
 *    3. THREAD SYNCHRONIZATION   (mutex, semaphore, condition variable, rwlock, barrier)
 *    4. SCHEDULING & BEHAVIOR    (priority, policy, affinity, yield)
 *    5. ATOMICS & SPINLOCK       (atomic ops, memory order, spinlock, CAS)
 *    6. RING BUFFER & MAILBOX    (SPSC lock-free ring, mailbox with cond var)
 *    7. PROCESSES                (fork, exec, wait, zombie, orphan, daemon)
 *    8. INTERRUPTS & SIGNALS     (signal handlers, the userspace "interrupt")
 * ============================================================================
 */

#define _GNU_SOURCE          /* enable sched_setaffinity, pthread_setaffinity_np */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include <pthread.h>         /* threads, mutex, cond, rwlock, barrier, spinlock */
#include <semaphore.h>       /* POSIX semaphores */
#include <stdatomic.h>       /* C11 atomics */
#include <sched.h>           /* scheduling policies, affinity, yield */

#include <sys/types.h>
#include <sys/wait.h>        /* waitpid */
#include <sys/stat.h>        /* mkfifo, mode constants */
#include <fcntl.h>           /* O_* constants for open/mq_open/shm_open */

#include <sys/socket.h>      /* sockets */
#include <sys/un.h>          /* AF_UNIX socket address */
#include <mqueue.h>          /* POSIX message queue */
#include <sys/mman.h>        /* shm_open, mmap */

#include <signal.h>          /* signals: the userspace interrupt mechanism */
#include <setjmp.h>          /* non-local jumps (used in signal recovery demo) */

/* ============================================================================
 *  SECTION 1: THREADS (POSIX pthreads)
 * ============================================================================
 *
 *  WHAT IS A THREAD?
 *    A thread is the smallest unit of execution that the OS schedules.
 *    Threads of one process share the same address space (globals, heap,
 *    file descriptors) but each has its OWN stack and registers.
 *
 *  THREAD vs PROCESS:
 *    Process: isolated memory, expensive to create, IPC needed to share data.
 *    Thread:  shared memory, cheap to create, synchronization needed to
 *             avoid data races.
 *
 *  KEY APIS:
 *    pthread_create(&tid, attr, start_routine, arg)  -- spawn a thread
 *    pthread_join(tid, &retval)                       -- wait for + collect result
 *    pthread_detach(tid)                              -- auto-cleanup, no join
 *    pthread_self()                                   -- get own thread id
 *    pthread_exit(retval)                             -- terminate calling thread
 *
 *  A thread function MUST have signature:  void *func(void *arg);
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 1. Basic thread: create and join
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Define a worker function with signature void *(*)(void *)
 *   step2: pthread_create() spawns the thread, which starts running worker()
 *   step3: pthread_join() blocks until the thread finishes and collects its
 *          return value (passed via pthread_exit or return)
 *
 * Example flow:
 *   main thread        worker thread
 *   ----------         -------------
 *   create()  ------->  starts worker()
 *   join()    (blocks)  ... does work ...
 *             <-------  return result
 *   resumes with result
 * -------------------------------------------------------------------------- */
static void *worker_basic(void *arg) {
    int id = *(int *)arg;
    printf("  [thread] worker %d running (tid=%lu)\n",
           id, (unsigned long)pthread_self());
    int *result = malloc(sizeof(int));   /* heap so it outlives the thread */
    if (result) *result = id * 100;
    return result;                        /* returned to pthread_join */
}

/* --------------------------------------------------------------------------
 * 2. Multiple threads with per-thread arguments
 * --------------------------------------------------------------------------
 * TRAP: Each thread must get its OWN copy of the argument. A common bug is
 *       passing &i from a loop -- all threads then see the SAME (final) i.
 *       Fix: give each thread a separate slot in an array.
 * -------------------------------------------------------------------------- */
static void *worker_sum(void *arg) {
    long n = *(long *)arg;
    long sum = 0;
    for (long i = 1; i <= n; i++) sum += i;
    long *result = malloc(sizeof(long));
    if (result) *result = sum;
    return result;
}

static void *worker_detached(void *arg) {
    int id = *(int *)arg;
    printf("  [thread] detached worker %d running (tid=%lu)\n",
           id, (unsigned long)pthread_self());
    /* Detached threads are never joined, so their return value is discarded.
     * Therefore we must NOT allocate anything the caller would need to free.
     * Any cleanup must happen here, inside the thread itself. */
    return NULL;
}

void demo_threads(void) {
    printf("\n=== SECTION 1: THREADS ===\n");

    /* --- 1. Basic create + join --- */
    printf("1. Basic thread create/join:\n");
    pthread_t tid;
    int arg = 7;
    pthread_create(&tid, NULL, worker_basic, &arg);
    int *ret;
    pthread_join(tid, (void **)&ret);       /* wait + collect */
    printf("  [main] worker returned %d\n", ret ? *ret : -1);
    free(ret);

    /* --- 2. Multiple threads, separate args --- */
    printf("2. Multiple threads (parallel sum 1..n):\n");
    #define NT 4
    pthread_t tids[NT];
    long args[NT] = {10, 100, 1000, 10000};   /* each thread its OWN slot */
    for (int i = 0; i < NT; i++)
        pthread_create(&tids[i], NULL, worker_sum, &args[i]);
    for (int i = 0; i < NT; i++) {
        long *r;
        pthread_join(tids[i], (void **)&r);
        printf("  sum(1..%ld) = %ld\n", args[i], r ? *r : -1);
        free(r);
    }

    /* --- 3. Detached thread (no join needed; auto-cleanup) --- */
    printf("3. Detached thread:\n");
    pthread_t dtid;
    int darg = 42;
    pthread_create(&dtid, NULL, worker_detached, &darg);
    pthread_detach(dtid);                      /* resources auto-freed on exit */
    usleep(50000);                             /* give it time to run for demo */
    printf("  [main] detached thread launched (no join)\n");
    #undef NT
}

/* ============================================================================
 *  SECTION 2: INTER-PROCESS COMMUNICATION (IPC)
 * ============================================================================
 *
 *  WHY IPC?
 *    Separate processes have ISOLATED memory. To exchange data they need an
 *    OS-provided channel. Five classic mechanisms, from simplest to richest:
 *
 *    | Mechanism      | Direction | Scope            | Speed   | Use case        |
 *    |----------------|-----------|------------------|---------|-----------------|
 *    | pipe           | one-way   | related procs    | fast    | parent<->child  |
 *    | FIFO (named)   | one-way   | any procs        | fast    | unrelated procs |
 *    | message queue  | msgs      | any procs        | medium  | discrete msgs   |
 *    | shared memory  | R/W       | any procs        | fastest | bulk data       |
 *    | socket         | two-way   | any (+ network)  | medium  | client/server   |
 *
 *  KEY INSIGHT:
 *    Shared memory is FASTEST (no kernel copy) but needs separate
 *    synchronization. Pipes/queues/sockets COPY through the kernel but
 *    provide built-in synchronization (blocking read/write).
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 4. Anonymous Pipe (parent <-> child, one-way)
 * --------------------------------------------------------------------------
 * Definition:
 *   A pipe is a unidirectional byte stream with two ends:
 *     fd[0] = read end,  fd[1] = write end.
 *   Created BEFORE fork() so the child inherits the file descriptors.
 *
 * Algorithm:
 *   step1: pipe(fd) creates the pipe (fd[0]=read, fd[1]=write)
 *   step2: fork() -- child inherits both ends
 *   step3: Each side closes the end it doesn't use (good hygiene)
 *   step4: Writer writes to fd[1], reader reads from fd[0]
 *   step5: Reader sees EOF when all write ends are closed
 *
 * Example flow:
 *   parent: close(read), write "Hello" to fd[1], close(write)
 *   child:  close(write), read from fd[0] -> "Hello"
 * -------------------------------------------------------------------------- */
static void demo_pipe(void) {
    printf("4. Anonymous pipe (parent->child):\n");
    int fd[2];
    if (pipe(fd) == -1) { perror("  pipe"); return; }

    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); return; }

    if (pid == 0) {                       /* CHILD: reader */
        close(fd[1]);                     /* close unused write end */
        char buf[64] = {0};
        ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
        if (n > 0) printf("  [child] received: %s\n", buf);
        close(fd[0]);
        fflush(stdout);
        _exit(0);
    } else {                              /* PARENT: writer */
        close(fd[0]);                     /* close unused read end */
        const char *msg = "Hello from parent";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);                     /* signal EOF to child */
        waitpid(pid, NULL, 0);            /* reap child */
    }
}

/* --------------------------------------------------------------------------
 * 5. Named Pipe / FIFO (unrelated processes)
 * --------------------------------------------------------------------------
 * Definition:
 *   A FIFO is a pipe with a NAME in the filesystem (created by mkfifo).
 *   Unlike anonymous pipes, ANY two processes can open it by path -- they
 *   need not be related by fork.
 *
 * Algorithm:
 *   step1: mkfifo(path, mode) creates the special file
 *   step2: One process opens it O_WRONLY, another O_RDONLY
 *          (open blocks until BOTH ends are open)
 *   step3: write/read as with a normal pipe
 *   step4: unlink(path) removes it when done
 *
 * For the demo we fork so it runs self-contained, but the FIFO could be
 * opened by two completely separate programs.
 * -------------------------------------------------------------------------- */
static void demo_fifo(void) {
    printf("5. Named pipe / FIFO:\n");
    const char *path = "/tmp/sysprog_fifo";
    unlink(path);                         /* clean any stale FIFO */
    if (mkfifo(path, 0600) == -1) { perror("  mkfifo"); return; }

    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); unlink(path); return; }

    if (pid == 0) {                       /* CHILD: reader */
        int fd = open(path, O_RDONLY);    /* blocks until writer opens */
        char buf[64] = {0};
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) printf("  [child] FIFO received: %s\n", buf);
        close(fd);
        fflush(stdout);
        _exit(0);
    } else {                              /* PARENT: writer */
        int fd = open(path, O_WRONLY);    /* blocks until reader opens */
        const char *msg = "Hello via FIFO";
        write(fd, msg, strlen(msg));
        close(fd);
        waitpid(pid, NULL, 0);
        unlink(path);                     /* remove the FIFO file */
    }
}

/* --------------------------------------------------------------------------
 * 6. POSIX Message Queue (discrete messages, optional priority)
 * --------------------------------------------------------------------------
 * Definition:
 *   A message queue holds DISCRETE messages (not a byte stream). The kernel
 *   preserves message boundaries and can order by priority. Persists in the
 *   kernel until removed (mq_unlink) even if no process has it open.
 *
 * Key APIs (link with -lrt):
 *   mq_open(name, flags, mode, &attr)  -- create/open ("/name" format)
 *   mq_send(mq, buf, len, priority)    -- enqueue a message
 *   mq_receive(mq, buf, len, &prio)    -- dequeue highest-priority message
 *   mq_close / mq_unlink               -- close handle / destroy queue
 *
 * Algorithm:
 *   step1: Define mq_attr (max messages, max message size)
 *   step2: mq_open with O_CREAT
 *   step3: mq_send messages with priorities
 *   step4: mq_receive returns HIGHEST priority message first
 * -------------------------------------------------------------------------- */
static void demo_mqueue(void) {
    printf("6. POSIX message queue:\n");
    const char *name = "/sysprog_mq";
    struct mq_attr attr;
    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;                 /* max messages in queue */
    attr.mq_msgsize = 64;                 /* max bytes per message */
    attr.mq_curmsgs = 0;

    mq_unlink(name);                      /* clean stale queue */
    mqd_t mq = mq_open(name, O_CREAT | O_RDWR, 0600, &attr);
    if (mq == (mqd_t)-1) { perror("  mq_open"); return; }

    /* Send three messages with different priorities */
    mq_send(mq, "low priority",  12, 1);
    mq_send(mq, "high priority", 13, 9);  /* higher prio dequeued first */
    mq_send(mq, "mid priority",  12, 5);

    /* Receive: kernel returns HIGHEST priority first */
    for (int i = 0; i < 3; i++) {
        char buf[64] = {0};
        unsigned int prio;
        ssize_t n = mq_receive(mq, buf, sizeof(buf), &prio);
        if (n >= 0) printf("  received (prio %u): %s\n", prio, buf);
    }

    mq_close(mq);
    mq_unlink(name);                      /* destroy the queue */
}

/* --------------------------------------------------------------------------
 * 7. Shared Memory (fastest IPC - zero-copy)
 * --------------------------------------------------------------------------
 * Definition:
 *   Two processes map the SAME physical memory pages into their address
 *   spaces. Reads/writes are direct memory accesses -- no kernel copy, so
 *   this is the FASTEST IPC. BUT: you must provide your own synchronization
 *   (mutex/semaphore) because there is no built-in ordering.
 *
 * Key APIs (link with -lrt):
 *   shm_open(name, flags, mode)   -- create/open a shared memory object
 *   ftruncate(fd, size)           -- set its size
 *   mmap(...)                     -- map it into the address space
 *   munmap / close / shm_unlink   -- cleanup
 *
 * Algorithm:
 *   step1: shm_open creates a named shared region
 *   step2: ftruncate sizes it
 *   step3: mmap maps it (MAP_SHARED so changes are visible to other procs)
 *   step4: fork -- child inherits the mapping
 *   step5: One process writes, the other reads the SAME memory
 *
 * Here we use a simple flag + busy-wait for synchronization (real code
 * should use a process-shared semaphore -- see section 3).
 * -------------------------------------------------------------------------- */
typedef struct {
    volatile int ready;                   /* simple handshake flag */
    int value;
} SharedData;

static void demo_shared_memory(void) {
    printf("7. Shared memory (zero-copy IPC):\n");
    const char *name = "/sysprog_shm";
    shm_unlink(name);

    int fd = shm_open(name, O_CREAT | O_RDWR, 0600);
    if (fd == -1) { perror("  shm_open"); return; }
    if (ftruncate(fd, sizeof(SharedData)) == -1) { perror("  ftruncate"); close(fd); return; }

    SharedData *shm = mmap(NULL, sizeof(SharedData),
                           PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm == MAP_FAILED) { perror("  mmap"); close(fd); return; }
    shm->ready = 0;

    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid == 0) {                       /* CHILD: writer */
        shm->value = 12345;               /* write directly to shared mem */
        shm->ready = 1;                   /* signal data is ready */
        munmap(shm, sizeof(SharedData));
        fflush(stdout);
        _exit(0);
    } else {                              /* PARENT: reader */
        while (!shm->ready) usleep(1000); /* wait for child (busy-wait demo) */
        printf("  [parent] read shared value: %d\n", shm->value);
        waitpid(pid, NULL, 0);
        munmap(shm, sizeof(SharedData));
        close(fd);
        shm_unlink(name);
    }
}

/* --------------------------------------------------------------------------
 * 8. Unix Domain Socket (two-way, local client/server)
 * --------------------------------------------------------------------------
 * Definition:
 *   A socket is a BIDIRECTIONAL endpoint. Unix domain sockets (AF_UNIX) work
 *   between processes on the same machine; switch to AF_INET for network.
 *   Unlike pipes, sockets are full-duplex and support a connection model.
 *
 * Key APIs:
 *   socket(domain, type, proto)   -- create endpoint
 *   bind(fd, addr, len)           -- server: assign an address
 *   listen(fd, backlog)           -- server: mark as accepting
 *   accept(fd, ...)               -- server: take next connection
 *   connect(fd, addr, len)        -- client: connect to server
 *   send / recv                   -- exchange data both ways
 *
 * Algorithm (stream socket, SOCK_STREAM):
 *   SERVER: socket -> bind -> listen -> accept -> recv/send
 *   CLIENT: socket -> connect -> send/recv
 * -------------------------------------------------------------------------- */
static void demo_socket(void) {
    printf("8. Unix domain socket (client/server):\n");
    const char *path = "/tmp/sysprog_sock";
    unlink(path);

    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); return; }

    if (pid == 0) {                       /* CHILD: client */
        usleep(50000);                    /* let server bind first */
        int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
        struct sockaddr_un addr = {0};
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
        if (connect(cfd, (struct sockaddr *)&addr, sizeof(addr)) == 0) {
            const char *msg = "ping from client";
            send(cfd, msg, strlen(msg), 0);
            char buf[64] = {0};
            ssize_t n = recv(cfd, buf, sizeof(buf) - 1, 0);
            if (n > 0) printf("  [client] got reply: %s\n", buf);
        }
        close(cfd);
        fflush(stdout);
        _exit(0);
    } else {                              /* PARENT: server */
        int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        struct sockaddr_un addr = {0};
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
        bind(sfd, (struct sockaddr *)&addr, sizeof(addr));
        listen(sfd, 1);
        int conn = accept(sfd, NULL, NULL);     /* blocks for client */
        if (conn >= 0) {
            char buf[64] = {0};
            ssize_t n = recv(conn, buf, sizeof(buf) - 1, 0);
            if (n > 0) printf("  [server] got: %s\n", buf);
            const char *reply = "pong from server";
            send(conn, reply, strlen(reply), 0);
            close(conn);
        }
        close(sfd);
        waitpid(pid, NULL, 0);
        unlink(path);
    }
}

void demo_ipc(void) {
    printf("\n=== SECTION 2: IPC ===\n");
    demo_pipe();
    demo_fifo();
    demo_mqueue();
    demo_shared_memory();
    demo_socket();
}

/* ============================================================================
 *  SECTION 3: THREAD SYNCHRONIZATION
 * ============================================================================
 *
 *  THE PROBLEM - DATA RACE:
 *    When two threads access the SAME memory and at least one writes, without
 *    ordering the result is undefined. Example: counter++ is actually
 *    READ-MODIFY-WRITE (load, add, store). Two threads can both load the same
 *    value, both add 1, both store -- losing one increment.
 *
 *  THE TOOLS:
 *    | Primitive        | Purpose                                         |
 *    |------------------|-------------------------------------------------|
 *    | mutex            | mutual exclusion - one thread in critical sec   |
 *    | semaphore        | counting permit - allow N concurrent           |
 *    | condition var    | wait for a condition / signal an event          |
 *    | rwlock           | many readers OR one writer                      |
 *    | barrier          | all threads wait until everyone arrives         |
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 9. The Data Race (demonstration of the problem)
 * --------------------------------------------------------------------------
 * Without locking, counter++ from many threads loses updates.
 * Expected NT*ITERS, but you typically get less.
 * -------------------------------------------------------------------------- */
#define SYNC_NT    4
#define SYNC_ITERS 100000

static long g_unsafe_counter = 0;
static long g_safe_counter   = 0;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *race_unsafe(void *arg) {
    (void)arg;
    for (int i = 0; i < SYNC_ITERS; i++) {
        /* Force a separate load-modify-store so the race is visible.
         * (A bare counter++ may compile to one instruction on some CPUs
         * and hide the race; the volatile temp widens the race window.) */
        volatile long tmp = g_unsafe_counter;
        tmp = tmp + 1;
        g_unsafe_counter = tmp;           /* DATA RACE: lost updates */
    }
    return NULL;
}

/* --------------------------------------------------------------------------
 * 10. Mutex (Mutual Exclusion)
 * --------------------------------------------------------------------------
 * Definition:
 *   A mutex is a lock that only ONE thread can hold at a time. Code between
 *   lock and unlock is the "critical section" -- guaranteed exclusive.
 *
 * Key APIs:
 *   pthread_mutex_init / PTHREAD_MUTEX_INITIALIZER
 *   pthread_mutex_lock(&m)     -- blocks until acquired
 *   pthread_mutex_trylock(&m)  -- non-blocking attempt
 *   pthread_mutex_unlock(&m)   -- release
 *   pthread_mutex_destroy(&m)
 *
 * Algorithm (safe counter):
 *   step1: lock the mutex (others now block)
 *   step2: do the read-modify-write in the critical section
 *   step3: unlock (one waiting thread proceeds)
 *
 * TRAP: Always unlock on every exit path. Holding a lock too long kills
 *       concurrency; forgetting to unlock causes deadlock.
 * -------------------------------------------------------------------------- */
static void *race_safe(void *arg) {
    (void)arg;
    for (int i = 0; i < SYNC_ITERS; i++) {
        pthread_mutex_lock(&g_mutex);     /* enter critical section */
        g_safe_counter++;                 /* protected: no lost updates */
        pthread_mutex_unlock(&g_mutex);   /* leave critical section */
    }
    return NULL;
}

/* --------------------------------------------------------------------------
 * 11. Semaphore (Counting Permit)
 * --------------------------------------------------------------------------
 * Definition:
 *   A semaphore holds a count of available "permits".
 *     sem_wait  decrements (blocks if count == 0)
 *     sem_post  increments (wakes a waiter)
 *   - Binary semaphore (count 1) acts like a lock.
 *   - Counting semaphore (count N) allows up to N concurrent holders --
 *     ideal for limiting access to a pool of N resources.
 *
 * Key APIs:
 *   sem_init(&sem, pshared, initial_count)
 *   sem_wait(&sem)   -- P operation (acquire/decrement)
 *   sem_post(&sem)   -- V operation (release/increment)
 *   sem_destroy(&sem)
 *
 * Example: a semaphore initialized to 2 lets at most 2 threads into a
 * region at once (e.g. limiting concurrent DB connections).
 * -------------------------------------------------------------------------- */
static sem_t g_sem;
static int   g_concurrent = 0;        /* how many threads are "inside" now */
static int   g_max_seen   = 0;        /* peak concurrency observed */
static pthread_mutex_t g_track_mtx = PTHREAD_MUTEX_INITIALIZER;

static void *sem_worker(void *arg) {
    int id = *(int *)arg;
    sem_wait(&g_sem);                 /* acquire a permit (at most 2 inside) */

    pthread_mutex_lock(&g_track_mtx);
    g_concurrent++;
    if (g_concurrent > g_max_seen) g_max_seen = g_concurrent;
    pthread_mutex_unlock(&g_track_mtx);

    usleep(20000);                    /* simulate work inside the region */

    pthread_mutex_lock(&g_track_mtx);
    g_concurrent--;
    pthread_mutex_unlock(&g_track_mtx);

    sem_post(&g_sem);                 /* release the permit */
    (void)id;
    return NULL;
}

/* --------------------------------------------------------------------------
 * 12. Condition Variable (wait for an event)
 * --------------------------------------------------------------------------
 * Definition:
 *   A condition variable lets a thread SLEEP until another thread signals
 *   that some condition became true -- without busy-waiting (spinning).
 *   ALWAYS used together with a mutex protecting the shared condition.
 *
 * Key APIs:
 *   pthread_cond_wait(&cond, &mutex)   -- atomically unlock+sleep; relock on wake
 *   pthread_cond_signal(&cond)         -- wake ONE waiter
 *   pthread_cond_broadcast(&cond)      -- wake ALL waiters
 *
 * Algorithm (consumer waiting for producer):
 *   CONSUMER: lock -> while(!ready) cond_wait -> consume -> unlock
 *   PRODUCER: lock -> set ready=1 -> cond_signal -> unlock
 *
 * TRAP: Always re-check the predicate in a WHILE loop, not an if --
 *       spurious wakeups and multiple waiters require re-checking.
 * -------------------------------------------------------------------------- */
static pthread_mutex_t g_cv_mtx  = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_cv_cond = PTHREAD_COND_INITIALIZER;
static int             g_cv_ready = 0;
static int             g_cv_data  = 0;

static void *cv_consumer(void *arg) {
    (void)arg;
    pthread_mutex_lock(&g_cv_mtx);
    while (!g_cv_ready)                       /* WHILE, not if! */
        pthread_cond_wait(&g_cv_cond, &g_cv_mtx);  /* sleep until signalled */
    printf("  [consumer] got data: %d\n", g_cv_data);
    pthread_mutex_unlock(&g_cv_mtx);
    return NULL;
}

static void *cv_producer(void *arg) {
    (void)arg;
    usleep(30000);                            /* simulate production delay */
    pthread_mutex_lock(&g_cv_mtx);
    g_cv_data  = 999;
    g_cv_ready = 1;
    pthread_cond_signal(&g_cv_cond);          /* wake the consumer */
    pthread_mutex_unlock(&g_cv_mtx);
    return NULL;
}

/* --------------------------------------------------------------------------
 * 13. Read-Write Lock (many readers OR one writer)
 * --------------------------------------------------------------------------
 * Definition:
 *   Optimizes the common case of frequent reads, rare writes. Multiple
 *   threads may hold the READ lock simultaneously, but the WRITE lock is
 *   exclusive (no readers, no other writers).
 *
 * Key APIs:
 *   pthread_rwlock_rdlock(&rw)   -- shared read lock
 *   pthread_rwlock_wrlock(&rw)   -- exclusive write lock
 *   pthread_rwlock_unlock(&rw)
 *
 * Use when reads vastly outnumber writes (config tables, caches).
 * -------------------------------------------------------------------------- */
static pthread_rwlock_t g_rwlock = PTHREAD_RWLOCK_INITIALIZER;
static int g_shared_config = 100;

static void *rw_reader(void *arg) {
    int id = *(int *)arg;
    pthread_rwlock_rdlock(&g_rwlock);     /* shared - many readers at once */
    printf("  [reader %d] config = %d\n", id, g_shared_config);
    usleep(5000);
    pthread_rwlock_unlock(&g_rwlock);
    return NULL;
}

static void *rw_writer(void *arg) {
    (void)arg;
    pthread_rwlock_wrlock(&g_rwlock);     /* exclusive - blocks all readers */
    g_shared_config += 1;
    printf("  [writer] updated config to %d\n", g_shared_config);
    pthread_rwlock_unlock(&g_rwlock);
    return NULL;
}

/* --------------------------------------------------------------------------
 * 14. Barrier (rendezvous - all wait for all)
 * --------------------------------------------------------------------------
 * Definition:
 *   A barrier makes every participating thread WAIT until a fixed number of
 *   threads have all reached the barrier. Then they all proceed together.
 *   Used in phased parallel computation (e.g. all threads finish phase 1
 *   before any starts phase 2).
 *
 * Key APIs:
 *   pthread_barrier_init(&b, attr, count)  -- count threads must arrive
 *   pthread_barrier_wait(&b)               -- block until all arrive
 * -------------------------------------------------------------------------- */
static pthread_barrier_t g_barrier;

static void *barrier_worker(void *arg) {
    int id = *(int *)arg;
    printf("  [worker %d] phase 1 done, waiting at barrier\n", id);
    pthread_barrier_wait(&g_barrier);     /* all wait here */
    printf("  [worker %d] phase 2 starting (all synced)\n", id);
    return NULL;
}

void demo_sync(void) {
    printf("\n=== SECTION 3: THREAD SYNCHRONIZATION ===\n");

    /* --- 9 & 10. Data race vs mutex-protected counter --- */
    printf("9/10. Data race vs mutex (expect %d):\n", SYNC_NT * SYNC_ITERS);
    pthread_t t[SYNC_NT];
    g_unsafe_counter = 0;
    for (int i = 0; i < SYNC_NT; i++) pthread_create(&t[i], NULL, race_unsafe, NULL);
    for (int i = 0; i < SYNC_NT; i++) pthread_join(t[i], NULL);
    printf("  UNSAFE counter = %ld (lost updates due to race)\n", g_unsafe_counter);

    g_safe_counter = 0;
    for (int i = 0; i < SYNC_NT; i++) pthread_create(&t[i], NULL, race_safe, NULL);
    for (int i = 0; i < SYNC_NT; i++) pthread_join(t[i], NULL);
    printf("  SAFE counter   = %ld (mutex-protected, correct)\n", g_safe_counter);

    /* --- 11. Counting semaphore limits concurrency to 2 --- */
    printf("11. Counting semaphore (max 2 concurrent of 5 threads):\n");
    sem_init(&g_sem, 0, 2);               /* 2 permits */
    g_concurrent = g_max_seen = 0;
    pthread_t st[5]; int sid[5];
    for (int i = 0; i < 5; i++) { sid[i] = i; pthread_create(&st[i], NULL, sem_worker, &sid[i]); }
    for (int i = 0; i < 5; i++) pthread_join(st[i], NULL);
    printf("  peak concurrency observed = %d (capped at 2)\n", g_max_seen);
    sem_destroy(&g_sem);

    /* --- 12. Condition variable producer/consumer --- */
    printf("12. Condition variable (consumer waits for producer):\n");
    g_cv_ready = 0;
    pthread_t cons, prod;
    pthread_create(&cons, NULL, cv_consumer, NULL);
    pthread_create(&prod, NULL, cv_producer, NULL);
    pthread_join(cons, NULL);
    pthread_join(prod, NULL);

    /* --- 13. Read-write lock --- */
    printf("13. Read-write lock (3 readers + 1 writer):\n");
    pthread_t rt[3], wt; int rid[3];
    for (int i = 0; i < 3; i++) { rid[i] = i; pthread_create(&rt[i], NULL, rw_reader, &rid[i]); }
    pthread_create(&wt, NULL, rw_writer, NULL);
    for (int i = 0; i < 3; i++) pthread_join(rt[i], NULL);
    pthread_join(wt, NULL);

    /* --- 14. Barrier --- */
    printf("14. Barrier (3 threads rendezvous):\n");
    pthread_barrier_init(&g_barrier, NULL, 3);
    pthread_t bt[3]; int bid[3];
    for (int i = 0; i < 3; i++) { bid[i] = i; pthread_create(&bt[i], NULL, barrier_worker, &bid[i]); }
    for (int i = 0; i < 3; i++) pthread_join(bt[i], NULL);
    pthread_barrier_destroy(&g_barrier);
}

/* ============================================================================
 *  SECTION 4: SCHEDULING & THREAD BEHAVIOR
 * ============================================================================
 *
 *  HOW THE OS SCHEDULES THREADS:
 *    The kernel scheduler decides which thread runs on which CPU and for how
 *    long. Each thread has a SCHEDULING POLICY and a PRIORITY.
 *
 *  POLICIES (Linux):
 *    SCHED_OTHER  -- default time-sharing (CFS). "nice" value affects share.
 *    SCHED_FIFO   -- realtime, run-to-completion within priority, no timeslice
 *    SCHED_RR     -- realtime round-robin, like FIFO but with timeslices
 *    SCHED_BATCH  -- for non-interactive CPU-bound batch work
 *    SCHED_IDLE   -- runs only when nothing else wants the CPU
 *
 *  KEY CONCEPTS:
 *    - Priority: higher-priority realtime threads preempt lower ones.
 *    - Affinity: pin a thread to a specific CPU core (cache locality, RT).
 *    - Yield: voluntarily give up the CPU to another ready thread.
 *
 *  NOTE: SCHED_FIFO/RR require privileges (root or CAP_SYS_NICE). The demo
 *        below shows the API; it falls back gracefully if not permitted.
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 15. Query current scheduling policy and priority
 * --------------------------------------------------------------------------
 * Key APIs:
 *   sched_getscheduler(pid)              -- returns the policy
 *   sched_get_priority_min/max(policy)   -- valid priority range
 *   pthread_getschedparam(tid, &pol, &param)
 * -------------------------------------------------------------------------- */
static const char *policy_name(int policy) {
    switch (policy) {
        case SCHED_OTHER: return "SCHED_OTHER (time-sharing/CFS)";
        case SCHED_FIFO:  return "SCHED_FIFO (realtime FIFO)";
        case SCHED_RR:    return "SCHED_RR (realtime round-robin)";
        case SCHED_BATCH: return "SCHED_BATCH";
        case SCHED_IDLE:  return "SCHED_IDLE";
        default:          return "unknown";
    }
}

static void show_scheduling_info(void) {
    int policy = sched_getscheduler(0);   /* 0 = calling process */
    printf("  current policy: %s\n", policy_name(policy));
    printf("  SCHED_OTHER priority range: [%d, %d]\n",
           sched_get_priority_min(SCHED_OTHER), sched_get_priority_max(SCHED_OTHER));
    printf("  SCHED_FIFO  priority range: [%d, %d]\n",
           sched_get_priority_min(SCHED_FIFO),  sched_get_priority_max(SCHED_FIFO));
    printf("  SCHED_RR    priority range: [%d, %d]\n",
           sched_get_priority_min(SCHED_RR),    sched_get_priority_max(SCHED_RR));
}

/* --------------------------------------------------------------------------
 * 16. Try to set a realtime scheduling policy on a thread
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Build sched_param with desired priority
 *   step2: pthread_setschedparam(tid, SCHED_FIFO, &param)
 *   step3: If it fails with EPERM, we lack privileges -- report gracefully
 *
 * Key APIs:
 *   pthread_setschedparam(tid, policy, &param)
 *   pthread_attr_setschedpolicy / setschedparam / setinheritsched
 * -------------------------------------------------------------------------- */
static void try_set_realtime(void) {
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    int rc = pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    if (rc == 0) {
        printf("  set SCHED_FIFO priority %d (have privileges)\n", param.sched_priority);
        /* restore default so the rest of the program behaves normally */
        struct sched_param def = { .sched_priority = 0 };
        pthread_setschedparam(pthread_self(), SCHED_OTHER, &def);
    } else {
        printf("  could not set SCHED_FIFO (rc=%d: %s) -- needs root/CAP_SYS_NICE\n",
               rc, strerror(rc));
    }
}

/* --------------------------------------------------------------------------
 * 17. CPU Affinity (pin a thread to specific cores)
 * --------------------------------------------------------------------------
 * Definition:
 *   Affinity restricts which CPU cores a thread may run on. Pinning improves
 *   cache locality and is essential for deterministic realtime behavior.
 *
 * Key APIs:
 *   CPU_ZERO(&set), CPU_SET(cpu, &set)
 *   pthread_setaffinity_np(tid, sizeof(set), &set)
 *   pthread_getaffinity_np(tid, sizeof(set), &set)
 *   sched_getcpu()  -- which CPU am I running on right now?
 * -------------------------------------------------------------------------- */
static void demo_affinity(void) {
    long ncpu = sysconf(_SC_NPROCESSORS_ONLN);
    printf("  online CPUs: %ld\n", ncpu);

    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);                     /* pin to CPU 0 */
    int rc = pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
    if (rc == 0) {
        /* give the scheduler a moment to migrate us */
        sched_yield();
        printf("  pinned to CPU 0; now running on CPU %d\n", sched_getcpu());
        /* restore: allow all CPUs again */
        CPU_ZERO(&set);
        for (long i = 0; i < ncpu; i++) CPU_SET(i, &set);
        pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
    } else {
        printf("  could not set affinity (rc=%d: %s)\n", rc, strerror(rc));
    }
}

/* --------------------------------------------------------------------------
 * 18. sched_yield (voluntarily give up the CPU)
 * --------------------------------------------------------------------------
 * Definition:
 *   sched_yield() tells the scheduler "I have nothing urgent; run someone
 *   else." The thread stays READY but goes to the back of its run queue.
 *   Useful in spin-wait loops to reduce wasted cycles (though a proper
 *   condition variable is usually better).
 * -------------------------------------------------------------------------- */
static void demo_yield(void) {
    printf("  calling sched_yield() 3 times...\n");
    for (int i = 0; i < 3; i++) sched_yield();
    printf("  yielded CPU voluntarily (cooperative hint to scheduler)\n");
}

/* --------------------------------------------------------------------------
 * 19. nice value (priority hint for SCHED_OTHER threads)
 * --------------------------------------------------------------------------
 * Definition:
 *   For ordinary (SCHED_OTHER) threads, the "nice" value (-20 highest
 *   priority .. +19 lowest) biases the CFS scheduler's CPU share. Lower
 *   nice = more CPU. Lowering below 0 needs privileges.
 * -------------------------------------------------------------------------- */
static void demo_nice(void) {
    errno = 0;
    int cur = nice(0);                    /* read current nice (0 delta) */
    if (errno == 0)
        printf("  current nice value: %d (range -20..19, lower = more CPU)\n", cur);
}

void demo_scheduling(void) {
    printf("\n=== SECTION 4: SCHEDULING & THREAD BEHAVIOR ===\n");
    printf("15. Scheduling info:\n");
    show_scheduling_info();
    printf("16. Realtime policy attempt:\n");
    try_set_realtime();
    printf("17. CPU affinity:\n");
    demo_affinity();
    printf("18. Yield:\n");
    demo_yield();
    printf("19. Nice value:\n");
    demo_nice();
}

/* ============================================================================
 *  SECTION 5: ATOMICS & SPINLOCK
 * ============================================================================
 *
 *  WHY ATOMICS?
 *    A mutex involves the kernel (sleep/wake) -- expensive for tiny critical
 *    sections. Atomics perform an operation that the CPU guarantees is
 *    indivisible (single instruction, no interruption) WITHOUT a kernel call.
 *    Perfect for counters, flags, and lock-free data structures.
 *
 *  C11 ATOMICS (<stdatomic.h>):
 *    atomic_int, atomic_long, atomic_bool, _Atomic(T)
 *    atomic_fetch_add / sub / or / and / xor   -- read-modify-write, returns old
 *    atomic_load / atomic_store                 -- atomic read / write
 *    atomic_compare_exchange_weak/strong (CAS)  -- the universal primitive
 *
 *  MEMORY ORDER (advanced but critical):
 *    memory_order_relaxed  -- atomicity only, no ordering (counters)
 *    memory_order_acquire  -- no later reads/writes move before this load
 *    memory_order_release  -- no earlier reads/writes move after this store
 *    memory_order_seq_cst  -- total global order (default, safest, slowest)
 *
 *  COMPARE-AND-SWAP (CAS) - the heart of lock-free programming:
 *    "If the value is still what I expect, swap in my new value, atomically."
 *    Loop on CAS until it succeeds = optimistic concurrency.
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 20. Atomic counter (lock-free, no mutex)
 * --------------------------------------------------------------------------
 * Definition:
 *   atomic_fetch_add increments without a lock. The CPU guarantees no two
 *   threads lose an update -- compare to the data race in section 3.
 *
 * Algorithm:
 *   Each thread loops calling atomic_fetch_add(&counter, 1).
 *   Final value is ALWAYS exactly NT * ITERS (no lost updates).
 * -------------------------------------------------------------------------- */
#define ATOM_NT    4
#define ATOM_ITERS 100000

static atomic_long g_atomic_counter = 0;

static void *atomic_inc_worker(void *arg) {
    (void)arg;
    for (int i = 0; i < ATOM_ITERS; i++)
        atomic_fetch_add(&g_atomic_counter, 1);   /* lock-free increment */
    return NULL;
}

/* --------------------------------------------------------------------------
 * 21. Spinlock (busy-wait lock built from an atomic flag)
 * --------------------------------------------------------------------------
 * Definition:
 *   A spinlock is a lock where a waiting thread SPINS (busy-loops) instead of
 *   sleeping. No kernel involvement -> extremely low latency when the lock is
 *   held only briefly. BUT it wastes CPU while spinning, so only use for very
 *   short critical sections and never when a thread could hold it long.
 *
 * Algorithm (test-and-set spinlock via CAS):
 *   LOCK:   spin while atomic_exchange(&flag, 1) returns 1 (was already held)
 *   UNLOCK: atomic_store(&flag, 0)
 *
 * The acquire/release memory orders ensure the critical section's memory
 * operations are correctly ordered relative to the lock.
 *
 * COMPARISON:
 *   Mutex:    sleeps if contended  -> good for long/contended sections
 *   Spinlock: spins if contended   -> good for very short sections on SMP
 * -------------------------------------------------------------------------- */
typedef struct {
    atomic_flag flag;            /* atomic_flag is the only lock-free guaranteed type */
} spinlock_t;

static void spin_lock(spinlock_t *s) {
    /* atomic_flag_test_and_set returns previous value; spin while it was set */
    while (atomic_flag_test_and_set_explicit(&s->flag, memory_order_acquire)) {
        /* optional: __builtin_ia32_pause() / sched_yield() to be nice */
    }
}
static void spin_unlock(spinlock_t *s) {
    atomic_flag_clear_explicit(&s->flag, memory_order_release);
}

static spinlock_t g_spin = { ATOMIC_FLAG_INIT };
static long g_spin_counter = 0;

static void *spin_worker(void *arg) {
    (void)arg;
    for (int i = 0; i < ATOM_ITERS; i++) {
        spin_lock(&g_spin);
        g_spin_counter++;        /* protected by spinlock */
        spin_unlock(&g_spin);
    }
    return NULL;
}

/* --------------------------------------------------------------------------
 * 22. Compare-And-Swap (CAS) - lock-free maximum
 * --------------------------------------------------------------------------
 * Definition:
 *   CAS atomically does: if (*ptr == expected) { *ptr = desired; return true; }
 *   else { expected = *ptr; return false; }
 *   It is the universal building block for lock-free algorithms.
 *
 * Example: atomically update a shared max without a lock.
 *   step1: read current max into 'expected'
 *   step2: if our value isn't bigger, done
 *   step3: try CAS(max, expected, our value)
 *   step4: if CAS fails (someone else changed max), retry with new expected
 * -------------------------------------------------------------------------- */
static atomic_int g_atomic_max = 0;

static void atomic_update_max(int value) {
    int expected = atomic_load(&g_atomic_max);
    while (value > expected) {
        /* try to install 'value'; if max changed, expected gets refreshed */
        if (atomic_compare_exchange_weak(&g_atomic_max, &expected, value))
            break;                /* success */
        /* else: expected now holds the current value; loop re-checks */
    }
}

static void *cas_max_worker(void *arg) {
    int base = *(int *)arg;
    for (int i = 0; i < 1000; i++)
        atomic_update_max(base + i);
    return NULL;
}

void demo_atomic(void) {
    printf("\n=== SECTION 5: ATOMICS & SPINLOCK ===\n");

    /* --- 20. Atomic counter --- */
    printf("20. Atomic counter (lock-free, expect %d):\n", ATOM_NT * ATOM_ITERS);
    atomic_store(&g_atomic_counter, 0);
    pthread_t t[ATOM_NT];
    for (int i = 0; i < ATOM_NT; i++) pthread_create(&t[i], NULL, atomic_inc_worker, NULL);
    for (int i = 0; i < ATOM_NT; i++) pthread_join(t[i], NULL);
    printf("  atomic counter = %ld (always exact, no lock)\n",
           atomic_load(&g_atomic_counter));

    /* --- 21. Spinlock --- */
    printf("21. Spinlock-protected counter (expect %d):\n", ATOM_NT * ATOM_ITERS);
    g_spin_counter = 0;
    for (int i = 0; i < ATOM_NT; i++) pthread_create(&t[i], NULL, spin_worker, NULL);
    for (int i = 0; i < ATOM_NT; i++) pthread_join(t[i], NULL);
    printf("  spinlock counter = %ld (correct, busy-wait)\n", g_spin_counter);

    /* --- 22. CAS lock-free max --- */
    printf("22. Lock-free max via CAS:\n");
    atomic_store(&g_atomic_max, 0);
    pthread_t mt[3]; int mbase[3] = {0, 500, 1500};
    for (int i = 0; i < 3; i++) pthread_create(&mt[i], NULL, cas_max_worker, &mbase[i]);
    for (int i = 0; i < 3; i++) pthread_join(mt[i], NULL);
    printf("  final max = %d (expected 2499)\n", atomic_load(&g_atomic_max));
}

/* ============================================================================
 *  SECTION 6: RING BUFFER & MAILBOX
 * ============================================================================
 *
 *  RING BUFFER (circular buffer / FIFO queue):
 *    A fixed-size array used as a queue with head (read) and tail (write)
 *    indices that wrap around modulo capacity. The backbone of:
 *      - ISR-to-task data passing in firmware
 *      - audio/network packet buffering
 *      - logging pipelines
 *
 *  SPSC LOCK-FREE RING (Single Producer, Single Consumer):
 *    With exactly ONE producer and ONE consumer, a ring buffer needs NO lock.
 *    The producer owns 'head', the consumer owns 'tail'; atomic loads/stores
 *    with acquire/release ordering make it safe and very fast. This is the
 *    classic embedded ISR<->main-loop pattern.
 *
 *  MAILBOX:
 *    A mailbox is a synchronized single-slot (or small-queue) message handoff
 *    between threads. A thread can POST a message and another can FETCH it,
 *    blocking until one is available -- built from a mutex + condition var.
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 23. SPSC Lock-Free Ring Buffer
 * --------------------------------------------------------------------------
 * Definition:
 *   Capacity must be a power of 2 so wrap = index & (cap-1) is a cheap mask.
 *   We keep one slot empty to distinguish full from empty without a count:
 *     EMPTY when head == tail
 *     FULL  when (head+1) & mask == tail
 *
 * Algorithm (push, producer side):
 *   step1: load head (relaxed - we own it) and tail (acquire - see consumer)
 *   step2: if next head == tail, buffer is FULL -> reject
 *   step3: write data at slot[head]
 *   step4: store head = next (release - publishes the write to consumer)
 *
 * Algorithm (pop, consumer side):
 *   step1: load tail (relaxed - we own it) and head (acquire - see producer)
 *   step2: if head == tail, buffer is EMPTY -> nothing to read
 *   step3: read data at slot[tail]
 *   step4: store tail = next (release)
 *
 * Why acquire/release? They create a happens-before relationship so the
 * consumer never reads a slot before the producer's write is visible.
 * -------------------------------------------------------------------------- */
#define RING_CAP 8                         /* power of 2 */
#define RING_MASK (RING_CAP - 1)

typedef struct {
    int data[RING_CAP];
    _Atomic unsigned head;                 /* producer writes here (next free) */
    _Atomic unsigned tail;                 /* consumer reads here (next item) */
} SPSCRing;

static void ring_init(SPSCRing *r) {
    atomic_store(&r->head, 0);
    atomic_store(&r->tail, 0);
}

static bool ring_push(SPSCRing *r, int value) {
    unsigned head = atomic_load_explicit(&r->head, memory_order_relaxed);
    unsigned next = (head + 1) & RING_MASK;
    unsigned tail = atomic_load_explicit(&r->tail, memory_order_acquire);
    if (next == tail) return false;        /* full */
    r->data[head] = value;
    atomic_store_explicit(&r->head, next, memory_order_release);
    return true;
}

static bool ring_pop(SPSCRing *r, int *out) {
    unsigned tail = atomic_load_explicit(&r->tail, memory_order_relaxed);
    unsigned head = atomic_load_explicit(&r->head, memory_order_acquire);
    if (head == tail) return false;        /* empty */
    *out = r->data[tail];
    atomic_store_explicit(&r->tail, (tail + 1) & RING_MASK, memory_order_release);
    return true;
}

static SPSCRing g_ring;
#define RING_ITEMS 20

static void *ring_producer(void *arg) {
    (void)arg;
    int produced = 0;
    while (produced < RING_ITEMS) {
        if (ring_push(&g_ring, produced)) produced++;
        else sched_yield();                /* full: let consumer drain */
    }
    return NULL;
}

static void *ring_consumer(void *arg) {
    (void)arg;
    long *sum = malloc(sizeof(long));
    *sum = 0;
    int got = 0, value;
    while (got < RING_ITEMS) {
        if (ring_pop(&g_ring, &value)) { *sum += value; got++; }
        else sched_yield();                /* empty: let producer fill */
    }
    return sum;
}

/* --------------------------------------------------------------------------
 * 24. Mailbox (blocking message handoff, mutex + condition variable)
 * --------------------------------------------------------------------------
 * Definition:
 *   A mailbox holds up to CAP messages. POST blocks if full; FETCH blocks if
 *   empty. Unlike the lock-free ring, this supports MULTIPLE producers and
 *   consumers and blocks cleanly instead of busy-spinning.
 *
 * Algorithm (post):
 *   lock -> while(full) wait(not_full) -> enqueue -> signal(not_empty) -> unlock
 * Algorithm (fetch):
 *   lock -> while(empty) wait(not_empty) -> dequeue -> signal(not_full) -> unlock
 *
 * This is the textbook bounded-buffer producer/consumer solution.
 * -------------------------------------------------------------------------- */
#define MBOX_CAP 4

typedef struct {
    int             slots[MBOX_CAP];
    int             count;                 /* number of messages held */
    int             in, out;               /* circular indices */
    pthread_mutex_t mtx;
    pthread_cond_t  not_full;
    pthread_cond_t  not_empty;
} Mailbox;

static void mbox_init(Mailbox *m) {
    m->count = m->in = m->out = 0;
    pthread_mutex_init(&m->mtx, NULL);
    pthread_cond_init(&m->not_full, NULL);
    pthread_cond_init(&m->not_empty, NULL);
}
static void mbox_destroy(Mailbox *m) {
    pthread_mutex_destroy(&m->mtx);
    pthread_cond_destroy(&m->not_full);
    pthread_cond_destroy(&m->not_empty);
}

static void mbox_post(Mailbox *m, int msg) {
    pthread_mutex_lock(&m->mtx);
    while (m->count == MBOX_CAP)            /* WHILE guards spurious wakeups */
        pthread_cond_wait(&m->not_full, &m->mtx);
    m->slots[m->in] = msg;
    m->in = (m->in + 1) % MBOX_CAP;
    m->count++;
    pthread_cond_signal(&m->not_empty);    /* wake a fetcher */
    pthread_mutex_unlock(&m->mtx);
}

static int mbox_fetch(Mailbox *m) {
    pthread_mutex_lock(&m->mtx);
    while (m->count == 0)
        pthread_cond_wait(&m->not_empty, &m->mtx);
    int msg = m->slots[m->out];
    m->out = (m->out + 1) % MBOX_CAP;
    m->count--;
    pthread_cond_signal(&m->not_full);     /* wake a poster */
    pthread_mutex_unlock(&m->mtx);
    return msg;
}

static Mailbox g_mbox;
#define MBOX_MSGS 10

static void *mbox_producer(void *arg) {
    (void)arg;
    for (int i = 1; i <= MBOX_MSGS; i++) mbox_post(&g_mbox, i);
    return NULL;
}
static void *mbox_consumer(void *arg) {
    (void)arg;
    long *sum = malloc(sizeof(long));
    *sum = 0;
    for (int i = 0; i < MBOX_MSGS; i++) *sum += mbox_fetch(&g_mbox);
    return sum;
}

void demo_ring(void) {
    printf("\n=== SECTION 6: RING BUFFER & MAILBOX ===\n");

    /* --- 23. SPSC lock-free ring --- */
    printf("23. SPSC lock-free ring buffer (produce 0..%d):\n", RING_ITEMS - 1);
    ring_init(&g_ring);
    pthread_t prod, cons;
    pthread_create(&prod, NULL, ring_producer, NULL);
    pthread_create(&cons, NULL, ring_consumer, NULL);
    pthread_join(prod, NULL);
    long *rsum;
    pthread_join(cons, (void **)&rsum);
    printf("  consumer sum = %ld (expected %d)\n",
           rsum ? *rsum : -1, RING_ITEMS * (RING_ITEMS - 1) / 2);
    free(rsum);

    /* --- 24. Mailbox (blocking, mutex + cond var) --- */
    printf("24. Mailbox (bounded buffer, %d msgs through cap-%d box):\n",
           MBOX_MSGS, MBOX_CAP);
    mbox_init(&g_mbox);
    pthread_t mp, mc;
    pthread_create(&mp, NULL, mbox_producer, NULL);
    pthread_create(&mc, NULL, mbox_consumer, NULL);
    pthread_join(mp, NULL);
    long *msum;
    pthread_join(mc, (void **)&msum);
    printf("  consumer sum = %ld (expected %d)\n",
           msum ? *msum : -1, MBOX_MSGS * (MBOX_MSGS + 1) / 2);
    free(msum);
    mbox_destroy(&g_mbox);
}

/* ============================================================================
 *  SECTION 7: PROCESSES
 * ============================================================================
 *
 *  WHAT IS A PROCESS?
 *    A process is a running program with its OWN isolated address space,
 *    file descriptor table, and process ID (PID). Unlike threads (which share
 *    memory), processes are isolated -- a crash in one cannot corrupt another.
 *
 *  PROCESS vs THREAD:
 *    Process: isolated memory, own PID, heavier to create, needs IPC to share.
 *    Thread:  shares the process's memory, lighter, needs locks to share.
 *
 *  THE LIFECYCLE APIS:
 *    fork()    -- duplicate the current process (child is a near-exact copy)
 *    exec*()   -- REPLACE the current process image with a new program
 *    wait()/waitpid() -- parent collects a child's exit status (reaps it)
 *    exit()/_exit()   -- terminate a process
 *    getpid()/getppid()-- own PID / parent's PID
 *
 *  THE fork+exec PATTERN (how shells launch programs):
 *    fork() to make a child, then the child calls exec() to become the new
 *    program, while the parent waits. This is THE Unix process-creation idiom.
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 25. fork() - duplicate a process
 * --------------------------------------------------------------------------
 * Definition:
 *   fork() creates a new (child) process that is a copy of the parent. It
 *   returns TWICE:
 *     - in the PARENT: returns the child's PID (> 0)
 *     - in the CHILD:  returns 0
 *     - on failure:    returns -1
 *
 * Algorithm:
 *   step1: call fork()
 *   step2: branch on the return value to run parent vs child code
 *   step3: parent waits for child with waitpid() to avoid a zombie
 *
 * Example flow:
 *   pid = fork()
 *   if (pid == 0)  -> child code path
 *   else           -> parent code path, then waitpid(pid)
 *
 * KEY: after fork, both processes have SEPARATE copies of memory. Changing a
 *      variable in the child does NOT affect the parent (copy-on-write).
 * -------------------------------------------------------------------------- */
static void demo_fork(void) {
    printf("25. fork() - process duplication:\n");
    int shared_value = 100;               /* each process gets its own copy */

    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); return; }

    if (pid == 0) {                       /* CHILD */
        shared_value += 50;               /* only the child's copy changes */
        printf("  [child]  pid=%d ppid=%d value=%d\n",
               getpid(), getppid(), shared_value);
        fflush(stdout);                   /* _exit skips flush, so flush manually */
        _exit(0);                         /* _exit: no atexit/flush in child */
    } else {                              /* PARENT */
        waitpid(pid, NULL, 0);            /* wait so child prints first */
        printf("  [parent] pid=%d value=%d (unchanged - separate memory)\n",
               getpid(), shared_value);
    }
}

/* --------------------------------------------------------------------------
 * 26. fork + exec - launch a different program
 * --------------------------------------------------------------------------
 * Definition:
 *   exec*() family REPLACES the current process image with a new program.
 *   The PID stays the same, but the code, data, and stack are all replaced.
 *   If exec succeeds it NEVER returns; if it returns, it failed.
 *
 * Variants:
 *   execl  / execlp  -- args as a list, 'p' searches PATH
 *   execv  / execvp  -- args as a vector (array), 'p' searches PATH
 *   execve           -- the actual syscall (vector + environment)
 *
 * Algorithm (run "/bin/echo hello"):
 *   step1: fork()
 *   step2: child calls execlp("echo", "echo", "hello from exec", NULL)
 *   step3: parent waitpid()s for the child to finish
 *
 * Example flow:
 *   parent: fork -> waitpid
 *   child:  execlp replaces itself with /bin/echo, which prints and exits
 * -------------------------------------------------------------------------- */
static void demo_exec(void) {
    printf("26. fork + exec - run an external program:\n");
    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); return; }

    if (pid == 0) {                       /* CHILD: become 'echo' */
        printf("  [child] about to exec /bin/echo...\n");
        fflush(stdout);
        execlp("echo", "echo", "  [echo]  hello from exec'd program", (char *)NULL);
        /* only reached if exec FAILS */
        perror("  execlp");
        fflush(stdout);
        _exit(127);                       /* 127 = command not found convention */
    } else {                              /* PARENT */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("  [parent] child exited with code %d\n", WEXITSTATUS(status));
    }
}

/* --------------------------------------------------------------------------
 * 27. Exit status and waitpid (reaping children correctly)
 * --------------------------------------------------------------------------
 * Definition:
 *   When a child exits, the kernel keeps a small record (exit status) until
 *   the parent collects it with wait/waitpid. The macros decode the status:
 *     WIFEXITED(status)   -- did it exit normally?
 *     WEXITSTATUS(status) -- the exit code (0-255)
 *     WIFSIGNALED(status) -- was it killed by a signal?
 *     WTERMSIG(status)    -- which signal killed it
 *
 * Algorithm:
 *   step1: child exits with a specific code (e.g. exit(3))
 *   step2: parent waitpid()s and decodes status with the W* macros
 * -------------------------------------------------------------------------- */
static void demo_exit_status(void) {
    printf("27. Exit status decoding:\n");
    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); return; }

    if (pid == 0) {                       /* CHILD: exit with code 3 */
        fflush(stdout);
        _exit(3);
    } else {                              /* PARENT: decode it */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("  child exited normally, code = %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("  child killed by signal %d\n", WTERMSIG(status));
    }
}

/* --------------------------------------------------------------------------
 * 28. Zombie and Orphan processes (what to avoid / understand)
 * --------------------------------------------------------------------------
 * Definitions:
 *   ZOMBIE: a child that has exited but whose status has NOT been collected
 *           by the parent. It occupies a slot in the process table (a
 *           "defunct" entry). FIX: always wait()/waitpid() for your children.
 *
 *   ORPHAN: a child whose parent exited first. The orphan is "adopted" by
 *           init/systemd (PID 1), which reaps it automatically. Orphans are
 *           normal and harmless (this is how daemons detach).
 *
 * We demonstrate the CORRECT pattern (reap promptly) and explain the bad one
 * in comments -- we never intentionally leak a zombie.
 * -------------------------------------------------------------------------- */
static void demo_zombie_orphan(void) {
    printf("28. Zombie / orphan avoidance:\n");
    printf("  ZOMBIE  = child exited but parent never wait()ed (table leak)\n");
    printf("  ORPHAN  = parent died first; init (PID 1) adopts and reaps it\n");

    /* Demonstrate the CORRECT fix: prompt reaping prevents zombies. */
    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid == 0) {                       /* CHILD exits immediately */
        fflush(stdout);
        _exit(0);
    } else {
        waitpid(pid, NULL, 0);            /* prompt reap -> no zombie */
        printf("  child reaped promptly -> no zombie created\n");
    }
}

void demo_processes(void) {
    printf("\n=== SECTION 7: PROCESSES ===\n");
    demo_fork();
    demo_exec();
    demo_exit_status();
    demo_zombie_orphan();
}

/* ============================================================================
 *  SECTION 8: INTERRUPTS & SIGNALS
 * ============================================================================
 *
 *  WHAT IS A SIGNAL? (the userspace "interrupt")
 *    A signal is an asynchronous notification delivered to a process to tell
 *    it that an event occurred. It is the userspace analogue of a HARDWARE
 *    INTERRUPT: normal execution is suspended, a handler runs, then execution
 *    resumes. In embedded firmware you write an ISR; in Linux userspace you
 *    write a signal handler -- the concept is the same.
 *
 *  HARDWARE INTERRUPT vs SIGNAL (the analogy):
 *    | Hardware interrupt (MCU)      | POSIX signal (Linux userspace)     |
 *    |-------------------------------|------------------------------------|
 *    | IRQ line asserts              | kernel delivers a signal           |
 *    | CPU vectors to an ISR         | process vectors to a handler       |
 *    | ISR must be short, no blocking| handler must be async-signal-safe  |
 *    | use 'volatile' for shared var | use 'volatile sig_atomic_t'        |
 *    | return from interrupt (RTI)   | handler returns, execution resumes |
 *
 *  COMMON SIGNALS:
 *    SIGINT  (2)  -- interrupt from keyboard (Ctrl-C)
 *    SIGTERM (15) -- polite termination request
 *    SIGKILL (9)  -- forced kill (cannot be caught or ignored)
 *    SIGSEGV (11) -- invalid memory access
 *    SIGALRM (14) -- timer expired (alarm)
 *    SIGUSR1/2    -- user-defined signals
 *    SIGCHLD      -- a child process changed state (exited)
 *
 *  KEY APIS:
 *    sigaction(signum, &act, &old)  -- install a handler (preferred over signal())
 *    kill(pid, signum)              -- send a signal to a process
 *    raise(signum)                  -- send a signal to self
 *    alarm(seconds)                 -- schedule a SIGALRM
 *    sigprocmask / pthread_sigmask  -- block/unblock signals (mask)
 *
 *  ASYNC-SIGNAL-SAFETY (critical rule):
 *    A handler may interrupt the program at ANY point -- even in the middle of
 *    malloc or printf. So a handler may ONLY call "async-signal-safe" functions
 *    (write() is safe; printf/malloc are NOT). The usual pattern: the handler
 *    just sets a 'volatile sig_atomic_t' flag, and the main loop acts on it.
 * ============================================================================ */

/* Shared flag written by the handler, read by the main loop.
 * 'volatile sig_atomic_t' is the ONLY type guaranteed safe to share with a
 * signal handler -- exactly like 'volatile' for an ISR-shared variable. */
static volatile sig_atomic_t g_sigint_count  = 0;
static volatile sig_atomic_t g_sigusr1_fired = 0;
static volatile sig_atomic_t g_sigalrm_fired = 0;

/* --------------------------------------------------------------------------
 * 29. Basic signal handler with sigaction
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: write a handler  void handler(int signo)  that ONLY sets a flag
 *   step2: fill a struct sigaction with the handler
 *   step3: sigaction(SIGUSR1, &act, NULL) installs it
 *   step4: when the signal arrives, the handler runs, sets the flag, returns
 *   step5: the main loop polls the flag and reacts safely
 *
 * Why sigaction over signal()? signal() has portability quirks; sigaction
 * gives reliable, well-defined semantics and finer control (masks, flags).
 * -------------------------------------------------------------------------- */
static void handle_sigusr1(int signo) {
    (void)signo;
    g_sigusr1_fired = 1;                  /* ONLY set a flag (async-safe) */
}

static void demo_signal_basic(void) {
    printf("29. Basic signal handler (SIGUSR1):\n");
    struct sigaction act = {0};
    act.sa_handler = handle_sigusr1;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, NULL);       /* install handler */

    g_sigusr1_fired = 0;
    raise(SIGUSR1);                       /* send SIGUSR1 to ourselves */
    /* handler has run by now; poll the flag */
    if (g_sigusr1_fired)
        printf("  handler caught SIGUSR1 (flag set, handled in main loop)\n");
}

/* --------------------------------------------------------------------------
 * 30. Counting signals (SIGINT / Ctrl-C style)
 * --------------------------------------------------------------------------
 * Demonstrates a handler that counts events. In a real program this is how
 * you'd catch Ctrl-C to do graceful shutdown instead of dying instantly.
 * -------------------------------------------------------------------------- */
static void handle_sigint(int signo) {
    (void)signo;
    g_sigint_count++;                     /* count the interrupts */
}

static void demo_signal_count(void) {
    printf("30. Counting signals (simulated Ctrl-C):\n");
    struct sigaction act = {0};
    act.sa_handler = handle_sigint;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);

    g_sigint_count = 0;
    raise(SIGINT);                        /* simulate 3 Ctrl-C presses */
    raise(SIGINT);
    raise(SIGINT);
    printf("  caught SIGINT %d times (would trigger graceful shutdown)\n",
           (int)g_sigint_count);

    /* restore default so a real Ctrl-C still works afterwards */
    signal(SIGINT, SIG_DFL);
}

/* --------------------------------------------------------------------------
 * 31. alarm() and SIGALRM (a software timer interrupt)
 * --------------------------------------------------------------------------
 * Definition:
 *   alarm(seconds) asks the kernel to deliver SIGALRM after the given delay.
 *   This is a software timer -- the userspace analogue of a hardware timer
 *   interrupt firing periodically in firmware.
 *
 * Algorithm:
 *   step1: install a SIGALRM handler
 *   step2: alarm(1) schedules the signal 1 second out
 *   step3: pause() sleeps until ANY signal arrives
 *   step4: handler sets the flag; main loop sees it
 * -------------------------------------------------------------------------- */
static void handle_sigalrm(int signo) {
    (void)signo;
    g_sigalrm_fired = 1;
}

static void demo_signal_alarm(void) {
    printf("31. alarm() / SIGALRM (software timer interrupt):\n");
    struct sigaction act = {0};
    act.sa_handler = handle_sigalrm;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    g_sigalrm_fired = 0;
    alarm(1);                             /* fire SIGALRM in 1 second */
    printf("  waiting for timer (1s)...\n");
    while (!g_sigalrm_fired) pause();     /* sleep until a signal arrives */
    printf("  timer fired -- SIGALRM handled\n");
}

/* --------------------------------------------------------------------------
 * 32. Sending a signal to another process with kill()
 * --------------------------------------------------------------------------
 * Definition:
 *   kill(pid, sig) sends signal 'sig' to process 'pid' despite its name, it
 *   sends ANY signal, not just lethal ones. This is how processes notify each
 *   other of events (a form of IPC).
 *
 * Algorithm:
 *   step1: fork a child that installs a SIGUSR1 handler and waits
 *   step2: parent sends kill(child, SIGUSR1)
 *   step3: child's handler runs, child reports and exits
 * -------------------------------------------------------------------------- */
static volatile sig_atomic_t g_child_got_signal = 0;
static void child_sig_handler(int signo) {
    (void)signo;
    g_child_got_signal = 1;
}

static void demo_signal_kill(void) {
    printf("32. kill() - send a signal to another process:\n");
    fflush(stdout);  /* flush before fork: avoid duplicated buffered output */
    pid_t pid = fork();
    if (pid < 0) { perror("  fork"); return; }

    if (pid == 0) {                       /* CHILD: wait for SIGUSR1 */
        struct sigaction act = {0};
        act.sa_handler = child_sig_handler;
        sigemptyset(&act.sa_mask);
        sigaction(SIGUSR1, &act, NULL);
        /* wait (up to ~1s) for the signal */
        for (int i = 0; i < 100 && !g_child_got_signal; i++) usleep(10000);
        if (g_child_got_signal)
            printf("  [child] received SIGUSR1 from parent\n");
        fflush(stdout);
        _exit(g_child_got_signal ? 0 : 1);
    } else {                              /* PARENT: send the signal */
        usleep(50000);                    /* let child install handler first */
        kill(pid, SIGUSR1);               /* send the signal */
        int status;
        waitpid(pid, &status, 0);
        printf("  [parent] sent SIGUSR1; child exit code %d\n",
               WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    }
}

/* --------------------------------------------------------------------------
 * 33. Blocking signals with a mask (critical sections)
 * --------------------------------------------------------------------------
 * Definition:
 *   Sometimes you must protect a critical section from being interrupted by
 *   a signal -- exactly like DISABLING INTERRUPTS around a critical section
 *   in firmware. sigprocmask() blocks (defers) signals; they are delivered
 *   once you unblock.
 *
 * Algorithm:
 *   step1: build a signal set containing SIGUSR1
 *   step2: sigprocmask(SIG_BLOCK, &set, &old) -- defer it
 *   step3: do the critical work (signal stays pending, not lost)
 *   step4: sigprocmask(SIG_SETMASK, &old, NULL) -- unblock; pending delivered
 *
 * This is the userspace equivalent of cli()/sti() (disable/enable IRQ).
 * -------------------------------------------------------------------------- */
static void demo_signal_mask(void) {
    printf("33. Signal masking (defer signals = disable interrupts):\n");
    struct sigaction act = {0};
    act.sa_handler = handle_sigusr1;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);
    g_sigusr1_fired = 0;

    sigset_t set, old;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, &old);   /* "disable" SIGUSR1 */

    raise(SIGUSR1);                       /* signal becomes PENDING, not lost */
    printf("  SIGUSR1 sent while blocked -> deferred (fired=%d)\n",
           (int)g_sigusr1_fired);         /* still 0: handler hasn't run */

    sigprocmask(SIG_SETMASK, &old, NULL); /* "enable" -> pending delivered now */
    printf("  after unblocking -> delivered (fired=%d)\n",
           (int)g_sigusr1_fired);         /* now 1: handler ran */
}

void demo_signals(void) {
    printf("\n=== SECTION 8: INTERRUPTS & SIGNALS ===\n");
    demo_signal_basic();
    demo_signal_count();
    demo_signal_alarm();
    demo_signal_kill();
    demo_signal_mask();
}

/* ============================================================================
 *  MAIN - DEMO DRIVER
 * ============================================================================ */
int main(int argc, char *argv[]) {
    const char *which = (argc > 1) ? argv[1] : "all";

    if (!strcmp(which, "all") || !strcmp(which, "threads")) demo_threads();
    if (!strcmp(which, "all") || !strcmp(which, "ipc"))     demo_ipc();
    if (!strcmp(which, "all") || !strcmp(which, "sync"))    demo_sync();
    if (!strcmp(which, "all") || !strcmp(which, "sched"))   demo_scheduling();
    if (!strcmp(which, "all") || !strcmp(which, "atomic"))  demo_atomic();
    if (!strcmp(which, "all") || !strcmp(which, "ring"))    demo_ring();
    if (!strcmp(which, "all") || !strcmp(which, "proc"))    demo_processes();
    if (!strcmp(which, "all") || !strcmp(which, "signal"))  demo_signals();

    printf("\n=== ALL DEMOS COMPLETE ===\n");
    return 0;
}
