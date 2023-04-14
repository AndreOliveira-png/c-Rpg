/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h> 

using namespace std;

class Item{
    public:
        Item(){
            _nome = "";
            _descricao = "";
            _comando = 0;
            _valor = 0;
            _quantidade = 0;
        }
        Item(string nome, string descricao, string comando, string valor, string quantidade){
            _nome = nome;
            _descricao = descricao;
            _comando = std::stoi( comando );
            _valor = std::stoi( valor );
            _quantidade = std::stoi( quantidade );
        }
        void setQuantidade(int valor){
            cout << "\nAqui";
            _quantidade = valor;
            cout << "\n" << _quantidade;
        }
        int getQuantidade(){
            return _quantidade;
        }
        int getValor(){
            return _valor;
        }
        string getNome(){
            return _nome;
        }
        string getDescricao(){
            return _descricao;
        }
        int getComando(){
            return _comando;
        }
        
        void resetItem(){
            _quantidade = 0;
        }
    
    private:
        string _nome;
        string _descricao;
        int _comando; //0 - cura, 1 - aumentoAtaque, 2 - aumentoDefesa, 3 - aumentoExperiencia, 4 - veneno
        int _valor;
        int _quantidade;
};
Item geradorDeItens() {
    //Um gerador randômico simples, só confia nos dados.
    string itensName[][5]{
        {"Poção de Cura","Uma poção que cura uma porcentagem da vida do usuário","0","20","1"},
        {"Espada","Uma espada de aço enferrujado","1","20","1"},
        {"Armadura","Uma Armadura feita de couro","2","20","1"},
        {"Poção de Experiência","Uma pequena ajudinha do ADM","3","3","1"},
        {"Veneno","Favor não tomar","4","3"}
    };
    srand (time(NULL));
    
    //rand funciona da seguinte forma. rand % (o valor que vem aqui é o limite) + (Valor inicial que, 
    //por sua vez, altera o valor limite )
    int v1 = rand() % 5;  // de 0 a 4

    
    Item item(itensName[v1][0],itensName[v1][1],itensName[v1][2],itensName[v1][3],itensName[v1][4]);
    cout << "\n" << "Parabéns, você conseguiu um novo item: " << item.getNome() <<" : " << item.getDescricao() <<" x " << item.getQuantidade();
    return item;
}
//A classe Criatura é basicamente um grupo genérico pra qualquer criatura viva no jogo. Player, monstro, npc, etc.
class Criatura{
    //Os atributos privados são aqueles que não queremos que sejam acessados fora da classe em questão( Mais pela segurança).
    private:
        string _nome;
        int _vidaMax;
        int _vida;
        int _ataque;
        int _defesa;
        int _velocidade;
        int _level;
        int _experience;
        Item _item;
        
    //Os atributos publicos, por sua vez, podem ser acessados fora da classe como "funcionalidades/ações" do objeto.
    public:
        Criatura(string nome, int vida, int ataque, int defesa, int velocidade, int level){
            _nome = nome;
            _vidaMax = vida + round(vida / 10 * (level - 1));
            _vida = _vidaMax;
            _ataque = ataque + round(ataque / 10 * (level - 1));
            _defesa = defesa + round(defesa / 10 * (level - 1));
            _velocidade = velocidade + round(velocidade / 10 * (level - 1));
            _level = level;
            _experience = 0;
         
        }
        //SET
        //Para modificar a vida ou qualquer outro atributo privado fora da classe, é necessaria uma função genérica.
        void setVida(int valor){
            if(valor >= _vida){
                _vida = 0;
            }else{
                _vida -= valor;
            }
        }
         void setItem(Item i){
            _item = i;
        }
        void setExperience(int valor){
            //O levelCap fica a sua escolha.
            int levelCap = _level * 5;
            _experience += valor;
            if(_experience >= levelCap){
                //Só entra aqui se a experiência for igual ou maior ao limite do seu respectivo level.
                _experience = _experience - levelCap;
                _level = _level + 1;
                subirDeNivel();
            }
        }
        
        //GET
        int getLevel(){
            return _level;
        }
        int getDano(){
            return _ataque;
        }
        int getVida(){
            return _vida;
        }
        int getVidaMax(){
            return _vidaMax;
        }
        string getNome(){
            return _nome;
        }
        int getVelocidade(){
            return _velocidade;
        }
        Item* getItem(){
            return &_item;
        }
        
