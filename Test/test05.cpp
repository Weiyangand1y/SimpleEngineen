#include "L1/Debug/Log.h"
#include "L1/Object/SignalObject.h"
int main(){
    SignalObject so;
    int id1=so.connect("a",[](Info i){
        debug("a1\n");
    });
    int id2=so.connect("a",[](Info i){
        debug("a2\n");
    });
    so.emit("a");
    so.disconnect("a",id1);
    debug("after disconnect a1\n")
    so.emit("a");

    int id3=so.connect("a",[](Info i){
        debug("a3\n");
    });

    so.disconnect("a",id2);
    debug("after disconnect a2\n")
    so.emit("a");

    
    so.emit("a");
    debug("->{}",id3)
}