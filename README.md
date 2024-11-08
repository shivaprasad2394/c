﻿C
=============================================================================================================================
c practice perpose
http://cse.unl.edu/~cbourke/searchingSorting.pdf

https://github.com/rafi007akhtar/c-algorithms/blob/master/single_pointer_doublelinkedlist.c

https://github.com/caisah/Sedgewick-algorithms-in-c-exercises-and-examples

storage classes :- 
---------------
                   1)decide the extent(lifetime) of variable.
                   2)scope (visibility) of the variable
                   3)storage location in memory.
there are 4 types of storage class specifier:-
--------------------------------------------

    1)auto------->a default specifier class for local variables,if variable not specifeid any storage class.
                 • Local variables are auto by default,Garbage value(default).
                 •function with auto specifier cannot have return type.if tried will give compilation error.
    2)static----->varible with static specifier,have internal or no linkage,memory persistant,initialized once.
    3)extern----->default specifier class for global variables and function.
                 •varibles with extern class have no storage allocation for variable.
                 •indicates/informs compiler about offload declaration/definition of variable.
    4)register--->variable with register class have visibility Local to Function.
                 •informs compiler to store the variable in cpu registers.

----------------------------------------------------------------------------------------------------------------------------
scope difference
----------------
    
    1)Global variable-->Extenal linkage. [i.e visible outside the program]
    2)Global static  -->Internal linkage. [i.e visibity is restricted to the program where it is defined]
    3)Local static   -->no linkage.[i.e visibility is restricted to the local function where it is defined]

----------------------------------------------------------------------------------------------------------------------------

    static default value-->0 
    note:-the start up code initializes the the data segment to 0.
    ============================================================================================

Macro------------------->>v/s<<-----------------functions
================================================================================================                                        
    No TypeChecking (ex:- func parameter)     |                             exist
    preprocessed                              |                             compiled
    codelength increases on Macro call        |                             remains same
    Speed of Execution faster                 |                             Speed of execution Slower
    useful in small code                      |                             usefull in large code
    difficult to debug                        |                             Easy
    
    =============================================================================================

     • In macros, no type checking(incompatible operand, etc.) is done and thus use of macros can lead to errors/side-effects in some cases.
     •However, this is not the case with functions. Also, macros do not check for compilation error (if any). 
     Consider the following two codes:
      #include<stdio.h> 
      #define CUBE(b) b*b*b 
      int main() 
      { 
        printf("%d", CUBE(1+2)); 
        return 0; 
      } 
------------------------------------------------------------------------------------------

typedef :-defining new names to existing types.
-------  
    Pros:-
        • to reduce complexity
        • to increase code readability and portability.
        
        
        // C program to demonstrate importance 
        // of typedef over #define for data types 
        #include <stdio.h> 
        typedef char* ptr; 
        #define PTR char* 
        int main() 
        { 
          ptr a, b, c; 
          PTR x, y, z; 
          printf("sizeof a:%u\n" ,sizeof(a) ); 
          printf("sizeof b:%u\n" ,sizeof(b) ); 
          printf("sizeof c:%u\n" ,sizeof(c) ); 
          printf("sizeof x:%u\n" ,sizeof(x) ); 
          printf("sizeof y:%u\n" ,sizeof(y) ); 
          printf("sizeof z:%u\n" ,sizeof(z) ); 
          return 0; 
        } 

      Output:

      sizeof a:8
      sizeof b:8
      sizeof c:8
      sizeof x:8
      sizeof y:1
      sizeof z:1
      From the output of the above program size of “a” which is a pointer is 8 (on a machine where pointers are stored using 8 bytes). In the above program, when the compiler comes to

      typedef char* ptr;
      ptr a, b, c;
      the statement effectively becomes

      char *a, *b, *c;
      This declares a, b, c as char*.

      In contrast, #define works like this:

      #define PTR char*
      PTR x, y, z;
      the statement effectively becomes

      char *x, y, z;

This makes x, y and z different, as, x is pointer-to-a char, whereas, y and z are char variables. When we declare macros with pointers while defining if we declare more than one identifier then the actual definition is given to the first identifier and for the rest non-pointer definition is given. In the above case x will be declared as char*, so its size is the size of a pointer, whereas, y and z will be declared as char so, their size will be 1 byte.

