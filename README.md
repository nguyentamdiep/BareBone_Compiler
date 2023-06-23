# Bare Bone Programming Language

init <variable> <value>  | init X 5     | X:=5
-------------------------------------------------
in <variable>            | in X         | cin>>X
-------------------------------------------------
out <variable>           | out X        | cout<<X
-------------------------------------------------
clear <variable>         | clear X      | X:=0
-------------------------------------------------
incr <variable>          | incr X       | X:=X+1
-------------------------------------------------
decr <variable>          | decr X       | X:=X-1
-------------------------------------------------
while <variable> not     |while X not 0 |
<value> do               |do            |
	...					 |  decr X      |
end						 |end           |
-------------------------------------------------
//                       |//comment     |
