#include <iostream>
#include <random>
#include <vector>
#include <string>

//to-do
//fazer clausula na movimentação para caso haja algum obstáculo


using namespace std;

class Sensor {
    private:
        float range, noise;

    public:

        //construtor padrão
        Sensor(): range(0), noise(0) {}
        //construtor
        Sensor(int r) {
            //modelo de aleatorização de números (optei por usar algo mais robusto que o ctime)

            random_device rd; //inicialização do modelo
            mt19937 gen(rd()); //definição do motor dos pseudoaleatórios
            uniform_real_distribution<> dis(0.250000001, 0.75); //definição de intervalo

            range = dis(gen); //geração do numero

            noise = (rand() % 50 + 25) / 100;
        }

        //cálculo de distância
        float readDistance() {
            return range*noise;
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

        //setters
        int set_x(int n){
            return posX += n;
        }

        int set_y(int n) {
            return posY += n;
        }

        void move(int dist) {
            //condição para definir a direção da movimentação
            switch (theta) {
                case 0:
                    posX += dist;
                    return;
                case 180:
                    posX -= dist;
                    return;
                case 90:
                    posY += dist;
                    return;
                case 270:
                    posX += dist;
                    return;
                default:
                    return;
            }

        }

        //função para rotação
        void turn(int angle) {
            //tratamento de rotação
            if (angle != 90 && angle != 180 && angle != 270) {
                throw invalid_argument("Faça a rotação apenas com 90, 180 e 270 (360 e 0 retornariam a mesma rotação)");
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
            if (obs.get_x() - this->posX - (obs.get_size()/2) <= sensor.readDistance() && (theta == 0 || theta == 180) ) {
                return true;
            }
            else if (obs.get_y() - this->posY - (obs.get_size()/2) <= sensor.readDistance() && (theta == 90 || theta == 270)) {
                return true;
            }
            return false;
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

class Enviroment {
    private:
    //definição de vetores para escolha de obstáculo 
        vector <Robot> robotList;
        vector <Obstacle> obsList;

    public:
        void simulate() {
            int x, y, robPos;
            char resp;
            cout << "Deseja se movimentar? [S/N] " << endl;
            cin >> resp;

            if (resp == 'S') {
                for (int i = 0; i < robotList.size(); i++) {
                    cout << i + 1 << " - " << robotList[i].name << endl;
                }
                cout << "Escolha seu robÔ: " << endl;
                cin >> robPos;
                robPos -= 1;
                cout << "Em X ou Y? " << endl;
                cin >> resp;
                if (resp == 'X') {
                    robotList[robPos].set_x(1);
                } else if (resp == 'Y') {
                    robotList[robPos].set_y(1);
                } else {
                    cout << "Respota Inválida!" << endl;
                }
            } 
        }
};