=======================================================================================

Macro:-    A preprocessor directive.
-----
          • It replaces the value before compiling.
      Cons:-
          • no typecasting.
          • Usually used to create alias in c
          • used has file guard in c.
========================================================================================

Enum:- A userdefined data type  and it consist of a set of named constant integers.
----
      Pro:-
          • increases code readability.
          • Easy to debug symbolic constant.

=========================================================================================

# Inline function in C
    Inline Function are those function whose definitions are small and be substituted at the place where its function call is happened. 
    Function substitution is totally compiler choice.

    Let’s take below example:
    #include <stdio.h> 

    // Inline function in C 
    static inline int foo() 
    { 
      return 2; 
    } 

    // Driver code 
    int main() 
    { 

      int ret; 

      // inline function call 
      ret = foo(); 

      printf("Output is: %d\n", ret); 
      return 0; 
    } 
# note:if static is not used then it will give error.
    In function `main':
    undefined reference to `foo'
    To resolve this problem use “static” before inline. 
    Using static keyword forces the compiler to consider this inline function in the linker, 
    and hence the program compiles and run successfully.[for more refer the readme in inline subs]
watch it really good :https://www.youtube.com/watch?v=gINI12EMbds   &
https://www.youtube.com/watch?v=MNxNlMQ5QJ4
-----------------------------------------------------------------------------------------
const:- a qualifier ,gives direction to the compiler that the value of declaring object could not be changed.[not modifiable]
-----
    •const int a------------>a constant integer.
    •int const a------------>a constant integer.
  -------------------------------------------
  
    •const int *a ==========>a pointer to constant integer-->[value constant]
    •int const *a ==========>a constant pointer to integer-->[address constant]
  ---------------------------------------
    
    •const int* const a \==>
                          =========>constant pointer to a constant int.
    •int const* a const /==>
  
  --------------------------------------------
========================================================================================
  
pre increment 
==========
    --->increament is done *immediatly.
post increment
===========
    --->increment effect is done in *next statement.
    ex:-
    char ac[5]={'A','B','C','D','E'};
    char *pcdata = ac;
    ---------------------------------- 
    *++pcdata =====>'B' 
    <--------           
    ++*pcdata =====>'A' 
    <--------           
    *p++  =========>'A' 
    <---                
   ------------------------------------
--------------------------------------------------------

    ++*p -->take data and increment data.
    *++p -->move pointer to next and read data.
    *p++ -->read data ,then move pointer to next.
    (*p)++ >increment the data.
    [P++ + ++p] or [++P + p++] -->????

===========================================================================================

extras:-

Difference between const and Macro:-
====================================
Const-------------------->>v/s<<-----------------Macro
======================================================
    handled by compiler                          |                             handled by preprocessor
    A qualifier (modifies behavior of identifier)|                             A pre processor directive
    type checking                                |                             No typechecking
    Scoped by c block                            |                             applies for file
        
=======================================================

volatile keyword
================
    A Type qualifier that prevents object from the compiler optimization.
according to c standards:-
========================
          • A volatile object can be modified in ways unknown to the implementation.
          • the value of the object can be changed at any time without any action being taken by the code.
          • when a variable or object is declared volatile the compiler reloads the value from the memory each time it is accessed by the programm. [i.e:-it prevents from cacheing a variable into registers]
          •reading the value from memory is the only way to check the unpredictable change of the value.
          
   Example:-
   ======= 
    access the memory-mapped peripheral register or hardware status register
======================================================================

    #define COM_STATUS_BIT  0x00000006

    uint32_t const volatile * const pStatusReg = (uint32_t*)0x00020000;


    unit32_t GetRecvData()
    {
      //Code to recv data
        while (((*pStatusReg)  & COM_STATUS_BIT) == 0)
      {
            // Wait untill flag does not set
        }

        return RecvData;
    }
=======================================================================    

    • Sharing the global variables or buffers between the multiple threads.
    • Accessing the global variables in an interrupt routine or signal handler.
======================================================================= [note:-1st explain without volatile]

    volatile int Flag = 0;

    ISR(void) 
    { 
      Flag = 1; 
    } 

    int main(void) 
    { 

      while (!Flag)
      {
          //do some work
      }

      return 0;
    }

