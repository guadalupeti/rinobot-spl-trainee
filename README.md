# Projeto de Capacitação Rinobot

## Objetivo do Programa
Este programa é uma simulação básica de um robô em um ambiente bidimensional, projetada para realizar movimentações, rotações e detectar obstáculos. O usuário pode interagir com a simulação através de um menu, controlando robôs e observando o comportamento no mapa. Obstáculos são detectados pelo robô utilizando sensores.

## Estrutura do Programa
O programa é composto por quatro classes principais:

### 1. **Classe `Sensor`**
Representa o sensor do robô, que é responsável por detectar a distância de obstáculos.
- **Atributos:**
  - `range`: Alcance do sensor.
  - `noise`: Ruído aleatório que afeta as medições.
- **Métodos:**
  - `Sensor()`: Construtor padrão que inicializa os atributos com valores padrão.
  - `Sensor(int r)`: Inicializa o sensor com um alcance `r` e gera ruído aleatório.
  - `float readDistance()`: Retorna a distância medida considerando o ruído.

### 2. **Classe `Obstacle`**
Representa os obstáculos no ambiente.
- **Atributos:**
  - `posX`, `posY`: Coordenadas do obstáculo.
  - `size`: Tamanho do obstáculo.
- **Métodos:**
  - `Obstacle(int pX, int pY, int s)`: Constrói o obstáculo com posição e tamanho especificados.
  - Getters: `get_x()`, `get_y()`, `get_size()` retornam os valores das coordenadas e tamanho.

### 3. **Classe `Robot`**
Controla o robô e suas funcionalidades.
- **Atributos:**
  - `name`: Nome do robô.
  - `sensor`: Instância da classe `Sensor` associada ao robô.
  - `posX`, `posY`: Coordenadas atuais do robô.
  - `theta`: Angulação (direção) do robô em graus.
- **Métodos:**
  - Construtor: Inicializa o robô com nome, sensor e coordenadas iniciais.
  - Getters e setters para as coordenadas e orientação.
  - `void move(int dist)`: Move o robô em linha reta na direção atual.
  - `void turn(int angle)`: Altera a orientação do robô em incrementos de 90, 180 ou 270 graus.
  - `bool detect(Obstacle obs)`: Detecta se um obstáculo está no alcance do sensor.

### 4. **Classe `Enviroment`**
Define o ambiente onde os robôs e os obstáculos interagem.
- **Atributos:**
  - `robotList`: Lista de robôs no ambiente.
  - `obsList`: Lista de obstáculos no ambiente.
  - `map`: Representação do ambiente em uma matriz 20x20.
- **Métodos:**
  - `void createRobot(string n, Sensor s, int px, int py)`: Adiciona um robô ao ambiente.
  - `void createObs(int px, int py, int s)`: Adiciona um obstáculo ao ambiente.
  - `void setMap()`: Atualiza o mapa com as posições dos robôs e obstáculos.
  - `void simulate()`: Controla a simulação, permitindo ao usuário interagir com os robôs.

## Fluxo de Execução
1. O programa inicializa o ambiente e cria um robô e um obstáculo de exemplo.
2. O método `simulate()` é chamado, exibindo um menu com as opções:
   - **Mover o robô**: Permite que o usuário escolha um robô, insira a distância desejada e verifica as condições para o movimento (obstáculos, limite do mapa e alcance do sensor).
   - **Rotacionar o robô**: Altera a orientação do robô.
   - **Sair do modelo**: Finaliza a simulação.
3. O mapa é atualizado e exibido após cada ação.

## Requisitos do Programa
- **Compilador C++**: Certifique-se de usar um compilador que suporte C++11 ou superior.
- **Entrada do Usuário**: O programa é baseado em entradas do usuário para interagir com os robôs.

## Pontos a Melhorar
- Adicionar condições para movimentação mais precisas em relação aos obstáculos.
- Implementar mais funções para o robô (por exemplo, coleta de objetos ou interações mais complexas com obstáculos).
- Ampliar a representação gráfica do mapa para interfaces mais intuitivas.

## Exemplos de Uso
### Criando um Robô:
```cpp
Sensor sensor(5);
env.createRobot("Robo1", sensor, 0, 0);
```

### Criando um Obstáculo:
```cpp
env.createObs(3, 0, 1);
```

### Simulação:
A simulação exibe um menu onde o usuário pode escolher:
1. Mover o robô.
2. Rotacionar o robô.
3. Sair do programa.

O programa verifica automaticamente as condições de movimentação, como colisões e limites do mapa.
