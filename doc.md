## Scene

A environment to run nodes, build scene-tree.

### Roles

Manage Scene, run, provide app envirenment to nodes.

### API

#### `make_enter_scene`

This method is used to allow a node to access certain resources such as a renderer or a physics node. It is designed to facilitate the interaction between different nodes and the scene itself.

Usage:

```c++
scene.make_enter_scene( node )
```

#### `run`

This method should be placed within a loop for continuous execution. It is responsible for the main execution flow of the scene.

Usage:

```c++
scene.run()
```

## SceneNode

The `SceneNode` class represents a node within a scene. It is used to facilitate interactions between the scene and its nodes.

### Methods

#### `enter_scene`

This method allows a node to access the pointer of a scene. This can be used to access a renderer or perform other tasks. It is also used to perform initialization tasks such as creating a world for a `PhysicalNode` or getting a `Drawer` for a `DrawableNode`.

Usage:

```c++
scene.make_enter_scene(node)
```

In the initial stages, creating and initializing a `SceneNode`, adding it to a node, setting a viewport, and other tasks required writing many lines of code. This made the code look cluttered and difficult to manage. To address this issue, the following methods were introduced:

#### `create_from_scene`

This method simplifies the process of creating a `SceneNode` from a scene.

Usage:

```c++
scene.make_enter_scene(node)
```

#### `create_add_node`

This method simplifies the process of adding a `SceneNode` to a node.

Usage:

```c++
scene.make_enter_scene(node)
```

These methods help in making the code cleaner and more manageable.
