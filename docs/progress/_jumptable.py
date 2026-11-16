import struct
f = open('C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe','rb')
data = f.read()
# image base: find PE header
pe = struct.unpack('<I', data[0x3C:0x40])[0]
imgbase = struct.unpack('<Q', data[pe+0x1C:pe+0x24])[0] if False else None
# optional header magic
magic = struct.unpack('<H', data[pe+0x18:pe+0x1A])[0]
print('pe', hex(pe), 'magic', hex(magic))
if magic == 0x20b:  # PE32+
    imgbase = struct.unpack('<Q', data[pe+0x18+0x10:pe+0x18+0x18])[0]
else:
    imgbase = struct.unpack('<I', data[pe+0x18+0x10:pe+0x18+0x14])[0]
print('imgbase', hex(imgbase))
rva = 0xF2BF2B0
off = rva - imgbase
print('file off', hex(off))
for i in range(8):
    v = struct.unpack('<i', data[off+i*4:off+i*4+4])[0]
    print(i, hex(rva+i*4), '->', hex(rva+v))