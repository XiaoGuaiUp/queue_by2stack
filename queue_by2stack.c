#include <stdio.h>
#include "seqstack.h"

typedef struct QueueBy2Stack{
    SeqStack input;//input栈 用于入队列的场景
    SeqStack output;//output栈 用于出队列和取队首元素的场景
} QueueBy2Stack;

//初始化
void QueueInit(QueueBy2Stack* q){
    if(q==NULL){
        return;
    }
    SeqStackInit(&q->input);
    SeqStackInit(&q->output);
}

//入队列
void QueuePush(QueueBy2Stack* q,SeqStackType value){
    if(q==NULL){
        return;
    }
    while(1){
        //先把所有output中的元素转移到input中
        SeqStackType top;
        int ret=SeqStackTop(&q->output,&top);
        if(ret==0){
            break;
        }
        SeqStackPop(&q->output);
        SeqStackPush(&q->input,top);
    }
    //把新元素value插入input中
    SeqStackPush(&q->input,value);
    return;
}

//出栈
void QueuePop(QueueBy2Stack* q){
    if(q==NULL){
        return;
    }
    while(1){
        //出栈：把input中的元素，转移到output中
        SeqStackType top;
        int ret=SeqStackTop(&q->input,&top);
        if(ret==0){
            break;
        }
        SeqStackPop(&q->input);
        SeqStackPush(&q->output,top);
    }
    //把output的栈顶元素出栈
    SeqStackPop(&q->input);
}

//取队首元素
int QueueFront(QueueBy2Stack* q,SeqStackType* value){
    //取队首是从output中取队首元素
    //先把input中的元素top插入到output中
    if(q==NULL){
        return 0;
    }
    while(1){
        SeqStackType top;
        int ret=SeqStackTop(&q->input,&top);
        if(ret==0){
            break;
        }
        SeqStackPush(&q->output,top);
    }
    SeqStackTop(&q->output,value);
    return 1;
}

void QueuePrint(QueueBy2Stack* q,const char* msg){
    if(q==NULL){
        return;
    }
    printf("=== input ===\n");
    SeqStackPrint(&q->input,msg);
    printf("=== output ===\n");
    SeqStackPrint(&q->output,msg);
}
void Test(){
    printf("=============%s===============\n",__FUNCTION__);
    QueueBy2Stack q;
    QueueInit(&q);

    QueuePush(&q,'a');
    QueuePush(&q,'b');
    QueuePush(&q,'c');
    QueuePush(&q,'d');
    QueuePrint(&q,"入队列四个元素");

    QueuePop(&q);
    QueuePrint(&q,"出队列一个元素");

    SeqStackType top;
    int ret=QueueFront(&q,&top);
    printf("测试取队首元素\n");
    printf("返回值期望值为1，实际值为：%d\n",ret);
    printf("队首元素为：%c\n",top);
}


void main(){
    Test();
}


