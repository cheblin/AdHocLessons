Для того чтобы начать создавать проекты описания протокола **AdHoc**, необходимо:

-   установить [JDK
    8](https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html),
    прописать в PATH необходимые пути на java компилятор **javac** так, чтобы он
    был доступен из консоли.

-   установить редактор **JAVA** кода (**[Intellij IDEA](https://www.jetbrains.com/idea/download/)** - идеально)

-   скачать [набор AdHoc
    аннотаций](https://github.com/cheblin/AdHoc-protocol/tree/master/org/unirail/AdHoc).
    Всем проектам описания **AdHoc** протокола будет необходима ссылка на эти
    аннотации, точнее на папку, в которой находится `org` - корневая папка аннотаций.
    Поскольку аннотации представлены в исходниках, в IDEA, в модуль проекта
    необходимо добавлять их через [Add Content
    Root](https://www.jetbrains.com/help/idea/content-roots.html) .

-   для отправки готового описания протокола на сервер генерации исходников и
    получения результата, необходима утилита
    [AdHocAgent](https://github.com/cheblin/AdHocAgent)**.** Скачайте [готовый
    jar](https://github.com/cheblin/AdHocAgent/tree/master/bin) либо
    скомпилируйте утилиту самостоятельно.
