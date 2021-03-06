Перед тем как начать создавать проекты описания **AdHoc** протокола, необходимо:

- установить **[JDK 8](https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)** и убедитесь, что
 `javac` (компилятор java) находится в PATH и доступен из консоли.
- установить любую **JAVA** IDE (**[Intellij IDEA](https://www.jetbrains.com/idea/download/)** - отличный выбор)
- загрузить [аннотации AdHoс протокола](https://github.com/cheblin/AdHoc-protocol/tree/master/org/unirail/AdHoc).
    Всем проектам описания AdHoc протокола потребуется ссылка на эти аннотации, точнее на папку, в которой находится `org` - 
корневая папка аннотаций. Поскольку аннотации даны в исходниках, в **ИДЕЯ** их добавляют в проект 
[как дополнительные исходники](https://www.jetbrains.com/help/idea/content-roots.html).
- Чтобы отправить файл с описанием AdHoc протокола на сервер, для генерации там исходного кода / тестирования и получения результата, 
потребуется утилита **[AdHocAgent](https://github.com/cheblin/AdHocAgent)**.  
Скачайте [скомпилированный jar](https://github.com/cheblin/AdHocAgent/tree/master/bin) либо скомпилируйте самостоятельно из предоставленных исходников.

Открыв среду разработки необходимо придумать название и [создать новый **JAVA**
проект](https://www.jetbrains.com/help/idea/creating-and-running-your-first-java-application.html). Определившись c пространством имен, создадим в
папке исходников проекта соответствующую иерархию. Затем, в этой иерархии, в кодировке
**UTF8** создадим обычный java файл с информативным названием проекта.

Предположим пространство имен будет **org.company.namespace,** а проект
**MyDemoProject**

![image](https://user-images.githubusercontent.com/29354319/72199746-25eafb80-347b-11ea-9e45-e8f8ca8bc2dd.png)

Это были первые **обязательные** элементы файла описания протокола **AdHoc**.

Теперь можно начинать описывать участников информационного обмена. В **AdHoc** это делается **JAVA** конструкцией `class` в теле интерфейса проекта.
Создадим двоих участников с оригинальными названиями `Server` и `Client`.

![image](https://user-images.githubusercontent.com/29354319/72199784-91cd6400-347b-11ea-8262-5d709f030d89.png)


Далее опишем на каких языках будут сгенерированы исходники для `Server` и `Client`.  
Допустим мы хотим чтобы код для `Server` был сгенерирован на трех языках, на **С\#** , **С++** и **C,**   
а для `Client` на **Rust, Kotlin** и **Typescript** для работе в web браузере.

Языковые конфигурации кодогенератору, задаются с помощью интерфейсов, которые необходимо [подключить в проект](https://www.jetbrains.com/help/idea/content-roots.html) и
импортировать конструкцией `import org.unirail.AdHoc.\*;`

Требуемые языки кодогенерации перечисляются через запятую после `implements` узла

![image](https://user-images.githubusercontent.com/29354319/72199865-38663480-347d-11ea-87e2-e0ae9c774426.png)


Каждый узел содержит в себе набор интерфейсов, через которые он взаимодействует с другими узлами
 
Интерфейсы узлов описываются в теле узла, **JAVA** конструкцией **interface.**
Узел может содержать неограниченное число интерфейсов. Интерфейсы в свою
очередь, конструкцией **extends** могут неограниченно наследовать пакеты от других интерфейсов

![image](https://user-images.githubusercontent.com/29354319/72199918-c3dfc580-347d-11ea-8a20-3cdb9049d55f.png)


 
 Каждый интерфейс в свою очередь, с помощью вложенных в него **JAVA** конструкции **class**
 описывает какие пакеты через этот интерфейс узел будет способен **получить и
 обработать**. Не отправлять(!), а именно, и только, получать

 Для примера, добавим узлу `Server` возможность **получать** через созданный интерфейсе **ToMyClients**, пустой пакет `FirstPack`.

![image](https://user-images.githubusercontent.com/29354319/72199950-2a64e380-347e-11ea-8d19-4ebd7b4ba523.png)

`FirstPack` пакет, по сути пуст, кроме своего ID, не содержит в себе никакой информации, но этого достаточно. 
Информацией будет является сам факт получения этого пакета. Такие пакеты используются когда необходимо послать
некоторую информацию/сигнал с минимальным трафиком.

На узле `Client` пока ничего неизвестно о возможностях узла `Server`
принимать какие либо пакеты на интерфейсе **ToMyClients**. Для завершения
конфигурирования, кодогенератору необходимо сообщить какими интерфейсами
взаимодействуют узлы `Client` и `Server`

Для соединения интерфейсов, в **AdHoc** используются компоненты **Channels**,
которые могут описать два типа подключения

-   **StdProtocol** простой, базовый вариант предназначен для передачи по
    надежным каналам, либо для сохранения информации в файл

-   **AdvProtocol** содержит в себе механизм быстрого восстановления после сбоя от
    помех, подсчёт контрольной суммы и предназначен для работы по ненадежным, зашумленным
    радиоканалам / UART.

Соединим интерфейс **Server.ToMyClients** с интерфейсом **Client.ToServer**
каналом с именем **ClientServerLink** и пусть этот канал будет с **AdvProtocol**
в итоге получаем следующее описание протокола.

![image](https://user-images.githubusercontent.com/29354319/72200011-0eae0d00-347f-11ea-98e1-7a0204677f11.png)

Выглядит понятно и логично, однако, именно как JAVA программа - совершенно бесполезно. 

Теперь эту спецификацию необходимо отправить на сервер
кодогенерации. Это делается с помощью утилиты **[AdHocAgent](https://github.com/cheblin/AdHocAgent)**

Данная прогарамма способна, в зависимости от текущих требований, использовать  **TCP** либо **HTTP** ( если вынуждены
работать через proxy). Подробное описание работы утилиты можно найти по ссылке. Стоит упомянуть, что помимо кодогенерации 
утилита позволяет запрашивать в дополнение тестирование сгенерированного.
Запрос на тестирование, осуществляется добавлением в конце пути к спецификации протокола знака **!**.

>   С момента отправки файла спецификации на обработку и до получения
>   сгенерированных по нему исходников, файла спецификации будет заблокирован
>   для измерений.
>   Если блокировка в это время будет снята, **AdHocAgent** потеряет связь с уже
>   отправленной версией и не сможет получить на её ответ.

Полученный результат кодогенерации на сервере, **AdHocAgent** выгрузит **в текущую рабочую директорию** своего процесса

При попытке отправить обсуждаемую тестовую спецификацию, будет получена ошибка.

>   **WARNING: Package \< org.company.namespace.Client\$ToServer \> name component\< namespace \> is prohibited**  
>   **WARNING: Prohibited names detected**

Дело в том, что перед отправкой спецификации на сервер **AdHocAgent** проверяет использованные в
описании протокола имена.

Имена пакетов, их полей, каналов, констант и проч. не должны
начинаться либо заканчиваться подчеркиванием `_` и не должны совпадать с
зарезервированными словами **ВСЕХ** языков программирования, на которых способен
генерировать **AdHoc**. Таких слов более двух сотен. И если с зарезервированными
в **JAVA** словами все просто, **JAVA** IDE недопустит их использования, то проверка по остальными
языкам производится непосредственно утилитой **[AdHocAgent](https://github.com/cheblin/AdHocAgent)**.

Исправляем компонент пространства имён спецификации, меняем **org.company.namespace** на
**org.company.some_namespace**

![image](https://user-images.githubusercontent.com/29354319/72200031-516fe500-347f-11ea-9bda-9381bdd49154.png)

Перезапускаем **AdHocAgent**, и, через короткое время, получаем [сгенерированные сервером
исходники](https://github.com/cheblin/AdHocLessons/tree/master/1/GeneratedCode) в **рабочей/текущей папке** отработавшего **AdHocAgent** процесса.
Обычно языки С и С++ используют одинаковые статические библиотеки. Но если пакеты генерируемого на С кода не используют строк и 
прочих динамических массивов, то в этом случае для С используется оптимизированная библиотека. В результате получается очень компактный 
бинарник способный уместиться и работать даже на восьмибитных микроконтроллерах типа STM8. 

**[Файл спецификации](https://github.com/cheblin/AdHocLessons/blob/master/1/MyDemoProject.java)** также был изменён **сервером**. И теперь она выглядит так:

![image](https://user-images.githubusercontent.com/29354319/72133085-8f0b3a00-33bb-11ea-9572-e83807ed5354.png)

У `FirstPack` появился уникальный идентификатор, по которому будет определяться тип пакета.  
Всем пакетам, у которых нет уникального идентификатора, сервер назначает их автоматически.
И рядом с файлом спецификации появился бэкап предыдущей версии спецификации.
 
 Примерная схема получившейся конфигурации выглядит так
 
![image](https://user-images.githubusercontent.com/29354319/72135002-65a0dd00-33c0-11ea-806a-8d863cb794ad.png)

Неподсоединённые интерфейсы кодогенератором игнорируются.

При данной конфигурации на сервере для `FirstPack` будет сгенерирован исключительно код получения.  
А на `Client` только код создания пакета и отправки.

