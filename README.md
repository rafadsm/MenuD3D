# MenuD3D

## Creditos: Finn

### Informações do projeto:

Projeto criado em Visual Studio 2015

Lib DirectX9 SDK (June 2010)

### Requisitos:

- [DirectX SDK June 2010](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

## ScreenShots
#### Com fundo de imagem
![](https://image.prntscr.com/image/0LkWqxOARBuiF5UoN3m12Q.png)

#### Fundo sem imagem
![](https://image.prntscr.com/image/3RZBvCleRHqUVzqE_aVjXQ.png)

#### Animação slide
[![](https://img.youtube.com/vi/9xZnB_kWtl8/0.jpg)](https://www.youtube.com/watch?v=9xZnB_kWtl8)

## Como adicionar um item ao menu?

Em: 
[Menu.cpp void MenuManager::CreateItems()](https://github.com/FinnProjects/MenuD3D/blob/master/Dll/Menu.cpp#L223)

Você encontrará:
m_Items.emplace(HK_TESTE1, new MenuItem("Item 1", false));

Onde **m_Items** é a lista onde armazena os itens, **HK_TESTE1** é uma enum [encontrada aqui](https://github.com/FinnProjects/MenuD3D/blob/master/Dll/Menu.h#L9)

Antes de tudo, crie um novo valor na enum, respeitando as regras de virgula

Volte para [Menu.cpp void MenuManager::CreateItems()](https://github.com/FinnProjects/MenuD3D/blob/master/Dll/Menu.cpp#L223)

Insira uma nova linha como:
m_Items.emplace(**SUAENUM**, new MenuItem("NomeDoItem", false));

**Para adicionar uma array, troque o status padrão (true, false) para {"str1", "str2", "str3"} e assim em diante, veja:**

m_Items.emplace(**SUAENUM**, new MenuItem("NomeDoItem", **{"LClick", "RClick", "Alt", "CTRL"}**));

[Exemplo simplificado](https://github.com/FinnProjects/MenuD3D/blob/master/Dll/Menu.cpp#L227)

## Como interagir com os itens do menu?

### Itens On/Off

Vá até [Menu.cpp void MenuManager::HackActions()](https://github.com/FinnProjects/MenuD3D/blob/master/Dll/Menu.cpp#L231)

Terá exemplos

Insira: 
if (GetActived(**SEUENUM**))
{
//Ação aqui
}

Quando o item for ativado no menu, ele executará a ação


### Itens tipo array:

Utilize GetArrayPos(**SUAENUM**) para obter a posição atual,

onde o primeiro item começará na posição **0**, 

ou seja, **"LClick"** = 0, **"RClick"** = 1, e assim em diante


**Lógica de uso:**

if(GetArrayPos(**SUAENUM**) == 0) //LCkick

{
//Ação Aqui
}

else if(GetArrayPos(**SUAENUM**) == 1) //RClick

{
//Ação Aqui
}

## Imagem / Animação desativadas por padrão do projeto
## Você poderá configurar para o menu utilizar imagem / animação em: 
[Header.h //Configurações](https://github.com/FinnProjects/MenuD3D/blob/master/Dll/Header.h#L74)

### Comente a definição para desativar

### OBS:

#### Caso a imagem não carregue em algumas aplicações, não force, isso trará memory leak