        //Metodos
        //Uma vez que o jogador tem a experiência igual ou maior a capacidade do seu level, ele sobe.
        void subirDeNivel(){
            //O modificador fica a sua escolha.
            int modificador = _level * 5;
            _vidaMax = _vidaMax + modificador;
            _ataque = _ataque + modificador;
            _defesa = _defesa + modificador;
            _velocidade = _velocidade + modificador;
            resetaVida();
        }
        void resetaVida(){
            _vida = _vidaMax;
        }
        void cura(int valor){
            if(_vida + valor > _vidaMax){
                _vida = _vidaMax;
            }else{
                _vida = _vida + valor;
            }
        }
         void aumentoAtaque(int valor){
           _ataque = _ataque + valor;
        }
         void aumentoDefesa(int valor){
           _defesa = _defesa + valor;
        }
        void aumentoExperiencia(int valor){
           setExperience(valor);
        }
        
        void usarItem(Criatura *alvo){
            if(alvo->getItem()->getQuantidade() > 0){
                switch(alvo->getItem()->getComando()) {
                    case 0:
                    {
                        int cura = round((alvo->getVidaMax() / 100 * alvo->getItem()->getValor()));
                        alvo->cura(cura);
                        cout << "\n" << alvo->getNome() <<" curou " << cura << " de vida";
                    }
                    break;
                    case 1:
                    {
                        alvo->aumentoAtaque(alvo->getItem()->getValor());
                        cout << "\n" << alvo->getNome() <<" ganhou " << alvo->getItem()->getValor() << " de ataque";
                    }
                    break;
                    case 2:
                    {
                        alvo->aumentoDefesa(alvo->getItem()->getValor());
                        cout << "\n" << alvo->getNome() <<" ganhou " << alvo->getItem()->getValor() << " de defesa";
                    }
                    break;
                    case 3:
                    {
                        int total = round((alvo->getLevel() * alvo->getItem()->getValor()));
                        alvo->aumentoExperiencia(total);
                        cout << "\n" << alvo->getNome() <<" ganhou " << total << " de experiência";
                    }
                    break;
                    case 4:
                    {
                        alvo->cura(alvo->getItem()->getValor());
                        cout << "\n" << alvo->getNome() <<" recebeu " << alvo->getItem()->getValor() << " de dano";
                    }
                    break;
                    default:
                         cout << "Algo deu errado {usarItem}";
                }
            }
            Item* i = getItem();
            i->resetItem();
            
        }
        //A recompensa é um metodo a parte porque aqui, consigo adicionar mais códigos sem precisar modificar nada em outros lugares.
        // Também deixa o código mais legivel.
        void recompensa(Criatura *alvo){
            resetaVida();
            int xp = alvo->getLevel() * 2;
            int lv = _level;
            setExperience(xp);
            cout <<"\n"<< _nome << " ganhou " << xp <<" de experiencia";
            if(lv < _level){
                cout  <<"\n"<< "Parabens, " << _nome << " subiu para o level " << _level;
            }
            //Aqui seria adicionado o item ao jogador (Caso tenha)
            
           
            
            if(_item.getQuantidade() == 0){
                _item = geradorDeItens(); 
                
            }
           
        }
        // Aqui é realizado o calculo de dano.
        bool recebeDano(int valor){
            //O valor é arredondado para não ter conflito com o seu tipo (inteiro)
            int valorReal = round((valor - (_defesa / 10) * _level));
            cout <<"\n" << _nome << " recebeu " << valorReal <<" de dano";
            if(_vida <= valorReal){
                //Caso a  vida seja menor ou igual ao dano... morreu.
                setVida(valorReal);
                return false;
            }
            //Do contrário, a vida continua    
            setVida(valorReal);
          
            return true; 
        }
        //Aqui são feitas as preparações do ataque.
        bool realizaAtaque(Criatura *alvo){
            cout <<"\n" << _nome << " esta atacando " << alvo->getNome();
            bool aux = alvo->recebeDano(_ataque);
            if(aux){
                //Caso o retorno seja true (de recebeDano()), quer dizer que ainda tem briga pela frente.
                return true;
            }
            //Caso o retorno seja falso, então... F
            cout <<"\n" << _nome << " derrotou " << alvo->getNome();
            recompensa(alvo);
            return false;
        }
    
};



//Crio um monstro e retorno ele para o uso no Main.
Criatura geradorDeMonstros(int playerLevel) {
    //Um gerador randômico simples, só confia nos dados.
    string monsterNames[4] = {"Capivara", "Pato", "Tio Naldo", "Pato Alado"};
    srand (time(NULL));
    
    //rand funciona da seguinte forma. rand % (o valor que vem aqui é o limite) + (Valor inicial que, 
    //por sua vez, altera o valor limite )
    int v1 = rand() % 5;  // de 0 a 4
    int v2 = rand() % 120 + 40;  // de 40 a 159 
    int v3 = rand() % 18 + 1;   // de 1 a 17
    int v4 = rand() % 18 + 1;   // de 1 a 17
    int v5 = rand() % 18 + 1;   // de 1 a 17
    
    Criatura monstro(monsterNames[v1],v2,v3,v4,v5,playerLevel);
    return monstro;
}
bool testeDeFuga(Criatura *player, Criatura *monstro) {
    
    //Um gerador randômico simples, só confia nos dados.
    srand (time(NULL));
    
    //rand funciona da seguinte forma. rand % (o valor que vem aqui é o limite) + (Valor inicial que, 
    //por sua vez, altera o valor limite )
    int v1 = rand() % 100 + 1;  // de 1 a 100
    
    int valor = round((100 * player->getVelocidade()) / ( monstro->getVelocidade() * 2));
    
    if(valor >= v1){
        return true;
    }
    return false;  
}

