ALLEGRO_LIBRARIES := allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_video-5
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs "$(ALLEGRO_LIBRARIES) <= 5.2.7") -lallegro -lallegro_main

CC := gcc
OUT:= task6.out    # 編譯完的執行檔的名字（可以自己設定）
MAIN:= task_6.c    # 要編譯的task檔案名稱

all: $(MAIN)
    $(CC) -o $(OUT) $(MAIN) $(ALLEGRO_FLAGS)
clean:
    rm $(OUT)