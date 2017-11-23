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
    int index ;
    bool emptyFlag;
    linked_List lkl;
    link_pointer start, current, rear;

    nested(int index)
    {
        this->index = index;
        emptyFlag =false;
    }

    void add(int num)
    {
        if(index == 0)
        {
            start = (link_pointer) malloc(sizeof(linked_List));
            start->element = num;
            start->link = NULL;
            current = start;
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
        if(indexNum < index)
        {
            link_pointer temp = (link_pointer) malloc(sizeof(linked_List));
            temp->element = num;
            temp->link = NULL;

            // find the right place
            if(indexNum > 0)
            {
                for(int i=0; i<indexNum-1; i++)
                    current = current->link;
                // and then insert
                temp->link = current->link;
                current->link = temp;

                current =start;
                index++;
                show();
            }
            else
                {
                    temp->link = start;
                    start = temp;
                    current = start;
                    index++;
                    show();
                }

        }
        else if(indexNum == index)
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
                if(start == NULL)
                    emptyFlag = true;
                index--;
            }
            else if(indexNum == index)
            {
                if(emptyFlag == false)
                {
                    while(current->link->link != NULL)
                        current = current->link;

                    // find and then delete
                    current->link = NULL;
                    rear = current;
                    index--;
                }
                current = start;

            }
            else if(indexNum < index && indexNum !=1)
            {
                link_pointer delete_ptr;
                for(int i=1;i<indexNum-1;i++)
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

            for(int k=0; k<index-1; k++)
            {
                next = current->link;
                current->link = before;
                before = current;
                current = next;
            }
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
    nested obj(0);
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
