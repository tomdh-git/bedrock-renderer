# 0xe83aaa0 — RendererContextD3D12 base slot 59

## Summary
Move-assignment of an object holding two small-buffer-optimized polymorphic members at +0x38 and +0x78. Releases a0's current members, then moves (steal or clone) a1's members into a0, leaving a1 empty. Returns a0.

## Signature (x64 Microsoft ABI)
`void* sub_e83aaa0(void* a0, void* a1)` — rcx=a0, rdx=a1, rax=return (a0).

## Reversed source (complete)

// 0xe83aaa0..0xe83aaaf
if (a0 == a1) return a0;

// 0xe83aab5..0xe83aad8
// release a0 +0x78 if present
// 0xe83aad2  call qword ptr [0xF99FFA0]

// 0xe83aae0..0xe83ab28
// move a1 +0x78 into a0 (steal or clone via slot)
// 0xe83ab02  call qword ptr [0xF99FFA0]
// 0xe83ab22  call qword ptr [0xF99FFA0]

// 0xe83ab30..0xe83ab4c
// release a0 +0x38 if present
// 0xe83ab46  call qword ptr [0xF99FFA0]

// 0xe83ab54..0xe83ab98
// move a1 +0x38 into a0 (steal or clone via slot)
// 0xe83ab72  call qword ptr [0xF99FFA0]
// 0xe83ab92  call qword ptr [0xF99FFA0]

// 0xe83aba0..0xe83abac
return a0;

## Struct fields touched
- +0x00: inline buffer for the +0x38 member (R/W via clone/destroy)
- +0x38: pointer member f38 (R/W)
- +0x40: inline buffer for the +0x78 member (R/W via clone/destroy)
- +0x78: pointer member f78 (R/W)

## Callees
- 0xeea6040 (sub_eea6040): vendor boundary, thunk via data slot 0xF99FFA0 (loader-resolved). x6.

## UNRESOLVED CALL = none
