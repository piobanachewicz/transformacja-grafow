#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//zmiennne globalne
int max;

//czytanie listy nastepnikow z pliku
std::vector<std::vector<int>> getGraph(){
    std::ifstream file("graf_wejsciowy.txt");

    int j = 0, end_of_line = 0;
    char vertex[5];
    std::vector<std::vector<int>> list;
    std::vector<int> v;

    if(file.is_open()) {
        while (file >> vertex) {
            if (vertex[0] == ';'){
                end_of_line = 0;
                j++;
                list.push_back(v);
                continue;
            } if (vertex[0] == '-'){
                v.clear();
                continue;
            }

            int i = atoi(vertex);
            if (i == j && end_of_line == 0){
                end_of_line = 1;
                continue;
            }

            v.push_back(i);
        }
    } else {
        throw "Nie znaleziono pliku!";
    }
    for(int i = 0; i < list.size(); i++) std::sort(list[i].begin(), list[i].end());
    return list;
}

//zapis listy nastepnikow do pliku
void listToFile(std::vector<std::vector<int>> list){
    std::ofstream file("graf_wyjsciowy.txt");
    for (int i = 0; i < list.size(); i++){
        file<<i<<" -> ";
        for (auto j: list[i]){
            file<<j<<" ";
        }
        file<<";"<<std::endl;
    }
    file.close();
}

//konwertowanie listy nastepnikow na macierz sasiedztwa
int** convertToMatrix(std::vector<std::vector<int>> list){
    int n = list.size();
    int** G = new int*[n];
    int o, p;
    for(o = 0; o < n; o++){
        G[o] = new int[n];
    }
    for (o = 0; o < n; o++){
        for (p = 0; p < n; p++){
            G[o][p] = 0;
        }
    }

    for (o = 0; o < list.size(); o++){
        for (p = 0; p < list[o].size(); p++){
            G[o][list[o][p]] = 1;
        }
    }
    return G;
}

////konwertowanie na liste nasteonikow STARA WERSJA PROJEKTU
/*std::vector<std::vector<int>> convertToList(int** G, int n){
//    std::vector<std::vector<int>> list;
//    for(int i = 0; i < n; i++){
//        std::vector<int> v;
//        for (int j = 0; j < n; j++){
//            if(G[i][j] == 1){
//                v.push_back(j);
//            }
//        }
//        list.push_back(v);
//    }
//    return list;
}*/


////lista poprzednikow DO STAREJ WERSJI SPRAWDZANIA LINIOWOWSCI
/*std::vector<std::vector<int>> predecessorList(std::vector<std::vector<int>> list) {
    std::vector<std::vector<int>> preList;
    for(auto e: list){
        std::vector<int> v;
        preList.push_back(v);
    }
    for(int k = 0; k < list.size(); k++) {
        for (int i = 0; i < list.size(); i++) {
            for (auto j: list[i]) {
                if (j == k) preList[k].push_back(i);
            }
        }
    }
    return preList;
}
*/

////sprawdzanie czy jest 1-grafem:
bool isOneGraph(std::vector<std::vector<int>> list){
    int v = 0, tmp;
    for (int i = 0; i < list.size(); i++){
        for (int j = 0; j < list[i].size(); j++){
            tmp = list[i][j];
            for(int k = 0; k < list[i].size(); k++){
                if(tmp == list[i][k]) v++;
            }
            if(v > 1) return false;
            else v = 0;
        }
    }
    return true;
}

////sprawdzenie czy wszytskie nastepniki sa takie same
bool allTheSame(std::vector<int> x, std::vector<int> y){
    if(x.size() == y.size()){
        for(int i = 0; i < x.size(); i++){
            if(x[i] != y[i]) return false;
        }
    } else return false;
    return true;
}

////sprawdzanie czy wszytskie sa rozne
bool allDiff(std::vector<int> x, std::vector<int> y){
    for(int i = 0; i < x.size(); i++){
        for(int j = 0; j < y.size(); j++){
            if(x[i] == y[j]) return false;
        }
    }
    return true;
}

////sprawdzenie czy jest sprzezony
bool isAdjoint(std::vector<std::vector<int>> list){
    bool is;
    if (isOneGraph(list)) is = true;
    else return false;

    for(int i = 0; i < list.size(); i++){
        for(int j = 0; j < list.size(); j++){
            if(allDiff(list[i], list[j])) is = true;
            else {
                if(allTheSame(list[i], list[j])) is = true;
                else return false;
            }
        }
    }

    return is;
}


