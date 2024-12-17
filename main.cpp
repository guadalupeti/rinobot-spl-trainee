#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <random>

class Sensor;
class Robot;
class Obstacle;
class Environment;

//to-do
//fazer clausula na movimentação para caso haja algum obstáculo


using namespace std;

void printMenu() {
    cout << "O que você deseja fazer? " << endl;
    cout << "[ 1 ] Mover o personagem" << endl;
    cout << "[ 2 ] Rotacionar robô" << endl;
    cout << "[ 0 ] Sair do modelo" << endl;
}

class Sensor {
    private:
        float range, noise;

    public:
        //construtor padrão
        Sensor(): range(0), noise(0) {}
        //construtor
        Sensor(int r) {
            range = r;
            //aleatorização de ruído
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.25, 0.75);

            noise = dis(gen);

        }

        //cálculo de distância
        float readDistance() {
            cout << range << " " << noise << endl;
            return range*noise;
        }
            

};



class Obstacle {
    private:
        int posX, posY, size;
    
    public:
        Obstacle(int pX, int pY, int s) {
            posX = pX;
            posY = pY;
            size = s;
        }

        //getters
        int get_x() {
            return posX;
        }

        int get_y() {
            return posY;
        }
        int get_size() {
            return size;
        }
};

//classe de ações do robô
class Robot {
    private:
        Sensor sensor;
        int posX, posY, theta; //coordenadas e direção

    public:
        string name;
        Robot(string n, Sensor s, int px, int py) {
            name = n;
            sensor = s;
            posX = px;
            posY = py;
            theta = 0; //robô começa na angulação 0
        }

        //getters
        int get_x() {
            return posX;
        }

        int get_y() {
            return posY;
        }

        int get_theta() {
            return theta;
        }
        Sensor get_sensor() {
            return sensor;
        }
        void set_x(int x) {
            posX = x;
        }
        void set_y(int y) {
            posY = y;
        }
        

        void move(int dist) {
            //condição para definir a direção da movimentação

            switch (theta) {
                case 0:
                    posX += dist;
                    break;
                case 180:
                    posX -= dist;
                    break;
                case 90:
                    posY += dist;
                    break;
                case 270:
                    posY -= dist;
                    break;
            }

        }

        //função para rotação
        void turn(int angle) {
            //tratamento de rotação
            if (angle != 90 && angle != 180 && angle != 270) {
                //rotação de 360 e 0 retornariam a mesma angulação
                cout << "Faça a rotação apenas com 90, 180 e 270.";
                return;
            }

            //tratamento de angulação
            theta += angle;
            if (theta >= 360) {
                theta -= 360;
            } else if (theta < 0) {
                theta += 360;
            }
        }

        bool detect(Obstacle obs) {
            //detecção de obstáculos baseada na angulação do robô e distancia de detecção do sensor
            if (theta == 0 || theta == 180) {
                return abs(obs.get_x() - posX) <= sensor.readDistance() + (obs.get_size() /2);
            }
            if (theta == 90 || theta == 270) {
                return abs(obs.get_y() - posY) <= sensor.readDistance() + (obs.get_size() /2);
            }
            return false;
        }

};

class Enviroment {
    private:
    //definição de vetores para escolha de obstáculo 
        vector <Robot> robotList;
        vector <Obstacle> obsList;
        char map[20][20];

    public:

        void createRobot(string n, Sensor s, int px, int py){
            Robot robot(n,s,px,py);
            robotList.push_back(robot);
        }
        void createObs(int px, int py, int s){
            Obstacle obs(px,py,s);
            obsList.push_back(obs);
        }

        void setMap() {
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    map[i][j] = '.';
                }
            }
            for (int r = 0; r < robotList.size(); r++) {
                map[robotList[r].get_y()][robotList[r].get_x()] = '@';
            }
            for (int o = 0; o < robotList.size(); o++) {
                map[obsList[o].get_y()][obsList[o].get_x()] = 'X';
            }

            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    cout << map[i][j] << " ";
                }
                cout << endl;
            }
        }

        //ambiente de simulação do modelo
        void simulate() {
            int x, y, robPos, dist, resp;
            bool canMove;
            while (1){
            printMenu();
            setMap();
            cin >> resp;

            system("cls");

            //condicional de ação do usuário
            switch (resp) {
                case 1:
                    for (int i = 0; i < robotList.size(); i++) {
                        cout << i + 1 << " - " << robotList[i].name << " - " << " ângulo = " << robotList[i].get_theta() << " - X: " << robotList[i].get_x()  << " - Y: " << robotList[i].get_y() << endl;
                    }
                    cout << "Escolha seu robô: " << endl;
                    cin >> robPos;
                    robPos -= 1;
                    cout << "Quantas casas você deseja que " << robotList[robPos].name << " mova?";
                    cin >> dist;
                    canMove = true;
                    
                    for (int a = 0; a < obsList.size(); a++) {
                        if ((robotList[robPos].get_x() + dist >= 20 || robotList[robPos].get_x() + dist >= 20) || (robotList[robPos].get_x() + dist < 0 || robotList[robPos].get_x() + dist < 0)) {
                            cout << "Você não pode sair do mapa!";
                            break;
                        }
                        if (!robotList[robPos].detect(obsList[a])) {
                        robotList[robPos].move(dist);
                    }
                        if (dist > robotList[robPos].get_sensor().readDistance()) {
                            cout << "Você está querendo ir longe demais! O sensor do " << robotList[robPos].name << " não consegue detectar tão longe!" << endl;
                            break;
                        }
                        if (robotList[robPos].detect(obsList[a])) {
                            if (robotList[robPos].get_theta() == 0 || robotList[robPos].get_theta() == 180) {                                
                                for (int j = 1; j <= dist; j++) {
                                    robotList[robPos].move(1);
                                    if (robotList[robPos].get_x() == obsList[a].get_x()) {
                                        robotList[robPos].move(1 + obsList[a].get_size()/2);
                                        break;
                                    } 
                                }
                            } else {
                                for (int j = 1; j <= dist; j++) {
                                    robotList[robPos].move(1);
                                    if (robotList[robPos].get_y() == obsList[a].get_y()) {
                                        robotList[robPos].move(1 + obsList[a].get_size()/2);
                                    } 
                                }
                            }
                                
                            break;
                    }
        
                    }
                    

                   
                    break;

                case 2:
                    int g;
                    for (int i = 0; i < robotList.size(); i++) {
                        cout << i + 1 << " - " << robotList[i].name << " - " << " ângulo = " << robotList[i].get_theta() << " - X: " << robotList[i].get_x()  << " - Y: " << robotList[i].get_y() << endl;
                    }
                    cout << "Escolha seu robô: " << endl;
                    cin >> robPos;
                    robPos -= 1;
                    cout << "Digite a angulação (em graus) que você deseja rotacionar: ";
                    cin >> g;
                    robotList[robPos].turn(g);
                    break;
                case 0:
                    break;
            }
            }      
                
            } 
        };

int main() {
    srand(time(0));
    Enviroment env;
    Sensor sensor(5);
    env.createRobot("Teste", sensor, 0,0);
    env.createObs(3, 0, 1);

    env.simulate();
    return 0;
}
