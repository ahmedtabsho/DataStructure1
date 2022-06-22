#include "PacmanAndFruitAndGhost.cpp"
#include <fstream>


void readGameArea();
void buildGame(Pacman &, List<Ghost> &, List<Fruit> &, int &);
void printGameArea();
void startGame(fstream &, fstream &, fstream &, Pacman &, List<Ghost> &, List<Fruit> &, int &);
void writeFruitsLocationToFile(List<Fruit> &, fstream &);
void writeGhostsLocationToFile(List<Ghost> &, fstream &);
void moveGhosts(List<Ghost> &);
void buildingFruit(Pacman &, fstream &);
void waitGhosts(Pacman &, List<Ghost> &, fstream &);


int main()
{
    int disks = 0;
    Pacman pacman;
    List<Ghost> ghosts;
    List<Fruit> fruits;
    fstream pacmanKonum;
    fstream hayaletKonum;
    fstream meyveKonum;
    pacmanKonum.open("pacmanKonum.txt", ios::out);
    hayaletKonum.open("hayaletKonum.txt", ios::out);
    meyveKonum.open("meyveKonum.txt", ios::out);
    readGameArea();
    printGameArea();
    buildGame(pacman, ghosts, fruits, disks);
    printGameArea();
    writeFruitsLocationToFile(fruits, meyveKonum);
    startGame(pacmanKonum, hayaletKonum, meyveKonum, pacman, ghosts, fruits, disks);
    (pacman.tookdisk == disks) ? pacmanKonum << "\n\nKazandi :)" << endl : pacmanKonum << "\n\nkayibetti :(" << endl;
    pacmanKonum << "\n\nTopladigi disk sayisi : " << pacman.tookdisk << endl;
    pacmanKonum << "Hayaletle carpisma : " << 3 - pacman.life << endl;
    pacmanKonum.close();
    hayaletKonum.close();
    meyveKonum.close();

    return 0;
}

void printGameArea(){
    for(int i = 0; i < 25; i++){
        for (int j = 0; j < 25; j++)
            cout << game[i][j] << " ";
        cout << endl;
    }
    cout << "\n\n\n" << endl;
}

void buildGame(Pacman &pacman, List<Ghost> &ghosts, List<Fruit> &fruits, int &disks) {
    for(int i = 0; i <= MAX_ROWS; i++){
        for (int j = 0; j <= MAX_COLUMNS; j++){
            if(game[i][j] == 1){
                disks++;
            }
            else if(game[i][j] == 2){
                Fruit f;
                f.set(i, j);
                fruits.push_back(f);
            }
            else if(game[i][j] == 9){
                pacman.set(i,j);
            }
            else if(game[i][j] > 2 && game[i][j] <= 6){
                Ghost g;
                g.set(game[i][j], i, j);
                ghosts.push_back(g);
            }
        }
    }
}

void readGameArea(){
    fstream gameFile;
    char ch;
    int i = 0, j = 0;
    gameFile.open ("pacman.txt", ios::in);
    while(gameFile >> ch){
        if(ch != ','){
            if(i <= MAX_ROWS){
                if(j > MAX_COLUMNS){
                    i++;
                    j = 0;
                    game[i][j] = (int)ch - 48;
                    j++;
                }
                else{
                    game[i][j] = (int)ch - 48;
                    j++;
                }
            }
        }
    }
    gameFile.close();
}

void startGame(fstream &pacmanKonum, fstream &hayaletKonum, fstream &meyveKonum, Pacman &pacman, List<Ghost> &ghosts, List<Fruit> &fruits, int &disks){
    while(pacman.continueGame() && (pacman.tookdisk < disks)){
        pacmanKonum << "(" << pacman.x << "," << pacman.y << "_" << gameTime << ")" << endl;
        writeGhostsLocationToFile(ghosts, hayaletKonum);
        moveGhosts(ghosts);
        pacman.pacmanMove();
        buildingFruit(pacman, meyveKonum);
        waitGhosts(pacman, ghosts, hayaletKonum);
        printGameArea();
        cout << "kalan sure : " << gameTime << endl;
        cout << "kalan can : " << pacman.life << endl;
        cout << "total diskler : " << disks << endl;
        cout << "toplanan diskler : " << pacman.tookdisk << endl;
        cout << "kalan diskler : " << disks - pacman.tookdisk << endl;
    }
}

void writeFruitsLocationToFile(List<Fruit> &fruits, fstream &meyveKonum){
    Node<Fruit>* f = fruits.begin();
    int fruitNum = 0;
    while(f != fruits.end()){
        fruitNum++;
        meyveKonum << "Meyve" << fruitNum << "-->" << " (" << f->data.x << "," << f->data.y << ")" << endl;
        f = f->next;
    }
}

void writeGhostsLocationToFile(List<Ghost> &ghosts, fstream &hayaletKonum){
    Node<Ghost>* g = ghosts.begin();
    int ghostNum = 1;
    while(g != ghosts.end()){
        if(g->data.waitTime == 0)
            hayaletKonum << "Hayalet" << ghostNum << "-->" << " (" << g->data.x << "," << g->data.y << ")" << endl;
        g = g->next;
        ghostNum++;
    }
}

void moveGhosts(List<Ghost> &ghosts){
    Node<Ghost>* g = ghosts.begin();
        while(g != ghosts.end()){
            g->data.ghostMove();
            g = g->next;
        }
}

void buildingFruit(Pacman &pacman, fstream &meyveKonum){
    if(pacman.istooktendisk()){
        pacman.buildFruit();
        meyveKonum << "Meyve yeniden olusturuldu.." << endl;
    }
}

void waitGhosts(Pacman &pacman, List<Ghost> &ghosts, fstream &hayaletKonum){
    if(pacman.EatFruit()){
        Stack<int> s;
        Node<Ghost>* g = ghosts.begin();
        int waitTime = 5;
        int ghostNum = 1;
        for(int g = ghosts.size(); g > 0; g--){
            s.push((waitTime * (g + 1)));
        }
        g = ghosts.begin();
        while(g != ghosts.end()){
            if(g->data.waitTime == 0){
                g->data.waitTime = s.getTop();
                s.pop();
            }
            else{
                g->data.waitTime += 5;
                s.pop();
            }
            if(g->data.waitTime)
                hayaletKonum << "Hayalet" << ghostNum << "bekleme durumunda " << endl;
            g = g->next;
            ghostNum++;
        }

    }
}