=========================================================================
    
    •volatile  prevents the object from any compiler optimization and says that the value of the object can be changed by something that is beyound the control of the program and so that compiler will not make any assumptions about the object.
    volatile int a;
    • When a compiler see the above declaration ,then it avoids to make any assumptions regarding the variable/object and in every iteration read the value from the address whic is assigned to the variable.
    
======================================================================================================================   
   
[todo from here]

      What is the difference between the const and volatile qualifier in C?
            Answer:
            The const keyword is compiler-enforced and says that the program could not change the value of the object that means it makes the object nonmodifiable type.
            e.g,
            const int a = 0;
            if you will try to modify the value of “a”, you will get the compiler error because “a” is qualified with const keyword that prevents to change the value of the integer variable.

      In another side volatile prevent from any compiler optimization and says that the value of the object can be changed by something that is beyond the control of the program and so that compiler will not make any assumption about the object.
      e.g,
      volatile int a;

      When the compiler sees the above declaration then it avoids to make any assumption regarding the “a” and in every iteration read the value from the address which is assigned to the variable.

      Can a variable be both constant and volatile in C?
      Answer:
      Yes, we can use both constant and volatile together. One of the great use of volatile and const keyword together is at the time of accessing the GPIO registers. In case of GPIO, its value can be changed by the ‘external factors’ (if a switch or any output device is attached with GPIO), if it is configured as an input. In that situation, volatile plays an important role and ensures that the compiler always read the value from the GPIO address and avoid to make any assumption.
      
     After using the volatile keyword, you will get the proper value whenever you are accessing the ports but still here is one more problem because the pointer is not const type so it might be your program change the pointing address of the pointer. So we have to create a constant pointer with the volatile keyword.

      Syntax of declaration,

      int volatile * const PortRegister;

      How to read the above declaration,
      int volatile * const PortRegister;
       |     |     |   |    |
       |     |     |   |    +------> PortRegister is a
       |     |     |   +-----------> constant
       |     |     +---------------> pointer to a
       |     +---------------------> volatile
       +---------------------------> integer
       
       Consider a simple below example:

 

      #define PORTX 0x00020000 // Address of the GPIO

      uint32_t volatile * const pcPortReg = (uint32_t *) PORTX;
      The pcPortReg is a constant pointer to a volatile unsigned integer, using *pcPortReg we can access the memory-mapped register.

      *pcPortReg = value; // Write value to the port
      value = *pcPortReg; // Read value from the port
      

==============================================================================================

bit manipulation
----------------
1)SET a Bit
-----------

    •Bitwise OR Operator used to set a int data type
    •OR of two bit is always 1(SET) , if any one of them is 1.
                          
                          Number | = (1<< nth Position)    1010 1000
                                                           0100 0000
                                                            <-------nth bit
                                                           -----------
                                                           1100 1000
                                                           -----------
--------------------------------------------------------------------------------------------------------
2)Clear a Bit
-------------

    •Bitwise AND oprator used to clear.
    •AND of two bit is always 0(clear) if any of the bit is 0.
                          
                        Number &= ~ (1<< nth Position)    0100 1000
                                                          1011 1111
                                                          (~)<------nth bit
                                                           -----------
                                                           10001000
                                                           -----------
 -------------------------------------------------------------------------------------------------------
 3)Checking a Bit
-----------------

    •Bitwise AND oprator used to check wether ser or not.
    •AND of two bit is always 1(SET) if any of the bit is 1.
                          
                  Bit = Number & (1 << nth)               0100 1000
                                                          0100 0000
                                                            <------nth bit
                                                          ------------
                                                          0100 0000
                                                          ------------
-------------------------------------------------------------------------------------------------------
 3)Toggle a Bit
-----------------

    •Bitwise XOR oprator used to Toggle .
                                                      Number ^= (1<< nth Position)
                          
                                                           1010 1000
                                                           0100 0000
                                                            <-------nth bit
                                                           -----------
                                                           1110 1000
                                                           ----------- 
-----------------------------------------------------------------------------------------------------
4)Detect if two Integers have opposite Signs.
--------------------------------------------

     •EX-OR of “a” and “b” will be negative,if “a” and “b” have the opposite signs.
     •XOR less than 0.
                       bRetValue = ((a ^ b) < 0); // true if a and b have opposite signs
