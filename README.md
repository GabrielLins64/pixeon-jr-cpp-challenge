<h1>Desafio Pixeon - Relatório</h1>

Repositório com a solução do desafio Pixeon para o cargo de Analista Desenvolvedor C++ Júnior.

**Desenvolvedor**: Gabriel Furtado Lins Melo

---

<h2>Índice</h2>

- [Dependências](#dependências)
- [Como compilar e executar](#como-compilar-e-executar)
- [Metodologia](#metodologia)
  - [Ferramentas e ambiente de desenvolvimento](#ferramentas-e-ambiente-de-desenvolvimento)
  - [Visualizador de imagens](#visualizador-de-imagens)
  - [Editor de imagens](#editor-de-imagens)
  - [Tipos de imagens](#tipos-de-imagens)
- [Dificuldades encontradas](#dificuldades-encontradas)
  - [Aprendizado rápido do *framework* Qt](#aprendizado-rápido-do-framework-qt)
- [Técnicas aplicadas](#técnicas-aplicadas)
  - [Padrões de código e *clean architecture*](#padrões-de-código-e-clean-architecture)
- [Melhorias futuras](#melhorias-futuras)
  - [Menus de ferramentas](#menus-de-ferramentas)
  - [Barra de status](#barra-de-status)
  - [Mais opções de edição](#mais-opções-de-edição)
  - [Refatoração do módulo ImageViewer](#refatoração-do-módulo-imageviewer)
- [Resultado](#resultado)

---

## Dependências

- [Qt 5.12+](https://doc.qt.io/archives/qt-5.12/linux.html)
- C++ 14+

---

## Como compilar e executar

**OBS:** Caso seja executado no Windows, talvez seja necessária alguma modificação de nomenclatura para o executável gerado no arquivo do projeto `pixeon-jr-cpp-challenge.pro`.

1. Prepare o projeto Qt com o qmake:

```shell
qmake
```

2. Compile o projeto com o Makefile gerado:

```shell
make
```

3. Rode o executável criado:

```shell
./build/main
```

---

## Metodologia

### Ferramentas e ambiente de desenvolvimento

A aplicação foi desenvolvida num sistema operacional **Linux (Ubuntu 20.04)**, utilizando principalmente o compilador **g++** para o **C++14**. Para GUI foi utilizado o *framework* **Qt 5.12.8**. Os IDEs utilizados foram o **VSCode** para a maior parte do código (a arquitetura, lógica e design) e o **QtCreator** para produzir o *design* de alguns *dialogs*.

### Visualizador de imagens

Para não reinventar a roda, foi utilizado como base o [template de um ImageViewer da documentação do *Qt*](https://doc.qt.io/archives/qt-5.12/qtwidgets-widgets-imageviewer-example.html). Este exemplo esclareceu como carregar uma imagem em uma aplicação gráfica, efetuar operações básicas (apenas de visualização) de "*Zoom*" e "*Fit to Window*" e como salvar uma imagem (sem modificação).

Após a base estar feita e estudada, melhorias e ajustes foram feitos na aplicação, incluindo o conserto do método de salvar a imagem, a adição da possibilidade de abertura (e fechamento) de mais de uma imagem e estas visualizadas numa QWidgetList com o nome e o ícone do arquivo da imagem, operações de edição sobre a imagem e, de maneira simplificada, a adição de *designs* agradáveis para a UI.

### Editor de imagens

A classe auxiliar `ImageEditor` definiu as operações de edição sobre as imagens. As operações consistem em:

1. Redimensionamento
2. Rotação
3. Ajuste de brilho
4. Ajuste de contraste

### Tipos de imagens

A aplicação foi configurada para aceitar qualquer um dos 3 tipos mencionados no desafio (BMP, PNG ou JPEG), permitindo que o usuário escolha o de sua preferência. (obs: para permitir apenas 1 tipo, basta remover os outros dois na `QStringList mimeTypeFilters` do método `ImageViewer::initializeImageFileDialog(QFileDialog)`)

---

## Dificuldades encontradas

### Aprendizado rápido do *framework* Qt

Foi um desafio realizar o estudo, a implementação do projeto e o balanço com as atividades acadêmicas e profissionais neste intervalo de tempo até a *deadline*, considerando que foi meu primeiro contato com o *framework* Qt.

Alguns pequenos contratempos surgiram, como: ao buscar uma forma de instalar o *framework* para o Ubuntu, segui a documentação oficial, indicando compilar a versão *open-source* em minha máquina. No entanto, a compilação não foi bem sucedida, apesar de todas as dependências instaladas, e as tentativas de solucionar os erros reportados foram levando a erros mais específicos até não encontrar mais nenhuma solução para compilação. Todavia, após quase uma hora e meia de tentativas, descobri que era possível a instalação do *framework* na versão 5.12 diretamente pelo APT... 😅. Com isto resolvido, procedi para os estudos do *framework*.

Apesar destes desafios, o processo de aprendizado de uma nova tecnologia é sempre divertido, gratificante e enriquecedor.

---

## Técnicas aplicadas

### Padrões de código e *clean architecture*

Como padrões de codificação, foram adotados os [padrões de estilo para C++ do Google](https://google.github.io/styleguide/cppguide.html). Para boas práticas de codificação e projeto, foram adotadas algumas sugestões do livro **Código Limpo: Hábilidades Práticas do Agile Software** (MARTIN, R. C.).

---

## Melhorias futuras

### Menus de ferramentas

Uma melhora signifativa para a UX da aplicação seria a adição de uma *QToolBar* para facilitar o acesso às operações de edição sobre a imagem e tornar a interface com o usuário mais agradável e profissional.

### Barra de status

Uma melhora, também para a UX da aplicação, consistiria na manipulação da *QStatusBar* da classe principal `ImageViewer` para mostrar informações como: dimensões atuais da imagem (útil para edições), coordenadas do cursor e o caminho completo da imagem atualmente selecionada.

### Mais opções de edição

Fornecer mais opções para edição das imagens, incluindo algumas mais avançadas, como suavização de bordas, equalização de histograma, redução de ruídos, melhora da nitidez, etc.

### Refatoração do módulo ImageViewer

A classe principal do visualizador de imagens ficou bastante extensa, englobando várias *features* que poderiam ser modularizadas para melhor organização do código. Então, uma melhora para permitir um desenvolvimento mais rápido, claro e com menos possibilidade de erros seria a refatoração deste módulo.

---

## Resultado

O tempo de implementação do projeto acabou sendo mais extenso do que planejei, e acabei não conseguindo implementar algumas features extras (também mencionadas nas [melhorias futuras](#melhorias-futuras)).

No entanto, a aplicação é executada e performa eficientemente todas as operações sugeridas e requisitadas sobre as imagens. Além disto, a aplicação possui uma UI simples, clara e intuitiva, o que permite uma experiência de usuário agradável e satisfatória.
