# Landlords

[![GitHub license](https://img.shields.io/github/license/Co1lin/landlords?style=flat-square)](https://github.com/Co1lin/landlords/blob/master/LICENSE)  [![Qt](https://img.shields.io/badge/Qt-5-brightgreen?style=flat-square)](https://www.qt.io/)  [![C++](https://img.shields.io/badge/C%2B%2B-11-brightgreen?style=flat-square)](https://en.cppreference.com)  [![CodeFactor](https://www.codefactor.io/repository/github/co1lin/landlords/badge?style=flat-square)](https://www.codefactor.io/repository/github/co1lin/landlords?style=flat-square)  [![GitHub stars](https://img.shields.io/github/stars/Co1lin/landlords?style=flat-square)](https://github.com/Co1lin/landlords/stargazers)  [![GitHub forks](https://img.shields.io/github/forks/Co1lin/landlords?style=flat-square)](https://github.com/Co1lin/landlords/network)  

The classic Chinese card game Landlords. An assignment for Qt network programming, in summer term 2020.  

![preview](https://github.com/Co1lin/Landlords/blob/master/others/preview.png)  

## 工作流程

### 操作流程

1. 用户选择工作模式：“开设房间等待他人进入”或“连接他人开设的房间”。  
   （1）开设房间者可以更改默认的监听端口，可以从列表复制合适的本机IP给其它玩家方便连接。  
   （2）连接他人者可以设置他人开设的房间的IP和端口号。  
   
2. 开设房间者点击开始监听，根据配置正式创建房间，随后其它玩家配置相关信息后点击连接。三人连接成功后共同跳转到游戏界面，开始游戏。  

### 实现逻辑与细节

1. 通信协议：TCP （全部）  
2. 采用C/S模式。建立连接的流程如下：  
   （1）开设房间者点击开设房间之后，会建立一个TCP Server，监听指定端口的连接。同时也会建立一个TCP Socket，作为本地玩家与本地服务器的通信接口。  
   （2）连接他人所创房间者点击开设房间之后，会建立一个TCP Socket，连接开设房间者建立的TCP Server。  
   于是三名玩家共同连接到了一个TCP Server上，完成了连接。通过TCP Server，他们之间可以交换数据进行通信。  
3. 为了解决TCP通信的“粘包”问题，实现了接收和发送数据的函数，分别为`MyTools::send`和`MyTools::read`。  
   发送函数中，为了适应不同运行环境，先将数据转换为大端字节序；然后在写入的`QByteArray`中预留一个固定长度的变量的位置用于保存之后写入的数据的长度。  
   接收函数中，首先读取接收到的的数据包前面的长度信息。如果此信息没有读到，则等待下次有新数据到达时再读入。如果读到了数据的大小信息，就往下读取固定长度的数据，通过一些判断保证正确读取每一次发送的信息，而不会”漏读“或”读串“。  
   此外，为了各阶段通信处理的方便性与统一性，实现了一个自定义类`DataPackage`作为数据通信的“载体”。  
4. 显示界面主要采用Graphics View Framework，实现手牌、桌上的牌、底牌、其它玩家的信息的显示以及相关动态效果。其中使用了HTML、QSS等技术美化视觉效果。  
5. 游戏规则实现：
   服务器通过TCP通信告知玩家是否出牌，以及场上的必要信息，比如上次其它玩家出的牌。收到数据后，客户端允许玩家出牌，在确认出牌时通过自己实现的检测函数检测出牌是否合法（包括出牌本身是否合法、出牌是否能大过上家的牌）。如果合法则成功出牌，将出牌信息发送给服务器。服务器收到后更新状态，并将场上最新状态告知所有玩家，同时通知下一位玩家出牌，以此循环。  
   当一位玩家在场上其它玩家之前出完所有牌后，其客户端向服务器发送相应信息。服务器确认后告知所有玩家本场游戏结局。三位玩家的客户端收到结局后显示是否重新开始的选择。若选择重新开始，则重新开始游戏，重新发牌，等等。若选择No，则退出游戏程序。  
   至于出牌是否合法的判断方法，在此做简要介绍：主体部分为判断牌型的函数；在判断牌型之后，若牌型合法，且需要与上家牌比较大小，只需要比较“关键牌”即可。判断牌型的算法主要是统计每张牌出现了多少次；根据有几张牌都出现了同样的次数，即可确定“关键牌”，进行初步筛选，然后对剩余牌进行与“关键牌”的匹配，看是否能匹配成功，经过一系列条件判断，最后得出相应的牌型。  