----------------------------------------------------------------------------------------------------
5)Reverse Bits of a Number
--------------------------

Method 1:
---------
    • check the set bits of num and run the loop through all the bits of an integer.
    • If we find the ith bits of num is set then just put 1 at the ((INT_BITS – 1) – ith ) position of tmp, where INT_BITS is the number of bits of an integer.

                  #define CHAR_BITS  8  // size of character
                  #define INT_BITS  ( sizeof(int) * CHAR_BITS)


                  //bit reversal function
                  unsigned int ReverseTheBits(unsigned int num)
                  {
                      unsigned int iLoop = 0;
                      unsigned int tmp = 0;         //  Assign num to the tmp 
                      int iNumberLopp = (INT_BITS - 1);     

                      for(; iLoop < iNumberLopp; ++iLoop)
                      {

                        if((num & (1 << iLoop))) // check set bits of num
                        {
                         tmp |= 1 << ((INT_BITS - 1) - iLoop); //putting the set bits of num in tmp
                        }    
                      }

                      return tmp;
                  }

Method 2:
---------
     • It is a simple algorithm to reverse bits of the 32-bit integer.
     • This algorithm uses the eight constant value for the reversing the bits and takes five simple steps.
     
      • Steps 1:
      num = (((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1));

  #  This expression used to swap the bits.
    Let an example, suppose num is 0100, after the above expression it will be 1000.

     • Steps 2:
      num = (((num & 0xcccccccc) >> 2) | ((num & 0x33333333) << 2));

  #  Above expression uses to swap the 2 bits of a nibble.
    Suppose num is 10 00, after the above expression, it will be 00 01.

     • Steps 3:
      num = (((num & 0xf0f0f0f0) >> 4) | ((num & 0x0f0f0f0f) << 4));

  #  An expression used to swaps the nibbles.
    like if num is 0011 0010 then after the above expression it will be 0010 0011.

     • Steps 4:
      num = (((num & 0xff00ff00) >> 8) | ((num & 0x00ff00ff) << 8));

  #  This statement uses to swap the bytes of an integer. 
    Let num is 00001000 00001100, after the above expression, it will be 00001100 00001000.

     • Steps 5:
      ((num >> 16) | (num << 16));
   #   The above expression uses to swap the half-word of an integer.
      Means that if the num is 0000000011001110 1000100100000110 
      after the above result number will be 1000100100000110 0000000011001110.
      
--------------------------------------------------------------------------------------------------------

# decimal to Binary
[todo from here]

--------------------------------------------------------------------------------------------------------
# pointers
[todo from here]

•pointers deal with address and value.

•memory address store value,address also strore other address has value.

-->**pointers** are variables which store address.
when we declare  int *p=&a;
p stores '&a' has value. 
so, **'p'** has **value** '&a' ,if not assigned it wil be (**NIL**).

there are two operators associated with pointers.
1) '*' which refers to indirection operation ('content @').
2) '&' which refers to address of the operator.

**Example**

    int i =0;                                     |
    int *q,*p=NULL;                               |
    printf("&i=%p i=%d\n",&i,*(&i));              | &i==>004(a's address)  i=0(a's value)
    printf("p=%p\n",p);                           | p=(NIL) -->p's value
    p=&i;                                         |
    printf("p=%p *p=%d &p=%p q=%p\n",p,*p,&p,q);  | p=004 (p's value)  *p=0 (contenet @ p's value)  &p=008 (address of p)  
    return 0;                                     | q=(NIL) --> Q's value(no address value stored yet). 

**Note** &(&p)  -->we cannot take address of address(i.e its a constant not a valid memory location)
-------------------------------------------------------------------------------------------------------
# memory
[todo from here]

-------------------------------------------------------------------------------------------------------
# big/little endian
[todo from here]

-------------------------------------------------------------------------------------------------------
# function pointers & typedef
[todo from here]

------------------------------------------------------------------------------------------------------
# pointers and array
[todo from here]

------------------------------------------------------------------------------------------------------
# data structure(linked list)
[todo from here]

-----------------------------------------------------------------------------------------------------
# strings
[todo from here]

