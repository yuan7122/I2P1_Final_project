OUT := game
CC := gcc

CXXFLAGS := -Wall -std=c11 -O2
SOURCE := $(wildcard *.c */*.c)
# SOURCE := $(filter-out tutorial, $(SOURCE))
OBJ := $(patsubst %.c, %.o, $(notdir $(SOURCE)))
RM_OBJ := 
RM_OUT := 

ifeq ($(OS), Windows_NT) # Windows OS
	ALLEGRO_PATH := ../allegro
	export Path := ../MinGW/bin;$(Path)

	ALLEGRO_FLAGS_RELEASE := -I$(ALLEGRO_PATH)/include -L$(ALLEGRO_PATH)/lib/liballegro_monolith.dll.a
	ALLEGRO_DLL_PATH_RELEASE := $(ALLEGRO_PATH)/lib/liballegro_monolith.dll.a
	ALLEGRO_FLAGS_DEBUG := -I$(ALLEGRO_PATH)/include -L$(ALLEGRO_PATH)/lib/liballegro_monolith-debug.dll.a
	ALLEGRO_DLL_PATH_DEBUG := $(ALLEGRO_PATH)/lib/liballegro_monolith-debug.dll.a

	RM_OBJ := $(foreach name, $(OBJ), del $(name) & )
	RM_OUT += $(foreach name, $(*.gch */*.gch), del $(name) & )
	ifeq ($(suffix $(OUT)),)
		RM_OUT += del $(OUT).exe
	else
		RM_OUT += del $(OUT)
	endif
	RM_OUT += $(RM_OBJ)
else # Mac OS / Linux
	UNAME_S := $(shell uname -s)
	export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

	ALLEGRO_LIBRARIES := allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5
	ALLEGRO_FLAGS_RELEASE := $(shell pkg-config --cflags --libs "$(ALLEGRO_LIBRARIES) <= 5.2.7") -lallegro -lallegro_main
	ALLEGRO_DLL_PATH_RELEASE := 
	ALLEGRO_FLAGS_DEBUG := $(ALLEGRO_FLAGS_RELEASE)
	ALLEGRO_DLL_PATH_DEBUG := 

	RM_OBJ := rm $(OBJ)
	RM_OUT := rm $(OUT)

	ifeq ($(UNAME_S), Darwin) # Mac OS
	endif
endif

debug:
	$(CC) -c -g $(CXXFLAGS) $(SOURCE) $(ALLEGRO_FLAGS_DEBUG) -D DEBUG
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_FLAGS_DEBUG) $(ALLEGRO_DLL_PATH_DEBUG)
	$(RM_OBJ)

release:
	$(CC) -c $(CXXFLAGS) $(SOURCE) $(ALLEGRO_FLAGS_RELEASE)
	$(CC) $(CXXFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_FLAGS_RELEASE) $(ALLEGRO_DLL_PATH_RELEASE)
	$(RM_OBJ)

clean:
	$(RM_OUT)