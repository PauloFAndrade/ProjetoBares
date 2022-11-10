# Identificação Pessoal

Preencha os dados abaixo para identificar a autoria do trabalho.

- Nome: *Paulo Vitor Fernandes Andrade*
- Email: *paulovitorfandrade2002@gmail.com*
- Turma: *DIM0120*

# Erros tratados pelo programa
- [x] Fim inesperado da entrada. (ex: `expressão vazia`)
- [x] Inteiro mal formado. (ex: `%5 * 10`)
- [x] Faltando termo.  (ex: `2+`)
- [x] Símbolo estranho após expressão válida encontrada.  (ex: `2 = 3`)
- [x] Inteiro fora do intervalo válido.  (ex: `100000000 - 2`)
- [x] Faltando fechamento de parênteses.  (ex: `(2+3`)
- [x] Divisão por zero explícita.  (ex: `2/0`)
- [x] Divisão por zero "disfarçada". (ex: `2/(1-1)`)
- [x] Overflow numérico após operação.  (ex: `5000*5000`)

# Como Compilar, Executar e Funcionamento

## Compilar
    ##### Usando g++
    ```
    cd EBNF_basic
    cd source
    cd core
    ```

## Executar
    Utilize o seguinte comando para executar o programa. obs: esteja dentro da pasta core.
    ```
    ./bares
    ```

## Funcionamento
    Ao executar com "./bares" o programa vai esperar indefinidas vezes o cliente passar expressões matemáticas que envolvam os operadores (+,-,*,%,/,^) e após apertar a tecla "enter" o programa irá exibir o resultado da expressão passada caso esteja formada corretamente ou uma mensagem de erro caso não seja uma expressão válida.

# Indique quais itens da avaliação foram realizados

- [X] Lê expressões do `std::cin` e cria corretamente a lista de tokens (20 pontos)
- [X] Converte corretamente expressões do formato infixo para posfixo (15 pontos)
- [X] Trata corretamente o uso de parênteses e `-` unário (5 pontos)
- [X] Avalia corretamente expressão no formato posfixo (15 créditos)
- [X] Detecta corretamente o conjunto de erros solicitados (20 créditos)
- [X] Gera a saída conforma solicitado (15 créditos)
- [X] Código é organizado em classes (10 créditos)

- [ ] **Extra**: utilizou pilha feito pelos autores
- [ ] **Extra**: utilizou fila feito pelos autores
- [ ] **Extra**: utilizou vector feito pelos autores

--------
&copy; DIMAp/UFRN 2021.