-----------------------------------------------------------------------------------------------------
# alignment in structure and bit feilds
[todo from here]
https://www.youtube.com/watch?v=Tk-i7iSzCWY
------------------------------------------------------------------------------------------------------
honor mention 
https://www.youtube.com/channel/UCb9okJF6NGPDUGgAQxu3TcA/search?query=c
https://www.youtube.com/watch?v=gGTad760ogM&list=PLTQzjZn0BgA7BHHWKiuhG59bLO7TbNS41&index=48
https://www.youtube.com/user/EmbeddedSoftware/search?query=static


to-do 
-----
wifi p2p service implementaion ref with praneeth bog

Overview of WifiP2pService Impl in androidT Source

  WifiP2pServiceImpl is the core implementation of WiFi P2P (Peer-to-Peer) services in Android.
  It manages Wi-Fi P2P connections, group formation, and device discovery.
  This class implements the IWifiP2pManager interface, which defines the methods that can be called by applications to use Wi-Fi P2P feature.

Key Components
1. State Management

The class maintains various state variables to keep track of P2P operations, such as:
    mP2pStateMachine: Handles the Wi Fi P2P state machine
    mDiscoveryStarted:Indicates if device discovery is active
    mNetworkInfo: Stores current network information

2. P2P State Machine

The P2P state machine (implemented in a separate class) handles different states of Wi-Fi P2P operations, such as:
    Inactive
    Enabled
    Discovering
    Connected

3. Device Discovery

    Methods like discoverPeers () initiate the discovery of nearby Wi Fi P2P devices.
4. Connection Handling

    Functions like connect () and cancelConnect () manage P2P connections with other devices.
5. Group Operations

    Methods for creating, removing, and managing P2P groups, such as createGroup () and removeGroup ()) .

Key Methods
Here are some important methods in WifiP2pServiceImpl:

    initialize () : Sets up the P2P service, including initializing the state machine.
    discoverPeers (): Starts peer discovery.
    connect () : Initiates a connection to another P2P device
    cancelConnect () : Cancels an ongoing connection attempt.
    CreateGroup (): Creates a P2P group with the device as the group owner.
    removeGroup (): Removes the current P2P group.
    getDeviceList (): Retrieves the list of d1scovered P2P devices.
    setDeviceName () : Sets the device name
    setWfdInfo () : Sets.Wi-Fi Display information.

Implementation Details

    The class uses a lot of asynchronous operations, often returning immediately and using callbacks to notify results.
    It extensively uses the WifiP2pStateMachine to managel different states and transitions.
    Many operations involve checking permissions and validating parameters before execution.
    The class interacts with lower-level Wi-Fi services and hardware through the WifiNative interface.

Based on the WifiP2pServiceImpl.java code ,

state machine diagram description for the Wi-Fi P2P process, including main states, substates, and a sequence diagram for the enable
Here's a detailed breakdown:

State Machine Diagram
----------------------

    Main States and Substates
    DefaultState
        Substate: MessageHandling
        Substate: ErrorLogging
    P2pDisabledState
        Substate: WaitingForEnable
    P2pEnablingState
        Substate: InitializingP2p
        Substate: StartingSupplicant
        Substate: SettingDeviceName
        Substate: DiscoveryPeer
    InactiveState
        Substate: IdleListening
        Substate: HandleConnectRequest
    GroupCreatingState
        Substate: NegotiatingGroupParameters
        Substate: FormingGroup
    UserAuthorizingInvitationState
        Substate: DisplayingInvitation
        Substate: WaitingForUserResponse
    ProviionDiscoveryState
        Substate: ExchangingProvisionInfo
        Substate: PreparingGroupFormation
    GroupNegotiationState
        Substate: DeterminingGroup0wner
        Substate: ConfiguringConnection
    FrequencyConfliċtState
        Substate: DetectingConflicts
        Substate: ResolvingConflicts
    GroupCreatedState
        Substate: ManagingConnections
        Substate: MaintainingGroup
    P2pDisablingState
        Substate: StoppingP2p
        Substate: ReleasingResources

