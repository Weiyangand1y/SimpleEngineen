用于用户最开始写的子类

写完后就main里面用了

如下：

```c++
class TestApplication : public Application{
	//......
}
int main(){
    system("cls");
    TestApplication app;
    app.init();
    app.run();
}
```

就算什么都不写都会有窗口出现

编写子类，在三个地方

成员变量，写在这里app哪里都能访问到了，如果成员变量太多，需要封装为类，防止成员变量太乱。

初始化函数

更新函数


当前还没有开放足够的配置接口，可以改改源码
