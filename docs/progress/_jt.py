import struct
f = open('C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe','rb')
data = f.read()
sections = [
 ('.text', 0x1000, 0xeec65d6, 0x400, 0xeec6600),
 ('.rdata', 0xeec8000, 0x3441284, 0xeec6a00, 0x3441400),
 ('.data', 0x1230a000, 0x8d4b68, 0x12307e00, 0x56c800),
]
def rva2off(rva):
    for name, va, vs, raw, rs in sections:
        if va <= rva < va+vs:
            return raw + (rva - va)
    return None
off = rva2off(0xF2BF2B0)
print('off', hex(off))
for i in range(8):
    v = struct.unpack('<i', data[off+i*4:off+i*4+4])[0]
    print(i, hex(0xF2BF2B0+i*4), 'rel', hex(v), '-> abs', hex(0xF2BF2B0+v))