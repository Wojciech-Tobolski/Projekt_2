#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

class movie{
  string title;    /* Pole repezentuje tytul filmu*/
  double rate;     /* Pole repezentuje ocene filmu - po niej bedziemy filtrowac dane*/

  public:
  string get_title() const {return title;};  /*funkcja zwracajaca tytul*/
  double get_rate() const {return rate;};    /*funkcja zwracajaca ocene*/

  void set_title(string _title) {title=_title;};    /*funkcja ustawiajaca tytul na wskazany*/
  void set_rate(double _rate) {rate=_rate;};        /*funkcja ustawiajaca ocene na wskazana*/
};

//Przeciazenie operatora wyjscia
ostream& operator << (ostream &cout, const movie &mo){    //przekazujemy jako referencje, ale nie chcemy modyfikowac obiektu dlatego uzywamy const

  cout<<mo.get_rate()<< " "<<mo.get_title()  <<"\n";
  return cout;
}

/*Kolejka*/
typedef movie data_type; //definiujemy typ danych

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
    bool isEmpty(void);        // informuje czy kolejka jest pusta
    void enqueue(data_type n); // dodaje element na końcu kolejki
    data_type dequeue(void);   // usuwa i zwraca element z początku kolejki
    data_type front(void);     // zwraca element na przodzie kolejki bez usuwania go
    int size();                // zwraca ilosc przechowywanych elemntow
};

queue::queue(){
  head = tail = NULL;
}

queue::~queue(){
  while(head) dequeue();
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
  else {
    cout<<"!!!Empty Queue Exception!!!";
    exit;
  } 
}

data_type queue::front(void){
  if(head)  return head->data;
  //else return "!!!Empty Queue Exception!!!";
else {
    cout<<"!!!Empty Queue Exception!!!";
    exit;
  }
}

int queue::size(){
  int size = 0;
  if(head==NULL) return size;
  else{
    element *wsk=head;
    while(wsk!=NULL){
      size++;
      wsk = wsk->next;
      //data;
    }
  }
  return size;
}

/*Sortowania*/

void merge(movie *table, int idx_start, int idx_middle, int idx_end) {

    int n1 = idx_middle - idx_start + 1; // ustalam ilość elementów pierwszej połowy tablicy
    int n2 = idx_end - idx_middle; // ustalam ilość elementów drugiej połowy tablicy
    movie *L = new movie[n1];
    movie *P = new movie[n2]; // iniciuje dwie tablice o rozmiarach jak wyżej

    for (int i = 0; i < n1; i++)
        L[i] = table[idx_start + i]; // zapełniam tablice pierwszą połową wyrazów z tablicy początkowej
    for (int j = 0; j < n2; j++)
        P[j] = table[idx_middle + 1 + j]; // zapełniam tablice drugą połową wyrazów z tablicy początkowej

    int i1, i2, i3;
    i1 = 0; // index tablicy L
    i2 = 0; // index tablicy P
    i3 = idx_start; // index tablicy scalonej

    while (i1 < n1 && i2 < n2) { // gdy oba argumenty są prawdziwe
        if (L[i1].get_rate() <= P[i2].get_rate()) { // jeśli element "lewej" tablicy jest mniejszy badz rowny elementowi prawej
            table[i3] = L[i1]; // przypisuje go do tablicy scalonej
            i1++; // przechodze do nastepnego elementu TEJ SAMEJ tablicy
        } else {
            table[i3] = P[i2]; // jesli elementy w lewej sa juz wieksze - do tablicy scalonej wchodzi element z tablicy "prawej"
            i2++; // przesuniecie na nastepny element w porównaniu
        }
        i3++; // przesuniecie co wykonanie petli o 1 w tablicy z elementami scalonymi
    }

    while (i1 < n1) { // jeśli w tablicy lewej zostały jeszcze jakieś elementy to je przenosimy
        table[i3] = L[i1];
        i1++;
        i3++;
    }
    while (i2 < n2) { // jeśli w tablicy prawej zostały jeszcze jakieś elementy to je przenosimy
        table[i3] = P[i2];
        i2++;
        i3++;
    }
}

void merge_sort(movie *table, int idx_start, int idx_end) {
    if (idx_start < idx_end) {
        int idx_middle = (idx_end + idx_start) / 2; // index podzielenia tablicy na dwie

        merge_sort(table, idx_start, idx_middle); // rekurencyjnie dziele lewa czesc do 1 elementu
        merge_sort(table, idx_middle + 1, idx_end); // rekurencyjnie dziele prawa czesc do 1 elementu
        merge(table, idx_start, idx_middle, idx_end); // scalam te czesci w mniejsze az do rozmiaru tablicy startowej
    }
}

