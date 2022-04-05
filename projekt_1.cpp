#include <iostream>
using namespace std;
typedef string data_type; //definiujemy typ danych

// Definicja typu elementów listy
struct element{
  element *next; //wskaźnik na nastepny element listy
  data_type data;   //dana
};

// Definicja typu obiektowego queue
class queue{
  private:
    element *head;
    element *tail;

  public:
    queue();                   // konstruktor pustej kolejki
    ~queue();                  // destruktor
    int queue_f(int);          // konstruktor pelnej losowej kolejki
    bool isEmpty(void);        // informuje czy kolejka jest pusta
    void enqueue(data_type n); // dodaje element na końcu kolejki
    data_type dequeue(void);   // usuwa i zwraca element z początku kolejki
    data_type front(void);     // zwraca element na przodzie kolejki bez usuwania go
    int size();                // zwraca ilosc przechowywanych elemntow
    int display();             // wysietla wszystkie elementy w kolejce
};

queue::queue(){
  head = tail = NULL;
}

queue::~queue(){
  while(head) dequeue();
}

int queue::queue_f(int n){
  string tab[]={"WT","ST","AR","JD","KJ","MK","OF","JR","PM","AW","AD","JS",
  "KB","JG","WR","JP","DJ","KD","MP","RL","BF","GH","LW","TZ","EB"};
  
  for(int i=0;i<n;i++){
    enqueue(tab[(rand() % 25)]);
  }
  return 1;
}

bool queue::isEmpty(void){
  return !head;
}

void queue::enqueue(data_type n){
  element *w = new element;
  w->next = NULL;
  w->data = n;
  if(tail) tail->next = w;
  else  head = w;
  tail = w;
}

data_type queue::dequeue(void){
  if(head){
    element *w = head;
    data_type returned = head->data;
    head = head->next;
    if(!head) tail = NULL;
    delete w;
    return returned;
  }
  else return "!!!Empty Queue Exception!!!";
}

data_type queue::front(void){
  if(head)  return head->data;
  else return "!!!Empty Queue Exception!!!";
}

int queue::size(){
  int size = 0;
  if(head==NULL) return size;
  else{
    element *wsk=head;
    while(wsk!=NULL){
      size++;
      wsk = wsk->next;
    }
  }
  return size;
}

int queue::display(){
  if(head==NULL){
    cout<<"Kolejka jest pusta";
    return 0;
  }
  else{
    int size = 1;
    element *wsk=head;
    while(wsk!=NULL){
    cout<<endl<<size;
    if(size<10)cout<<".  "<<wsk->data;
    else cout<<". "<<wsk->data;
    wsk = wsk->next;
    size++;
    }
  cout<<endl;
  return 1;
  }
}

int main(){
  queue Q;
  int i;
  data_type data;
  int x=-1;
  string input;
  while(x!=0){
    cout<<endl<<"***********************MENU************************"<<endl;
    cout<<"1. Enqueue (dodanie elementu na koncu kolejki)"<<endl;
    cout<<"2. Dequeue (usuniecie i zwrucenie elementu z poczatku kolejki)"<<endl;
    cout<<"3. Wyswietla element na przodzie kolejki"<<endl;
    cout<<"4. Wyswietl rozmiar kolejki"<<endl;
    cout<<"5. Stwoz gotowa kolejke"<<endl;
    cout<<"6. Wyswietl kolejke"<<endl;
    cout<<"0. Wyjscie z programu."<<endl;
    cout<<"Wybieram: ";
    while(!(cin>>x)){
      cout<<"To nie jest liczba :(\nPodaj jedna z wartosci powyzej\n";
      cout<<"Wybieram: ";
      cin.clear();
      cin.sync();
    }
    switch(x){
       case 0:
              return 0;
              break;
       case 1:
              cout<<"Wprowadz inicjaly:";
              cin>>data;
              Q.enqueue(data);
              break;
       case 2:
              if(Q.isEmpty()){
                cout<<endl<<"Kolejka jest pusta"<<endl;
                break;
              }
              else{
              cout<<endl<<Q.dequeue()<<endl;
              break;
              }
              
       case 3:
              if(Q.isEmpty()){
                cout<<endl<<"Kolejka jest pusta"<<endl;
                break;
              }
              else{
              cout<<endl<<Q.front()<<endl;
              break;
              }
       case 4:
              cout<<endl<<"W kolejce jest "<<Q.size()<<" osob."<<endl;
              break;
       case 5:
              int n;
              cout<<"Podaj liczbe osob w kolejce: ";
              while(!(cin>>n)){
              cout<<"To nie jest liczba :(\nPodaj liczbe osob w kolejce: ";
              cin.clear();
              cin.sync();
              }
              Q.queue_f(n);
              break;
       case 6:
              if(Q.isEmpty()){
                cout<<endl<<"Kolejka jest pusta"<<endl;
                break;
              }
              else{
              Q.display();
              break;
              }
       default:
              cout<<endl<<"Podano bledna wartosc\n";
      }

  }
  return 0;
}