基础，主要为了封装OpenGL的接口，使用该内容，可以用较短的代码量建立程序，并用Drawer进行绘制。

但是，不是完全没有冗余的，比如Debug、ScriptObject功能，放在L2及以上是不太合适的，但是如果不想要的话也很容易删除。L1的结构比较好理解，大部分都是相对独立的。

从整体上，有3个主要的：封装OpenGL，常用Object，应用层封装。

封装OpenGL，意味着在/Lib/OpenGL之外几乎不用再使用glXXX函数了，要用也是一些clear等简单的函数。


常用Object，分为Node, SignalObject, ScriptObject，其中SignalObject用得最多，Node在L3是基础，ScriptObject好像就只是封装，也许未来Lua绑定的话会重写。

应用层，分为Application，Window，Config，用于快速创建应用、获取事件的封装、集中获取设置数据。

Debug，用于调试。fmt的颜色非常好用。分为Log，测量时间，GL的check error。

资源加载，文本和图片在L1，3D模型在L3.5
