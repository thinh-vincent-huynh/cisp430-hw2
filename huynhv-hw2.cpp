using namespace std;

SIZE = 10;
ARRAY[SIZE] = [7, 4, 8, 11, 6, 5, 10, 3, 9, 2];

struct node{
    int value;
    node* prev;
    node* next;
    node(int _value, node* _prev, node* _next){
        value = _value;
        prev  = _prev;
        next  = _next;
    }
};

void split(node* head,node*&a,node*&b){
    a = b = head;
    count = 1;
    while (b->next){
        b = b->next;
        count++;
    }
    for (int i = 0; i < count / 2; i++){
        b = b->prev;
    }
    b->prev = b->prev->next = NULL;
}

node* merge(node* a, node* b){
    node* c = a;
    while (a->next){ a = a->next; }
    a->next = b;
    b->prev = a;
    return c;
}

node* mergeSort(node* head){
    if (head==NULL){
        return NULL;
    }
    if (head->next==NULL){
        return head;
    }
    node* a = NULL, b = NULL;
    split(head, a, b);
    a = mergeSort(a);
    b = mergeSort(b);
    if (a->value < b->value){
        c = merge(a,b);
    }else{
        c = merge(b,a);
    }
    return c;
}

int main(){
    node* head = new node(ARRAY[0], NULL, NULL);
    node* curr = head;
    for (int i = 1; i < SIZE; i++){
        curr->next = new node(ARRAY[i], curr, NULL);
        curr = curr->next;
    }
}