void quick_sort(movie *table, int idx_start, int idx_end)
{   
    int size = idx_end-idx_start;
    int MAXiteration = 2 * log(size) / M_LN2;
    int iteration = 0;
    iteration ++;
  

    if(idx_end <= idx_start) return;

    int i = idx_start - 1; // index pomocniczy idacy od lewej strony
    int j = idx_end + 1; // index pomocniczy idacy od prawej strony
    movie pivot = table[(idx_start + idx_end)/2]; //wybieramy punkt odniesienia

    while(1)
    {
        while(pivot.get_rate() > table[++i].get_rate()); // idąc od lewej strony tabeli do prawej szukam elementu wiekszego od ustalonego pivota
        while(pivot.get_rate() < table[--j].get_rate()); // idąc od prawej strony tabeli do lewej szukam elementu mniejszego od ustalonego pivota

        if( i <= j) // sprawdzam czy liczniki sie minely, jesli nie to zamieniam elementy
            swap(table[i],table[j]); // z biblioteki std, zamienia wartosciami tab[i] z tab[j]
        else
            break; // konczy petle gdy operatory indeksujace sie miną
    }
            // gdy operatory indeksujace sie miną wykonujemy oddzielne sortowanie dla lewej i prawej czesci
            if(j > idx_start)                            // rekurencja do quick_sort, sortowanie lewej czesci
            quick_sort(table, idx_start, j); // tablicy(ktorej juz elementy sa mniejsze niz prawej)
            if(i < idx_end)                              // rekurencja do quick_sort, sortowanie prawej czesci
            quick_sort(table, i, idx_end);  // tablicy(ktorej juz elementy sa wieksze niz lewej)
}


void shell_sort(movie *table, int size) {
    int space = size / 2; // odstep do podziału tablic
    movie temp; // zmienna pomocnicza
    int j = 0; // zmienna pomocnicza
    while(space >= 1) { // aż tablice nie beda jednoelementowe
        for (int i = space; i < size; i++) {
            temp = table[i]; // obierany jest element tablicy na ktorym konczyla sie ostatnia operacja
            for (j = i; j >= space && table[j - space].get_rate() > temp.get_rate(); j -= space) //inx wiekszy od przerwy i gdy element tablicy wiekszy od przyrownywanego
                table[j] = table[j - space];
            table[j] = temp; // zamiana elementów
        }
        space /= 2;
    }
}
 
void bucket_sort(movie *table, int n, int min, int max) { //musimy podać min i max najmniejsza i najwieksza wartosc w zbioze
 
  movie *buckets;
  buckets = new movie[max - min + 1];  //tworzymy max-min+1 kubelkow do sortowania danych
  
  for (int x = 0; x < (max - min + 1); x++){ //ustwiamy początkowe wartości liczników (kubelkow)
  buckets[x].set_rate(0);
  }
  for (int x = 0; x < n; x++){    //zliczamy ilość wystąpień poszczególnych elementów i zapisujemy w odpowiednim kubelku
    int r = table[x].get_rate();
    buckets[r-min].set_rate(buckets[r-min].get_rate()+1);
  }
  int j = 0;
  for (int x = 0; x < (max - min + 1); x++){
      int y;
      for ( y = j; y < buckets[x].get_rate() + j; y++){ //wpisujemy odpowiednio elementy z kubeczkow do tablicy
        table[y].set_rate(x + min);
      }
      j = y;
  }
}

