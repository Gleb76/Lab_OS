Написать программы для консольного процесса __Administrator__ и консольных процессов __Reader__ и __Writer__. _Для
моделирования передачи сообщений ввести специальные события, которые обозначают сообщение «А» , «B», «C» ,
«D» и конец сеанса для процессов __Reader__ и __Writer___. Для сообщений «C» и «D» использовать __события c
ручным сбросом__.  
Одновременно принимать и отправлять сообщения могут только __два АКТИВНЫХ процесса Writer(использовать
мьютексы) и два АКТИВНЫХ процесса Reader(использовать семафор__), передача остальных сообщений от других
процессов должна временно блокироваться (находиться в режиме ожидания).  

Процесс __Administrator__:
1. Инициализация объектов синхронизации;
2. запрашивает у пользователя количество процессов Writer( Reader);
3. запрашивает у пользователя кол-во отправленных сообщений для процессов Writer и кол-во
полученных сообщений Reader (общее количество отправленных и принятых сообщений должно
совпадать);
4. запускает заданное количество процессов Reader и Writer;
5. принимает от каждого процесса Writer сообщения и выводит на консоль, затем отправляет сообщения
процессам Reader.
6. принимает от каждого процесса Reader и Writer сообщение о завершении сеанса и выводит его на
консоль в одной строке.
7. завершает свою работу.

Процесс __Writer__:
1. синхронизировать работу процессов Writer с помощью мьютексов
2. передачу сообщений реализовать с помощью событий
3. запрашивает с консоли сообщения, состоящее из “A” или “B”, и передает их (по одному) процессу
Administrator;
4. передает сообщение о завершении сеанса процессу Administrator;
5. завершает свою работу.

Процесс __Reader__:
1. синхронизировать работу процессов Reader с помощью семафора
2. передачу сообщений реализовать с помощью событий
3. принимает сообщения «C» , «D» от процесса Administrator;
4. выводит на консоль сообщения;
5. передает сообщение о завершении сеанса процессу Administrator;
6. завершает свою работу.
