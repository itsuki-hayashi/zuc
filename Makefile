main.exe: zuc.c main.c zuc.h 
    cl /nologo main.c zuc.c
clean:
    del *.obj *.exe
