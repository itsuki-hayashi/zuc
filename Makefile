main.exe: zuc.c main.c zuc.h 
    cl /nologo /Ox /Oi /favor:INTEL64 /arch:AVX2 /Gr /Qpar /Za /Wall  main.c zuc.c
clean:
    del *.obj *.exe
test: main.exe
    .\main.exe