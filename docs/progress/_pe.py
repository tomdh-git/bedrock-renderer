import struct
f = open('C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe','rb')
data = f.read()
print('size', hex(len(data)))
print('first8', data[:8].hex())
pe = struct.unpack('<I', data[0x3C:0x40])[0]
print('e_lfanew', hex(pe))
print('sig', data[pe:pe+4])
magic = struct.unpack('<H', data[pe+0x18:pe+0x1A])[0]
print('magic', hex(magic))
if magic == 0x20b:
    imgbase = struct.unpack('<Q', data[pe+0x28:pe+0x30])[0]
else:
    imgbase = struct.unpack('<I', data[pe+0x28:pe+0x2C])[0]
print('imgbase', hex(imgbase))
# number of sections
nsec = struct.unpack('<H', data[pe+0x06:pe+0x08])[0]
optsize = struct.unpack('<H', data[pe+0x14:pe+0x16])[0]
print('nsec', nsec, 'optsize', hex(optsize))
sec = pe + 0x18 + optsize
for i in range(nsec):
    s = data[sec+i*40:sec+(i+1)*40]
    name = s[:8].rstrip(b'\0').decode()
    vsize, vaddr, rsize, raddr = struct.unpack('<IIII', s[8:24])
    print(name, 'VA', hex(vaddr), 'VSize', hex(vsize), 'Raw', hex(raddr), 'RSize', hex(rsize))