#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Kind;

typedef struct {
    std::string face;
    Kind naipe;
    int value;
} Card;

const char* naipe_names[] = { "hearts", "diamonds", "clubs", "spades" };
int hand_size = 0;

// Inicializa/constroi o deck
void initialize_deck(Card deck[], int deck_size)
{
    const std::string faces[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    int index = 0;

    for (int f = 0; f < 13; f++) {  // face
        for (int n = 0; n < 4; n++) {  // naipe

            deck[index].face = faces[f];
            deck[index].naipe = (Kind)n;
            deck[index].value = f + 1 + n * 10;
            index++;
        }
    }
}

// Embaralha o deck
void randomize_deck(Card deck[], int deck_size) {
    Card first_card;
    Card random_card;
    std::srand(std::time(0)); // Inicializa a semente aleatória
    int rand_num = 0;
    int c = 0;

    for (int i = 0; i < 52; i++) {
        rand_num = i + std::rand() % (52 - i); // Gera um rand_num entre 0 e 12
        first_card = deck[i];
        random_card = deck[rand_num];
        deck[rand_num] = first_card;
        deck[i] = random_card;
    }
}

// Compra cartas para a mão
void draw_hand(Card deck[], Card hand[], int& hand_size, int& deck_size) {
    for (int i = 0; i < hand_size; i++) {
        hand[i] = deck[i];
    }
    for (int i = 0; i < deck_size - 1; i++) {
        deck[i] = deck[i + 1];
    }
    deck_size = deck_size - hand_size;
    std::cout << "Tamanho do deck: " << deck_size << std::endl;
}

// Comprar mais cartas para a mão
void draw_card(Card deck[], Card hand[], int& hand_size, int& deck_size) {
    int draw;
    do
    {
    std::cout << std::endl << "Escolha a quantidade de cartas para comprar entre 1 e "
    << deck_size << "." << std::endl;
    std::cin >> draw;
        if (draw < 1 || draw > deck_size)
        {
            std::cin.clear(); // Limpa o erro do fluxo
            std::cin.ignore(1000, '\n'); // Ignora caracteres ínvalidos até a próxima linha
            std::cout << "Entrada ínvalida! Digite um número inteiro: ";
        }
    } while (draw < 1 || draw > deck_size);
    {
        hand_size += draw;
        for (int i = hand_size - draw; i < hand_size; i++) {
            hand[i] = deck[i];
        }
        deck_size -= draw;
        for (int i = 0; i < deck_size - 1; i++) {
            deck[i] = deck[i + 1];
        }
    }
}

// Organiza as cartas da mao manualmente
void manualsort_hand(Card hand[], int hand_size) {
    if (hand_size == 1) {
        std::cout << std::endl << "A mao contem apenas uma carta! Nao e possivel trocar de lugar!" << std::endl;
        return;
    }
    int primeiro_num;
    int segundo_num;
    int primeira_pos;
    int segunda_pos;
    Card temp;
    std::cout << std::endl << "Escolha duas cartas pelas suas posicoes para troca-las de posicao: " << std::endl;
    std::cout << "Digite o numero da posicao da primeira carta: " << std::endl;
    std::cin >> primeiro_num;
    //Valida a posição da primeira carta
    while (primeiro_num < 1 || primeiro_num > hand_size) {
        std::cout << "Posição invalida! Digite uma posicao entre 1 e " << hand_size << std::endl;
    }
    primeira_pos = primeiro_num - 1;
    std::cout << "Digite o numero da posicao da segunda carta: " << std::endl;
    std::cin >> segundo_num;
    //Valida a posição da segunda carta
    while (segundo_num < 1 || segundo_num > hand_size || primeiro_num == segundo_num) {
        if (primeiro_num == segundo_num) {
            std::cout << "As posicoes nao podem ser iguais! Digite uma posicao diferente para a segunda carta!" << std::endl;
        }
        else {
            std::cout << "Posicao invalida! Digite uma posicao entre 1 e " << hand_size << ": " << std::endl;
        }
        std::cout << "Posição invalida! Digite uma posicao entre 1 e " << hand_size << std::endl;
        std::cin >> segundo_num;
    }
    segunda_pos = segundo_num - 1;
    temp = hand[primeira_pos];
    hand[primeira_pos] = hand[segunda_pos];
    hand[segunda_pos] = temp;
}

// Organiza as cartas da mão em ordem crescende de acordo com o valor "value" atribuido as cartas
void ascending_hand(Card hand[], int hand_size) {
    Card temp;
    //Inicializando temp com a primeira carta da mão para garantir que tenha um valor valido
    temp = hand[0];

    for (int i = 0; i < hand_size - 1; i++) {
        for (int j = 0; j < hand_size - i - 1; j++) {
            if (hand[j].value > hand[j + 1].value) {
                //Troca as cartas
                temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }
    }
}

// Organiza as cartas da mão em ordem decrescende de acordo com o valor "value" atribuido as cartas
void descending_hand(Card hand[], int& hand_size) {
    Card temp;
    //Inicializando temp com a primeira carta da mão para garantir que tenha um valor valido
    temp = hand[0];
    for (int i = 0; i < hand_size - 1; i++) {
        for (int j = 0; j < hand_size - i - 1; j++) {
            if (hand[j].value < hand[j + 1].value) {
                //Troca as cartas
                temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }
    }
}

void discardone_hand(Card hand[], std::vector<Card>& discardpile, int& hand_size, int& discard_size, int& disc_count) {
    int disc_pos;
    do 
    {
        std::cout << std::endl << "Digite a posicao da carta a ser descartada: " << std::endl;
        std::cin >> disc_pos;
        if (disc_pos < 1 || disc_pos > hand_size) 
        {
            std::cin.clear(); // Limpa o erro do fluxo
            std::cin.ignore(1000, '\n'); // Ignora caracteres ínvalidos até a próxima linha
            std::cout << "Entrada ínvalida! Digite um número inteiro: ";
        }

    } while (disc_pos < 1 || disc_pos > hand_size /*|| !(std::cin >> disc_pos)*/); // Repete enquanto posição for inválida
                std::cout << "Posicao da carta a ser descartada: " << disc_pos << ". " << std::endl; // Exibe a carta que será descartada
                std::cout << "Carta a ser descartada: " << hand[disc_pos - 1].face << " of " << naipe_names[hand[disc_pos - 1].naipe] << "." << std::endl;
                discard_size++;
                disc_count++;
                discardpile.push_back(hand[disc_pos - 1]);
                for (int i = disc_pos - 1; i < hand_size - 1; i++) 
                {
                    hand[i] = hand[i + 1]; // Move os elementos uma posição para trás
                }
                hand_size--;
}

void play_card(Card hand[], std::vector<Card>& gamepile, int& hand_size, int& playp_size, int game_count) {
    int play_pos;

    do
    {
        std::cout << std::endl << "De o numero da posiçao da carta a ser jogada:  (entre 1 e " 
            << hand_size << ".)" << std::endl;
        std::cin >> play_pos;
        if (play_pos < 1 || play_pos > hand_size)
        {
            std::cin.clear(); // Limpa o erro do fluxo
            std::cin.ignore(1000, '\n'); // Ignora caracteres ínvalidos até a próxima linha
            std::cout << "Entrada ínvalida! Digite um número inteiro valido entre 1 e " 
                      << hand_size + 1 << ": " << std::endl;
        }
    } while (play_pos < 1 || play_pos > hand_size /*|| !(std::cin >> disc_pos)*/); // Repete enquanto posição for inválida
    std::cout << "Posicao da carta a ser jogada: " << play_pos << ". " << std::endl; // Exibe a carta que será jogada
    std::cout << "Carta a ser jogada: " << hand[play_pos - 1].face << " of " << naipe_names[hand[play_pos - 1].naipe] << "." << std::endl;
    playp_size++;
    game_count++;
    gamepile.push_back(hand[play_pos - 1]);

    for (int i = play_pos - 1; i < hand_size - 1; i++)
    {
        hand[i] = hand[i + 1]; // Move os elementos uma posição para trás
    }
    hand_size--;
}

void print_deck(Card deck[]) // Imprime as cartas do deck na ordem do momento da execução
{
    for (int i = 0; i < 52; i++) 
    {
        std::cout << "[" << i << "] - " << deck[i].face << " of " << naipe_names[deck[i].naipe] << "." << std::endl << "Value of the card: " << deck[i].value << std::endl;
    }
}

void print_hand(Card hand[], int hand_size) // Mostra as cartas da mão na ordem do momento da execução
{
    std::cout << std::endl << "Cartas na mao: " << std::endl;
        for (int i = 0; i < hand_size; i++) 
        {
            std::cout << "[" << i + 1 << "] - " << hand[i].face << " of " << naipe_names[hand[i].naipe] << ". " << " - Value of the card: " << hand[i].value << std::endl;
        }
    std::cout << std::endl << "Tamanho da mao: " << hand_size << std::endl;
}

void print_discardpile(Card discardpile[], int discard_size) // Mostra as cartas da pilha de descarte em ordem de descarte
{
    std::cout << std::endl << "Cartas descartadas: " << std::endl;
        for (int i = 0; i < discard_size; i++)
        {
            std::cout << "[" << i << "] - " << discardpile[i].face << " of " << naipe_names[discardpile[i].naipe] << "." << std::endl << "Value of the card: " << discardpile[i].value << std::endl;
        }
    std::cout << std::endl << "Tamanho da pilha de descarte: " << discard_size << std::endl;
}

void print_gamepile(Card gamepile[], int playp_size) //Mostra carta em jogo na pilha de jogo
{
    std::cout << std::endl << "Carta no topo da pilha jogada: " << std::endl;
    std::cout << gamepile[playp_size-1].face << " of " << naipe_names[gamepile[playp_size-1].naipe] << ". " << "Value of the card: " << gamepile[playp_size-1].value << std::endl
              << std::endl << "Tamanho da pilha de jogo: " << playp_size << std::endl;
}

int main() {
    //Declarando variaveis para main()
    int disc_pos = 0;
    int deck_size = 52;
    int discard_size = 0;
    int playp_size = 0;
    int disc_count = 0;
    int play_count = 0;
    int comando = 0;
    bool out = false;

    //Verificando se o tamanho da mão é valido
    do {
        std::cout << std::endl << "Escolha o numero de cartas, entre 1 e 52, para sua mao: " << std::endl;
        std::cin >> hand_size;
        std::cout << std::endl;
        if (hand_size < 1 || hand_size > 52)
        std::cin.clear(); // Limpa o erro do fluxo
        std::cin.ignore(1000, '\n'); // Ignora caracteres ínvalidos até a próxima linha
        std::cout << "Número invalido de cartas! O valor deve estar entre 1 e 52." << std::endl;
        } while ((hand_size < 1 || hand_size > 52));

    std::vector<Card> gamedeck(deck_size);
    std::vector<Card> hand(deck_size);
    std::vector<Card> discardpile(discard_size);
    std::vector<Card> gamepile(playp_size);
    initialize_deck(gamedeck.data(), deck_size);


    //Comprando cartas para a mão
    randomize_deck(gamedeck.data(), deck_size);
    draw_hand(gamedeck.data(), hand.data(), hand_size, deck_size);
    gamedeck.resize(deck_size);
    hand.resize(hand_size);

    // Recebendo comando para a mão
    do{
        print_hand(hand.data(), hand_size);
    std::cout << std::endl << "Digite o numero correspondente ao comando: "
        << std::endl << "1. Comprar cartas."
        << std::endl << "2. Ordenar as cartas da mao de forma crescente." 
        << std::endl << "3. Ordenar as cartas da mao de forma decrescente." 
        << std::endl << "4. Ordenar as cartas da mao de forma manual." 
        << std::endl << "5. Escolher uma carta para descartar." 
        << std::endl << "6. Apenas mostrar mao."
        << std::endl << "7. Jogar carta."
        << std::endl << "8. Mostra pilha de descarte."
        << std::endl << "9. Mostra topo da pilha em jogo."
        << std::endl << "0. Finalizar." << std::endl << std::endl;

    std::cin >> comando;
    switch (comando) 
    {
    // Executando funções
    case 1:
        draw_card(gamedeck.data(), hand.data(), hand_size, deck_size);
        break;
    case 2:
        ascending_hand(hand.data(), hand_size);
        break;
    case 3:
        descending_hand(hand.data(), hand_size);
        break;
    case 4:
        manualsort_hand(hand.data(), hand_size);
        break;
    case 5:
        discardone_hand(hand.data(), discardpile, hand_size, discard_size, disc_count);
        break;
    case 6:
        break;
    case 7:
        play_card(hand.data(), gamepile, hand_size, playp_size, play_count);
        print_gamepile(gamepile.data(), playp_size);
        break;
    case 8:
        print_discardpile(discardpile.data(), discard_size);
        break;
    case 9:
        print_gamepile(gamepile.data(), playp_size);
        break;
    case 0:
        std::cout << std::endl << "Finalizando..." << std::endl;
        out = true;
        break;
    default:
        std::cout << std::endl << "Numero invalido! Nenhum comando correspondente ao número!" << std::endl;
        break;
    } 
    } while (!out);
    return 0;
}