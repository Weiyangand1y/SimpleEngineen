一个单例类，

当前通过lua进行配置，唯一硬编码是config.lua的路径，由此扩展到其他路径

接口很简单，如果不想要lua的话，可以通过硬编码改源码，

不过有一些必须配置的，像窗口的大小

如果后面有相对独立的Config用途，也可以用类似的写法，相对独立的不要写在全局Config

后面需要分离单例和一个小子类吗