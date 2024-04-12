## [Node2D]

因为频繁修改，需要重构的类

### [Members]

#### who_to_follow

Node2D\*

#### m_relative_pos

vec2 

#### m_position

 vec2 

#### m_scale

 vec2 

#### m_size

 vec2 

#### m_rotation

 float //radians

### [Methods]

####   Node2D()

####   mat4 get_transform()

####   mat4 get_transform2()

####   set_position(float x,float y)

####   set_position_and_angle(float x,float y,float angle)

####   set_scale(float x,float y)

####   set_scale(float s)

####   set_who_to_follow(Node2D* p_to_follow)

####   _process(float delta)override

