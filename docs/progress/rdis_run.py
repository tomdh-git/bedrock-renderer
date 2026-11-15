import subprocess, sys
EXE = r"C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe"
RDIS = r"tools\rdis\target\release\rdis.exe"
lo, hi, n = sys.argv[1], sys.argv[2], sys.argv[3] if len(sys.argv) > 3 else "200"
out = subprocess.run([RDIS, EXE, lo, "--max", n], capture_output=True, text=True, encoding="utf-8", errors="replace")
print(out.stdout)
print(out.stderr[:500])