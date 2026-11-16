# U-CW: Clouds & Weather description matching (live data)

## NEXT
Decoding pending: read SkyDescriptions.h, read the 5 visitor .txt files, run python struct decode, compare against Clouds/Weather signatures.

## Method
Python struct decode of each (file, tag) hex line; test Clouds (matrixA +0x00, matrixB +0x40, mesh ptr +0x88... wait, mesh at +0x80) and Weather (mesh +0x00, matrix +0x10, ten vec4 +0x88..+0x127).