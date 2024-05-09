OUT := game
CC := gcc
CXXFLAGS := -Wall -std=c11 -O2
# Change th numbe to the desired testcase
SOURCE := algif5/src/algif.c algif5/src/bitmap.c algif5/src/lzw.c algif5/src/gif.c
OBJ := algif.o  bitmap.o  lzw.o  gif.o
ifeq ($(OS), Windows_NT)
    ALLEGRO_PATH := ../allegro
	export Path := ../MinGW/bin;$(Path)
	ALLEGRO_FLAGS_RELEASE := -I$(ALLEGRO_PATH)/include -L$(ALLEGRO_PATH)/lib/liballegro_monolith.dll.a
	ALLEGRO_DLL_PATH_RELEASE := $(ALLEGRO_PATH)/lib/liballegro_monolith.dll.a
	ALLEGRO_FLAGS_DEBUG := -I$(ALLEGRO_PATH)/include -L$(ALLEGRO_PATH)/lib/liballegro_monolith-debug.dll.a
	ALLEGRO_DLL_PATH_DEBUG := $(ALLEGRO_PATH)/lib/liballegro_monolith-debug.dll.a
	RM_OBJ := del $(OBJ) *.o
    ifeq ($(suffix $(OUT)),)
		RM_OUT += del $(OUT).exe
	else
		RM_OUT += del $(OUT)
	endif
else
	UNAME_S := $(shell uname -s)
	ALLEGRO_LIBRARIES := allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_video-5
	ALLEGRO_FLAGS_RELEASE := $(shell pkg-config --cflags --libs "$(ALLEGRO_LIBRARIES) <= 5.2.7") -lallegro -lallegro_main
	ALLEGRO_DLL_PATH_RELEASE := 
	ALLEGRO_FLAGS_DEBUG := $(ALLEGRO_FLAGS_RELEASE)
	ALLEGRO_DLL_PATH_DEBUG := 
	RM_OBJ := rm *.o
	RM_OUT := rm $(OUT)
endif


all:
	"Please select one of the testcase: test1, test2, test3.....test7"
test1:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task1_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task1_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
test2:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task2_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task2_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
test3:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task3_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task3_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
test4:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task4_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task4_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
test5:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task5_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task5_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
test6:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task6_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task6_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
test7:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) task7_ans.c $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) task7_ans.o $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)
clean:
	$(RM_OUT)