
# Table of Contents

1.  [Simple Docker](#org53f3f14)
    1.  [Часть 1. Готовый docker](#org06b6a38)
    2.  [Часть 2. Операции с контейнером](#org2833c5b)
    3.  [Часть 3. Мини веб-сервер](#org7572688)


<a id="org53f3f14"></a>

# Simple Docker


<a id="org06b6a38"></a>

## Часть 1. Готовый docker

![img](./images/1_1.png)

Скачивание docker-образа nginx

![img](./images/1_2.png)

Docker-образ nginx

![img](./images/1_3.png)

Запуск docker-образа nginx

![img](./images/1_4.png)

Результат команды docker ps

![img](./images/1_5.png)

Информация о контейнере с помощью команды docker inspect nginx

![img](./images/1_6.png)

Размер контейнера

![img](./images/1_7.png)

Вывод порта и IP адреса контейнера

![img](./images/1_8.png)

Остановка контейнера

![img](./images/1_9.png)

Запуск nginx на локальной машине

![img](./images/1_10.png)

Стартовая страница nginx


<a id="org2833c5b"></a>

## Часть 2. Операции с контейнером

![img](./images/2_1.png)

Доступ в контейнер с помощью команды docker exec

![img](./images/2_2.png)

Файл nginx.conf в контейнере

![img](./images/2_3.png)

Файл nginx.conf на локальной машине

![img](./images/2_4.png)

Копирование файла nginx.conf с локальной машины в контейнер

![img](./images/2_5.png)

Перезапуск nginx в контейнере

![img](./images/2_6.png)

Страница localhost:80 на локальной машине

![img](./images/2_7.png)

Страница localhost:80/status на локальной машине

![img](./images/2_8.png)

Сохранение контейнера с помощью docker export

![img](./images/2_9.png)

Остановка контейнера

![img](./images/2_10.png)

Удаление образа nginx

![img](./images/2_11.png)

Удаление остановленного контейнера

![img](./images/2_12.png)

Добавление образа с помощью docker import

![img](./images/2_13.png)

Запуск контейнера my_nginx

![img](./images/2_14.png)

Страница localhost:80

![img](./images/2_15.png)

Страница localhost:80/status


<a id="org7572688"></a>

## Часть 3. Мини веб-сервер

![img](./images/3_1.png)

Код hello_fcgi.c

![img](./images/3_2.png)

Создание процесса с помощью spawn-fcgi

![img](./images/3_3.png)

Конфигурация nginx.conf для проксирования fcgi-запросов

![img](./images/3_4.png)

Страница по адресу localhost:81

