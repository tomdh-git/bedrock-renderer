#pragma once
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

/*
 * docs/progress/oc_U-C4b_header.h — IntraFrameAllocator layouts (unit U-C4b)
 * Target: Minecraft.Windows.exe 1.26.62.01. RVAs relative to image base.
 *
 * Tags: [V] offset verified in disassembly (cite RVA), [I] inferred, [?] unknown.
 * Only VERIFIED offsets are static_asserted. No invented sizes: sizeof() is
 * asserted only where the disassembly establishes the full object size
 * (the 0x38-byte block). Allocator/arena sizes are NOT asserted — view size
 * = last read end; the object may extend beyond observed fields.
 *
 * Layouts:
 *   ifa_allocator_t  — "this"/IntraFrameAllocator object (rcx at 0xa78940 entry)
 *   ifa_arena_t      — pooled arena A = [this+0x00] (bump allocator, rcx in 0xa79700)
 *   ifa_block_t      — 0x38-byte block returned by 0xa78940 (out struct)
 *   ifa_ctrl_t       — shared_ptr-style refcount control block [_Refcount_base] [I]
 */

/* ------------------------------------------------------------------ */
/* ifa_ctrl_t — refcount control block (_Refcount_base-like) [I shared_ptr pattern] */
/*   ctrl+0x00 vtable ptr; ctrl+0x08 use count; ctrl+0x0C weak count. */
/*   Ops seen: lock inc/dec [ctrl+0x08], lock dec [ctrl+0x0C],            */
/*             mov [ctrl]->vtable[0] (destroy), vtable[8] (delete).       */
/* ------------------------------------------------------------------ */
typedef struct ifa_ctrl_t {
	void*     vtable;        /* +0x00 vtable pointer                              [I] */
	volatile int32_t use_count;   /* +0x08 use count (lock inc/dec)                   [I] */
	volatile int32_t weak_count;  /* +0x0C weak count (lock dec)                      [I] */
} ifa_ctrl_t;

_Static_assert(offsetof(ifa_ctrl_t, use_count) == 0x08, "ctrl use_count offset");
_Static_assert(offsetof(ifa_ctrl_t, weak_count) == 0x0c, "ctrl weak_count offset");
_Static_assert(sizeof(ifa_ctrl_t) == 0x10, "ctrl size (pad to 16)");

/* ------------------------------------------------------------------ */
/* ifa_block_t — block returned by 0xa78940 (out struct, 0x38 bytes) [V] */
/*   Built by sub_a78fc0 (stack [rbp]) then copied to real out (rsi)   */
/*   by sub_a78940 at 0xa789ca/0xa789d5/0xa789d9.                      */
/* ------------------------------------------------------------------ */
typedef struct ifa_block_t {
	uintptr_t arena_field0;  /* +0x00 [A+0x00]  (0xa7903c mov [rsi],rcx; 0xa7982f)   [V] */
	void*     allocator;     /* +0x08 this        (0xa7903f mov [rsi+8],rdi)           [V] */
	void*     block_ptr;     /* +0x10 aligned start addr  (0xa79836 mov [rsi+0x10],r10)[V] */
	uintptr_t size;          /* +0x18 size in bytes       (0xa7983a mov [rsi+0x18],r8) [V] */
	uintptr_t offset;        /* +0x20 offset within arena (0xa7983e mov [rsi+0x20],rax)[V] */
	uintptr_t page_base;     /* +0x28 [A+0x88] page base  (0xa79842 mov [rsi+0x28],rdx)[V] */
	uint8_t   flag;          /* +0x30 success flag =1     (0xa79053 mov byte [rsi+0x30],1)[V] */
	char      pad_0x31[7];   /* +0x31..0x37                                           */
} ifa_block_t;

_Static_assert(offsetof(ifa_block_t, arena_field0) == 0x00, "block arena_field0 offset");
_Static_assert(offsetof(ifa_block_t, allocator)   == 0x08, "block allocator offset");
_Static_assert(offsetof(ifa_block_t, block_ptr)   == 0x10, "block block_ptr offset");
_Static_assert(offsetof(ifa_block_t, size)        == 0x18, "block size offset");
_Static_assert(offsetof(ifa_block_t, offset)      == 0x20, "block offset offset");
_Static_assert(offsetof(ifa_block_t, page_base)   == 0x28, "block page_base offset");
_Static_assert(offsetof(ifa_block_t, flag)        == 0x30, "block flag offset");
_Static_assert(sizeof(ifa_block_t) == 0x38, "block size == 0x38 (verified: sub_a78fc0 writes [rbp+0x00..0x2F] + byte [rbp+0x30])");

