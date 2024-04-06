function add_sprite(key,px,py,s)
    local sp=Sprite2D.new()
    rigster(sp)
    sp:set_texture(key)
    sp:set_position(px,py)
    if(s)then
        sp:set_scale(s)
    end
    add_node(sp)
end

add_sprite("p1",-80.0,30.0)
add_sprite("Sugar_Kairo", -30.0,90.0, 1.0)
add_sprite("Sugar_Kairo",80.0,30.0)

-- add_tpn_node(-30,40)
add_tpn_node(-40,80)