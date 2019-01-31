#include "servocomm.h"

int fd = -1;               // used to open /dev/mem for access to physical addresses
void *LW_virtual;          // used to map physical addresses for the light-weight bridge

int init_servos(void){
   // Create virtual memory access to the FPGA light-weight bridge
   if ((fd = open_physical (fd)) == -1)
      return (-1);
   if ((LW_virtual = map_physical (fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)) == NULL)
      return (-1);
   return 0;
}

int close_servos(void){
    unmap_physical (LW_virtual, LW_BRIDGE_SPAN);   // release the physical-memory mapping
    close_physical (fd);   // close /dev/mem
}

// This program writes a PWM value to servos
int servo_write_R(int pulse){
    // if(argc < 2) {
	//     printf("Please supply argument for value to write to servo");
	//     return 0;
    // }

    volatile int * CTR_ptr;   // virtual address pointer to servos

    // Value to be written on servo
    int write_val = pulse;

    // Set virtual address pointer to I/O port
    CTR_ptr = (unsigned int *) (LW_virtual + SERVO_1_BASE);
    *(CTR_ptr) = write_val;

    return 0;
}

// This program writes a PWM value to servos
int servo_write_L(int pulse){
    // if(argc < 2) {
	//     printf("Please supply argument for value to write to servo");
	//     return 0;
    // }

    volatile int * CTR_ptr;   // virtual address pointer to servos

    // Value to be written on servo
    int write_val = pulse;

    // Set virtual address pointer to I/O port
    CTR_ptr = (unsigned int *) (LW_virtual + SERVO_0_BASE);
    *(CTR_ptr) = write_val;

    return 0;
}

int servo_feedback_R(void){

    volatile int * servo_ptr;   // virtual address pointer to servos
    unsigned int read_val;

    servo_ptr = (unsigned int *) (LW_virtual + SERVO_1_BASE);
    read_val = *(servo_ptr);
    // printf("%d\n", read_val);
    usleep(1000);
    return read_val;
}

int servo_feedback_L(void){

    volatile int * servo_ptr;   // virtual address pointer to servos
    unsigned int read_val;

    servo_ptr = (unsigned int *) (LW_virtual + SERVO_0_BASE);
    read_val = *(servo_ptr);
    // printf("%d\n", read_val);
    usleep(1000);
    return read_val;
}

// Open /dev/mem, if not already done, to give access to physical addresses
int open_physical (int fd)
{
   if (fd == -1)
      if ((fd = open( "/dev/mem", (O_RDWR | O_SYNC))) == -1)
      {
         printf ("ERROR: could not open \"/dev/mem\"...\n");
         return (-1);
      }
   return fd;
}

// Close /dev/mem to give access to physical addresses
void close_physical (int fd)
{
   close (fd);
}

/*
 * Establish a virtual address mapping for the physical addresses starting at base, and
 * extending by span bytes.
 */
void* map_physical(int fd, unsigned int base, unsigned int span)
{
   void *virtual_base;

   // Get a mapping from physical addresses to virtual addresses
   virtual_base = mmap (NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, base);
   if (virtual_base == MAP_FAILED)
   {
      printf ("ERROR: mmap() failed...\n");
      close (fd);
      return (NULL);
   }
   return virtual_base;
}

/*
 * Close the previously-opened virtual address mapping
 */
int unmap_physical(void * virtual_base, unsigned int span)
{
   if (munmap (virtual_base, span) != 0)
   {
      printf ("ERROR: munmap() failed...\n");
      return (-1);
   }
   return 0;
}

