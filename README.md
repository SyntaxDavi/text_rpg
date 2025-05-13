# text_rpg

Um RPG de texto simples desenvolvido em C++ com foco em aprendizado de programação e estruturação de jogos por turnos.

## Como jogar

1. Compile o projeto no Visual Studio (modo Debug ou Release).
2. Execute o programa.
3. Siga as instruções no terminal para:
   - Criar seu personagem
   - Escolher uma arma inicial
   - Escolher um poder inicial
   - Visitar a cidade, descansar, explorar e lutar

## Funcionalidades

- Criação de personagem com nome personalizado
- Escolha entre quatro armas diferentes
- Escolha entre quatro poderes com efeitos distintos
- Sistema de cidade 
- Lutas contra 2 inimigos em turnos
- Pontuação de vida (HP) e sistema de morte
- Sistema de aventura com exploração

## Tecnologias utilizadas

- Linguagem: C++
- IDE: Microsoft Visual Studio 2022
- Paradigmas: Programação orientada a objetos
- Recursos adicionais: manipulação de tempo, entrada de usuário e geração de números aleatórios

## Estrutura do projeto

text_rpg/
├── main.cpp # Entrada do jogo e lógica principal
├── city.cpp # Funções relacionadas à cidade e menu
├── battle.cpp # Lógica das batalhas
├── player.cpp / .h # Classe do jogador e métodos relacionados
├── enemy.cpp / .h # Classe dos inimigos
├── weapon.cpp # Armas e estatísticas
├── power.cpp # Poderes especiais
├── headers.h # Inclusões gerais e protótipos
└── README.md # Documentação do projeto

## Como compilar

Abra o Visual Studio 2022, carregue o projeto como uma solução C++ e utilize a opção "Compilar" no menu. Certifique-se de que todos os arquivos `.cpp` e `.h` estejam adicionados à solução.

## Autor

Desenvolvido por SyntaxDavi. Repositório disponível no GitHub.
