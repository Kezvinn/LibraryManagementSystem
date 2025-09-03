# Compiler
CXX = g++
CXXFLAGS = -c

# Object files
OBJS = ./output/main.o ./output/member.o ./output/user.o ./output/admin.o ./output/share_fn.o ./output/book.o ./output/library.o

# Final target
all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe

./output/main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o ./output/main.o

./output/user.o: ./user/user.cpp
	$(CXX) $(CXXFLAGS) ./user/user.cpp -o ./output/user.o

./output/member.o: ./member/member.cpp
	$(CXX) $(CXXFLAGS) ./member/member.cpp -o ./output/member.o

./output/admin.o: ./admin/admin.cpp
	$(CXX) $(CXXFLAGS) ./admin/admin.cpp -o ./output/admin.o

./output/share_fn.o: ./share_fn/share_fn.cpp
	$(CXX) $(CXXFLAGS) ./share_fn/share_fn.cpp -o ./output/share_fn.o

./output/book.o: ./book/book.cpp
	$(CXX) $(CXXFLAGS) ./book/book.cpp -o ./output/book.o

./output/library.o: ./library/library.cpp
	$(CXX) $(CXXFLAGS) ./library/library.cpp -o ./output/library.o

clean: 
	del /Q .\output\*.o main.exe
