# LSP (Low-level System Programming) Interview Preparation Guide

## Quick Reference: Code Examples for All Topics

This guide contains practical C examples for every concept you need to master.

---

## 1. MESSAGE QUEUE

**Concept**: A buffer (queue) where processes can place and retrieve messages asynchronously.

**Analogy**: Think of it like a postal mailbox. Process A leaves a letter (message) in the mailbox, and Process B picks it up later. They don't need to meet or synchronize - the mailbox stores the message until someone needs it.

**Key Features**:
- FIFO ordering
- Messages can be typed (retrieved by type, not just order)
- Kernel-managed buffer
- Asynchronous communication

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

## 4. SOCKETS - L2 and L3 Explanation

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
    
    // Set socket options (allow reuse)
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Bind socket to address and port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    
    // Listen for connections (backlog = 3)
    listen(server_fd, 3);
    
    // Accept connection from client
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);
    
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

**Concept**: When multiple threads access shared data without synchronization, and at least one modifies it, the result depends on execution order.

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
```

**How `counter++` causes race condition**:
1. Thread 1 reads counter: 5
2. Thread 2 reads counter: 5
3. Thread 1 increments: 6, writes back
4. Thread 2 increments: 6, writes back
Result: 6 (should be 7)

---

## 11. DEADLOCK

**Concept**: Two or more threads/processes are blocked forever, each waiting for the other to release a resource.

**Four Conditions Required**:
1. **Mutual Exclusion**: Only one thread can hold a resource
2. **Hold and Wait**: Thread holds a resource while waiting for another
3. **No Preemption**: Resources cannot be forcibly taken
4. **Circular Wait**: Thread 1 waits for Thread 2's resource, Thread 2 waits for Thread 1's resource

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
// Solution: Always acquire locks in the same order
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

