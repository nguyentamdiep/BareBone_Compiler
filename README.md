# Bare Bone Programming Language

| Barebone command        | explain        |
|-------------------------|----------------|
| init X 5                | X:=5           |
| in X                    | cin>>X         |
| out X                   | cout<<X        |
| clear X                 | X:=0           |
| incr X                  | X:=X+1         |
| decr X                  | X:=X-1         |
|                         |                |
|while X not 0 do         |while X not 0 do|       
|   ...                   |  decr X        |        
|end	                    |end	  	       |        
|   			                |	               |	                 
|//                       |//comment       |    

# For Windows

```
git clone https://github.com/nguyentamdiep/BareBone_Compiler.git
cd BareBone_Compiler\forWindows
g++ bbc.cpp -o bbc
```
Open Edit environment variables for your account, add path ...\BareBone_Compiler\forWindows

example:

```
cd BareBone_Compiler\Examples
bbc example1.txt example1
.\example1
```
# For Ubuntu
```
apt-get update
apt-get install build-essential
cd BareBone_Compiler/forLinux
g++ bbc.cpp -o bbc
```

example:
```
cd BareBone_Compiler/Examples
.../BareBone_Compiler/forLinux/bbc example1.txt example1
./example1
```

# For GUI in Windows
```
cd cd BareBone_Compiler\forWindows
pip install tk
python main.py
```





