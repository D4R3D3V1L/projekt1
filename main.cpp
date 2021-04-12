#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//          Sortowanie szybkie
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void QuickSort(int tab[], int left, int right) { // left to indeks pierwszego elementu, right to indeks ostatniego
    int l = left-1; //lewy pkt wykorzystany do przechodzenia po tablicy ++l
    int r = right+1; //prawy pkt wykorzystany do przechodzenia po tablicy --p
    int pivot = tab[(left+right)/2]; //pivot, punkt odniesienia w sortowaniu szybkim, który dzieli nam tablicę

    while(l<=r) { //dopoki sie nie spotkaja
        while(pivot>tab[++l]); // szuka elementu większego od pivota
        while(pivot<tab[--r]); // szuka elementu mniejszego od pivota
        if(l<r) { // jezeli są to indeksy po różnych stronach pivota
            swap(tab[l], tab[r]); // zamienia ich wartości
        }
    }
    if (r>left) { // jezeli jest dluzszy niz 1 element
        QuickSort(tab, left, r); // sortuje lewą część
    }
    if (l<right) { // jezeli prawa strona dluzsza od punktu z lewej
        QuickSort(tab, l, right);// sortuje prawą część
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//          Sortowanie przez scalanie
//////////////////////////////////////////////////////////////////////////////////////////////

void merge(int tab[], int help[], int left, int mid, int right){
    int l=left; //punkt poczatku
    int m=mid+1; // punkt srodka+1
    
    for(int i=left; i<=right; i++){
        help[i]=tab[i]; // wykorzystanie tablicy pomocniczej
        }
    while(left<=mid && m<=right){ //sprawdzamy warunki 2 tablic czy indeksy są dobre
        if(help[left]<=help[m]){ //wtedy gdy w 1wszej tablicy lewa jest mniejsza lub rowna prawej
            tab[l++]=help[left++]; // przepisujemy z pomocniczej
        }
        else{
            tab[l++]=help[m++]; 
        }
    }
    while(left<=mid){ // warunek gdy pozostały w 1wszej tablicy
        tab[l++]=help[left++];
    }
    while(m<=right){ //gdy w drugiej (po prawej)
        tab[l++]=help[m++];
    }
}

void MergeSort(int tab[], int help[], int left, int right){

    if(left<right){ // gdy indeksy sie nie spotykaja
        int mid=(left+right)/2; //pkt przedziału, koniec 1wszej tablicy
        MergeSort(tab, help, left, mid); //dzielimy lewą tablicę 
        MergeSort(tab, help, mid+1, right); // dzielimy prawą
        merge(tab, help, left, mid, right); //sortowanie
    }
}

//////////////////////////////////////////////////////////////////////////////
//          Sortowanie przez kopcowanie
//////////////////////////////////////////////////////////////////////////////

void heap(int tab[], int i, int j){
    int top = j; //nasz rodzic
    int left = 2*j + 1;//lewe dziecko
    int right= 2*j + 2;//prawe dziecko
    if(left<i && tab[left]>tab[top]) { // gdy indeks jest w tablicy i lewo dziecko wieksze od rodzica
        top=left; // nowy rodzic
    }
    if(right<i && tab[right]>tab[top]){ // miesci sie w tablicy i prawe wieksze od rodzica
        top=right; // nowy rodzic
    }
    if(top != j){ //szuka zmiany indeksu
        swap(tab[j], tab[top]); // zamiana w tablicy
        heap(tab, i, top); // powtarza czynność
    }
}

void HeapSort(int tab[], int i){
    for(int j=i/2; j>=0; j-- ){ //j to nasz wybrany rodzic, i idziemy w tyl tablicy po wykonanych operacjach
        heap(tab, i, j); // tworzy kopiec
    }
    for(int k=i; k>=0; k--) { // ostatni element, wiekszy rowny zero , idziemy do tylu
        swap(tab[0], tab[k]); // wylonienie najwiekszego elementu na koniec
        i--;
        heap(tab, k, 0); // tworzy kopiec tablicy o 1 mniejsze , bo ostatni element zostal juz posortowany
    }
}

/////////////////////////////////////////////
//          kopiowanie tablicy
/////////////////////////////////////////////

void copy(int tab1[], int tab2[], int index){ //do kopiowania tablic w main
    for (int i=0; i<index; i++ )
    tab2[i]=tab1[i];
}

//////////////////////////////////////////////
//          Main
//////////////////////////////////////////////

int main(){

    srand(time(NULL));

    int n, choice;
    //int *tab, *tabQ, *tabM, *tabH, *temp;
    double timeQ, timeM, timeH;
    double dQ, dM, dH;
    int *tab = new int [n];
    int *tabQ = new int [n];
    int *tabM = new int [n];
    int *tabH = new int [n];
    int *temp = new int [n];
    cout.setf(ios::fixed);
    cout.precision(3);
    clock_t start, stop;
    
    cout<<"Liczba elementow w tablicy:"<<endl;
    cin>>n;

    tab = new int [n];
    tabQ = new int [n];
    tabM = new int [n];
    tabH = new int [n];
    temp = new int [n];

    // wszystkie losowe

    timeQ=timeM=timeH=0;

    for(int a=0; a<7; a++){
    for(int i=0; i<100; i++){
        for(int j=0; j<n; j++){
            tab[j]=rand()%n;
        }
        copy(tab, tabQ, n);
        copy(tab, tabM, n);
        copy(tab, tabH, n);

        start=clock();
        QuickSort(tabQ, 0, n-1);
        stop=clock();
        dQ=(stop-start)/(double)CLOCKS_PER_SEC;
        timeQ+=dQ;

        start=clock();
        MergeSort(tabM, temp, 0, n-1);
        stop=clock();
        dM=(stop-start)/(double)CLOCKS_PER_SEC;
        timeM+=dM;

        start=clock();
        HeapSort(tabH, n-1);
        stop=clock();
        dH=(stop-start)/(double)CLOCKS_PER_SEC;
        timeH+=dH;
    }
    }
    cout<<"czas sortowania szybkiego: "<<timeQ/7<<"s"<<endl;
    cout<<"czas sortowania przez scalanie: "<<timeM/7<<"s"<<endl;
    cout<<"czas sortowania przez kopcowanie: "<<timeH/7<<"s"<<endl;

    // czesc posortowana

    double procent;
    cout<<"jaki procent elementow tablicy jest posortowanych: ";
    cin>>procent;
    int p=n*procent/100;
    int starter=0;
    timeQ=timeM=timeH=0;

    for(int a=0; a<7; a++){
    for(int i=0; i<100; i++){
        for(int j=0; j<p; j++) {
            tab[j]=starter++;
        }
        for(int i=p; i<n; i++){
            tab[i]=rand()%n;
        }
        copy(tab, tabQ, n);
        copy(tab, tabM, n);
        copy(tab, tabH, n);

        start=clock();
        QuickSort(tabQ, 0, n-1);
        stop=clock();
        dQ=(stop-start)/(double)CLOCKS_PER_SEC;
        timeQ+=dQ;

        start=clock();
        MergeSort(tabM, temp, 0, n-1);
        stop=clock();
        dM=(stop-start)/(double)CLOCKS_PER_SEC;
        timeM+=dM;

        start=clock();
        HeapSort(tabH, n-1);
        stop=clock();
        dH=(stop-start)/(double)CLOCKS_PER_SEC;
        timeH+=dH;
    }
    }
    cout<<"czas sortowania szybkiego: "<<timeQ/7<<"s"<<endl;
    cout<<"czas sortowania przez scalanie: "<<timeM/7<<"s"<<endl;
    cout<<"czas sortowania przez kopcowanie: "<<timeH/7<<"s"<<endl;

    // odwrotnie posortowane

    int cap=n;
    timeQ=timeM=timeH=0;

    for(int a=0; a<7; a++){
    for(int i=0; i<100; i++){
        for(int j=0; j<n; j++){
            tab[j]=cap--;
        }
        copy(tab, tabQ, n);
        copy(tab, tabM, n);
        copy(tab, tabH, n);

        start=clock();
        QuickSort(tabQ, 0, n-1);
        stop=clock();
        dQ=(stop-start)/(double)CLOCKS_PER_SEC;
        timeQ+=dQ;

        start=clock();
        MergeSort(tabM, temp, 0, n-1);
        stop=clock();
        dM=(stop-start)/(double)CLOCKS_PER_SEC;
        timeM+=dM;

        start=clock();
        HeapSort(tabH, n-1);
        stop=clock();
        dH=(stop-start)/(double)CLOCKS_PER_SEC;
        timeH+=dH;
    }
    }
    cout<<"czas sortowania szybkiego, odw: "<<timeQ/7<<"s"<<endl;
    cout<<"czas sortowania przez scalanie, odw: "<<timeM/7<<"s"<<endl;
    cout<<"czas sortowania przez kopcowanie, odw: "<<timeH/7<<"s"<<endl;


/*********************************
    cout<<"szybkie ";
    for(int i=0;i<n;i++)
        cout<<tabQ[i];
    cout<<endl;

    cout<<"scalanie ";
    for(int i=0;i<n;i++)
        cout<<tabM[i];
    cout<<endl;

    cout<<"kopcowanie ";
    for(int i=0;i<n;i++)
        cout<<tabH[i];
    cout<<endl;

    cout<<"bylo ";
    for(int i=0;i<n;i++)
        cout<<tab[i];
    cout<<endl;
 **********************************/   
return 0;
}

///////////////////////////////////
//          Main Testowy
///////////////////////////////////

/*************************************************************
main(){
    int n;
    int *tab, *tabQuick, *help;
  	cout<<"Ile liczb bedziesz chcial posortowac? "<<endl;
  	cin>>n;
    tab=new int [n];
    tabQuick=new int [n];
    help=new int[n];
    for(int i=0; i<n; i++)
        cout<<tab[i]<<" ";
    cout<<endl<<"Podaj liczby do sortowania" <<endl;
  	//wczytanie liczb
  	for(int i=0;i<n;i++)
    	cin>>tab[i];
    copy(tab, tabQuick, n);
    //QuickSort(tabQuick,0, n-1);
    //MergeSort(tabQuick, help, 0, n-1);
    HeapSort(tabQuick, n-1);
  	//wypisanie posortowanych elementów
  	for(int i=0;i<n;i++)
        cout<<tabQuick[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++)
        cout<<tab[i]<<" ";
 
  	cin.ignore();
  	cin.get();
  	return 0;
}
***********************************************************/