Key Transitions
---------------

    P2pDisabledstate P2pEnablingState (on enable request)
    P2pEnablingState → InactiveState (when P2P enabled success fully)
    InactiveState → GroupCreatingState (on group creation request)
    GroupCreatingState GroupNegotiationState (when negotiation starts)
    GroupNegotiationState GroupCreatedState (when group formed)
    InactiveState UserAuthorizingInvitationState (on invitation received)
    UserAuthorizingInvitationState ProvisionDiscoveryState (on user acceptance)
    ProvisionDiscoveryState GroupNegotiationState (when provision complete)
    Any State → FrequencyConflictState (on frequency conflict detected)
    Any State → P2pDisablingState (on disable request)


1-2
Sequence Diagram for  **Enable State**

    User -> WifiP2pServiceImpl: Enable P2P
    WifiP2pService Impl> P2pEnablingState: Transition
    P2pEnablingState -> WifiNative: Initialize P2P
    WifiNative -> P2pEnablingState: P2P Initialized
    P2pEnablingState -> WifiNative: Start Supplicant
    WifiNative -> P2pEnablingState: Supplicant Started
    P2pEnablingState -> WifiNative: Set Device Name
    WifiNative -> P2pEnablingState: Device Name Set
    P2pEnablingState -> WifiNative: Discover Peers
    WifiNative -> P2pEnablingState: Discovery Started
    P2pEnablingState -> InactiveState: Transition
    InactiveState -> User: P2P Enabled

This sequence diagram shows the flow of actions when enabling P2P:

    User requests to enable P2P
    System transitions to P2pEnablingState
    P2P is initialized
    Supplicant is started
    Device name is set
    Peer discovery is initiated
    System transitions to Inactivestate
    User is notified that P2P is enabled

    The DiscoveryPeer substate in the P2pEnablingState, is represented by the "discover Peers" step in this sequence.
    This action initiates the peer discovery process, which is a crucial part of enabling P2P functionality.
    This state machine and sequence diagram capture the complex behavior of the Wi-Fi P2P service,
    showing how it transitions between different states and substates based on user actions, system event9, and P2P protocol requirements,

HIGH LEVEL TRANSISTION SEQUENCE
-------------------------------

DefaultState
------------

    specific events or conditions that trigger transitions between states.
    Detailed State Transitions
    Defaultstate → P2pDisabledstate
    Trigger: System startup, P2P support detected
    External    Defaultstate: Message
    DefaultState → MessageHandling: Process Message
    MessageHandling → DefaultState: Message Handled
    Defaultstate → ErrorLogging: Log Error (if any)
    ErrorLogging → DefaultState: Error Logged

P2pDisabledState
----------------

    specific events or conditions that trigger transitions between states.
    P2pDisabledState P2pEnablingState
    Trigger: CMD P2P ENABLE
    User → P2pDisabledState: Enable P2P
    P2pDisabledState → WaitingForEnable: Wait for Enable
    WaitingForEnable → P2pEnablingState: Transition

P2pEnablingState
----------------

    specific events or conditions that trigger transitions between states.
    P2PEnablingState → InactiveState
    Trigger: Wifi P2pManager. ENABLE P2P SUCCEEDED

high level sequence

    P2pEnablingState -> InitializingP2p: Initialize P2P
    InitializingP2p -> StartingSupplicant: Start Supplicant
    StartingSupplicant -> SettingDeviceName: Set Device Name
    SettingDeviceName -> DisçoveryPeer: Start Peer Discovery
    DiscoveryPeer -> InactiveState: Transition

******************************************************

detailed sequence diagrams and trigger information for the transitions from P2pEnablingState to InactiveState.

    P2pEnablingState → InactiveState
    Trigger: WifiP2pManager. ENABLE P2P SUCCEEDED
    Trigger Details:
    The **ENABLE P2P SUCCEEDED** event is generated internally by the P2pEnablingState after successfully completing 
    all the steps to enable P2P.

    This includes setting up the interface, registering callbacks, qetting the device address, setting the device 
    name, and flushing any existing P2 P and service configurat

    If all these steps complete successfully, the state machine transitions to the InactiveState, indicating that 
    P2P is now enabled and ready for further operations.

