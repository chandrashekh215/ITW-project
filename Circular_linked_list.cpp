#include<iostream>
using namespace std;
class node{
    public:
    int val;
    node*next;
    node*prev;
    node(int data){
        val=data;
        next=NULL;
    }
    ~node(){
        delete next;
    }
};
void insertatfirst(node*&head,int data){
    if(head==NULL){
        node*insertnode=new node(data);
        head=insertnode;
        head->next=head;
    }
    else{
        node*insertnode=new node(data);
        node*temp=head;
        while(temp->next!=head){
            temp=temp->next;
        }
        insertnode->next=head;
        temp->next=insertnode;
        head=insertnode;
        //return head;
    }
}
void insertatpositon(node*&head,int position,int data){
    if(head==NULL){
        node*insertnode=new node(data);
        insertnode=head;
        head->next=head;
    }
    else{
        node*insertnode=new node(data);
        node*temp=head;
        int count=1;
        while(count<position-1){
            temp=temp->next;
            count++;
        }
        insertnode->next=temp->next;
        temp->next=insertnode;
    }
}
void deletefirst(node*&head,int position){
    if(position==1){
        node*temp=head;
        node*prev=head;
        while(temp->next!=head){
            temp=temp->next;
        }
        head=head->next;
        prev->next=NULL;
        delete prev;
        temp->next=head;

    }
}
void reverse(node*&head){
    node* prev = NULL;
    node* current = head;
    node* next = NULL;
    do{
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }while(current!=head);
    head->next = prev;
    head = prev;

}


void print(node*head){
    node*temp=head;
    do{
        cout<<temp->val<<" ";
        temp=temp->next;

    }while(temp!=head);
}
int main(){
    node*head=NULL;
    insertatfirst(head,20);
    insertatfirst(head,15);
    insertatfirst(head,10);
    insertatfirst(head,8);
    
    print(head);
    cout<<endl;
    insertatpositon(head,2,40);
    

    print(head);
    cout<<endl;
    deletefirst(head,1);
    print(head);
    cout<<endl;
    insertatpositon(head,3,100);
    print(head);
    cout<<endl;
    cout<<"reverse LL"<<endl;
    reverse(head);
    print(head);


}