CC = g++
CFLAGS = -Wall -std=c++17
TARGET = elfs_tool.exe

all: $(TARGET)

$(TARGET): elfs.cpp
	$(CC) $(CFLAGS) elfs.cpp -o $(TARGET)

clean:
	@if exist $(TARGET) del /f $(TARGET)
	@if exist elfs_disk.img del /f elfs_disk.img

run: $(TARGET)
	./$(TARGET) format