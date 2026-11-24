import re
pat = re.compile(r"^\s*(?://\s*)?(?:0x)?([0-9a-fA-F]{7,8})  ([a-z]\S*(?: .*)?)", re.M)
ln = "//   0xbcac92a  call qword ptr [0xF99FFA0]"
m = pat.match(ln)
print("match:", m)
if m:
    print(m.group(1), m.group(2))
# also test second form (backticked inline)
pat2 = re.compile(r"\s*0x([0-9a-fA-F]{6,8})\s{2,}([a-zA-Z]\S*(?: .*)?)$")
seg = "0xbcac92a  call qword ptr [0xF99FFA0]"
m2 = pat2.match(seg)
print("inline match:", m2)