////sprawdzenie czy jest liniowy Zmienione na inne warunki
/*bool isLinear(std::vector<std::vector<int>> prelist, std::vector<std::vector<int>> list){
    bool is = true;
//    for(int i = 0; i < list.size()-1; i++) {
//        for(int j = 0; j < list[i].size(); j++) {
//            for (int k = 0; k < list[i+1].size(); k++) {
//                if (list[i][j] != list[i+1][k]) is = true;
//                else return false;
//            }
//        }
//    }
    for(int i = 0; i < prelist.size()-1; i++) {
        for(int j = 0; j < prelist[i].size(); j++) {
            for (int k = 0; k < prelist[i+1].size(); k++) {
                if (prelist[i][j] != prelist[i+1][k]) is = true;
                else return false;
            }
        }
    }
    return is;
}*/

//generowanie osobnych lukow
int** gnerateSeparateEdges(int vertices){
    int** H = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        H[i] = new int[2];
    }

    int k = 0;
    for (int i = 0; i < vertices; i++){
        for (int j = 0; j < 2; j++){
            H[i][j] = k;
            k++;
        }
    }
    return H;
}

////drukowanie grafow
////jako macierz sasiedztwa DO TESTOW
/*void printGraph(int** G, int v){
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << G[i][j]<<" ";
        }
        std::cout << std::endl;
    }
}*/

////jako lista nastepnikow
void printList(std::vector<std::vector<int>> list){
    for (int i = 0; i < list.size(); i++){
        std::cout<<i<<" -> ";
        for (auto j: list[i]){
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }
}

////sortowanie H: przeindeksowanie wierzcholkow zeby byly po kolei
int** sortH(int** H, int vertices){
    int** copyH = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        copyH[i] = new int[2];
    }

    int v = 0;
    int next = 0;
    int changed = 0;
    while(next < vertices*2){
        for(int i = 0; i < vertices; i++){
            if(H[i][0] == next){
                copyH[i][0] = v;
                changed++;
            }
            if(H[i][1] == next){
                copyH[i][1] = v;
                changed++;
            }
        }
        if (changed > 0) v++;
        changed = 0;
        next++;
    }
    max = v;
    return copyH;
}

////transformacja
int** transformToOriginal(std::vector<std::vector<int>> list){
    int** G = convertToMatrix(list);
    int** H = gnerateSeparateEdges(list.size());
    int temp, temp2;

    for(int i = 0; i < list.size(); i++){
        for(int j = 0; j < list.size(); j++){
            if(G[i][j] == 1){
                temp = H[i][1];
                temp2 = H[j][0];
                for(int k = 0; k<list.size(); k++){
                    if(H[k][0] == temp2) H[k][0] = temp;
                    if(H[k][1] == temp2) H[k][1] = temp;
                }
            }
        }
    }
    return sortH(H, list.size());
}



////konwertowanie z par (krawedzi) na liste nastepnikow
std::vector<std::vector<int>> originalToList(int** H, int vertices) {
    std::vector<std::vector<int>> orgList;
    for(int i = 0; i < max; i++){
        std::vector<int> v;
        for(int j = 0; j < vertices; j++){
            if(H[j][0] == i) v.push_back(H[j][1]);
        }
        orgList.push_back(v);
    }
    for(int i = 0; i < orgList.size(); i++){
        std::sort(orgList[i].begin(), orgList[i].end());
    }

    return orgList;
}

////MAIN TODO: wczytanie z pliku podanego przez uzytkownika
int main() {
    std::vector<std::vector<int>> list;
    std::vector<std::vector<int>> orglist;
    try {
        list = getGraph();
    } catch (const char* msg) {
        std::cout << msg << std::endl;
        std::cin.ignore();
        return 0;
    }

    std::cout<<"Wczytany graf:"<<std::endl;
    printList(list);

    std::cout<<"Czy graf jest sprzezony? ";
    if(isAdjoint(list)){
        std::cout<<"TAK"<<std::endl;

        int** H = transformToOriginal(list);
        orglist = originalToList(H, list.size());

        std::cout<<"Czy graf jest liniowy? ";
        if(isOneGraph(orglist)) std::cout<<"TAK"<<std::endl;
        else std::cout<<"NIE"<<std::endl;

        std::cout<<"\nGraf po transformacji w graf oryginalny: "<<std::endl;
        printList(orglist);

        listToFile(orglist);
        std::cin.ignore();
        return 0;
    } else {
        std::cout<<"NIE"<<std::endl;
        std::cin.ignore();
        return 0;
    }
}
