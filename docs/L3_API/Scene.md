## [Scene]

in [[SceneTreeCore]]

### [Members]

#### - app

type: Application\*

这是通过信息的方法，因为当初设计时避免使用全局单例，就通过这个来传，也许Applicaton应该是单例比较好吧

#### - root_node

type: SceneNode*

根节点，一个场景至少有一个根节点吧

---

#### - default_viewport

type: Viewport*

frame buffer单元

#### - default_camera

type: Camera*

获取View Matrix和Projection Matrix的单元

### [Methods]

#### - Scene(Application* p_app)

构造方法，传入app变量

#### - make_enter_scene(SceneNode* scene_node)

因为节点需要一些跟场景有关的量进行初始化，所以需要这个函数，调用之后节点也会调用enter_scene方法

---

#### - add_to_root_node(SceneNod *scene_node)

封装的函数，因为很多时候测试直接添加到根节点即可

#### - add_free_node(SceneNode\*node)

将node添加到free队列中

#### - do_queue_free()

将free队列中的元素执行删除，先执行完所有节点的before_free()之后再执行delete

#### - run(float delta_time)

场景的process行为有很多，一行更不容易搞错吧

---

#### - T* create_scene_node(Args... args)

#### - T\* create_scene_node()

#### - void\* handle_requst(string what, void\* data)

也许在达成约定后强制类型转换为其子类更加合适

### [Examples]

#### - 常用开始使用

```cpp
class SubClassofApp : public Application{
	SubClassofScene* scene;
	void _init(){
        scene=new SubClassofScene(...);
		scene->init();
	}
    void _run(){
        scene->run(delta_time);
    }
}
```

#### - 子类

比较合适的是physicScene

#### -进行queue_free

scene node调用queue_free()，scene调用do_queue_free()

```c++
auto n1=scene->root_node->create_add_child<SceneNode>();
n1->connect_signal(so,"hello",[](const Info&){debug("***n1\n")});

auto n2=scene->root_node->create_add_child<SceneNode>();
n2->connect_signal(so,"hello",[](const Info&){debug("***n2\n")});

auto n3=scene->root_node->create_add_child<SceneNode>();
n3->connect_signal(so,"hello",[](const Info&){debug("***n3\n")});

auto n4=n1->create_add_child<SceneNode>();
n4->connect_signal(so,"hello",[](const Info&){debug("***n4\n")});

so.emit("hello");


n1->queue_free();
scene->do_queue_free();

debug("---after free\n");
so.emit("hello");
```

