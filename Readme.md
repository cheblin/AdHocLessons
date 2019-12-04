To start creating **AdHoc** protocol description projects, you need to:

-   install **[JDK
    8](https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)** and
    ensure that `javac` (java compiler) is in PATH and accessible from the
    console.

-   install any **JAVA** IDE (**[Intellij IDEA](https://www.jetbrains.com/idea/download/)** – just fine)

-   download [AdHoс protocol annotations](https://github.com/cheblin/AdHoc-protocol/tree/master/org/unirail/AdHoc).
    All AdHoc protocol description projects will need a reference to these
    annotations, precisely to the folder where the `org` - the annotations root
    folder is located. Since annotations are referenced as sources, in **IDEA**, you
    have to add them to the project in this way [Add Content
    Root](https://www.jetbrains.com/help/idea/content-roots.html).

-   To send completed protocol description file to the server (to generate of
    AdHoc protocol handler source code) and receive the result, you will need the
    **[AdHocAgent](https://github.com/cheblin/AdHocAgent)** utility. Please download
    the [precompiled jar](https://github.com/cheblin/AdHocAgent/tree/master/bin)
    or compile the utility from provided source by yourself.
