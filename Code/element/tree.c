#include "tree.h"
#include "../scene/sceneManager.h"
#include <time.h>
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "../algif5/src/algif.h"

//#include "Rectangle.h" :not right - see line 3
/*
   [tree function]
*/
int randomTreePosition()
{
    return rand() % 8; // 生成0到7之間的隨機整數
}

bool CheckCollision(Shape *shape1, Shape *shape2) {
    // 获取 shape1 和 shape2 的类型
    ShapeType type1 = shape1->getType();
    ShapeType type2 = shape2->getType();

    // 确保两个形状都是矩形类型，因为你的目的是检测矩形之间的碰撞
    if (type1 != RECTANGLE || type2 != RECTANGLE) {
        return false; // 如果有一个不是矩形，直接返回 false
    }

    // 强制类型转换为 Rectangle
    Rectangle *rect1 = (Rectangle *)(shape1->pDerivedObj);
    Rectangle *rect2 = (Rectangle *)(shape2->pDerivedObj);

    // 判断两个矩形是否相交
    return !(rect1->x2 < rect2->x1 || rect1->x1 > rect2->x2 ||
             rect1->y2 < rect2->y1 || rect1->y1 > rect2->y2);
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
    if (lastTreeTime==0 || now - lastTreeTime >= 10.0) // 檢查是否已經過了十秒
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
        // setting derived object function
        pObj->pDerivedObj = pDerivedObj;
        pObj->Update = Tree_update;
        pObj->Interact = Tree_interact;
        pObj->Draw = Tree_draw;
        pObj->Destroy = Tree_destory;
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
void Tree_update(Elements *self) {}
void Tree_interact(Elements *self, Elements *tar) {
    // 这里假设 Character 使用的是 'Character' 标签
    printf("in tree interact\n");
    if (tar->label == Character_L) {
        Tree *Obj = (Tree *)(self->pDerivedObj);
        Character *charObj = (Character *)(tar->pDerivedObj);

        // 检查是否碰撞
        if (CheckCollision(Obj->hitbox, charObj->hitbox)) {
            self->dele = 1; // 标记树木为删除
            printf("-10s\n"); // 打印 -10s
        }
        else {
            printf("No collision detected\n"); // 没有检测到碰撞
        }
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