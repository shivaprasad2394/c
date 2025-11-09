# LSP (Low-level System Programming) Interview Preparation Guide

## Quick Reference: Code Examples for All Topics

This guide contains practical C examples for every concept you need to master.

---

## 1. MESSAGE QUEUE

**Concept**: A buffer (queue) where processes can place and retrieve messages asynchronously.

**Analogy**: Think of it like a postal mailbox. Process A leaves a letter (message) in the mailbox, and Process B picks it up later. They don't need to meet or synchronize - the mailbox stores the message until someone needs it.

**Key Features**:
- FIFO ordering :-messages are handled in the order in which they are placed in the queue. The first message that arrives will be the first to be picked up.
- Messages can be typed (retrieved by type, not just order):-Messages can have types (e.g., "email", "notification", "warning"). Process B can choose to only retrieve messages of a certain type if desired, making it easier to filter out unnecessary messages.
- Kernel-managed buffer:-it manages the message queue, ensuring that messages are stored safely and that processes can interact with it efficiently. it knows when a letter arrives and keeps track of when it gets picked up.
- Asynchronous communication:-sending and receiving processes do not need to be synchronized or communicate directly. Process A doesn’t need to know when Process B will pick up the message

**C Code Example**:

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long mtype;      // message type
    char mtext[100]; // message data
};

int main() {
    // Create/access message queue with key 1234
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    
    // Sender: put message in queue
    struct message msg;
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from Process A");
    msgsnd(msgid, &msg, sizeof(msg), 0);
    
    // Receiver: get message from queue
    struct message recv_msg;
    msgrcv(msgid, &recv_msg, sizeof(recv_msg), 1, 0);
    printf("Received: %s\n", recv_msg.mtext);
    
    return 0;
}
//lately using posix
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <pthread.h>
#include <unistd.h>

#define QUEUE_NAME "/typed_message_queue"
#define MAX_MSG_SIZE sizeof(struct message)
#define QUEUE_SIZE 10

// Define a message structure with ID and type
struct message {
    int msg_id;       // unique message ID
    int msg_type;     // message type (can be used for filtering)
    char data[80];    // actual message text
};

// Message queue descriptor
mqd_t mq;

// Sender thread
void *senderTask(void *param) {
    struct message msg;

    msg.msg_id = 1;
    msg.msg_type = 42;
    strcpy(msg.data, "Hello from Process A");

    while (1) {
        // Use msg_type as POSIX priority (0–31)
        if (mq_send(mq, (const char *)&msg, sizeof(msg), msg.msg_type) == -1) {
            perror("mq_send failed");
        } else {
            printf("Sent: [ID=%d, Type=%d] %s\n", msg.msg_id, msg.msg_type, msg.data);
        }

        sleep(1); // 1s delay
    }
    return NULL;
}

// Receiver thread
void *receiverTask(void *param) {
    struct message recv_msg;
    unsigned int priority;

    while (1) {
        ssize_t bytes_read = mq_receive(mq, (char *)&recv_msg, sizeof(recv_msg), &priority);
        if (bytes_read >= 0) {
            printf("Received: [ID=%d, Type=%d, Priority=%u] %s\n",
                   recv_msg.msg_id, recv_msg.msg_type, priority, recv_msg.data);
        } else {
            perror("mq_receive failed");
        }
    }
    return NULL;
}

int main(void) {
    // Queue attributes
    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = QUEUE_SIZE,
        .mq_msgsize = MAX_MSG_SIZE,
        .mq_curmsgs = 0
    };

    // Create/open the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("Failed to create/open message queue");
        return 1;
    }

    // Create sender & receiver threads
    pthread_t senderThread, receiverThread;
    pthread_create(&senderThread, NULL, senderTask, NULL);
    pthread_create(&receiverThread, NULL, receiverTask, NULL);

    pthread_join(senderThread, NULL);
    pthread_join(receiverThread, NULL);

    // Cleanup
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}

