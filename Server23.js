// git                https://github.com/Entrol25/Server23.git

git remote add origin https://github.com/Entrol25/Server23.git
git push -u origin main
git clone https://github.com/Entrol25/Server23.git
//-------------------------------------------------------------//
…or create a new repository on the command line
echo "# Server23" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/Entrol25/Server23.git
git push -u origin main
…or push an existing repository from the command line
git remote add origin https://github.com/Entrol25/Server23.git
git branch -M main
git push -u origin main
-----------------------------------------------------------------
отправка игроку 
Client::SendMessageToClient(int ID, SOCKET* Connections)// ф. рассылает всем сообщения
 > serverManager.WorkVector3(sizeBuffer, bufferRoom, buffer)// заполняем временный буфер для сообщения
 > ServerManager::WorkVector3(int _sizeBuffer, char bufferRoom[], char buffer[])// заполняем временный буфер для сообщения
 > send(Connections[id], bufferRoom, strlen(bufferRoom), NULL)// отправить сообщение игроку[i]
 
//       0       1  2      3         4
//*status/комната/id/кнопка/vector   / (start:)  time `
//*  2:2 /   0   /0/   R   /1,23:0,01/   0:m:s:frame  `






























