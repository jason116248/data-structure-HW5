#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
typedef struct linked_List* link_pointer;
typedef struct linked_List
{
    int element;
    link_pointer link;
};

typedef struct nested
{
    int index ; //用來計算現在list中有幾個元素的變數
    bool emptyFlag; //用來控制list中若沒有元素的情況
    linked_List lkl;
    link_pointer start, current, rear;

    nested(int index)
    {
        this->index = index;
        emptyFlag =false;
    }

    void add(int num)
    {
        if(index == 0) //如果list中沒有任何元素
        {
            start = (link_pointer) malloc(sizeof(linked_List));
            start->element = num;
            start->link = NULL;
            current = start; //current在最初和最後都會和start指向一樣的地方
            rear = start;
        }
        else
        {
            link_pointer temp = (link_pointer) malloc(sizeof(linked_List));
            temp->element = num;
            temp->link = NULL;
            rear->link = temp;
            rear = temp;
        }
        index++;
        show();
    }

    void insertion(int indexNum, int num)
    {
        if(indexNum < index) //插入的位置比總個數要小，合理
        {
            link_pointer temp = (link_pointer) malloc(sizeof(linked_List));
            temp->element = num;
            temp->link = NULL;

            // find the right place
            if(indexNum > 0)
            {
                for(int i=0; i<indexNum-1; i++) //讓current移動到要插入的位置的前一個元素
                    current = current->link; 
                // and then insert
                temp->link = current->link;  // 此二行順序不可掉換
                current->link = temp;

                current =start;  //最後讓current回到最初的狀態
                index++;
                show();
            }
            else //想插在第一個元素前面
                {
                    temp->link = start;
                    start = temp;
                    current = start;
                    index++;
                    show();
                }

        }
        else if(indexNum == index) //剛好要插在最後一個元素的後面
        {
            link_pointer temp = (link_pointer) malloc(sizeof(linked_List));
            temp->element = num;
            temp->link = NULL;

            rear->link = temp;
            rear = temp;
            index++;
            show();
        }
        else if(indexNum > index)
            {
                cout << "Insert index is out of range!!" << endl ;
                show();
            }
    }

    void deletion(int indexNum)
    {
        if(indexNum <= index)
        {
            if(indexNum == 1)
            {
                current = current->link;
                start = current;
                if(start == NULL) //表示刪除後沒有元素在list中
                    emptyFlag = true;
                index--;
            }
            else if(indexNum == index)  //要刪除list中最後一個元素
            {
                if(emptyFlag == false) //表示list中還有元素
                {
                    while(current->link->link != NULL) //讓current移到list中倒數第二個位置的地方，因為最後一個即將被刪除
                        current = current->link;

                    // find and then delete
                    current->link = NULL;
                    rear = current;
                    index--;
                }
                current = start;

            }
            else if(indexNum < index && indexNum !=1) //刪除非頭尾的元素
            {
                link_pointer delete_ptr; //宣個此指標是為了要記錄即將被刪除元素的連結
                for(int i=1;i<indexNum-1;i++) //找到要刪除的元素的前一個元素，因為刪除就等於跳過元素
                    current = current->link;
                delete_ptr = current->link;
                current->link = delete_ptr->link;
                index--;
                current =start;
            }
            show();
        }
        else
        {
            cout << "Delete index is out of range!!" << endl ;
            show();
        }
    }

    void reversed()
    {
        if(index > 0)
        {
            link_pointer before, next;
            before = start;
            current = before->link;
            //把連結的“箭頭”倒過來指
            for(int k=0; k<index-1; k++)
            {
                next = current->link;
                current->link = before;
                before = current;
                current = next;  //current最後和next變成null
            }
            //最後在頭尾交換前需要將頭的連結設為null
            start->link = NULL;
            current = rear;
            rear = start;
            start = current;
            show();
        }

    }

    void show()
    {
        if(emptyFlag==false)
        {
            for(int i=0; i<index; i++)
            {
                cout << current->element << " ";
                current = current->link;
            }
            //cout << "index: " << index << endl;
            cout << endl << endl;
            current = start;
        }
        else
           {
               cout << "" << endl;
               emptyFlag = false;
           }

    }
};
int main()
{
    char file_name[20]= {};

    cout << "Please enter file's name(remember to enter file's format): ";
    cin >> file_name;
    ifstream ifs(file_name,ios::in);
    string str_add ="ADD";
    string str_delete = "DELETE";
    string str_insert = "INSERT";
    string str_reverse = "REVERSE";
    string str;
    int num,indexNum;
    nested obj(0);  //初始nested，裡面無元素
    while(ifs >> str)
    {
        if(str.compare(str_add)==0)
        {
            ifs >> num;
            obj.add(num);
        }
        else if(str.compare(str_delete)==0)
        {
            ifs >> indexNum;
            obj.deletion(indexNum);
            //cout << indexNum << endl;
        }
        else if(str.compare(str_insert)==0)
        {
            ifs >> num;
            ifs >> str; // input "behind" to str
            ifs >> indexNum;
            obj.insertion(indexNum,num);
            //cout << num << " " << indexNum << endl;
        }
        else if(str.compare(str_reverse)==0)
        {
            obj.reversed();
        }
    }

    return 0;
}