int porcentagemDeFuga(Criatura *player, Criatura *monstro) {
    
    //Um gerador randômico simples, só confia nos dados.
    srand (time(NULL));
    
    //rand funciona da seguinte forma. rand % (o valor que vem aqui é o limite) + (Valor inicial que, 
    //por sua vez, altera o valor limite )
    int v1 = rand() % 100 + 1;  // de 1 a 100
    
    int valor = round((100 * player->getVelocidade()) / ( monstro->getVelocidade() * 2));
    
    if(valor >= 100){
        return 100;
    }
    return valor;  
}

int main()
{
    string nome;
    cout << "Digite o nome do Personagem\n";
    cin >> nome;
    
    Criatura player(nome,100, 20, 13, 10, 1);
    
    //O controlador existe para o propósito de continuar o looping principal, ou termina-lo.
    int controlador = 1;
    while(controlador != 0){
        
        cout << "Você encontrou um monstro";
        Criatura monstro = geradorDeMonstros(player.getLevel());
        bool combate = true;
        //O combate acaba quando um dos dois não respirar mais, neste caso, um valor falso retornar.
        while(combate){
            cout << "\n\n***************************" << "\n" 
                << "* LV "<< player.getLevel() << " " << player.getNome() <<": HP "<<  player.getVida()<<"/"<< player.getVidaMax() << "\n" 
                << "* LV "<< monstro.getLevel() << " " << monstro.getNome() <<": HP "<< monstro.getVida()<<"/"<< monstro.getVidaMax()  << "\n" 
                << "* 0 - Atacar " << "\n" 
                << "* 1 - Usar Item " << "\n" 
                << "* 2 - Fugir " << porcentagemDeFuga(&player, &monstro) <<"% \n" 
                << "***************************";
           
            cout << "\nO que deseja fazer? ";
            int resp;
            cin >> resp;
            switch(resp) {
                case 0:
                //Caso ataque
                    combate = player.realizaAtaque(&monstro);
                    if(monstro.getVida() > 0){
                        //Se o player não matou o monstro ainda, é a vez dele, somos todos cavalheiros
                        combate = monstro.realizaAtaque(&player);
                    }else{
                        combate = false;
                    }
                    cout << "\n\nDigite algo para continuar...\n";
                    cin.ignore();
                break;
                
                case 1:
                    if(player.getItem()->getQuantidade() > 0){
                            cout << "\n\n********** ITENS ***********"
                            <<"\n"<< player.getItem()->getNome() << " : " << player.getItem()->getDescricao() << " x" 
                            << player.getItem()->getQuantidade()
                            << "\nDeseja usar? 0 - Sim, 1 - Não"
                            << "\n***************************\n";
                        int op;
                        cin >> op; 
                        switch(op){
                            case 0:{
                                player.usarItem(&player);
                                break;
                            }
                            case 1:{
                                cout << "\nVocê não usou o item";
                                break;
                            }
                            default:
                            {
                                cout << "Algo deu errado {main.case1}";

                            }
                        }
                    
                      
                    }else{
                        cout << "Você não possui nenhum item";
                    }
                    cout << "\n\nDigite algo para continuar...\n";
                    cin.ignore();
                break;
                
                case 2:
                    if(testeDeFuga(&player, &monstro)){
                        cout << "\n" << "Você Fugiu com sucesso!";
                        combate = false;
                    }else{
                        cout << "\n" << "Você não conseguiu fugir";
                        if(monstro.getVida() > 0){
                            //Se o player não matou o monstro ainda, é a vez dele, somos todos cavalheiros
                            combate = monstro.realizaAtaque(&player);
                        }else{
                            combate = false;
                        }
                    }
                    cout << "\n\nDigite algo para continuar...\n";
                    cin.ignore();
                break;
                default:
                      cout << "Algo deu errado {main}";
            }
         cin.ignore();
        }
        if(player.getVida() == 0){
            cout << "\n\nVocê Morreu!";
            controlador = 0;
        }else{
            cout << "\n\nDeseja continuar a sua aventura? 1 - Sim, 0 - Não\n";
            cin >> controlador; 
        }
        
    }
    cout << "\n\nObrigado por jogar!";
    
    return 0;
}
