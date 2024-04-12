add_sprite("p1",-80.0,30.0)
add_sprite("Sugar_Kairo", -30.0,90.0, 1.0)
add_sprite("Sugar_Kairo",80.0,30.0)

local sp=Sprite2D.new()
rigster(sp)
function f(info)
    print("hello")
    local t=get_info(info);
    print("...",t[1],t[2])
end
sp.signal:connect("hello",f)
sp.signal:emit("hello",make_info(100,"你好"))

add_tpn_node(-30,40)
add_tpn_node(-40,80)