```

---

## 2. SHARED MEMORY

**Concept**: Two processes attach to the same memory segment and communicate by reading/writing to it.

**Analogy**: Like two people sharing a whiteboard in a room. Both can read and write on it directly. It's faster than passing notes (message queues) but requires coordination to avoid conflicts.

**Key Features**:
- Fastest IPC method (no data copying)
- Requires synchronization (mutex/semaphore) to prevent race conditions
- Persistent in system until explicitly deleted
- Uses shmget(), shmat(), shmdt()

**C Code Example**:

```c
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    // Create shared memory segment: 1024 bytes, key 5678
    int shmid = shmget((key_t)5678, 1024, 0666 | IPC_CREAT);
    
    // Attach to shared memory
    char *shared_mem = (char *) shmat(shmid, NULL, 0);
    
    // Write data
    strcpy(shared_mem, "Data written to shared memory");
    
    // Read data
    printf("Data: %s\n", shared_mem);
    
    // Detach from shared memory
    shmdt(shared_mem);
    
    // Delete shared memory (optional)
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
```

---

## 3. PIPES (Named and Unnamed)

### Unnamed Pipes

**Concept**: One-way communication channel between parent and child process (or sibling processes).

**Analogy**: Like a water pipe - water flows one way. Parent writes, child reads (or vice versa).

**Key Features**:
- Unidirectional (one-way)
- Short-lived (disappears when processes die)
- Default: parent-child communication
- File descriptors: [0] = read, [1] = write

**C Code Example - Unnamed Pipe**:

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0] = read, fd[1] = write
    char buffer[100];
    
    // Create pipe
    pipe(fd);
    
    pid_t pid = fork();
    
    if (pid == 0) { // Child process
        close(fd[1]); // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    } else { // Parent process
        close(fd[0]); // Close read end
        write(fd[1], "Message from parent", 19);
        close(fd[1]);
    }
    
    return 0;
}
```

### Named Pipes (FIFO)

**Concept**: A file-based pipe that persists in the filesystem. Multiple processes can communicate.

**Analogy**: Like a physical mailbox at home with an address. Any process can write to it, and any process can read from it.

**C Code Example - Named Pipe**:

```c
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Create named pipe (FIFO) file
    mkfifo("/tmp/myfifo", 0666);
    
    // Writer process
    int fd = open("/tmp/myfifo", O_WRONLY);
    write(fd, "Hello from FIFO", 15);
    close(fd);
    
    // Reader process (in another terminal/process)
    fd = open("/tmp/myfifo", O_RDONLY);
    char buffer[100];
    read(fd, buffer, 100);
    printf("Received: %s\n", buffer);
    close(fd);
    
    return 0;
}
```

---

## 4. SOCKETS  Explanation:-
The socket() function creates a new socket in the operating system. A socket is essentially a communication endpoint that allows processes to send and receive data, either over the network or locally.
```c
int socket(int domain, int type, int protocol);
```
- domain → What kind of addresses the socket can communicate with.

- type → What type of communication you want (stream vs datagram).

- protocol → Which protocol to use; 0 usually means “choose default for this type.”

**OSI Layers**:
- **Layer 2 (Data Link)**: MAC addresses, physical network addressing, Ethernet frames
- **Layer 3 (Network)**: IP addresses, routing between networks, packet forwarding

**Analogy for Socket Communication**:
- **L3 Socket (TCP/UDP over IP)**: Like sending a package to an address across the country. The postal system (routing) ensures it reaches the right city (network).
- **L2 Socket (Raw Ethernet)**: Like handing a package directly to someone in the same building (same network segment).

### Socket at L3 (IP-based, TCP/UDP)

**C Code Example - L3 Socket (TCP Server)**:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    /*
    AF_INET (Address Family Internet):
    This tells the OS we want an IPv4 socket.
    IPv6 would be AF_INET6.
    There are also AF_UNIX (local IPC), AF_PACKET (raw packets), etc.

    SOCK_STREAM:
    This tells the OS we want a stream-oriented socket.
    Stream = TCP: reliable, ordered, connection-based.
    Other common type: SOCK_DGRAM → UDP (datagram, connectionless, unreliable).

    Protocol = 0:
    OS chooses the default protocol for this combination of domain and type.
    For AF_INET + SOCK_STREAM, that’s TCP.
    For AF_INET + SOCK_DGRAM, that’s UDP.

    Allocates a file descriptor in the kernel.
    Creates a socket data structure in kernel memory to track:
    Address family (AF_INET)
    Type (SOCK_STREAM)
    Protocol (TCP)
    Buffers for sending/receiving
    State (for TCP: LISTEN, ESTABLISHED, etc.)
    Returns the file descriptor (server_fd) to your program.
    You can now use this descriptor with bind(), listen(), accept(), read(), write(), etc.
    */
    // Set socket options (allow reuse)
    int opt = 1;
    //configure options for a socket at runtime.SO_REUSEADDR → Allows reusing a port immediately after a previous socket on the same port is closed
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Bind socket to address and port
    //tell the OS which IP address and port your server will listen on
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY means listen on all available interfaces. Could also be inet_addr("192.168.1.2") for a specific IP.
    address.sin_port = htons(8080);//htons(8080) converts 8080 to network byte order (big-endian).Network protocols expect big-endian order.

    //Associate this socket (server_fd) with this IP address and port.”
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    
    // Listen for connections (backlog = 3)
    //When a client tries to connect:TCP handshake starts.
    listen(server_fd, 3);//If server_fd is in listening mode, the kernel queues the connection in a pending queue.
    
    // Accept connection from client
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);//call accept() to take the connection off the queue
    
    // Send/Receive data
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received: %s\n", buffer);
    
    send(client_socket, "Hello from server", 17, 0);
    
    close(client_socket);
    close(server_fd);
    return 0;
}
```

### Socket at L2 (Raw Ethernet)

**C Code Example - L2 Socket (Raw Ethernet)**:

```c
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <string.h>