int main(){
    fstream file; //obiekt typu fstream (uchwyt do pliku)
    queue Q;
    
    file.open("ranking.txt");
    movie m;
    string bufor;
    char ch[100];
    char c;
    int i=0;
      clock_t start, finish; // zmienne do zliczania czasu
      double time = 0;
      start = clock(); // początek zliczania czasu
    
      while(!file.eof()){
        file.get(c);
        string bufor;
        char ch[100];
        
        while(c != '\r' && c != '\n') { 
          int j = 0;
          bufor+=std::string()+c;
          file.get(c);
          j++;
         
        } 
            char ostatni = bufor[bufor.size()-1];
            if ((ostatni>47)&&(ostatni<58)){ //sprawdzamy, czy jest cyfra
            m.set_title(bufor.substr(bufor.find(',')+1, bufor.rfind(',')-(bufor.find(',')+1)));
            char tab[4];
            string str=bufor.substr(bufor.rfind(',')+1, bufor.length()-bufor.rfind(','));
            strcpy(tab,str.c_str());
            m.set_rate(atof(tab));
            Q.enqueue(m);
            /*i++;
            cout<<i<<bufor.substr(bufor.find(',')+1, bufor.rfind(',')-(bufor.find(',')+1))<<endl*/;
          }
    }
    finish = clock(); // koniec zliczania czasu
    
    time = (double)(finish - start) / (double)(CLOCKS_PER_SEC); // przeliczenie na sekundy
    int n = Q.size();
    cout<<"Czas przeszukiwania i tworzenia kolejki z "<<n<<" poprawnymi wpisami trwal : "<<time<<"s."<<endl;
    file.close(); //zamykamy plik
    
    //cout<<n<<endl;
    //cout<<"Koniec"<<endl;
    movie *tabl1,*tabl2,*tabl3,*tabl4,*tab1,*tab2,*tab3,*tab4,*ta1,*ta2,*ta3,*ta4,*t1,*t2,*t3,*t4;
    tabl1 = new movie[n];
    tabl2 = new movie[n];
    tabl3 = new movie[n];
    tabl4 = new movie[n];
    tab1 = new movie[n];
    tab2 = new movie[n];
    tab3 = new movie[n];
    tab4 = new movie[n];
    ta1 = new movie[n];
    ta2 = new movie[n];
    ta3 = new movie[n];
    ta4 = new movie[n];
    t1 = new movie[n];
    t2 = new movie[n];
    t3 = new movie[n];
    t4 = new movie[n];

    for( int i = 0; i < n; i++ ){
      tab4[i]=tab3[i]=tab2[i]=tab1[i]=Q.dequeue();
    }
    for( int i = 0; i < n; i++ ){
      ta4[i]=ta3[i]=ta2[i]=ta1[i]=tab1[i];
    }
    for( int i = 0; i < n; i++ ){
      t4[i]=t3[i]=t2[i]=t1[i]=tab1[i];
    }
    for( int i = 0; i < n; i++ ){
      tabl4[i]=tabl3[i]=tabl2[i]=tabl1[i]=tab1[i];
    }
    movie *t[4];
    t[0]=t1;
    t[1]=t2;
    t[2]=t3;
    t[3]=t4;
    movie *ta[4];
    ta[0]=ta1;
    ta[1]=ta2;
    ta[2]=ta3;
    ta[3]=ta4;
    movie *tab[4];
    tab[0]=tab1;
    tab[1]=tab2;
    tab[2]=tab3;
    tab[3]=tab4;
    movie *tabl[4];
    tabl[0]=tabl1;
    tabl[1]=tabl2;
    tabl[2]=tabl3;
    tabl[3]=tabl4;

    int z = 100000;      //Podajemy tutaj ile ma byc elemntow sortowanych
    clock_t start_5, finish_5; // zmienne do zliczania czasu
    double time_5 = 0;
    for(int i=0; i<=3;i++){
    start_5 = clock(); // początek zliczania czasu
    shell_sort(tabl[i], z);
    finish_5 = clock(); // koniec zliczania czasu
    time_5 += (double)(finish_5 - start_5) / (double)(CLOCKS_PER_SEC); // przeliczenie na sekundy
    }
    long s=0;
    for(int i=0; i<z;i++){
      s+=tabl1[i].get_rate();
    }
    cout<<"Srednia wartosc rankingu dla "<<z<<" elementow, to: "<<s/z<<endl;
    if(z%2==0){
      cout<<"Mediana rankingu dla "<<z<<" elementow, to: "<< (tabl1[(z/2)-1].get_rate()+tabl1[(z)/2].get_rate())/2<<endl;
    }
    else{
      cout<<"Mediana rankingu dla "<<z<<" elementow, to: "<< (tabl1[(z-1)/2].get_rate())/2<<endl;
    }
    
    cout << time_5/4 << " s średni czas shell sort" << endl;
    clock_t start_2, finish_2; // zmienne do zliczania czasu
    double time_2 = 0;
    for(int i=0; i<=3;i++){
    start_2 = clock(); // początek zliczania czasu
    bucket_sort(tab[i], z,0,10);
    finish_2 = clock(); // koniec zliczania czasu
    time_2 += (double)(finish_2 - start_2) / (double)(CLOCKS_PER_SEC); // przeliczenie na sekundy
    }
    cout << time_2/4 << "s średni czas bucket sort" << endl;
     clock_t start_3, finish_3; // zmienne do zliczania czasu
    double time_3 = 0;
    for(int i=0; i<=3;i++){
    start_3 = clock(); // początek zliczania czasu
    quick_sort(ta[i], 0,z);
    finish_3 = clock(); // koniec zliczania czasu
    time_3 += (double)(finish_3 - start_3) / (double)(CLOCKS_PER_SEC); // przeliczenie na sekundy
    }
    cout << time_3/4 << "s średni czas quick sort" << endl;
    clock_t start_4, finish_4; // zmienne do zliczania czasu
    double time_4 = 0;
    for(int i=0; i<=3;i++){
    start_4 = clock(); // początek zliczania czasu
    merge_sort(tabl[i],0,z);
    finish_4 = clock(); // koniec zliczania czasu
    time_4 += (double)(finish_4 - start_4) / (double)(CLOCKS_PER_SEC); // przeliczenie na sekundy
    }
    cout << time_4/4 << "s średni czas merge sort" << endl;
    return 0;
}