/* ------------------------------------------------------------------ */
/* ifa_allocator_t — IntraFrameAllocator object ("this") [V field reads] */
/*   Tracked via descscan2.py 0xa78940 --reg r15 (this) + direct reads */
/*   in sub_a78940 / sub_a79120. this+0x00 = pointer to arena A.       */
/*   Reset-zeroed fields (+0x38,+0x58,+0x68,+0x78,+0x80,+0x98,+0xA8)   */
/*   are from sub_a79900 (init/reset candidate) — [I].                 */
/*   sizeof NOT asserted (not fully verified; view size = last write   */
/*   end = +0xA9).                                                     */
/* ------------------------------------------------------------------ */
typedef struct ifa_allocator_t {
	void*     arena;         /* +0x00 ptr to arena A           [V] 0xa78fda mov rcx,[rcx] */
	volatile int64_t refcount; /* +0x08 refcount (lock inc/dec qword) [V] 0xa7897d/0xa78a0c */
	uintptr_t  field_0x10;   /* +0x10                          [V] 0xa78b27 mov r8,[r15+0x10] */
	uintptr_t  field_0x18;   /* +0x18 cumulative bytes (lock add) [V] 0xa78cc8/0xa78ff9 */
	char       pad_0x20[8];  /* +0x20..0x27 gap */
	uintptr_t  field_0x28;   /* +0x28                          [V] 0xa78b2b */
	uintptr_t  field_0x30;   /* +0x30                          [V] 0xa78b2f */
	uintptr_t  field_0x38;   /* +0x38 zeroed by sub_a79900       [I] */
	uintptr_t  page_begin;   /* +0x40 page-vector begin        [V] 0xa78b46 / sub_a79120 */
	uintptr_t  page_end;     /* +0x48 page-vector end/cap      [V] 0xa78b4a / sub_a79120 */
	char       pad_0x50[8];  /* +0x50..0x57 gap */
	uintptr_t  field_0x58;   /* +0x58 zeroed by sub_a79900       [I] */
	char       pad_0x60[8];  /* +0x60..0x67 gap */
	uintptr_t  field_0x68;   /* +0x68 zeroed by sub_a79900       [I] */
	char       pad_0x70[8];  /* +0x70..0x77 gap */
	uintptr_t  field_0x78;   /* +0x78 zeroed by sub_a79900       [I] */
	uint16_t   generation;   /* +0x80 generation word          [I] sub_a79900 word+0x80=0 */
	char       pad_0x82[6];  /* +0x82..0x87 gap */
	void*     mutex;         /* +0x88 mutex (lea rcx,[this+0x88] -> sub_e943178) [V] 0xa78a1f */
	volatile int32_t state;  /* +0x90 arena state (0/1)        [V] 0xa7896f/0xa78a2f */
	char       pad_0x94[4];  /* +0x94..0x97 gap */
	volatile uint8_t flag_0x98;/* +0x98 flag                      [I] sub_a79900 byte+0x98=0 */
	char       pad_0x99[0xA8 - 0x99]; /* +0x99..0xA7 gap */
	volatile uint8_t flag_0xA8;/* +0xA8 flag                      [I] sub_a79900 byte+0xA8=0 */
} ifa_allocator_t;

_Static_assert(offsetof(ifa_allocator_t, arena)        == 0x00, "allocator arena offset");
_Static_assert(offsetof(ifa_allocator_t, refcount)     == 0x08, "allocator refcount offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x10)   == 0x10, "allocator field_0x10 offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x18)   == 0x18, "allocator field_0x18 offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x28)   == 0x28, "allocator field_0x28 offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x30)   == 0x30, "allocator field_0x30 offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x38)   == 0x38, "allocator field_0x38 offset");
_Static_assert(offsetof(ifa_allocator_t, page_begin)   == 0x40, "allocator page_begin offset");
_Static_assert(offsetof(ifa_allocator_t, page_end)     == 0x48, "allocator page_end offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x58)   == 0x58, "allocator field_0x58 offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x68)   == 0x68, "allocator field_0x68 offset");
_Static_assert(offsetof(ifa_allocator_t, field_0x78)   == 0x78, "allocator field_0x78 offset");
_Static_assert(offsetof(ifa_allocator_t, generation)   == 0x80, "allocator generation offset");
_Static_assert(offsetof(ifa_allocator_t, mutex)        == 0x88, "allocator mutex offset");
_Static_assert(offsetof(ifa_allocator_t, state)        == 0x90, "allocator state offset");
_Static_assert(offsetof(ifa_allocator_t, flag_0x98)    == 0x98, "allocator flag_0x98 offset");
_Static_assert(offsetof(ifa_allocator_t, flag_0xA8)    == 0xA8, "allocator flag_0xA8 offset");

