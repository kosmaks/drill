Drill
=====

Задание
-------

Разработать программу, реализующую цветное движущееся изображение.
Изображение задается преподавателем.
Сверление отверстия. Толщина материала, толщина сверла и скорость его вращения задаются пользователем.

Пример работы
-------------

![alt tag](https://github.com/kosmaks/drill/blob/master/screenshot.png?raw=true)

Как собрать и запустить
-----------------------

Необходимо: 
* OpenGL 4.1+
* DirectX 11 (для Windows)
* gcc (для OSX)
* cl.exe (для Windows)
* glfw, glew, glm
* GNU utils (для Windows тоже :)

OSX:

```bash
$ mkdir dist
$ make
```

Windows:

```bash
> mkdir dist
> make windows
> make gl # чтобы запустить opengl версию
> make dx # чтобы запустить directx версию
```
