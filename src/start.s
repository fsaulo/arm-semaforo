.syntax unified
.cpu    cortex-m3
.fpu    softvfp
.thumb

.section .text.vector_table
.global  _vector_table

_vector_table:
	.word _estack
	.word _start

.section .text.start
.thumb_func

_start:
	bl main
	b  .