int main() {
    // Create raw socket for Ethernet frames (Layer 2)
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    
    if (sock < 0) {
        perror("Socket error");
        return 1;
    }
    
    unsigned char buffer[65535];
    
    // Receive Ethernet frame
    struct sockaddr saddr;
    socklen_t saddr_len = sizeof(saddr);
    
    int data_size = recvfrom(sock, buffer, sizeof(buffer), 0, &saddr, &saddr_len);
    
    printf("Received %d bytes\n", data_size);
    
    // Parse Ethernet header (Layer 2)
    // Destination MAC: buffer[0-5]
    // Source MAC: buffer[6-11]
    // Type: buffer[12-13] (0x0800 = IPv4, 0x0806 = ARP)
    
    printf("Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
    printf("Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           buffer[6], buffer[7], buffer[8], buffer[9], buffer[10], buffer[11]);
    
    close(sock);
    return 0;
}
```

---

## 5. PROCESS, CHILD PROCESS, and FORK

**Concept**: fork() creates a new process (child) as a copy of the current process (parent).

**Analogy**: Like cloning yourself. After the clone happens, you and your clone are separate entities with separate memories, but identical at the moment of cloning.

**Key Points**:
- fork() returns: 0 in child, child PID in parent, -1 on error
- Both parent and child continue execution after fork()
- Child gets a copy of parent's memory (separate address space)

**C Code Example**:

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Before fork: PID = %d\n", getpid());
    
    pid_t child_pid = fork();
    
    if (child_pid == 0) { // Child process
        printf("I am child, my PID = %d, parent PID = %d\n", 
               getpid(), getppid());
        sleep(2);
        printf("Child exiting\n");
    } else if (child_pid > 0) { // Parent process
        printf("I am parent, my PID = %d, child PID = %d\n", 
               getpid(), child_pid);
        
        // Wait for child to finish
        int status;
        wait(&status); // or waitpid(child_pid, &status, 0)
        
        printf("Child finished with status: %d\n", status);
    } else { // Error
        perror("fork failed");
    }
    
    return 0;
}
```

---

## 6. CONTEXT SWITCHING

**Concept**: The CPU switches from executing one process/thread to another. The OS saves the state of the current process and loads the state of the next process.

**Analogy**: Like a teacher switching attention between two students. The teacher remembers where Student A was in their explanation (saves context), then focuses on Student B (loads new context). Later, when returning to Student A, the teacher remembers exactly where they left off.

**What Gets Saved (Context)**:
- CPU registers
- Program counter (instruction pointer)
- Stack pointer
- Process state flags

**C Illustration (Conceptual - actual context switching is OS-level)**:

```c
// Pseudocode showing concept:
struct ProcessContext {
    uint32_t registers[32];
    uint32_t program_counter;
    uint32_t stack_pointer;
    int process_state;
};

void context_switch(Process *current, Process *next) {
    // Save current process context
    save_context(&current->context);
    
    // Load next process context
    load_context(&next->context);
    
    // CPU resumes executing next process
}
```

**Triggers for Context Switching**:
1. Time slice expires (preemptive scheduling)
2. Process blocks on I/O
3. Higher priority process becomes ready
4. Process terminates

---

## 7. THREADS AND TASK SCHEDULING DURING SYNCHRONISATION

**Concept**: Multiple threads within a process share memory but execute independently. Scheduler determines which thread runs on CPU.

**Analogy**: Like multiple workers in a factory. They share the same factory (memory), but different workers can be assigned to different machines (CPU cores/timeslices).

**C Code Example - Basic Threading**:

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is running\n", thread_id);
    sleep(1);
    printf("Thread %d finished\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    
    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, &ids[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("All threads completed\n");
    return 0;
}
```

**Scheduling During Synchronisation**:
When a thread acquires a lock, other threads waiting for that lock are blocked and de-scheduled. When the lock is released, a waiting thread is scheduled and acquires the lock.

---

## 8. MUTEX FOR SYNCHRONISATION

**Concept**: Mutual exclusion lock. Only one thread can hold a mutex at a time.

**Analogy**: Like a bathroom key. Only one person can hold the key and use the bathroom. Others must wait outside.

**Key Operations**:
- `pthread_mutex_lock()`: Try to acquire lock (wait if held by another thread)
- `pthread_mutex_unlock()`: Release lock

**C Code Example**:

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        shared_counter++; // Critical section
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increment_counter, NULL);
    pthread_create(&t2, NULL, increment_counter, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Counter value: %d (should be 200000)\n", shared_counter);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
```

---

## 9. SEMAPHORE SYNCHRONISATION

**Concept**: A counter-based synchronization primitive. Can be used to manage access to multiple identical resources or for signaling.

**Analogy**: Like parking lot spaces. If there are 5 parking spots (semaphore = 5), each car that enters decrements the count. When it's full (count = 0), new cars must wait.

**Two Types**:
- **Binary Semaphore**: Value 0 or 1 (like mutex, but can be released by different thread)
- **Counting Semaphore**: Any non-negative value (resource pools)

**Key Operations**:
- `sem_wait()`: Decrement count; if 0, block
- `sem_post()`: Increment count; wake one waiting thread

**C Code Example**:

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    printf("Thread %d: waiting for resource...\n", thread_id);
    sem_wait(&semaphore); // Acquire
    
    printf("Thread %d: acquired resource\n", thread_id);
    sleep(2);
    printf("Thread %d: releasing resource\n", thread_id);
    
    sem_post(&semaphore); // Release
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    
    sem_init(&semaphore, 0, 1); // Binary semaphore (only 1 at a time)
    
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, &ids[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&semaphore);
    return 0;
}
```

---

## 10. RACE CONDITION

**Concept**: A race condition occurs when two or more processes or threads access shared data (like shared memory, a file, or a variable) concurrently, and the final result depends on the timing of how those accesses happen.

Because the CPU schedules processes unpredictably, this can cause inconsistent or corrupted data.

**Analogy**: Two people adding money to a shared bank account simultaneously without coordination. Both read the balance as $100, add $50, and write back $150. Result: $150 instead of $200.

**Example of Race Condition**:

```c
#include <stdio.h>
#include <pthread.h>

int counter = 0; // Shared data

void* increment_unsync(void* arg) {
    for (int i = 0; i < 100000; i++) {
        counter++; // NO LOCK - RACE CONDITION!
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increment_unsync, NULL);
    pthread_create(&t2, NULL, increment_unsync, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // Expected: 200000, Actual: Could be anything (due to race condition)
    printf("Counter: %d\n", counter);
    
    return 0;
}
//fix
#include <stdio.h>
#include <pthread.h>

int counter = 0;                  // Shared resource
pthread_mutex_t lock;             // Mutex for synchronization

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);   // Enter critical section
        counter++;
        pthread_mutex_unlock(&lock); // Exit critical section
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

```

**How `counter++` causes race condition**:
1. Thread 1 reads counter: 5
2. Thread 2 reads counter: 5
3. Thread 1 increments: 6, writes back
4. Thread 2 increments: 6, writes back
Result: 6 (should be 7)

---

## 11. DEADLOCK

**Concept**:A deadlock happens when two or more threads (or people) are each waiting for the other to release a resource, and none can proceed — they’re stuck forever..

**Four Conditions Required**:
1. **Mutual Exclusion**: Only one thread can hold a resource
2. **Hold and Wait**: Thread holds a resource while waiting for another
3. **No Preemption**: Resources cannot be forcibly taken
4. **Circular Wait**: Thread 1 waits for Thread 2's resource, Thread 2 waits for Thread 1's resource

If you break any one of these conditions, the deadlock is prevented

**Analogy**: Two people holding doors open for each other, but each refuses to enter first. They're both stuck.

**Example of Deadlock**:

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_B = PTHREAD_MUTEX_INITIALIZER;

void* thread1_func(void* arg) {
    printf("Thread 1: trying to lock A...\n");
    pthread_mutex_lock(&lock_A);
    printf("Thread 1: locked A\n");
    
    sleep(1); // Simulate work
    
    printf("Thread 1: trying to lock B...\n");
    pthread_mutex_lock(&lock_B); // WAITS FOR THREAD 2 TO RELEASE B
    printf("Thread 1: locked B\n");
    
    pthread_mutex_unlock(&lock_B);
    pthread_mutex_unlock(&lock_A);
    return NULL;
}

void* thread2_func(void* arg) {
    printf("Thread 2: trying to lock B...\n");
    pthread_mutex_lock(&lock_B);
    printf("Thread 2: locked B\n");
    
    sleep(1); // Simulate work
    
    printf("Thread 2: trying to lock A...\n");
    pthread_mutex_lock(&lock_A); // WAITS FOR THREAD 1 TO RELEASE A
    printf("Thread 2: locked A\n");
    
    pthread_mutex_unlock(&lock_A);
    pthread_mutex_unlock(&lock_B);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);
    
    // This will DEADLOCK - program hangs forever
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}
```

**Prevention - Lock Ordering**:

```c
// **Solution**: To prevent deadlocks, make sure all threads lock resources in the same order.
void* thread1_fixed(void* arg) {
    pthread_mutex_lock(&lock_A); // Always A first
    pthread_mutex_lock(&lock_B); // Then B
    
    // Critical section
    
    pthread_mutex_unlock(&lock_B); // Release in reverse order
    pthread_mutex_unlock(&lock_A);
    return NULL;
}

void* thread2_fixed(void* arg) {
    pthread_mutex_lock(&lock_A); // Always A first (same order!)
    pthread_mutex_lock(&lock_B); // Then B
    
    // Critical section
    
    pthread_mutex_unlock(&lock_B); // Release in reverse order
    pthread_mutex_unlock(&lock_A);
    return NULL;
}
```

---
| Concept            | Analogy                                                       | Problem                         | Solution                                              |
| ------------------ | ------------------------------------------------------------- | ------------------------------- | ----------------------------------------------------- |
| **Race Condition** | Two people updating a bank balance at the same time           | Lost update (inconsistent data) | Synchronization (mutex)                               |
| **Deadlock**       | Two people each holding one account and waiting for the other | Both stuck forever              | Consistent lock order / timeout / avoid circular wait |


## 12. SEGMENTATION FAULT

**Concept**: A signal (SIGSEGV) sent by the OS when a process tries to access memory it's not allowed to access.

**What Happens**:
1. Process attempts invalid memory access
2. MMU (Memory Management Unit) detects violation
3. CPU raises exception
4. OS terminates the process (usually)
5. Core dump may be generated (process memory snapshot)

**Common Causes**:

```c
// 1. Dereferencing NULL pointer
int* ptr = NULL;
*ptr = 10; // SEGFAULT

// 2. Out-of-bounds array access
int arr[10];
arr[100] = 5; // SEGFAULT

// 3. Using freed memory (dangling pointer)
int* p = malloc(sizeof(int));
free(p);
*p = 10; // SEGFAULT (use-after-free)

// 4. Stack overflow (infinite recursion)
void recursive() {
    recursive(); // SEGFAULT when stack overflows
}

// 5. Writing to read-only memory
char* str = "Hello"; // String literal in read-only segment
str[0] = 'h'; // SEGFAULT
```

**Memory Layout (where segfault occurs)**:

```
High Address
┌─────────────────┐
│   Stack         │ (local variables, function calls)
├─────────────────┤
│                 │ (unallocated - SEGFAULT if accessed)
├─────────────────┤
│   Heap          │ (malloc/new - dynamically allocated)
├─────────────────┤
│   BSS Segment   │ (global/static uninitialized data)
├─────────────────┤
│   Data Segment  │ (global/static initialized data, READ-ONLY strings)
├─────────────────┤
│   Text Segment  │ (code - READ-ONLY)
└─────────────────┘
Low Address
```

**How OS Handles Segfault**:
1. Hardware sends exception
2. Kernel handles exception in privileged mode
3. OS terminates the process
4. Generates core dump (memory image) for debugging
5. Returns control to shell/parent

---

## 13. INTERRUPT

**Concept**: A signal from hardware to CPU telling it to stop current execution and handle an urgent event.

**Analogy**: Like someone knocking on your door while you're working. You pause what you're doing, answer the door, help the visitor, then resume your work.

**What Happens When Interrupt Occurs**:
1. CPU saves current context (registers, program counter)
2. CPU enters kernel mode (privileged)
3. Interrupt handler (ISR) executes
4. ISR handles the interrupt
5. CPU restores saved context
6. CPU resumes execution

**Types of Interrupts**:
- **Hardware Interrupts**: From external devices (keyboard, disk, timer, network)
- **Software Interrupts**: From program (system calls, exceptions)

**Interrupt Handler Example (Pseudocode)**:

```c
// Interrupt handler (runs in kernel mode)
void keyboard_interrupt_handler() {
    // Read key from keyboard controller
    char key = read_from_keyboard();
    
    // Add to keyboard buffer
    add_to_input_buffer(key);
    
    // Signal waiting process if needed
    wake_up_waiting_process();
    
    // Acknowledge interrupt to hardware
    send_eoi_to_controller();
}

// Context before interrupt:
// CPU was executing: while(1) { process_data(); }
// CPU was in user mode

// After interrupt returns, CPU resumes:
// while(1) { process_data(); } // Continues from where it left off
```

---

## 14. MULTIPLE INTERRUPTS OCCURRING SIMULTANEOUSLY

**Concept**: When two or more interrupts request CPU attention at the same time. The system uses priority levels to decide which one to handle first.

**Priority Interrupt System**:

**Analogy**: Emergency room triage. When multiple patients arrive:
- Heart attack patient (highest priority) → served first
- Broken arm patient (medium priority) → served second
- Minor cut patient (low priority) → served last

**How Multiple Interrupts Are Handled**:

```
Scenario: Keyboard interrupt and Disk interrupt happen simultaneously

1. Both interrupts occur at same time
2. Interrupt controller receives both signals
3. Controller prioritizes: Disk (IRQ5) > Keyboard (IRQ1)
4. CPU is sent Disk interrupt first
5. Disk interrupt handler starts (CPU masked lower interrupts)
6. If Keyboard interrupt is higher priority, it can INTERRUPT the Disk handler
7. Keyboard handler executes
8. Returns to Disk handler (context restored)
9. Disk handler completes
10. Returns to original program
```

**Different Priorities Scenario**:

```c
// Interrupt Controller Priority (hardware-managed):
Priority 1 (Highest): Power Failure Interrupt
Priority 2:           Disk Controller Interrupt
Priority 3:           Network Interface Interrupt
Priority 4:           Timer Interrupt
Priority 5:           Keyboard Interrupt
Priority 6 (Lowest):  Printer Interrupt

// If Disk (Priority 2) is being handled and Power Failure (Priority 1) occurs:
// The Disk handler is PREEMPTED
// Power Failure handler runs immediately
// Returns to Disk handler when done
```

**Same Priority Interrupts**:

```c
// If two interrupts have same priority, they are handled in order:
// 1. First one to occur is handled first
// 2. Second one is PENDING while first is being handled
// 3. After first completes, second is handled

// Example:
// Time 0: Network interrupt arrives (Priority 3)
// Time 1: Disk interrupt arrives (Priority 3) - SAME PRIORITY
// Time 1-10: Network handler executes
// Time 10-20: Disk handler executes (it was waiting)
```

**Handling Multiple Interrupts (Pseudocode)**:

```c
void main_interrupt_handler(int interrupt_number) {
    // Save current context (CPU registers, PC, etc.)
    save_context();
    
    // Enter kernel mode (already done by CPU on interrupt)
    
    // Get interrupt priority
    int priority = get_interrupt_priority(interrupt_number);
    
    // Get specific interrupt handler
    void (*handler)(void) = interrupt_table[interrupt_number];
    
    // Unmask interrupts of lower priority (allow higher priority interrupts)
    enable_interrupts_above_priority(priority);
    
    // Execute specific interrupt handler
    handler();
    
    // Mask all interrupts again
    disable_all_interrupts();
    
    // Restore context (registers, PC, etc.)
    restore_context();
    
    // Return to interrupted code
    return;
}
```

**Interrupt Vector Table (IVT)**:

```
Memory Address    Interrupt Type
0x00              Division by Zero
0x04              Single Step
0x08              NMI (Non-Maskable Interrupt)
0x0C              Breakpoint
0x10              Keyboard (IRQ1)
0x14              Timer (IRQ0)
0x18              Network (IRQ3)
0x1C              Disk (IRQ5)
...
```

---

## Key Interview Tips

1. **Message Queues**: Remember FIFO, asynchronous, typed messages, kernel-managed
2. **Shared Memory**: Fastest IPC, but requires synchronization (race condition risk)
3. **Pipes**: One-way, parent-child, unnamed doesn't persist; FIFO persists
4. **Sockets**: L2 = MAC/Ethernet frames; L3 = IP-based, routing across networks
5. **Fork**: Returns 0 to child, child PID to parent, -1 on error
6. **Context Switch**: Saves/restores CPU registers, stack pointer, program counter
7. **Threads**: Share memory, independent execution, lighter weight than processes
8. **Mutex**: Binary lock, mutual exclusion, prevent race conditions
9. **Semaphore**: Counter-based, can manage multiple resources, binary or counting
10. **Race Condition**: Happens when threads access shared data without synchronization
11. **Deadlock**: Circular wait for locks; prevent by lock ordering or resource ordering
12. **Segfault**: Invalid memory access; check: null pointers, bounds, freed memory
13. **Interrupt**: Hardware signal; saves context, runs ISR, restores context
14. **Multiple Interrupts**: Prioritized; higher priority can preempt lower; same priority is FIFO

# System-Level Programming: Preemption and Interrupt Handling

## 1. What is Preemption?

Preemption is the OS forcefully interrupting a running process and removing it from the CPU to give CPU time to another process (usually a higher-priority one). The preempted process is moved back to the Ready queue and can resume later.

### Analogy

Think of a teacher calling on a student to answer a question. If another student raises their hand with a more urgent question, the teacher might interrupt the first student mid-sentence and address the urgent question first. The first student then waits their turn to finish.

### Preemptive vs Non-Preemptive Scheduling

| Aspect | Preemptive | Non-Preemptive |
|--------|-----------|----------------|
| Interruption | OS can interrupt a running process | Process runs until it finishes or blocks |
| Triggers | Time slice expires, higher priority arrives | Process completion or I/O block only |
| Context Switching | Frequent (overhead) | Less frequent (lower overhead) |
| Responsiveness | Better for real-time systems | Less responsive, may cause delays |
| Fairness | Better - all processes get turns | Can starve low-priority/short processes |
| Best For | Multitasking, real-time OS, time-sharing | Batch processing, simple systems |

### What Actually Happens During Preemption

1. **OS timer interrupt occurs** (time slice expired)
2. **CPU saves current process context** (registers, program counter, stack pointer)
3. **Process state changes** from Running → Ready
4. **Next process from Ready queue is selected**
5. **New process context is loaded** from memory
6. **CPU resumes** executing the new process
7. **Later**, the preempted process may be scheduled again

### Example in C (Conceptual - OS handles this)

```c
// Pseudocode showing context switch during preemption
struct Context {
    uint32_t registers[32];
    uint32_t program_counter;
    uint32_t stack_pointer;
};

void preemption_handler(Process *current_process, Process *next_process) {
    // Save state of current process
    save_context(&current_process->context);
    current_process->state = READY;  // Move to ready queue
    
    // Load state of next process
    load_context(&next_process->context);
    next_process->state = RUNNING;
    
    // CPU continues with next process
    // Later, current_process may be scheduled again
}
```

---

## 2. What Happens When Two Interrupts with Same Priority Occur at Exact Same Time?

When two interrupts of identical priority occur simultaneously, the system cannot serve both at once. Here's what happens:

### The Arbitration Process

**Step 1: Both Interrupts Arrive**

- Interrupt A (IRQ5) and Interrupt B (IRQ7) both have priority level 3
- Both signals reach the interrupt controller at virtually the same time

**Step 2: Interrupt Controller Arbitration**

The hardware uses an internal polling/arbitration sequence to break the tie:

#### Primary Tiebreaker - Hardware Priority / IRQ Number

- Lower IRQ numbers have inherent hardware priority
- If both IRQ5 and IRQ7 arrive with same priority: **IRQ5 is serviced first**
- This is the default mechanism

#### Secondary Tiebreaker - Subpriority (if configured)

- Some systems allow sub-priorities within a priority level
- Example: IRQ5 has subpriority 2, IRQ7 has subpriority 5
- Lower subpriority value is serviced first
- Only matters when main priority is identical

#### Tertiary Tiebreaker - First-Come-First-Served

- If both priority AND subpriority are identical
- Whichever interrupt was triggered first is served
- The second becomes PENDING

**Step 3: First Interrupt Handler Executes**

- Interrupt A handler runs to completion
- CPU in interrupt mode, lower priority interrupts masked
- Same-priority interrupts CANNOT preempt the current handler

**Step 4: Second Interrupt Goes to Pending State**

- Interrupt B is marked as PENDING
- NOT lost or missed (this is crucial)
- Waiting for Interrupt A handler to complete

**Step 5: After First Handler Completes**

- CPU acknowledges completion
- Checks for pending interrupts
- Interrupt B handler immediately starts
- Returns to original code

### Critical C Example - Same Priority Interrupts

```c
// Two interrupts with same priority
volatile int interrupt_a_count = 0;
volatile int interrupt_b_count = 0;

// ISR for Interrupt A (IRQ5)
void interrupt_a_handler() {
    interrupt_a_count++;
    printf("Interrupt A handled\n");
    // Simulation of work
    for(volatile int i = 0; i < 1000000; i++);
}

// ISR for Interrupt B (IRQ7)
void interrupt_b_handler() {
    interrupt_b_count++;
    printf("Interrupt B handled\n");
    // Simulation of work
    for(volatile int i = 0; i < 1000000; i++);
}

// NVIC Configuration (ARM Cortex-M)
void setup_interrupts() {
    // Set both to same priority (priority 3)
    NVIC_SetPriority(IRQ5, 3);  // Subpriority = 0 (default)
    NVIC_SetPriority(IRQ7, 3);  // Subpriority = 0 (default)
    
    // Register handlers
    NVIC_SetVector(IRQ5, interrupt_a_handler);
    NVIC_SetVector(IRQ7, interrupt_b_handler);
    
    NVIC_EnableIRQ(IRQ5);
    NVIC_EnableIRQ(IRQ7);
}

// What happens if both trigger simultaneously:
// Timeline:
// T1: Both IRQ5 and IRQ7 signals arrive at controller
// T2: Arbiter compares: both priority 3, both subpriority 0
// T3: IRQ5 has lower number → IRQ5 selected
// T4: interrupt_a_handler() executes
// T5: interrupt_a_count++, delay loop runs
// T6: IRQ7 is PENDING (in pending register)
// T7: interrupt_a_handler() completes, acknowledges interrupt
// T8: interrupt_b_handler() immediately starts (was pending)
// T9: interrupt_b_count++, delay loop runs
// T10: interrupt_b_handler() completes, returns to main code

int main() {
    setup_interrupts();
    
    // Simulate both interrupts triggering simultaneously
    // trigger_irq(5);  // Both triggered at same time
    // trigger_irq(7);
    
    // Result: Both handlers execute, neither is lost
    // Order: A first, then B
    // Final: interrupt_a_count = 1, interrupt_b_count = 1
    
    while(1);
    return 0;
}
```

### What If They're Different Priorities?

If Interrupt A is priority 2 (higher) and Interrupt B is priority 3 (lower):

1. Interrupt A handler starts immediately
2. Interrupt B is marked PENDING (cannot interrupt A)
3. Interrupt A completes
4. Interrupt B handler runs

This also prevents loss of Interrupt B

### Key Points for Interview

- **Neither interrupt is lost** - pending interrupts are queued, not discarded
- **Hardware decides the order** - not software (unless subpriorities configured)
- **Lower IRQ numbers win ties** - This is the default hardware tiebreaker
- **Same priority ≠ preemption** - Handler of same-priority interrupt cannot be preempted
- **Pending interrupts execute immediately after** - Not delayed significantly
- **Subpriorities can be configured** - For fine-grained control within a priority level
- **Order is deterministic** - Not random; always follows the same rule

### Comparison: Same Priority vs Different Priority Interrupts

| Scenario | Behavior |
|----------|----------|
| Both arrive at exactly same time, same priority | Arbiter uses IRQ number/hardware priority to decide |
| IRQ5 (priority 2) and IRQ7 (priority 2) simultaneously | IRQ5 served first (lower number) |
| IRQ5 (priority 2) and IRQ7 (priority 3) simultaneously | IRQ5 served first (higher priority), IRQ7 becomes pending |
| One arrives while other is executing, same priority | New interrupt becomes pending, doesn't preempt |
| One arrives while other is executing, higher priority | New interrupt PREEMPTS (if higher priority) |
