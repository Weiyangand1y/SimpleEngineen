## [SceneNode]

### [Members]

有很多private和protect成员

#### - signal

type: SignalObject

有了信号，很多东西都方便了起来

### [Methods]

这里有大量的虚函数，如果要重写的话不要忘了父类的

#### virtual enter_scene(Scene* scene)

在scene调用make_enter_scene

- SceneNode的话把scene指针放到成员

- DrawableNode则是把renderer和drawer放到其成员

- PhysicNode获取body指针

#### virtual add_child(SceneNode* node)

SceneNode传递viewport指针

#### set_viewport(Viewport* p_viewport)

设置viewport指针

#### virtual before_free()

SceneNode解除记录中的信号连接

#### queue_free()

把自己的指针添加到scene的free队列中

#### get_all_children(vector<SceneNode*>& result)

递归，把传入的result引用push

#### make_signal_record(SignalObject& so, string name, int id)

与这个节点有关的信号要记录在这个节点中，释放的时候自动断开连接

#### connect_signal(SignalObject& so, string signal_name, Callback func)

上一个函数的封装版

#### T* create_add_child(Args... args)

#### T* create_add_child()

和上面一个函数是简化代码的

### [Examples]

#### 创建和初始化

其实不算简单，有几个难点：可以设置的参数很多，如果要写的话有以下几种：

create->set1->set2->finish init

create->put a struct data->finish init

create and init->set

我们比较喜欢最后一种，但并不是都是那么优雅的，以最后一种为目标吧

```c++
auto* ground=create_add_child<PhysicNode>(sx,sy);
ground->set_transform(px,py,angle);
ground->set_body_type(PhysicNode::BodyType::STATIC);
```

因为physicNode重新设置形状有些麻烦，所以会出现构造函数就要把形状确定下来的情况。但是后面总是要添加change shape方法的。

#### 添加子节点

add_child

#### free，no delete

观察者模式的一个难点是hanging pointer，访问了一些奇怪的地址就出现段错误吧。
