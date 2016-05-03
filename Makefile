main.exe: zuc.c main.c zuc.h 
    cl /nologo /Ox main.c zuc.c
clean:
    del *.obj *.exe
test: main.exe
    .\main.exe