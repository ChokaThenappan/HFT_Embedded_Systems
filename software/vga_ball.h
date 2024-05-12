#ifndef _VGA_BALL_H
#define _VGA_BALL_H

#include <linux/ioctl.h>

typedef struct {
	unsigned char msg_type; 
  uint32_t timestamp;
  uint32_t order_ref_number;
  uint32_t trans_id;
  uint32_t order_book_id;
  unsigned char side;
  uint32_t qty;
  uint64_t price;
  uint32_t yield
  unsigned char buffer_not_empty;
  unsigned char readportt;
} vga_ball_color_t;


typedef struct {
  vga_ball_color_t message;
} vga_ball_arg_t;

#define VGA_BALL_MAGIC 'q'

/* ioctls and their arguments */
#define VGA_BALL_WRITE_DATA _IOW(VGA_BALL_MAGIC, 1, vga_ball_arg_t *)
#define VGA_BALL_READ_DATA  _IOR(VGA_BALL_MAGIC, 2, vga_ball_arg_t *)

#endif