Sequence Diagram:

  text
 
      User->WifiP2pServiceImpl: enable ()
      WifiP2pService Impl->P2pEnablingState: CMD P2P ENABLE
      P2pEnablingState->WifiNative: setup Interface ()
      WifiNative->P2pEnablingState: Success
      P2pEnablingState->WifiNative: registerCallback ()
      WifiNative->P2pEnablingState: Success
      P2pEnablingState->WifiNative: p2pGet DeviceAddress ()
      WifiNative->P2pEnablingState: Device Address
      P2pEnablingState->WifiNative: p2pSetDeviceName ()
      WifiNative->P2pEnablingState : Success
      P2pEnablingState->WifiNative : p2pFlush ()
      WifiNative->P2pEnablingState: Success
      P2pEnablingState->WifiNative: p2pServiceFlush ()
      WifíNative->P2pEnablingState: Success
      P2pEnablingState->WifiP2pServiceImpl: ENABLE P2P_ SUCCEEDED
      WifiP2pServiceImpl->InactiveState: Transition
      InactiveState->WifiP2pService Impl: Update internal state
      WifiP2pServiceImpl->User: onP2pEnabled callback

P2pEnablingState → P2pDisabledState
-----------------------------------
detailed sequence diagrams and trigger information for the transitions from P2pEnablingState to
P2pDisabledState.

    Trigger: WifiP2pManager.ENABLE P2P FAILED
      Trigger Details:
      The **ENABLE P2P FAILED** event is generated if any of the steps in the enabling process fail.
      This could happen due to various reasons such as:
      Failure to set up the P2P interface
      Unable to register callbacks with WifiNative
      Failure to get the device address
      Unable to set the device name
      Faílure ín flushing existing configurations
      If any of these steps fail, the state machine immediately transitions back to the P2pDisabledState.
      The failure ig reported back to the user through an onFailure callback.
  
Sequence Diagram:
----------------
    text
      User->WifiP2pService Impl: enable ()
      WifiP2pService Tmpl->P2pEnablingState: CMD P2P ENABLE
      P2pEnablingState->WifiNative: setup Tnterface ()
      WifiNative->P2pEnablingState: Failure
      P2pEnablingState->WifiP2pServiceImpl: NABLE P2P FAILED
      WifiP2pService Impl-SP2pDisabledState: Transition
      P2pDis abledState->WifiP2pServiceImpl: Update internal state
      WifiP2pService Impl->User:i onFailure callback
      Note: Failure coulld occur at any step (setupInterface, registerCallback, etc.)

Additional Notes:
    The P2pEnablingState is a transitional state. It's not meant for long-term residence.
    If the enabling process succeeds, it moves to InactiveState, making the P2P functionality available.
    If the process fails at any point, it reverts to P2pDisabledstate, ensuring the system rema ins in a consistent state.
    The detailed steps in the enabling process ensure that the P2P subsystem is properly initialized before allowing any P2P operations.
    
**************************************************
**InactiveState**

    specific events or conditions that trigger transitions between states
    InactiveState GroupCreatingState
    Trigger: CMD P2P CREATE GROUP or CMD P2P CONNECT
    InactiveState -> IdleListening: Listen for Events
    IdleListening -> HandleConnectRequest: Connection Request Received
    HandleConnectRequest -> GroupCreatingState: Initiate Group Creation

specific events or conditions that trigger transitions between states.

    InactiveState GroupCreatingState
    Trigger: CMD P2P CREATE GROUP or CMD P2P CONNECT
    Trigger details:-
    CMD P2P CREATE GROUP:
    Initiated when a user or application requests to Create a P2P group
    Can be triggered by calling WìfiP2pManager.createGroup () method
    Starts the process. of becoming a Group Owner (GO)
    CMD P2P CONNECT:
    Initiated when a user or application requests to Connect to another P2P device
    Can be triggered by calling WìfiP2pManager. connect () method
    Starts the process of either joining an existing group or negotiating to form a new group
    sequence
    User->WifiP2pService Impl: createGroup () or connect ()
    WifiP2pService Impl->InactiveState: CMD P2P CREATE GROUP or CMD P2P CONNECT
    InactiveState->WifiNative: p2pGroupAdd () or p2pConnect ()
    WifiNative->InactiveState: Success
    InactiveState->GroupCreatingState: Transition
    GroupCreatingState->WifiP2pService Impl: Update internal state
    WifiP2pService Impl->User: onSuccess callback
1-5
