add_sprite=function(key,px,py,s)
    local sp=Sprite2D.new()
    rigster(sp)
    sp:set_texture(key)
    sp:set_position(px,py)
    if(s)then
        sp:set_scale(s)
    end
    add_node(sp)
end