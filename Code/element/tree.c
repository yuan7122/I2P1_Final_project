#include "tree.h"
#include "../scene/sceneManager.h"
#include <time.h>
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "../algif5/src/algif.h"
#include "seeds_c.h"

//#include "Rectangle.h" :not right - see line 3
/*
   [tree function]
*/
int randomTreePosition()
{
    return rand() % 8; // 生成0到7之間的隨機整數
}

Elements *New_Tree(int label)
{
    printf("OK\n");
    Tree *pDerivedObj = (Tree *)malloc(sizeof(Tree));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    
    int position = randomTreePosition();
    static double lastTreeTime = 0.0;
    // setting derived object member
    double now = al_get_time(); // 獲取當前時間
    printf("lastTreeTime1=%f now1=%f\n", lastTreeTime, now);
    if (lastTreeTime==0||now - lastTreeTime >= 10.0) // 檢查是否已經過了十秒
    {
        lastTreeTime = now;
        // 隨機生成樹木位置
        int position = randomTreePosition();
        printf("posittion:%d\n", position);
        // setting derived object member
        pDerivedObj->img = al_load_bitmap("assets/image/Pupu.png");

        if(pDerivedObj->img == NULL)
        {
            printf("Error loading\n");
            free(pDerivedObj); // 釋放 Tree 物件的記憶體
            free(pObj); // 釋放 Elements 物件的記憶體
            return NULL; // 返回空指針，表示失敗
        }
        pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
        pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
        pDerivedObj->x = 0 + position * 118; // 根據隨機位置計算 x 座標
        pDerivedObj->y = HEIGHT - 130;//pDerivedObj->height;
        pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                            pDerivedObj->y + pDerivedObj->height / 3,
                                            pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                            pDerivedObj->y + 2 * pDerivedObj->height / 3);
        //printf("treehitbox: %d\n", pDerivedObj->hitbox);
        // setting the interact object
        pObj->inter_obj[pObj->inter_len++] = Character_L;
        // setting derived object function
        pObj->pDerivedObj = pDerivedObj;
        pObj->Update = Tree_update;
        pObj->Interact = Tree_interact;
        pObj->Draw = Tree_draw;
        pObj->Destroy = Tree_destory;
        pDerivedObj->create_time = al_get_time();
        //lastTreeTime = now;
        //lastTreeTime = now; // 更新上次生成樹木的時間
        //return pObj;
    }
    else{
       printf("else\n"); 
       //pDerivedObj->img = al_load_bitmap("assets/image/Pupu.png");

    }
    printf("lastTreeTime=%f now=%f\n", lastTreeTime, now);
    return pObj;
}
void Tree_update(Elements *self) {
    Tree *Obj = (Tree *)(self->pDerivedObj);
    double now = al_get_time();
    if (now - Obj->create_time >= 10.0) {
        self->dele = true; // 标记为删除
    }
}
void Tree_interact(Elements *self, Elements *tar) {
    // 这里假设 Character 使用的是 'Character' 标签
    Tree *Obj = ((Tree *)(self->pDerivedObj));
    printf("in tree interact\n");
    if (tar->label == Character_L) {
        //Tree *Obj = (Tree *)(self->pDerivedObj);
        Character *chara = (Character *)(tar->pDerivedObj);
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
            reduce_seeds_c_countdown();
            printf("-10s\n"); // 打印 -10
  
        } else {
                printf("No Seeds_c object detected\n"); // 没有检测到 Seeds_c 对象
        }
    } else {
        printf("No Character object detected\n"); // 没有检测到 Character 对象
    }

}
void Tree_draw(Elements *self)
{
    Tree *Obj = ((Tree *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Tree_destory(Elements *self)
{
    Tree *Obj = ((Tree *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}