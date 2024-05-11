#ifndef _VGA_BALL_H
#define _VGA_BALL_H

#include <linux/ioctl.h>

typedef struct {
	unsigned char msg_type, timestamp, order_ref_number, trans_id, order_book_id, side, qty, price, yield;
} vga_ball_color_t;


typedef struct {
  vga_ball_color_t message;
} vga_ball_arg_t;

#define VGA_BALL_MAGIC 'q'

/* ioctls and their arguments */
#define VGA_BALL_WRITE_DATA _IOW(VGA_BALL_MAGIC, 1, vga_ball_arg_t *)
#define VGA_BALL_READ_DATA  _IOR(VGA_BALL_MAGIC, 2, vga_ball_arg_t *)

#endif
