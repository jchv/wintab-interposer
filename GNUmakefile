CXX32 = i686-w64-mingw32-g++
CXX64 = x86_64-w64-mingw32-g++
LDFLAGS = -Wl,--enable-stdcall-fixup
CXXFLAGS = -Wall -Werror
all: x86 x64 
x86: out/x86/wintab32.dll
x64: out/x64/wintab32.dll
clean:
	@rm -f out/x86/wintab32.dll out/x86/wintab32.o
	@rm -f out/x64/wintab32.dll out/x64/wintab32.o
out/x86/wintab32.dll: src/wintab32.def out/x86/wintab32.o
	$(CXX32) $(LDFLAGS) -o $@ -shared src/wintab32.def out/x86/wintab32.o
	strip $@
out/x86/wintab32.o: src/wintab32.cpp src/wintab32.h
	$(CXX32) $(CXXFLAGS) -c -o $@ src/wintab32.cpp
out/x64/wintab32.dll: src/wintab32.def out/x64/wintab32.o
	$(CXX64) $(LDFLAGS) -o $@ -shared src/wintab32.def out/x64/wintab32.o
	strip $@
out/x64/wintab32.o: src/wintab32.cpp src/wintab32.h
	$(CXX64) $(CXXFLAGS) -c -o $@ src/wintab32.cpp
.PHONY: all, clean, x86, x64