/* ------------------------------------------------------------------ */
/* ifa_arena_t — pooled arena A = [this+0x00] (bump allocator) [V]     */
/*   Tracked via descscan2.py 0xa79700 --reg rcx (arena A).            */
/*   sizeof NOT asserted (view size = last read end +0x99).            */
/* ------------------------------------------------------------------ */
typedef struct ifa_arena_t {
	uintptr_t field_0x00;    /* +0x00                          [V] 0xa7982f mov [rsi],r9 (r9=[A+0]) */
	uintptr_t ctrl_ptr;      /* +0x08 ptr to refcount ctrl     [V] 0xa79832 mov [rsi+8],rdi (rdi=[A+8]) */
	char      pad_0x10[8];   /* +0x10..0x17 gap */
	uintptr_t field_0x18;    /* +0x18                          [V] descscan2 +0x18 mov */
	char      pad_0x20[8];   /* +0x20..0x27 gap */
	uintptr_t field_0x28;    /* +0x28                          [V] descscan2 +0x28 mov / sub_a79120 [this+0x28] */
	char      pad_0x30[8];   /* +0x30..0x37 gap */
	uintptr_t allocated;     /* +0x40 allocated cursor (lock add) [V] 0xa797e6 lock add [rcx+0x40] */
	uintptr_t limit;         /* +0x48 limit                    [V] 0xa79712 add rax,[rcx+0x48] */
	uintptr_t bump_cur;      /* +0x50 current bump ptr         [V] 0xa79707 mov rax,[rcx+0x50] */
	uintptr_t bump_end;      /* +0x58 end/cursor (cmpxchg tgt) [V] 0xa7970b/0xa7979f lock cmpxchg [rcx+0x58] */
	uintptr_t field_0x60;    /* +0x60                          [V] 0xa79724 add rax,[rcx+0x60] */
	uintptr_t field_0x68;    /* +0x68                          [V] 0xa79719 add rax,[rcx+0x68] */
	uintptr_t base_page;     /* +0x70 base page ptr            [V] 0xa7971d mov rdx,[rcx+0x70] */
	uintptr_t total;         /* +0x78 total allocated (lock add)[V] 0xa797e1 lock add [rcx+0x78] */
	uint16_t  generation;    /* +0x80 generation (lock inc word)[V] 0xa7972d lock inc word [rcx+0x80] */
	char      pad_0x82[6];   /* +0x82..0x87 gap */
	uintptr_t page_base;     /* +0x88 page base                [V] 0xa797ef mov rdx,[rcx+0x88] */
	uintptr_t cur_page_base; /* +0x90 current page base        [V] 0xa797f6 mov [rcx+0x90],rdx */
	uint8_t   flag;          /* +0x98 flag = 1                 [V] 0xa797fd mov byte [rcx+0x98],1 */
} ifa_arena_t;

_Static_assert(offsetof(ifa_arena_t, field_0x00)   == 0x00, "arena field_0x00 offset");
_Static_assert(offsetof(ifa_arena_t, ctrl_ptr)     == 0x08, "arena ctrl_ptr offset");
_Static_assert(offsetof(ifa_arena_t, field_0x18)   == 0x18, "arena field_0x18 offset");
_Static_assert(offsetof(ifa_arena_t, field_0x28)   == 0x28, "arena field_0x28 offset");
_Static_assert(offsetof(ifa_arena_t, allocated)    == 0x40, "arena allocated offset");
_Static_assert(offsetof(ifa_arena_t, limit)        == 0x48, "arena limit offset");
_Static_assert(offsetof(ifa_arena_t, bump_cur)     == 0x50, "arena bump_cur offset");
_Static_assert(offsetof(ifa_arena_t, bump_end)     == 0x58, "arena bump_end offset");
_Static_assert(offsetof(ifa_arena_t, field_0x60)   == 0x60, "arena field_0x60 offset");
_Static_assert(offsetof(ifa_arena_t, field_0x68)   == 0x68, "arena field_0x68 offset");
_Static_assert(offsetof(ifa_arena_t, base_page)    == 0x70, "arena base_page offset");
_Static_assert(offsetof(ifa_arena_t, total)        == 0x78, "arena total offset");
_Static_assert(offsetof(ifa_arena_t, generation)   == 0x80, "arena generation offset");
_Static_assert(offsetof(ifa_arena_t, page_base)    == 0x88, "arena page_base offset");
_Static_assert(offsetof(ifa_arena_t, cur_page_base)== 0x90, "arena cur_page_base offset");
_Static_assert(offsetof(ifa_arena_t, flag)         == 0x98, "arena flag offset");
